#include "../Headerfiles/Save.hpp"

bx::Save::Save(const std::string& levelName) {
	files.push_back(openFile(levelName + "_PlayerConfig.txt"));
	files.push_back(openFile(levelName + "_NPCsConfig.txt"));
	files.push_back(openFile(levelName + "_TilesConfig.txt"));
}

bx::Save::~Save() {
	for (auto& file : files) { file.close(); }
}

std::ofstream bx::Save::openFile(const std::string& fileName) {
	std::ofstream file("Levels/" + fileName, std::ios::app);
	if (!file) { 
		std::cerr << "[ERROR]: Cannot open the file " + fileName + "\n";
		openFileFailed = true;
	}
	return file;
}

void bx::Save::level(EntityManager& entities, Coordinates& coordinates) {
	if (openFileFailed) { return; }
	
	for (const auto entity : entities.getEntities()) {
		switch (entity->getComponent<CType>().type) {
		case EntityType::Player:	WriteOut::playerData(files[FileFor::Player], PlayerConfigData(entity, coordinates));	break;
		case EntityType::NPC:		WriteOut::NPCData(files[FileFor::NPCs], NPCConfigData(entity, coordinates));			break;
		case EntityType::Tile:		WriteOut::tileData(files[FileFor::Tiles], TileConfigData(entity, coordinates));			break;
		case EntityType::Weapon: break;
		case EntityType::Unknown: std::cerr << "[ERROR]: Unknown entity type!\n"; break;
		}
	}
	std::cout << "Files saved\n";
}