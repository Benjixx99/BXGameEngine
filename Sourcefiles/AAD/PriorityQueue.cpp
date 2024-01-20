#include "../../Headerfiles/AAD/PriorityQueue.hpp"


bx::PriorityQueue::PriorityQueue(uint maxSize) : maxSize(maxSize) {
	open.resize(maxSize);
}

void bx::PriorityQueue::resize() {
	maxSize *= 2;
	open.resize(maxSize);
}

bx::NodePointer bx::PriorityQueue::getMin(NodePointer node) {
	NodePointer min = node;
	for (int index = 0; index < numberOfNodes; ++index) {
		if (min->getF() > open[index]->getF()) {
			NodePointer temp = open[index];
			open[index] = min;
			min = temp;
		}
	}
	return min;
}

void bx::PriorityQueue::push(NodePointer node) {
	if (numberOfNodes == maxSize) { resize(); }
	open[numberOfNodes++] = getMin(node);
}

bx::NodePointer bx::PriorityQueue::popMinF() {
	if (empty()) { return NodePointer(); }
	return open[--numberOfNodes];
}

bool bx::PriorityQueue::empty() {
	return numberOfNodes == 0;
}