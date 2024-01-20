#pragma once

#include <fstream>
#include "../Config/Config.hpp"

namespace bx {

	using TileConfigDataVector = std::vector<TileConfigData>;

	class StoreConfigData {
		TileConfigDataVector tileConfigData;
		
	public:
		StoreConfigData();
		void setTileConfigData(const std::string& filePath);
		const TileConfigDataVector& getTileConfigData() const;
	};
}