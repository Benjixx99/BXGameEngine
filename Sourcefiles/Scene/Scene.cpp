#include "../../Headerfiles/Scene/Scene.hpp"

bx::Scene::Scene() {}

bx::Scene::Scene(GameEngine* gameEngine) 
	: game (gameEngine) {}

void bx::Scene::setPaused(bool pause) {
	paused = pause;
}

void bx::Scene::registerAction(int inputKey, const ActionName name) {
	actionMap[inputKey] = name;
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

