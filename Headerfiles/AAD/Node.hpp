#pragma once

#include "GridField.hpp"
#include "../Common/PrimitiveDatatypes.hpp"

namespace bx {

	class Node;
	class State;
	using NodePointer = std::shared_ptr<Node>;

	constexpr uchar cardinalCost = 64;
	constexpr uchar diagonalCost = 90;

	enum class MoveAction : uchar {
		Up,
		LeftUp,
		Left,
		LeftDown,
		Down,
		RightDown,
		Right,
		RightUp,
		NoAction
	};

	class Node : public std::enable_shared_from_this<Node> {
		Vector2 state;
		uint cost = 0;
		double heuristic = 0;
		double costPlusHeuristic = 0;
		MoveAction action;
		NodePointer parent;

		uint actionCost();
		void calculateCost();
	public:
		Node(const Vector2& state, const Vector2& target, MoveAction action, NodePointer parent = nullptr);

		const Vector2& getState() const;
		const double getCost() const;
		const double getF() const;
		const NodePointer getParent() const;
		const MoveAction getAction() const;
		std::vector<NodePointer> expand(GridField& field, const Vector2& target);
	};
}