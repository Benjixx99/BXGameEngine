#pragma once

#include "../Common/CompositeDataTypes.hpp"
#include "../ECS/EntityManager.hpp"
#include "../../Game/Headerfiles/GCollision.hpp"

namespace bx {

	class SCollision {
		void resolutionMovement(double& position, const double& overlap, bool blockMovement);
	public:
		SCollision();
		void detection(EntityManager& entities, GCollision& gCollision);
	};
}