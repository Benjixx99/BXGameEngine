#include "../../Headerfiles/SSC/Creation.hpp"

bx::Creation::Creation() {}

bx::Creation::Creation(Assets* assets, Coordinates* coordinates, EntityManager* entities)
	: assets (assets), coordinates (coordinates), entities (entities) {}

bx::EntityPointer bx::Creation::spawnPlayer(const PlayerConfigData& config) {
	EntityPointer player = entities->addEntity("Player");
	player->addComponent<CType>(EntityType::Player);
	player->addComponent<CAnimation>(assets->getAnimation("PlayerMovingDown"), false);
	player->addComponent<CTransform>(coordinates->computePosition(player, config.GRID), config.ROOM, config.SPEED);
	player->addComponent<CBoundingBox>(config.SIZE, true, false);
	player->addComponent<CInput>();
	player->addComponent<CState>();
	player->addComponent<CMobile>();
	player->addComponent<CHealth>(config.HEALTH);
	
	return player;
}

bx::EntityPointer bx::Creation::spawnSword(EntityPointer sword, EntityPointer player) {
	std::string textureName = "Sword";
	Vector2 swordSize(coordinates->getGridSize());

	sword->addComponent<CType>(EntityType::Weapon);
	sword->addComponent<CAnimation>(assets->getAnimation("SwordDown"), true);
	sword->addComponent<CTransform>(player->getComponent<CTransform>().position);
	sword->addComponent<CBoundingBox>(swordSize, false, false);
	sword->addComponent<CLifespan>(30);
	sword->addComponent<CState>(player->getComponent<CState>().facing, true);
	sword->addComponent<CMobile>();
	sword->addComponent<CDamage>(1);

	player->getComponent<CState>().isAttacking = true;
	return sword;
}

bx::EntityPointer bx::Creation::spawnBullet(EntityPointer bullet, EntityPointer player) {
	std::string textureName = "Bullet";
	Vector2 bulletSize(assets->getTexture(textureName).getSize());
	
	bullet->addComponent<CType>(EntityType::Weapon);
	bullet->addComponent<CAnimation>(Animation("Bullet", bulletSize, assets->getTexture(textureName)), false);
	bullet->addComponent<CTransform>(player->getComponent<CTransform>().position, Vector2(8, 0));
	bullet->addComponent<CBoundingBox>(bulletSize);
	bullet->addComponent<CLifespan>(60);
	bullet->addComponent<CState>(player->getComponent<CState>().facing, true);
	bullet->addComponent<CMobile>();

	player->getComponent<CState>().isAttacking = true;

	return bullet;
}

bx::EntityPointer bx::Creation::spawnNPC(const NPCConfigData& config, EntityPointer player) {
	EntityPointer enemy = entities->addEntity("NPC");
	
	enemy->addComponent<CType>(EntityType::NPC);
	enemy->addComponent<CAnimation>(assets->getAnimation(config.NAME), true);
	enemy->addComponent<CTransform>(coordinates->computePosition(enemy, config.GRID, config.ROOM), config.ROOM, config.SPEED);
	enemy->addComponent<CBoundingBox>(coordinates->getGridSize(), config.BLOCK_MOVEMENT, config.BLOCK_VISION);
	enemy->addComponent<CMobile>();
	enemy->addComponent<CHealth>(config.HEALTH);
	enemy->addComponent<CDamage>(config.DAMAGE);
	enemy->addComponent<CDraggable>();

	if (config.BEHAVIOR == NPCBehaviorType::FollowPrimitive) {
		enemy->addComponent<CFollowPrimitive>(player, enemy->getComponent<CTransform>().position);
	}
	else if (config.BEHAVIOR == NPCBehaviorType::FollowPath) {
		enemy->addComponent<CFollowPath>(config.TARGET, config.GRID);
	}
	else if (config.BEHAVIOR == NPCBehaviorType::Patrol) {
		enemy->addComponent<CPatrol>(config.POSITIONS);
	}

	return enemy;
}

bx::EntityPointer bx::Creation::spawnTile(const TileConfigData& config) {
	EntityPointer entity = entities->addEntity(config.NAME);
	sf::Texture& texture = assets->getTexture(config.NAME);

	entity->addComponent<CType>(EntityType::Tile);
	(assets->getAnimation(config.NAME).getName() != "NONE") ?
		entity->addComponent<CAnimation>(assets->getAnimation(config.NAME), true) :
		entity->addComponent<CAnimation>(Animation(config.NAME, texture.getSize(), texture), false);

	entity->addComponent<CTransform>(coordinates->computePosition(entity, config.GRID, config.ROOM), config.ROOM, Vector2(0, 0));
	entity->addComponent<CBoundingBox>(entity->getComponent<CAnimation>().animation.getSize(), config.BLOCK_MOVEMENT, config.BLOCK_VISION);
	entity->addComponent<CDraggable>();

	return entity;
}
