#pragma once

#include <string>
#include <tuple>

#include "Components.hpp"
#include "EntityMemoryPool.hpp"

namespace bx {

	class EntityMemoryPool;

	class Entity {
		friend class EntityManager;

		size_t id = 0;	
		
		// constructor is private so we can never create
		// entities outside the EntityManager which had friend access
		Entity(const size_t);
	public:
		void destroy();
		bool isActive() const;
		const std::string& getTag() const;
		const size_t getId() const;

		template<typename T>
		bool hasComponent() const {
			return EntityMemoryPool::Instance().hasComponent<T>(id);
		}

		template<typename T, typename... TArgs>
		T& addComponent(TArgs&&... args) {
			auto& component = getComponent<T>();
			component = T(std::forward<TArgs>(args)...);
			component.has = true;
			return component;
		}

		template<typename T>
		T& getComponent() {
			return EntityMemoryPool::Instance().getComponent<T>(id);
		}

		template<typename T>
		const T& getComponent() const {
			return EntityMemoryPool::Instance().getComponent<T>(id);
		}

		template<typename T>
		void removeComponent() {
			getComponent<T>() = T();
		}
	};
}