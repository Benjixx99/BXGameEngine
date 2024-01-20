#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

#include "Scene/Scene.hpp"
#include "Assets.hpp"
#include "DatabaseManager.hpp"
#include "SharedDataStructure.hpp"

namespace bx {

	class Scene;

	class GameEngine {
		using SceneMap = std::map<std::string, std::shared_ptr<Scene>>;

		GameType gameType;
		SceneMap sceneMap;
		sf::RenderWindow window;
		Assets assets;

		std::string currentSceneName;
		bool running = true;

		EditorSharedData editorData;
		ShellSharedData shellData;

		void init();
		void initAssets();
		void initShell();
		void openEditor();

		void userInput();
		std::shared_ptr<Scene> currentScene();
	public:
		GameEngine(GameType gameType);

		void run();
		void quit();
		void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false);
		Assets& getAssets();
		sf::RenderWindow& getWindow();
		GameType getGameType();
		bool isRunning();

		ShellSharedData& shellSharedData();
		EditorSharedData& editorSharedData();
	};
}