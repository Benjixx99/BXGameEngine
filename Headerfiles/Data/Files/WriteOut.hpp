#pragma once

#include <fstream>

#include "../../Config/Config.hpp"

namespace bx {

	namespace WriteOut {
		void playerData(std::ofstream& file, const PlayerConfigData&& config);
		void NPCData(std::ofstream& file, const NPCConfigData&& config);
		void tileData(std::ofstream& file, const TileConfigData&& config);
	}
}