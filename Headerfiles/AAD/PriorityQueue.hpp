#pragma once

#include "Node.hpp"
#include "../Common/PrimitiveDatatypes.hpp"

namespace bx {

	class PriorityQueue {
		std::vector<NodePointer> open;
		uint maxSize = 0;
		uint numberOfNodes = 0;

		void resize();
		NodePointer getMin(NodePointer node);
	public:
		PriorityQueue(uint maxSize = 10);

		void push(NodePointer node);
		NodePointer popMinF();
		bool empty();
	};
}