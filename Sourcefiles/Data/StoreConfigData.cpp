#include "../../Headerfiles/Data/StoreConfigData.hpp"
#include "../../Headerfiles/Data/Files/ReadIn.hpp"

bx::StoreConfigData::StoreConfigData() {}

void bx::StoreConfigData::setTileConfigData(const std::string& filePath) {
	std::string command;
	std::ifstream file(filePath);

	while (file >> command) {
		TileConfigData tileConfig;
		tileConfigData.push_back(ReadIn::tileData(file, tileConfig));
	}
}

const bx::TileConfigDataVector& bx::StoreConfigData::getTileConfigData() const {
	return tileConfigData;
}
