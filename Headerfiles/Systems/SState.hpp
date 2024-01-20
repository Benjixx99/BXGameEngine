#pragma once

#include "../Common/CompositeDataTypes.hpp"
#include "../ECS/EntityManager.hpp"

namespace bx {

	class SState {
		EntityPointer player;
		EntityPointer weapon;
		Vector2 playerStartPoint;
	public:
		SState();
		
		void lifeSpan(const std::string& entityTag, EntityManager& entities);
		void invicibility();

		void setPlayer(EntityPointer player);
		EntityPointer getPlayer();
		
		void setWeapon(EntityPointer weapon);
		EntityPointer getWeapon();
		
		void setPlayerStartPoint(const Vector2& playerStartPoint);
		Vector2& getPlayerStartPoint();

	};
}