#pragma once

#include "../../Headerfiles/Common/CompositeDataTypes.hpp"
#include "../../Headerfiles/ECS/EntityManager.hpp"
#include "../../Headerfiles/Systems/SSound.hpp"
#include "../../Headerfiles/Systems/SState.hpp"
#include "../../Headerfiles/Assets.hpp"

namespace bx {

	class GCollisionData {
	public:
		EntityManager* entities = nullptr;
		Assets* assets = nullptr;
		SState* state = nullptr;
		SSound* sound = nullptr;

		GCollisionData() {}
		GCollisionData(EntityManager* entities, Assets* assets, SState* state, SSound* sound)
			: entities(entities), assets(assets), state (state), sound(sound) {}
	};

	class GCollision : public GCollisionData {
		size_t IFRAMES = 30;
	public:
		GCollision();
		GCollision(GCollisionData&& data);

		void fromAllSides(EntityPointer mobileEntity, EntityPointer collidedEntity);
		void fromAbove(EntityPointer mobileEntity, EntityPointer collidedEntity);
		void fromBelow(EntityPointer mobileEntity, EntityPointer collidedEntity);
		void fromLeft(EntityPointer mobileEntity, EntityPointer collidedEntity);
		void fromRight(EntityPointer mobileEntity, EntityPointer collidedEntity);
	};
}