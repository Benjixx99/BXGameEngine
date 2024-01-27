#include "../../Headerfiles/Systems/SCollision.hpp"
#include "../../Headerfiles/PAM/Physics.hpp"
#include "../Headerfiles/Common/Paths.hpp"
#include "../Headerfiles/Tools/Logger.hpp"

bx::SCollision::SCollision() {}

void bx::SCollision::resolutionMovement(double& position, const double& overlap, bool blockMovement) {
	if (blockMovement) { position += overlap; }
}

void bx::SCollision::detection(EntityManager& entities, GCollision& gCollision) {
	for (auto mobileEntity : entities.getEntities()) {
		if (!mobileEntity->hasComponent<CMobile>()) { continue; }

		for (auto entity : entities.getEntities()) {
			if (mobileEntity->getId() == entity->getId() || !entity->hasComponent<CBoundingBox>()) { continue; }

			Vector2 overlap = Physics::getOverlap(mobileEntity, entity);

			if (overlap.x > 0 && overlap.y > 0) {
				Vector2 previousOverlap = Physics::getPreviousOverlap(mobileEntity, entity);
				Vector2& mobilePosition = mobileEntity->getComponent<CTransform>().position;
				Vector2& mobilePrePosition = mobileEntity->getComponent<CTransform>().prevPosition;
				bool blockMovement = mobileEntity->getComponent<CBoundingBox>().blockMovement && entity->getComponent<CBoundingBox>().blockMovement;

				if (previousOverlap.x > 0 && mobilePrePosition.y < mobilePosition.y) {
					resolutionMovement(mobilePosition.y, overlap.y * -1, blockMovement);
					gCollision.fromAbove(mobileEntity, entity);
					Logger::get().log(LogLevel::Tracing, "Collision from above", "SCollision", __LINE__);
				}
				else if (previousOverlap.x > 0 && mobilePrePosition.y > mobilePosition.y) {
					resolutionMovement(mobilePosition.y, overlap.y, blockMovement);
					gCollision.fromBelow(mobileEntity, entity);
					Logger::get().log(LogLevel::Tracing, "Collision from below", "SCollision", __LINE__);
				}

				if (previousOverlap.y > 0 && mobilePrePosition.x < mobilePosition.x) {
					resolutionMovement(mobilePosition.x, overlap.x * -1, blockMovement);
					gCollision.fromLeft(mobileEntity, entity);
					Logger::get().log(LogLevel::Tracing, "Collision from left", "SCollision", __LINE__);
				}
				else if (previousOverlap.y > 0 && mobilePrePosition.x > mobilePosition.x) {
					resolutionMovement(mobilePosition.x, overlap.x, blockMovement);
					gCollision.fromRight(mobileEntity, entity);
					Logger::get().log(LogLevel::Tracing, "Collision from right", "SCollision", __LINE__);
				}

				if (previousOverlap.x > 0 || previousOverlap.y > 0) {
					gCollision.fromAllSides(mobileEntity, entity);
				}
			}
		}
	}
}

