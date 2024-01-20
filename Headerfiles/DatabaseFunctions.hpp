#pragma once

#include "Common/PrimitiveDatatypes.hpp"
#include "Data/DataFromFilesystem.hpp"
#include "DatabaseManager.hpp"

#include <string>

namespace bx {

	enum class DatabaseType : uchar {
		Assets,
		Configfiles	// Just an example
	};

	namespace DatabaseFunctions {
		DatabaseManager&& createDatabase(DatabaseManager&& database, const DatabaseType type);
		DatabaseManager&& updateDatabase(DatabaseManager&& database, const DatabaseType type);
		void showTable(const std::string& tableName, DatabaseManager&& database);
		void dropTable(const std::string& tableName, DatabaseManager&& database);
	}
}