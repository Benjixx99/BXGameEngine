#pragma once

#include <SFML/Graphics/Text.hpp>
#include "../Common/CompositeDataTypes.hpp"
#include "../Common/PrimitiveDatatypes.hpp"

namespace bx {

	enum ColorType : uchar {
		Background,
		HeaderFont,
		HeaderOutline,
		MenuItemFont,
		MenuItemOutline,
		SelectedMenuItemFont,
		SelectedMenuItemOutline,
		FooterFont,
		FooterOutline,
		LAST
	};

	class MenuConfigData {
	public:
		std::string headerText = "None";
		std::string footerText = "None";
		std::string fontName = "None";
		VectorString menuItemTexts;
		std::vector<sf::Color> colors;
		
		int	headerSpaceFromTop = 25;
		int headerSpaceFromLeft = 50;
		int	menuItemSpaceFromHeader = 180;
		int menuItemSpaceFromLeft = 50;
		int	spaceBetweenMenuItems = 100;
		int	footerSpaceFromBottom = 100;
		int	footerSpaceFromLeft = 50;

		int headerFontSize = 80;
		int headerOutlineThickness = 0;
		int menuItemFontSize = 50;
		int menuItemOutlineThickness = 0;
		int footerFontSize = 50;
		int footerOutlineThickness = 0;

		MenuConfigData() { colors.resize(static_cast<int>(ColorType::LAST)); }
	};
}