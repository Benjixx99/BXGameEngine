#include "../../Headerfiles/ECS/EntityMemoryPool.hpp"

const std::string& bx::EntityMemoryPool::getTag(size_t entityID) const {
	return tags[entityID];
}

bool bx::EntityMemoryPool::isActive(size_t entityID) const {
	return active[entityID];
}

void bx::EntityMemoryPool::destroy(size_t entityID) {
	--numberOfEntities;
	active[entityID] = false;
}

size_t bx::EntityMemoryPool::getNextEntityIndex(const std::string& tag) {
	++numberOfEntities;

	if (numberOfEntities == maxEntities) {
		maxEntities *= 2;
		resize(pool);
		tags.resize(maxEntities);
		active.resize(maxEntities);
	}

	size_t index = 0;
	for (; index < active.size(); ++index) {
		if (!active[index]) { break; }
	}

	setToFalse(pool, index);
	active[index] = true;
	tags[index] = tag;

	return index;
}

void bx::EntityMemoryPool::setBack() {
	numberOfEntities = 0;
	for (auto index : active) { index = false; }
}