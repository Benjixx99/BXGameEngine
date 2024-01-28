#include "../Headerfiles/GameEngine.hpp"
#include "../Headerfiles/Scene/SceneMenu.hpp"
#include "../Headerfiles/Common/Paths.hpp"
#include "../Headerfiles/DatabaseFunctions.hpp"
#include "../Headerfiles/Load/LoadAssets.hpp"

#include "../Headerfiles/Tools/Editor/Editor.hpp"
#include "../Headerfiles/Tools/Shell.hpp"

#include <iostream>
#include <fstream>
#include <thread>

bx::GameEngine::GameEngine(GameType gameType) : gameType (gameType) {
	init();
}

void bx::GameEngine::init() {
	initAssets();
	initShell();
	changeScene("MENU", std::make_shared<SceneMenu>(this, "/StartMenuConfig.txt"));
}

void bx::GameEngine::initAssets() {
	LoadAssets::all(assets, DatabaseFunctions::createDatabase(DatabaseManager(Paths::databases + "/AssetsDatabase.db"), DatabaseType::Assets));
}

void bx::GameEngine::initShell() {
	bool startShell = false;
	std::ifstream file(Paths::configFiles + "/shellConfig.txt");
	file >> startShell;
	if (!startShell) { return; }

	std::thread shellThread([this]() {
		Shell shell(shellData);
		shell.run();	
	});
	shellThread.detach();
}

void bx::GameEngine::openEditor() {
	static Editor* editorPointer = nullptr;

	if (editorData.state == EditorState::None) {
		editorData.state = EditorState::Open;

		std::thread editorThread([this]() {
			int argc = 0;
			QApplication app(argc, nullptr);
			Editor editor(editorData);
			editorPointer = &editor;
			editor.show();
			app.exec();
			});
		editorThread.detach();
	}
	else if (editorData.state == EditorState::Hidden) {
		editorData.state = EditorState::Open;
		QEvent* show = new QEvent(QEvent::Show);
		QCoreApplication::postEvent(editorPointer, show);
	}
}

void bx::GameEngine::userInput() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
			if (currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end()) { continue; }
			const ActionType actionType = (event.type == sf::Event::KeyPressed) ? ActionType::Start : ActionType::End;
			currentScene()->doAction(Action(currentScene()->getActionMap().at(event.key.code), actionType));
		}

		if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) {
			const ActionType actionType = (event.type == sf::Event::MouseButtonPressed) ? ActionType::Start : ActionType::End;
			ActionName actionName = ActionName::NONE;
			
			if (event.mouseButton.button == sf::Mouse::Left) { actionName = ActionName::LeftClick; }
			if (event.mouseButton.button == sf::Mouse::Middle) { actionName = ActionName::MiddleClick; }
			if (event.mouseButton.button == sf::Mouse::Right) { actionName = ActionName::RightClick; }

			currentScene()->doAction(Action(actionName, actionType, sf::Vector2i(sf::Mouse::getPosition(window))));
		}

		if (event.type == sf::Event::MouseMoved) {
			currentScene()->doAction(Action(ActionName::MouseMove, ActionType::Start, sf::Vector2i(sf::Mouse::getPosition(window))));
		}
	}
}

std::shared_ptr<bx::Scene> bx::GameEngine::currentScene() {
	return sceneMap[currentSceneName];
}

void bx::GameEngine::run() {
	window.create(sf::VideoMode(2048, 1536), "BXGame Engine"); // sf::Style::None
	window.setFramerateLimit(80);

	// Main loop
	while (window.isOpen()) {
		userInput();
		currentScene()->update();

		if (shellData.openEditor && !(shellData.openEditor = false)) {
			openEditor();
		}
	}
}

void bx::GameEngine::quit() {
	running = false;
	window.close();	
}

void bx::GameEngine::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene) {
	if (scene != nullptr)	{ sceneMap[sceneName] = scene; }
	if (endCurrentScene)	{ sceneMap[currentSceneName] = nullptr; }
	currentSceneName = sceneName;
}


bx::Assets& bx::GameEngine::getAssets() {
	return assets;
}

sf::RenderWindow& bx::GameEngine::getWindow() {
	return window;
}

bx::GameType bx::GameEngine::getGameType() {
	return gameType;
}

bool bx::GameEngine::isRunning() {
	return running;
}

bx::ShellSharedData& bx::GameEngine::shellSharedData() {
	return shellData;
}

bx::EditorSharedData& bx::GameEngine::editorSharedData() {
	return editorData;
}
