#include "../../Headerfiles/AAD/Node.hpp"
#include "../../Headerfiles/PAM/Math.hpp"


bx::Node::Node(const Vector2& state, const Vector2& target, MoveAction action, NodePointer parent)
	: state (state), action (action), parent (parent) {
	calculateCost();
	heuristic = Math::diagonalManhattanDistance(state, target);
	costPlusHeuristic = cost + heuristic;
}

bx::uint bx::Node::actionCost() {
	switch (action)
	{
	case bx::MoveAction::Up:
	case bx::MoveAction::Left:
	case bx::MoveAction::Down:
	case bx::MoveAction::Right:		return cardinalCost;
	case bx::MoveAction::LeftUp:
	case bx::MoveAction::LeftDown:
	case bx::MoveAction::RightDown:
	case bx::MoveAction::RightUp:	return diagonalCost;
	case bx::MoveAction::NoAction:
	default:	return 0;
	}
}

void bx::Node::calculateCost() {
	cost = (parent != nullptr) ? actionCost() + parent->getCost() : actionCost();
}

const bx::Vector2& bx::Node::getState() const {
	return state;
}

const double bx::Node::getCost() const {
	return cost;
}

const double bx::Node::getF() const {
	return costPlusHeuristic;
}

const bx::NodePointer bx::Node::getParent() const {
	return parent;
}

const bx::MoveAction bx::Node::getAction() const {
	return action;
}

std::vector<bx::NodePointer> bx::Node::expand(GridField& field, const Vector2& target) {
	std::vector<NodePointer> nodeVector;
	std::vector<Vector2> vec{ Vector2(0, -1), Vector2(-1, -1), Vector2(-1, 0), Vector2(-1, 1),
								Vector2(0, 1), Vector2(1, 1), Vector2(1, 0), Vector2(1, -1), };

	for (int i = 0; i < 8; ++i) {
		if (state.x + vec[i].x < 0 || state.y + vec[i].y < 0) { continue; }

		if (!field.getOccupied(state + vec[i])) {
			nodeVector.push_back(std::make_shared<Node>(state + vec[i], target, static_cast<MoveAction>(i), shared_from_this()));
		}
	}
	return nodeVector;
}
