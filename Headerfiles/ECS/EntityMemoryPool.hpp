#pragma once

#include <tuple>
#include <vector>
#include <string>
#include "Entity.hpp"

namespace bx {

	constexpr int MAX_ENTITIES = 5000;

	class EntityMemoryPool {

		using EntityComponentVectorTuple = std::tuple<
			std::vector<CType>,
			std::vector<CTransform>,
			std::vector<CLifespan>,
			std::vector<CInput>,
			std::vector<CBoundingBox>,
			std::vector<CAnimation>,
			std::vector<CGravity>,
			std::vector<CState>,
			std::vector<CMobile>,
			std::vector<CHealth>,
			std::vector<CDamage>,
			std::vector<CInvincibility>,
			std::vector<CShader>,
			std::vector<CPatrol>,
			std::vector<CFollowPrimitive>,
			std::vector<CFollowPath>,
			std::vector<CDraggable>>;

		EntityComponentVectorTuple pool;
		std::vector<std::string> tags;
		std::vector<bool> active;
		size_t numberOfEntities = 0;
		size_t maxEntities = MAX_ENTITIES;

		EntityMemoryPool() {
			resize(pool);
			tags.resize(maxEntities);
			active.resize(maxEntities);
		};

		template <size_t I = 0, typename... Ts>
		void resize(std::tuple<Ts...>& pool) {
			if constexpr (I != sizeof...(Ts)) {
				std::get<I>(pool).resize(maxEntities);
				resize<I + 1>(pool);
			}
		}

		template <size_t I = 0, typename... Ts>
		void setToFalse(std::tuple<Ts...>& pool, size_t entity_ID) {
			if constexpr (I != sizeof...(Ts)) {
				std::get<I>(pool)[entity_ID].has = false;
				setToFalse<I + 1>(pool, entity_ID);
			}
		}
	
	public:
		EntityMemoryPool(EntityMemoryPool const&) = delete;
		void operator=(EntityMemoryPool const&) = delete;

		static EntityMemoryPool& Instance() {
			static EntityMemoryPool object;
			return object;
		}

		void destroy(size_t entityID);
		bool isActive(size_t entityID) const;
		const std::string& getTag(size_t entityID) const;
		size_t getNextEntityIndex(const std::string& tag);
		void setBack();

		template <typename T>
		T& getComponent(size_t entityID) {
			return std::get<std::vector<T>>(pool)[entityID];
		}

		template <typename T>
		bool hasComponent(size_t entityID) {
			return getComponent<T>(entityID).has;
		}
	};
}