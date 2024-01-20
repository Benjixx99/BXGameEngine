#include "../../Headerfiles/Systems/SState.hpp"

bx::SState::SState() {}

void bx::SState::lifeSpan(const std::string& entityTag, EntityManager& entities) {
	for (auto sword : entities.getEntities(entityTag)) {
		if (sword->getComponent<CLifespan>().remainingLifespan-- == 0) {
			player->getComponent<CState>().isAttacking = false;
			sword->destroy();
			weapon = nullptr;
		}
	}
}

void bx::SState::invicibility() {
	if (player->hasComponent<CInvincibility>() && player->getComponent<CInvincibility>().iframes-- <= 0) {
		player->removeComponent<CInvincibility>();
	}
}

void bx::SState::setPlayer(EntityPointer player) {
	this->player = player;
}

bx::EntityPointer bx::SState::getPlayer() {
	return player;
}

void bx::SState::setWeapon(EntityPointer weapon) {
	this->weapon = weapon;
}

bx::EntityPointer bx::SState::getWeapon() {
	return weapon;
}

void bx::SState::setPlayerStartPoint(const Vector2& playerStartPoint) {
	this->playerStartPoint = playerStartPoint;
}

bx::Vector2& bx::SState::getPlayerStartPoint() {
	return playerStartPoint;
}
