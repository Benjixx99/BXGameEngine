#include "../Headerfiles/Action.hpp"

bx::Action::Action() {}

bx::Action::Action(const ActionName name, const ActionType type)
	: name (name), type (type) {}

bx::Action::Action(const ActionName name, const ActionType type, const Vector2& position)
	: name (name), type (type), position (position) {}

const bx::ActionName bx::Action::getName() const {
	return name;
}

const bx::ActionType bx::Action::getType() const {
	return type;
}

const bx::Vector2& bx::Action::getPosition() const {
	return position;
}
