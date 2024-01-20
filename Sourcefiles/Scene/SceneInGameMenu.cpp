#include "../../Headerfiles/Scene/SceneInGameMenu.hpp"

bx::SceneInGameMenu::SceneInGameMenu(GameEngine* gameEngine, const std::string& menuConfigFile)
	: SceneMenu(gameEngine, menuConfigFile) {}

void bx::SceneInGameMenu::selectAction() {
	switch (selectedMenuIndex)
	{
	case 0: std::cout << "Resume Game\n"; game->changeScene("TestLevel", nullptr); break;
	case 1: std::cout << "Save Game\n"; break;
	case 2: std::cout << "Load Game\n"; break;
	case 3: std::cout << "Settings\n"; break;
	case 4:
		EntityMemoryPool::Instance().setBack();
		game->changeScene("MENU", nullptr, hasEnded = true);
		break;
	case 5: onEnd(); break;
	default:
		break;
	}
}