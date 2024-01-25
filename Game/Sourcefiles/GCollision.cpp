#include "../Headerfiles/GCollision.hpp"
#include "../../Headerfiles/Common/RandomNumber.hpp"
#include "../../Headerfiles/PAM/Physics.hpp"

bx::GCollision::GCollision() {}

bx::GCollision::GCollision(GCollisionData&& data) : GCollisionData(data) {}

void bx::GCollision::fromAllSides(EntityPointer mobileEntity, EntityPointer collidedEntity) {
	
	// Game specific code 
}

void bx::GCollision::fromAbove(EntityPointer mobileEntity, EntityPointer collidedEntity) {

	// Game specific code

}

void bx::GCollision::fromBelow(EntityPointer mobileEntity, EntityPointer collidedEntity) {

	// Game specific code

}

void bx::GCollision::fromLeft(EntityPointer mobileEntity, EntityPointer collidedEntity) {

	// Game specific code

}

void bx::GCollision::fromRight(EntityPointer mobileEntity, EntityPointer collidedEntity) {

	// Game specific code

}