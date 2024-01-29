#include "../../../Headerfiles/Data/Files/WriteOut.hpp"

void bx::WriteOut::playerData(std::ofstream& file, const PlayerConfigData&& config) {
	file << "Int\t SpawnGridPositionX\t" << config.GRID.x << "\n"
		<< "Int\t SpawnGridPositionY\t" << config.GRID.y << "\n"
		<< "Int\t SpawnRoomX\t" << config.ROOM.x << "\n"
		<< "Int\t SpawnRoomY\t" << config.ROOM.y << "\n"
		<< "Int\t SizeX\t" << config.SIZE.y << "\n"
		<< "Int\t SizeY\t" << config.SIZE.y << "\n"
		<< "Int\t MaxHealth\t" << config.HEALTH << "\n"

		<< "Double\t SpeedX\t" << config.SPEED.x << "\n"
		<< "Double\t SpeedY\t" << config.SPEED.y << "\n"
		<< "Double\t Gravity\t" << config.GRAVITY << "\n";
}

void bx::WriteOut::NPCData(std::ofstream& file, const NPCConfigData&& config) {
	file << "NPC" << "\t" << config.NAME << "\t" << config.ROOM.x << "\t" << config.ROOM.y << "\t" << config.GRID.x << "\t"
		<< config.GRID.y << "\t" << config.BLOCK_MOVEMENT << "\t" << config.BLOCK_VISION << "\t"
		<< config.HEALTH << "\t" << config.DAMAGE << "\t";
	file << config.BEHAVIOR << "\t" << config.SPEED.x << "\t";

	if (config.BEHAVIOR == NPCBehaviorType::Patrol) {
		file << config.NUMBER_OF_POSITIONS << "\t";

		for (const auto& position : config.POSITIONS) {
			file << "\t" << position.x << "\t" << position.y;
		}
	}

	if (config.BEHAVIOR == NPCBehaviorType::FollowPath) {
		file << config.TARGET.x << "\t" << config.TARGET.y;
	}

	file << "\n";
}

void bx::WriteOut::tileData(std::ofstream& file, const TileConfigData&& config) {
	file << "Tile" << "\t" << config.NAME << "\t" << config.ROOM.x << "\t" << config.ROOM.y << "\t"
		<< config.GRID.x << "\t" << config.GRID.y << "\t" << config.BLOCK_MOVEMENT << "\t" << config.BLOCK_VISION << "\n";
}
