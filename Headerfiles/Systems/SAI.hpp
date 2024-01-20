#pragma once

#include "../AAD/GridField.hpp"
#include "../Common/Vector2.hpp"
#include "../ECS/EntityManager.hpp"
#include "../SSC/Coordinates.hpp"

namespace bx {

	class Node;
	using NodePointer = std::shared_ptr<Node>;

	class SAI {
		GridField field;

		bool oscillationBalance(const Vector2& entityPosition, const Vector2& targetPosition);
		NodePointer pathFinding(const Vector2& start, const Vector2& target);
		double pathFollowingMovement(const double stateValue, const double velocityValue, double value);
	public:
		SAI();
		SAI(GridField&& field);

		void pathFollowing(EntityPointer entity, Coordinates& coordinates);
		void patrol(EntityPointer entity, Coordinates& coordinates);
		void follow(EntityPointer entity, EntityManager& entities);
		void flee(EntityPointer entity);
		void fighting(EntityPointer entity);
	};
}