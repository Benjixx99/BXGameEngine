#include "../../Headerfiles/Scene/SceneMenu.hpp"
#include "../../Headerfiles/Scene/ScenePlay.hpp"
#include "../../Headerfiles/Common/Paths.hpp"
#include "../../Headerfiles/Data/Files/ReadIn.hpp"
#include "../../Headerfiles/PAM/Physics.hpp"

#include <fstream>

bx::SceneMenu::SceneMenu(GameEngine* gameEngine, const std::string& menuConfigFile) : Scene(gameEngine) {
	std::ifstream file(Paths::menuConfigFiles + menuConfigFile);
	ReadIn::menuData(file, config);
	init();
}

void bx::SceneMenu::init() {
	registerAction(sf::Keyboard::W, ActionName::Up);
	registerAction(sf::Keyboard::S, ActionName::Down);
	registerAction(sf::Keyboard::D, ActionName::Action);
	registerAction(sf::Keyboard::Escape, ActionName::Quit);
	menuText.setFont(game->getAssets().getFont(config.fontName));
}

void bx::SceneMenu::sRender() {
	uint yPosition = config.headerSpaceFromTop + config.menuItemSpaceFromHeader, index = 0;
	const Vector2 mousePosition = sf::Mouse::getPosition(game->getWindow());

	setWindowsProperties();
	setHeaderProperties();
	game->getWindow().draw(menuText);
	
	for (const auto& text : config.menuItemTexts) {
		setMenuItemProperties(yPosition, text);

		if (Physics::isInside(menuText.getGlobalBounds(), mousePosition) || index == selectedMenuIndex) {
			setSelectedMenuItemProperties();
			selectedMenuIndex = index;
		} 
		yPosition += config.spaceBetweenMenuItems;
		++index;
		game->getWindow().draw(menuText);
	}
	setFooterProperties();
	game->getWindow().draw(menuText);
	game->getWindow().display();
}

void bx::SceneMenu::onEnd() {
	game->quit();
}

void bx::SceneMenu::doAction(const bx::Action& action) {
	if (action.getType() == ActionType::Start) {

		if (action.getName() == ActionName::Up) {
			if (selectedMenuIndex > 0) { selectedMenuIndex--; }
			else { selectedMenuIndex = config.menuItemTexts.size() - 1; }
		}
		else if (action.getName() == ActionName::Down) {
			selectedMenuIndex = (selectedMenuIndex + 1) % config.menuItemTexts.size();
		}
		else if (action.getName() == ActionName::Action) {
			selectAction();
		}
		else if (action.getName() == ActionName::Quit) {
			onEnd();
		}
		else if (action.getName() == ActionName::LeftClick) {
			selectAction();
		}
	}
}

void bx::SceneMenu::selectAction() {
	switch (selectedMenuIndex)
	{
	case 0: std::cout << "Continue\n"; break;
	case 1: std::cout << "Load Game\n"; break;
	case 2: std::cout << "New Game\n"; break;
	case 3: std::cout << "Levels\n"; break;
	case 4: std::cout << "Settings\n"; break;
	case 5: onEnd(); break;
	case 6: game->changeScene("TestLevel", std::make_shared<ScenePlay>(game, "Levels/TestLevel"));		break;
	default:
		break;
	}
}


void bx::SceneMenu::setHeaderProperties() {
	menuText.setPosition(config.headerSpaceFromLeft, config.headerSpaceFromTop);
	menuText.setFillColor(config.colors[ColorType::HeaderFont]);
	menuText.setOutlineColor(config.colors[ColorType::HeaderOutline]);
	menuText.setOutlineThickness(config.headerOutlineThickness);
	menuText.setCharacterSize(config.headerFontSize);
	menuText.setString(config.headerText);
}

void bx::SceneMenu::setSelectedMenuItemProperties() {
	menuText.setFillColor(config.colors[ColorType::SelectedMenuItemFont]);
	menuText.setOutlineColor(config.colors[ColorType::SelectedMenuItemOutline]);
}

void bx::SceneMenu::setMenuItemProperties(const uint yPosition, const std::string& text) {
	menuText.setPosition(config.menuItemSpaceFromLeft, yPosition);
	menuText.setFillColor(config.colors[ColorType::MenuItemFont]);
	menuText.setOutlineColor(config.colors[ColorType::MenuItemOutline]);
	menuText.setOutlineThickness(config.menuItemOutlineThickness);
	menuText.setCharacterSize(config.menuItemFontSize);
	menuText.setString(text);
}

void bx::SceneMenu::setFooterProperties() {
	menuText.setPosition(config.footerSpaceFromLeft, game->getWindow().getSize().y - config.footerSpaceFromBottom);
	menuText.setFillColor(config.colors[ColorType::FooterFont]);
	menuText.setOutlineColor(config.colors[ColorType::FooterOutline]);
	menuText.setOutlineThickness(config.footerOutlineThickness);
	menuText.setCharacterSize(config.footerFontSize);
	menuText.setString(config.footerText);
}

void bx::SceneMenu::setWindowsProperties() {
	game->getWindow().setView(sf::View(game->getWindow().getDefaultView()));
	game->getWindow().clear(config.colors[ColorType::Background]);
}

void bx::SceneMenu::update() {
	sRender();
}