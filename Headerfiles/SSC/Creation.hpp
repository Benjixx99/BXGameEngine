#pragma once

#include "../ECS/EntityManager.hpp"
#include "../Common/CompositeDataTypes.hpp"
#include "../Assets.hpp"
#include "../Config/Config.hpp"

namespace bx {

	class Creation {
		Assets* assets = nullptr;
		Coordinates* coordinates = nullptr;
		EntityManager* entities = nullptr;
		
	public:
		Creation();
		Creation(Assets* assets, Coordinates* coordinates, EntityManager* entities);

		EntityPointer spawnPlayer(const PlayerConfigData& config);
		EntityPointer spawnSword(EntityPointer sword, EntityPointer player);
		EntityPointer spawnBullet(EntityPointer bullet, EntityPointer player);
		EntityPointer spawnNPC(const NPCConfigData& config, EntityPointer player = nullptr);
		EntityPointer spawnTile(const TileConfigData& config);
	};
}