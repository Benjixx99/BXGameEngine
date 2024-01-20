#include "../../Headerfiles/ECS/EntityManager.hpp"
#include <algorithm>

bx::EntityManager::EntityManager() {}

void bx::EntityManager::update() {
	for (auto entity : entitiesToAdd) {
		entities.push_back(entity);
		entityMap[entity->getTag()].push_back(entity);
	}
	entitiesToAdd.clear();
	
	// Remove dead entities from the vector of all entities
	removeDeadEntities(entities);

	// Remove dead entities from each vector in the entity map
	for (auto& [tag, entities] : entityMap) {
		removeDeadEntities(entities);
	}
}

bx::EntityPointer bx::EntityManager::addEntity(const std::string& tag) {
	EntityPointer entity(new bx::Entity(EntityMemoryPool::Instance().getNextEntityIndex(tag)));
	entitiesToAdd.push_back(entity);
	return entity;
}

bx::EntityVector& bx::EntityManager::getEntities() {
	return entities;
}

bx::EntityVector& bx::EntityManager::getEntities(const std::string& tag) {
	return entityMap[tag];
}

void bx::EntityManager::removeDeadEntities(bx::EntityVector& entities) {

	entities.erase(std::remove_if(entities.begin(), entities.end(),
	[](EntityPointer& const entity) { 
			return !entity->isActive();
	}), entities.end());
}