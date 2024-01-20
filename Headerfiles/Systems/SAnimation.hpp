#pragma once

#include "../Common/CompositeDataTypes.hpp"
#include "../ECS/EntityManager.hpp"
#include "../Assets.hpp"

namespace bx {

	class SAnimation {
		Assets* assets = nullptr;
	public:
		SAnimation();
		SAnimation(Assets* assets);

		void playerMoving(EntityPointer player);
		void playerAttacking(EntityPointer player, EntityPointer weapon);
		void NPCMoving(EntityManager& entities);
		void NPCAttacking(EntityManager& entities);
	};
}