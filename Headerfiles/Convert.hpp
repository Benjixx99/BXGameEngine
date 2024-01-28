#pragma once

#include <string>
#include <SFML/Window/Keyboard.hpp>

#include "Action.hpp"

namespace bx {

	namespace Convert {
		std::string keyValueToString(const sf::Keyboard::Key keyValue);
		sf::Keyboard::Key stringToKeyValue(const std::string& value);

		std::string actionNameValueToString(const ActionName actionName);
		ActionName stringToActionNameValue(const std::string& value);
	}
}