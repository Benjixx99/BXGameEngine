#pragma once

#include "SceneMenu.hpp"

namespace bx {

	class SceneInGameMenu : public SceneMenu {
		std::shared_ptr<ScenePlay> scene;
	public:
		SceneInGameMenu(GameEngine* gameEngine, const std::string& menuConfigFile);
		void selectAction() override;
	};
}