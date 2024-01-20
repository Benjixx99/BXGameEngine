#pragma once

#include <vector>
#include <string>

#include "../DatabaseManager.hpp"

namespace bx {

	// Rename it to: DataToCreateDatabase
	// Think about simplify this structure or more precisely make it more intuitive
	struct DataToCreateAssetsDatabase {
		std::vector<std::string> tableNames;
		std::vector<std::vector<std::string>> columnNamesOfTables;
		std::vector<std::vector<std::vector<std::string>>> entries;
		std::vector<std::vector<bool>> isColumnUnique;
	};

	namespace DataFromFilesystem {
		void assetsDatabaseData(DatabaseManager& assetsDatabase, DataToCreateAssetsDatabase& data);
	}
}