#include "../../Headerfiles/Systems/SAI.hpp"
#include "../../Headerfiles/PAM/Physics.hpp"
#include "../../Headerfiles/AAD/Algorithm.hpp"
#include "../../Headerfiles/Common/PrimitiveDatatypes.hpp"

#include <stack>

bx::SAI::SAI() {}

bx::SAI::SAI(GridField&& field) : field (field) {}

bool bx::SAI::oscillationBalance(const Vector2& entityPosition, const Vector2& targetPosition) {
	const int balanceValue = 5;
	return (entityPosition.x >= targetPosition.x - balanceValue && entityPosition.x <= targetPosition.x + balanceValue &&
		entityPosition.y >= targetPosition.y - balanceValue && entityPosition.y <= targetPosition.y + balanceValue);
}

bx::NodePointer bx::SAI::pathFinding(const Vector2& start, const Vector2& target) {
	return Algorithm::AStar(start, target, field);
}

double bx::SAI::pathFollowingMovement(const double stateValue, const double velocityValue, double value) {
	if (value < stateValue) { value += velocityValue; }
	else if (value > stateValue) { value -= velocityValue; }
	return value;
}

void bx::SAI::pathFollowing(EntityPointer entity, Coordinates& coordinates) {
	Vector2& home = entity->getComponent<CFollowPath>().home;
	Vector2& target = entity->getComponent<CFollowPath>().target;
	std::stack<NodePointer>& stack = entity->getComponent<CFollowPath>().nodes;

	if (stack.empty() && home != target) {
		NodePointer node = pathFinding(home, target);

		while (node->getParent() != nullptr) {
			stack.push(node);
			node = node->getParent();
		}
	}

	if (!stack.empty()) {
		NodePointer node = stack.top();

		CTransform& transform = entity->getComponent<CTransform>();
		Vector2 statePosition = coordinates.computePosition(Vector2(64), node->getState());
		MoveAction action = node->getAction();
		transform.prevPosition = transform.position;

		if (action == MoveAction::Down || action == MoveAction::Up) { 
			transform.position.y = pathFollowingMovement(statePosition.y, transform.velocity.y, transform.position.y);
		}
		else if (action == MoveAction::Left || action == MoveAction::Right) {
			transform.position.x = pathFollowingMovement(statePosition.x, transform.velocity.x, transform.position.x);
		}
		else {
			transform.position.y = pathFollowingMovement(statePosition.y, transform.velocity.y, transform.position.y);
			transform.position.x = pathFollowingMovement(statePosition.x, transform.velocity.x, transform.position.x);
		}
		
		if (oscillationBalance(transform.position, statePosition)) {
			stack.pop();
		}
	}
	
	if (stack.empty()) {
		home = target;
	}
}

void bx::SAI::patrol(EntityPointer entity, Coordinates& coordinates) {
	uint& currentPosition = entity->getComponent<CPatrol>().currentPosition;
	CTransform& transform = entity->getComponent<CTransform>();
	Vector2 targetPosition = coordinates.computePosition(entity, entity->getComponent<CPatrol>().positions.at(currentPosition),
		entity->getComponent<CTransform>().roomCoordinate);
	Vector2 distanceVector = transform.position - targetPosition;

	transform.prevPosition = transform.position;
	transform.angle = atan2f(distanceVector.y, distanceVector.x);
	transform.position.x -= (transform.velocity.x * std::cos(transform.angle));
	transform.position.y -= (transform.velocity.y * std::sin(transform.angle));

	if (oscillationBalance(transform.position, targetPosition)) {
		currentPosition++;
		currentPosition %= entity->getComponent<CPatrol>().positions.size();
	}
}

void bx::SAI::follow(EntityPointer entityFollow, EntityManager& entities) {
	CTransform& transform = entityFollow->getComponent<CTransform>();
	EntityPointer targetEntity = entityFollow->getComponent<CFollowPrimitive>().targetEntity;
	Vector2 targetPosition = entityFollow->getComponent<CFollowPrimitive>().targetEntity->getComponent<CTransform>().position;
	Vector2 homePosition = entityFollow->getComponent<CFollowPrimitive>().home;
	bool visionBlocked = false;

	transform.prevPosition = transform.position;
	for (auto entity : entities.getEntities()) {
		if (entity->getTag() == targetEntity->getTag() || entity->getTag() == entityFollow->getTag()) { continue; }

		if (Physics::entityLineIntersect(transform.position, targetPosition, entity)) {
			if (entity->getComponent<CBoundingBox>().blockVision) {
				visionBlocked = true;
				break;
			}
		}
	}

	if (visionBlocked && oscillationBalance(transform.position, homePosition)) { return; }
	if (oscillationBalance(transform.position, targetPosition)) { return; }

	Vector2 distanceVector = (!visionBlocked ? transform.position - targetPosition : transform.position - homePosition);
	transform.angle = atan2f(distanceVector.y, distanceVector.x);
	transform.position.x -= (transform.velocity.x * std::cos(transform.angle));
	transform.position.y -= (transform.velocity.y * std::sin(transform.angle));
}

void bx::SAI::flee(EntityPointer entity) {

}

void bx::SAI::fighting(EntityPointer entity) {

}
