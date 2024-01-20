#pragma once

#include "Node.hpp"
#include "PriorityQueue.hpp"

namespace bx {
	namespace Algorithm {
		NodePointer AStar(const Vector2& start, const Vector2& target, GridField& field);
		NodePointer BFS(const Vector2& start, const Vector2& target, GridField& field);
		NodePointer DFS(const Vector2& start, const Vector2& target, GridField& field);
	}
}