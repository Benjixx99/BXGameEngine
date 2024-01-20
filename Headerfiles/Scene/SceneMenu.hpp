#pragma once

#include "Scene.hpp"
#include "../Common/CompositeDataTypes.hpp"
#include "../Config/MenuConfig.hpp"

namespace bx {
	class ScenePlay;

	class SceneMenu : public Scene {
	protected:
		VectorString levelPaths;
		sf::Text menuText;
		size_t selectedMenuIndex = 0;

		MenuConfigData config;

		void init();
		void sRender();
		void onEnd();
		void doAction(const Action& action);
		virtual void selectAction();
		
		void setHeaderProperties();
		void setSelectedMenuItemProperties();
		void setMenuItemProperties(const uint yPosition, const std::string& text);
		void setFooterProperties();

		void setWindowsProperties();
	
	public:
		SceneMenu(GameEngine* gameEngine, const std::string& menuConfigFile);
		void update();
	};
}