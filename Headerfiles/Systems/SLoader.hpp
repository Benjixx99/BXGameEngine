#pragma once

#include <fstream>
#include "SState.hpp"
#include "../ECS/EntityManager.hpp"
#include "../Data/StoreConfigData.hpp"
#include "../SSC/Creation.hpp"
#include "../Assets.hpp"
#include "../Config/Config.hpp"


namespace bx {

	struct ConfigFiles {
		std::string playerConfigFile = "NONE";
		std::string NPCsConfigFile = "NONE";
		std::string tilesConfigFile = "NONE";

		ConfigFiles(const std::string& playerConfigFile, const std::string& NPCsConfigFile, const std::string& tilesConfigFile)
			: playerConfigFile (playerConfigFile), NPCsConfigFile (NPCsConfigFile), tilesConfigFile (tilesConfigFile) {}
	};

	class SLoader {
		Creation* creation = nullptr;
		SState* state = nullptr;

		void loadPlayer(std::ifstream&& file);
		void loadNPCs(std::ifstream&& file);
		void loadTiles(std::ifstream&& file);
	public:
		SLoader();
		SLoader(const ConfigFiles& configFiles, Creation* creation, SState* state);

		void allTilesAtOnce(const std::string& levelConfigFile);
		void rooms(const Vector2& room, const Vector2& preRoom, const TileConfigDataVector& tileConfigData, EntityManager& entites);
		void playerCentered();
		void checkpoints();
	};

	class NineRooms {
		std::vector<Vector2> rooms;
	public:
		NineRooms(const Vector2& room);
		std::vector<Vector2> diffrence(const NineRooms& set);
	};
}