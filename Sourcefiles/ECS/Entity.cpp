#include "../../Headerfiles/ECS/Entity.hpp"

bx::Entity::Entity(const size_t id) : id(id) {}

void bx::Entity::destroy() {
	EntityMemoryPool::Instance().destroy(id);
}

bool bx::Entity::isActive() const {
	return EntityMemoryPool::Instance().isActive(id);
}

const std::string& bx::Entity::getTag() const {
	return EntityMemoryPool::Instance().getTag(id);
}

const size_t bx::Entity::getId() const {
	return id;
}