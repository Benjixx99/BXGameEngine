#include "../../Headerfiles/Systems/SLoader.hpp"
#include "../../Headerfiles/Data/Files/ReadIn.hpp"

bx::SLoader::SLoader() {}

bx::SLoader::SLoader(const ConfigFiles& configFiles, Creation* creation, SState* state) : creation(creation), state(state) {
	loadPlayer(std::ifstream(configFiles.playerConfigFile));
	loadNPCs(std::ifstream(configFiles.NPCsConfigFile));
}

void bx::SLoader::loadPlayer(std::ifstream&& file) {
	PlayerConfigData config;
	EntityPointer player = creation->spawnPlayer(ReadIn::playerData(file, config));
	
	state->setPlayerStartPoint(player->getComponent<CTransform>().position);
	state->setPlayer(player);
}

void bx::SLoader::loadNPCs(std::ifstream&& file) {
	std::string command;
	while (file >> command) {
		NPCConfigData config;
		creation->spawnNPC(ReadIn::NPCData(file, config), state->getPlayer());
	}
}

void bx::SLoader::loadTiles(std::ifstream&& file) {
	std::string command;
	while (file >> command) {
		TileConfigData config;
		creation->spawnTile(ReadIn::tileData(file, config));
	}
}

// Load all the tiles entites at once
void bx::SLoader::allTilesAtOnce(const std::string& levelConfigFile) {	
	loadTiles(std::move(std::ifstream(levelConfigFile)));
}

// Load nine rooms at any given time, one in which the player currently is and eight rooms around the player
void bx::SLoader::rooms(const Vector2& room, const Vector2& preRoom, const TileConfigDataVector& tileConfigData, EntityManager& entites) {

	// Compare which rooms are already loaded
	NineRooms rooms(room);
	NineRooms preRooms(preRoom);
	std::vector<Vector2> roomsToLoad = rooms.diffrence(preRooms);
	std::vector<Vector2> roomsToUnLoad = preRooms.diffrence(rooms);

	for (auto tileConfig : tileConfigData) {
		Vector2 tileRoom = tileConfig.ROOM;
	
		for (auto room : roomsToLoad) {
			if (tileRoom == room) {
				EntityPointer entity = creation->spawnTile(tileConfig);
				//std::cout << "Loaded: " << entity->getTag() << " in room " << room;
			}
		}
	}

	// Unload roomes which are not needed any longer
	for (auto entity : entites.getEntities()) {
		if (entity->hasComponent<CMobile>()) { continue; }
		Vector2 entityRoom = entity->getComponent<CTransform>().roomCoordinate;

		for (auto room : roomsToUnLoad) {
			if (entityRoom == room) {
				entity->destroy();
				//std::cout << "Unloaded: " << entity->getTag() << " in room " << room;
			}
		}
	}
}

// Load a specified square at any given time. If the player cross the inner square then a new outer square will be loaded
void bx::SLoader::playerCentered() {

}

// Use certain checkpoints to load the needed entities
void bx::SLoader::checkpoints() {

}

bx::NineRooms::NineRooms(const Vector2& room) {
	rooms.push_back(room);
	rooms.push_back(Vector2(room.x, room.y - 1));
	rooms.push_back(Vector2(room.x, room.y + 1));
	rooms.push_back(Vector2(room.x - 1, room.y));
	rooms.push_back(Vector2(room.x + 1, room.y));
	rooms.push_back(Vector2(room.x - 1, room.y - 1));
	rooms.push_back(Vector2(room.x + 1, room.y - 1));
	rooms.push_back(Vector2(room.x - 1, room.y + 1));
	rooms.push_back(Vector2(room.x + 1, room.y + 1));
}

std::vector<bx::Vector2> bx::NineRooms::diffrence(const NineRooms& set) {
	std::vector<Vector2> result;
	bool intersection = false;

	if (rooms[0].x + 3 <= set.rooms[0].x) { return rooms; }
	else if (rooms[0].x - 3 >= set.rooms[0].x) { return rooms; }
	else if (rooms[0].y + 3 <= set.rooms[0].y) { return rooms; }
	else if (rooms[0].y - 3 >= set.rooms[0].y) { return rooms; }

	for (auto thisRoom : rooms) {
		for (auto setRoom : set.rooms) {
			if (thisRoom == setRoom) {
				intersection = true;
				break;
			}
		}

		if (!intersection) {
			result.push_back(thisRoom);
		}
		intersection = false;
	}
	return result;
}
