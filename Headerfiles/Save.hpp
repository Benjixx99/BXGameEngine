#pragma once

#include <string>
#include <fstream>

#include "Common/PrimitiveDatatypes.hpp"
#include "ECS/EntityManager.hpp"
#include "Data/Files/WriteOut.hpp"
#include "SSC/Coordinates.hpp"
#include "Config/Config.hpp"

namespace bx {

	class Save {
		enum FileFor : uchar { Player, NPCs, Tiles, };

		std::vector<std::ofstream> files;
		bool openFileFailed = false;

		std::ofstream openFile(const std::string& fileName);
	public:
		Save(const std::string& levelName);
		~Save();

		void level(EntityManager& entities, Coordinates& coordinates);
	};
}