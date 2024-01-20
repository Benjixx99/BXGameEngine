#include <math.h>
#include "../../Headerfiles/PAM/Physics.hpp"

bx::Vector2 bx::Physics::getOverlap(EntityPointer firstEntity, EntityPointer secondEntity) {

	if (firstEntity->getComponent<CBoundingBox>().has && secondEntity->getComponent<CBoundingBox>().has) {
		Vector2 distance(
			std::abs(firstEntity->getComponent<CTransform>().position.x - secondEntity->getComponent<CTransform>().position.x), 
			std::abs(firstEntity->getComponent<CTransform>().position.y - secondEntity->getComponent<CTransform>().position.y));

		return Vector2(
			firstEntity->getComponent<CBoundingBox>().halfSize + secondEntity->getComponent<CBoundingBox>().halfSize - distance);
	}
	return Vector2(0, 0);
}

bx::Vector2 bx::Physics::getPreviousOverlap(EntityPointer firstEntity, EntityPointer secondEntity) {
	if (firstEntity->getComponent<CBoundingBox>().has && secondEntity->getComponent<CBoundingBox>().has) {
		Vector2 distance(
			std::abs(firstEntity->getComponent<CTransform>().prevPosition.x - secondEntity->getComponent<CTransform>().prevPosition.x),
			std::abs(firstEntity->getComponent<CTransform>().prevPosition.y - secondEntity->getComponent<CTransform>().prevPosition.y));

		return Vector2(
			firstEntity->getComponent<CBoundingBox>().halfSize + secondEntity->getComponent<CBoundingBox>().halfSize - distance);
	}
	return Vector2(0, 0);
}

std::pair<bool,bx::Vector2> bx::Physics::lineIntersect(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d) {
	Vector2 r(b - a), s(d - c), temp(c - a);
	double divisor =(r.x * s.y) - (r.y * s.x);
	double t = ((temp.x * s.y) - (temp.y * s.x)) / divisor;
	double u = ((temp.x * r.y) - (temp.y * r.x)) / divisor;

	return (t >= 0 && t <= 1 && u >= 0 && u <= 1 ? 
		std::pair<bool, Vector2>(true, Vector2(a + (r * t))) : std::pair<bool, Vector2>(false, Vector2(0, 0)));
}

bool bx::Physics::entityLineIntersect(const Vector2& p1, const Vector2& p2, EntityPointer entity) {
	Vector2 entityHalfSize = entity->getComponent<CBoundingBox>().halfSize;
	Vector2 entityPosition = entity->getComponent<CTransform>().position;
	Vector2 a(entityPosition - entityHalfSize);
	Vector2 b(entityPosition.x + entityHalfSize.x, entityPosition.y - entityHalfSize.y);
	Vector2 c(entityPosition.x - entityHalfSize.x, entityPosition.y + entityHalfSize.y);
	Vector2 d(entityPosition + entityHalfSize);

	if (lineIntersect(p1, p2, a, b).first) { return true; }
	if (lineIntersect(p1, p2, b, c).first) { return true; }
	if (lineIntersect(p1, p2, c, d).first) { return true; }
	if (lineIntersect(p1, p2, a, d).first) { return true; }

	return false;
}

bool bx::Physics::isInside(EntityPointer entity, const Vector2& position) {
	Vector2 entityPosition = entity->getComponent<CTransform>().position;
	Vector2 entityHalfSize = entity->getComponent<CAnimation>().animation.getSize() / 2;

	return (position.x < entityPosition.x + entityHalfSize.x && position.x > entityPosition.x - entityHalfSize.x &&
		position.y < entityPosition.y + entityHalfSize.y && position.y > entityPosition.y - entityHalfSize.y);
}

bool bx::Physics::isInside(const sf::FloatRect& rect, const Vector2& position, const Vector2& offset) {
	Vector2 rectPosition = rect.getPosition();
	Vector2 rectHalfSize = rect.getSize();
	rectHalfSize /= 2;
	rectPosition += rectHalfSize;

	return (position.x < rectPosition.x + rectHalfSize.x + offset.x && position.x > rectPosition.x - rectHalfSize.x - offset.x &&
		position.y < rectPosition.y + rectHalfSize.y + offset.y && position.y > rectPosition.y - rectHalfSize.y - offset.y);
}

