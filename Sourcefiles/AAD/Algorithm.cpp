#include "../../Headerfiles/AAD/Algorithm.hpp"

#include <queue>
#include <stack>

bx::NodePointer bx::Algorithm::AStar(const Vector2& start, const Vector2& target, GridField& field) {
	std::vector<Vector2> closed;
	PriorityQueue open;
	open.push(std::make_shared<Node>(start, target, MoveAction::NoAction));

	while (!open.empty()) {
		NodePointer node = open.popMinF();
		if (node->getState() == target) { return node; }
		if (std::find(closed.begin(), closed.end(), node->getState()) != closed.end()) { continue; }
		closed.push_back(node->getState());

		for (auto childNode : node->expand(field, target)) {
			open.push(childNode);
		}
	}
}

bx::NodePointer bx::Algorithm::BFS(const Vector2& start, const Vector2& target, GridField& field) {
	std::vector<Vector2> closed;
	std::queue<NodePointer> open;
	open.push(std::make_shared<Node>(start, target, MoveAction::NoAction));

	while (!open.empty()) {
		NodePointer node = open.front();
		open.pop();
		if (node->getState() == target) { return node; }
		if (std::find(closed.begin(), closed.end(), node->getState()) != closed.end()) { continue; }
		closed.push_back(node->getState());

		for (auto childNode : node->expand(field, target)) {
			open.push(childNode);
		}
	}
}

bx::NodePointer bx::Algorithm::DFS(const Vector2& start, const Vector2& target, GridField& field) {
	std::vector<Vector2> closed;
	std::stack<NodePointer> open;
	open.push(std::make_shared<Node>(start, target, MoveAction::NoAction));

	while (!open.empty()) {
		NodePointer node = open.top();
		open.pop();
		if (node->getState() == target) { return node; }
		if (std::find(closed.begin(), closed.end(), node->getState()) != closed.end()) { continue; }
		closed.push_back(node->getState());

		for (auto childNode : node->expand(field, target)) {
			open.push(childNode);
		}
	}
}