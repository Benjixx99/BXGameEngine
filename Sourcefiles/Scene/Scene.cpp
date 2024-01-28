#include "../../Headerfiles/Scene/Scene.hpp"
#include "../../Headerfiles/Common/Paths.hpp"
#include "../../Headerfiles/Data/Files/ReadIn.hpp"
#include "../../Headerfiles/Convert.hpp"

bx::Scene::Scene() {}

bx::Scene::Scene(GameEngine* gameEngine) 
	: game (gameEngine) {}

void bx::Scene::setPaused(bool pause) {
	paused = pause;
}

void bx::Scene::registerAction(int inputKey, const ActionName name) {
	actionMap[inputKey] = name;
}

void bx::Scene::registerAllActions(const std::string& keyActionFile) {
	VectorStringPair keyActionPair;
	std::ifstream file(Paths::keyboardLayoutConfigFiles + keyActionFile);
	ReadIn::keyboardLayout(file, keyActionPair);

	for (const auto& pair : keyActionPair) {
		actionMap[Convert::stringToKeyValue(pair.first)] = Convert::stringToActionNameValue(pair.second);
	}
}

size_t bx::Scene::getCurrentFrame() const {
	return currentFrame;
}

bool bx::Scene::getHasEnded() const {
	return hasEnded;
}

const bx::Scene::ActionMap& bx::Scene::getActionMap() const {
	return actionMap;
}

