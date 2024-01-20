#include "../../Headerfiles/Systems/SAnimation.hpp"
#include "../../Game/Headerfiles/GAnimation.hpp"

bx::SAnimation::SAnimation() {}

bx::SAnimation::SAnimation(Assets* assets) : assets (assets) {}

void bx::SAnimation::playerMoving(EntityPointer player) {
	if (player->getComponent<CState>().facing == Direction::Up) {
		player->getComponent<CAnimation>().animation.getSprite().setTexture(assets->getTexture("PlayerMovingUp"));
	}

	else if (player->getComponent<CState>().facing == Direction::Down) {
		player->getComponent<CAnimation>().animation.getSprite().setTexture(assets->getTexture("PlayerMovingDown"));
	}

	else if (player->getComponent<CState>().facing == Direction::Left || player->getComponent<CState>().facing == Direction::Right) {
		player->getComponent<CAnimation>().animation.getSprite().setTexture(assets->getTexture("PlayerMovingSide"));
	}

	player->getComponent<CAnimation>().repeat = player->getComponent<CState>().isRunning;
	player->getComponent<CAnimation>().animation.update(player->getComponent<CAnimation>().repeat);
}

void bx::SAnimation::playerAttacking(EntityPointer player, EntityPointer weapon) {
	if (!player->getComponent<CState>().isAttacking) { return; }

	player->getComponent<CAnimation>().repeat = true;
	if (player->getComponent<CState>().facing == Direction::Up) {
		player->getComponent<CAnimation>().animation.getSprite().setTexture(assets->getTexture("PlayerSwordUp"));
		weapon->getComponent<CAnimation>().animation.getSprite().setTexture(assets->getTexture("SwordUp"));
	}
	else if (player->getComponent<CState>().facing == Direction::Down) {
		player->getComponent<CAnimation>().animation.getSprite().setTexture(assets->getTexture("PlayerSwordDown"));
		weapon->getComponent<CAnimation>().animation.getSprite().setTexture(assets->getTexture("SwordDown"));
	}
	else if (player->getComponent<CState>().facing == Direction::Left || player->getComponent<CState>().facing == Direction::Right) {
		player->getComponent<CAnimation>().animation.getSprite().setTexture(assets->getTexture("PlayerSwordSide"));
		weapon->getComponent<CAnimation>().animation.getSprite().setTexture(assets->getTexture("SwordSide"));
		weapon->getComponent<CTransform>().scale.x = (player->getComponent<CState>().facing == Direction::Right ? 1 : -1);
	}

	weapon->getComponent<CAnimation>().animation.update(weapon->getComponent<CAnimation>().repeat);
	player->getComponent<CAnimation>().animation.update(player->getComponent<CAnimation>().repeat);
}

void bx::SAnimation::NPCMoving(EntityManager& entities) {
	for (auto entity : entities.getEntities("NPC")) {
		Game::GAnimation::NPCMoving(entity, assets);
	}
}

void bx::SAnimation::NPCAttacking(EntityManager& entities) {
	for (auto entity : entities.getEntities("NPC")) {
		Game::GAnimation::NPCAttacking(entity, assets);
	}
}