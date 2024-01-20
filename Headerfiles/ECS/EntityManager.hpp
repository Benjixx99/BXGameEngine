#pragma once
#include <string>

#include "EntityMemoryPool.hpp"
#include "Entity.hpp"
#include "../Common/CompositeDataTypes.hpp"

namespace bx {

	class EntityManager {
		EntityVector entities;
		EntityVector entitiesToAdd;
		EntityMap entityMap;

		void removeDeadEntities(EntityVector& entities);
	public:
		EntityManager();
		void update();
		EntityPointer addEntity(const std::string& tag);
		EntityVector& getEntities();
		EntityVector& getEntities(const std::string& tag);
	};
}