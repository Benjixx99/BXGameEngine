#include "../Headerfiles/Convert.hpp"

std::string bx::Convert::keyValueToString(const sf::Keyboard::Key keyValue) {
	
	switch (keyValue) {
	case sf::Keyboard::A: return "A";
	case sf::Keyboard::B: return "B";
	case sf::Keyboard::C: return "C";
	case sf::Keyboard::D: return "D";
	case sf::Keyboard::E: return "E";
	case sf::Keyboard::F: return "F";
	case sf::Keyboard::G: return "G";
	case sf::Keyboard::H: return "H";
	case sf::Keyboard::I: return "I";
	case sf::Keyboard::J: return "J";
	case sf::Keyboard::K: return "K";
	case sf::Keyboard::L: return "L";
	case sf::Keyboard::M: return "M";
	case sf::Keyboard::N: return "N";
	case sf::Keyboard::O: return "O";
	case sf::Keyboard::P: return "P";
	case sf::Keyboard::Q: return "Q";
	case sf::Keyboard::R: return "R";
	case sf::Keyboard::S: return "S";
	case sf::Keyboard::T: return "T";
	case sf::Keyboard::U: return "U";
	case sf::Keyboard::V: return "V";
	case sf::Keyboard::W: return "W";
	case sf::Keyboard::X: return "X";
	case sf::Keyboard::Y: return "Y";
	case sf::Keyboard::Z: return "Z";

	case sf::Keyboard::Num0: return "0";
	case sf::Keyboard::Num1: return "1";
	case sf::Keyboard::Num2: return "2";
	case sf::Keyboard::Num3: return "3";
	case sf::Keyboard::Num4: return "4";
	case sf::Keyboard::Num5: return "5";
	case sf::Keyboard::Num6: return "6";
	case sf::Keyboard::Num7: return "7";
	case sf::Keyboard::Num8: return "8";
	case sf::Keyboard::Num9: return "9";

	case sf::Keyboard::Escape: return "Esc";
	case sf::Keyboard::LControl: return "L-Crtl";
	case sf::Keyboard::LShift: return "L-Shift";
	case sf::Keyboard::LAlt: return "L-Alt";
	case sf::Keyboard::RControl: return "R-Crtl";
	case sf::Keyboard::RShift: return "R-Shift";
	case sf::Keyboard::RAlt: return "R-Alt";

	case sf::Keyboard::Space: return "Space";
	case sf::Keyboard::Enter: return "Enter";
	case sf::Keyboard::Backspace: return "Backspace";
	case sf::Keyboard::Tab: return "Tab";

	case sf::Keyboard::Left: return "Left-arrow";
	case sf::Keyboard::Right: return "Right-arrow";
	case sf::Keyboard::Up: return "Up-arrow";
	case sf::Keyboard::Down: return "Down-arrow";

	case sf::Keyboard::F1: return "F1";
	case sf::Keyboard::F2: return "F2";
	case sf::Keyboard::F3: return "F3";
	case sf::Keyboard::F4: return "F4";
	case sf::Keyboard::F5: return "F5";
	case sf::Keyboard::F6: return "F6";
	case sf::Keyboard::F7: return "F7";
	case sf::Keyboard::F8: return "F8";
	case sf::Keyboard::F9: return "F9";
	case sf::Keyboard::F10: return "F10";
	case sf::Keyboard::F11: return "F11";
	case sf::Keyboard::F12: return "F12";

	default: return "Key not supported!";
	}
}

sf::Keyboard::Key bx::Convert::stringToKeyValue(const std::string& value) {
	
	if (value == "A") { return sf::Keyboard::A; }
	else if (value == "B") { return sf::Keyboard::B; }
	else if (value == "C") { return sf::Keyboard::C; }
	else if (value == "D") { return sf::Keyboard::D; }
	else if (value == "E") { return sf::Keyboard::E; }
	else if (value == "F") { return sf::Keyboard::F; }
	else if (value == "G") { return sf::Keyboard::G; }
	else if (value == "H") { return sf::Keyboard::H; }
	else if (value == "I") { return sf::Keyboard::I; }
	else if (value == "J") { return sf::Keyboard::J; }
	else if (value == "K") { return sf::Keyboard::K; }
	else if (value == "L") { return sf::Keyboard::L; }
	else if (value == "M") { return sf::Keyboard::M; }
	else if (value == "N") { return sf::Keyboard::N; }
	else if (value == "O") { return sf::Keyboard::O; }
	else if (value == "P") { return sf::Keyboard::P; }
	else if (value == "Q") { return sf::Keyboard::Q; }
	else if (value == "R") { return sf::Keyboard::R; }
	else if (value == "S") { return sf::Keyboard::S; }
	else if (value == "T") { return sf::Keyboard::T; }
	else if (value == "U") { return sf::Keyboard::U; }
	else if (value == "V") { return sf::Keyboard::V; }
	else if (value == "W") { return sf::Keyboard::W; }
	else if (value == "X") { return sf::Keyboard::X; }
	else if (value == "Y") { return sf::Keyboard::Y; }
	else if (value == "Z") { return sf::Keyboard::Z; }

	else if (value == "0") { return sf::Keyboard::Num0; }
	else if (value == "1") { return sf::Keyboard::Num1; }
	else if (value == "2") { return sf::Keyboard::Num2; }
	else if (value == "3") { return sf::Keyboard::Num3; }
	else if (value == "4") { return sf::Keyboard::Num4; }
	else if (value == "5") { return sf::Keyboard::Num5; }
	else if (value == "6") { return sf::Keyboard::Num6; }
	else if (value == "7") { return sf::Keyboard::Num7; }
	else if (value == "8") { return sf::Keyboard::Num8; }
	else if (value == "9") { return sf::Keyboard::Num9; }

	else if (value == "Esc") { return sf::Keyboard::Escape; }
	else if (value == "L-Crtl") { return sf::Keyboard::LControl; }
	else if (value == "L-Shift") { return sf::Keyboard::LShift; }
	else if (value == "L-Alt") { return sf::Keyboard::LAlt; }
	else if (value == "R-Crtl") { return sf::Keyboard::RControl; }
	else if (value == "R-Shift") { return sf::Keyboard::RShift; }
	else if (value == "R-Alt") { return sf::Keyboard::RAlt; }

	else if (value == "Space") { return sf::Keyboard::Space; }
	else if (value == "Enter") { return sf::Keyboard::Enter; }
	else if (value == "Backspace") { return sf::Keyboard::Backspace; }
	else if (value == "Tab") { return sf::Keyboard::Tab; }

	else if (value == "Left-arrow") { return sf::Keyboard::Left; }
	else if (value == "Right-arrow") { return sf::Keyboard::Right; }
	else if (value == "Up-arrow") { return sf::Keyboard::Up; }
	else if (value == "Down-arrow") { return sf::Keyboard::Down; }

	else if (value == "F1") { return sf::Keyboard::F1; }
	else if (value == "F2") { return sf::Keyboard::F2; }
	else if (value == "F3") { return sf::Keyboard::F3; }
	else if (value == "F4") { return sf::Keyboard::F4; }
	else if (value == "F5") { return sf::Keyboard::F5; }
	else if (value == "F6") { return sf::Keyboard::F6; }
	else if (value == "F7") { return sf::Keyboard::F7; }
	else if (value == "F8") { return sf::Keyboard::F8; }
	else if (value == "F9") { return sf::Keyboard::F9; }
	else if (value == "F10") { return sf::Keyboard::F10; }
	else if (value == "F11") { return sf::Keyboard::F11; }
	else if (value == "F12") { return sf::Keyboard::F12; }

	else { return sf::Keyboard::Unknown; }
}

std::string bx::Convert::actionNameValueToString(const ActionName actionName) {
	
	switch (actionName) {
	case ActionName::Select: return "Select";
	case ActionName::Pause: return "Pause";
	case ActionName::Save: return "Save";
	case ActionName::Quit: return "Quit";

	case ActionName::ToggleTexture: return "Toggle texture";
	case ActionName::ToggleCollision: return "Toggle bounding box";
	case ActionName::ToggleGrid: return "Toggle grid";
	case ActionName::ToggleSightLine: return "Toggle sight line";
	case ActionName::ToggleFollowingCamera: return "Toggle following camera";

	case ActionName::Up: return "Up";
	case ActionName::Down: return "Down";
	case ActionName::Left: return "Left";
	case ActionName::Right: return "Right";

	case ActionName::Shoot: return "Shoot";
	case ActionName::Swing: return "Swing";

	case ActionName::LeftClick: return "Left click";
	case ActionName::MiddleClick: return "Middle click";
	case ActionName::RightClick: return "Right click";
	case ActionName::MouseMove: return "Move mouse";

	case ActionName::OpenQtWindwon: return "Open editor";

	case ActionName::NONE: return "";

	default: return "";
	}
}

bx::ActionName bx::Convert::stringToActionNameValue(const std::string& value) {
	
	if (value == "Select") { return ActionName::Select; }
	else if (value == "Pause") { return ActionName::Pause; }
	else if (value == "Save") { return ActionName::Save; }
	else if (value == "Quit") { return ActionName::Quit; }

	else if (value == "Toggle texture") { return ActionName::ToggleTexture; }
	else if (value == "Toggle bounding box") { return ActionName::ToggleCollision; }
	else if (value == "Toggle grid") { return ActionName::ToggleGrid; }
	else if (value == "Toggle sight line") { return ActionName::ToggleSightLine; }
	else if (value == "Toggle following camera") { return ActionName::ToggleFollowingCamera; }

	else if (value == "Up") { return ActionName::Up; }
	else if (value == "Down") { return ActionName::Down; }
	else if (value == "Left") { return ActionName::Left; }
	else if (value == "Right") { return ActionName::Right; }

	else if (value == "Shoot") { return ActionName::Shoot; }
	else if (value == "Swing") { return ActionName::Swing; }

	else if (value == "Left click") { return ActionName::LeftClick; }
	else if (value == "Middle click") { return ActionName::MiddleClick; }
	else if (value == "Right click") { return ActionName::RightClick; }
	else if (value == "Move mouse") { return ActionName::MouseMove; }

	else if (value == "Open editor") { return ActionName::OpenQtWindwon; }
	else if (value == "") { return ActionName::NONE; }
	else { return ActionName::NONE; }
}
