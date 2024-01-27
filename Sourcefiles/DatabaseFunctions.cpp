#include "../Headerfiles/DatabaseFunctions.hpp"
#include "../Headerfiles/Common/Paths.hpp"
#include "../Headerfiles/Tools/Logger.hpp"

using namespace bx;
void typeToCreate(DatabaseManager& database, DataToCreateAssetsDatabase& data, const DatabaseType type) {
	switch (type) {
	case DatabaseType::Assets: DataFromFilesystem::assetsDatabaseData(database, data); break;
	default:
		Logger::get().log(LogLevel::Warning, "Unknown database type!", __FILE__, __LINE__, Paths::logs + "/Database.log");
		break;
	}
}

bx::DatabaseManager&& bx::DatabaseFunctions::createDatabase(DatabaseManager&& database, const DatabaseType type) {
	DataToCreateAssetsDatabase data;
	typeToCreate(database, data, type);

	for (int i = 0; i < data.tableNames.size(); ++i) {
		database.createTable(data.tableNames[i], data.columnNamesOfTables[i], data.isColumnUnique[i]);
	}

	for (int i = 0; i < data.entries.size(); ++i) {
		database.insertEntries(data.tableNames[i], data.entries[i]);
	}

	return std::move(database);
}

DatabaseManager&& bx::DatabaseFunctions::updateDatabase(DatabaseManager&& database, const DatabaseType type) {
	DataToCreateAssetsDatabase data;
	typeToCreate(database, data, type);

	for (int i = 0; i < data.entries.size(); ++i) {
		for (int j = 0; j < data.entries[i].size(); ++j) {
			database.insertEntry(data.tableNames[i], data.entries[i][j]);
		}
	}

	return std::move(database);
}

void bx::DatabaseFunctions::showTable(const std::string& tableName, DatabaseManager&& database) {
	for (const auto& row : database.selectAllEntriesFrom(tableName)) {
		for (const auto& entry : row) {
			std::cout << entry << "\t";
		}
		std::cout << "\n";
	}
}

void bx::DatabaseFunctions::dropTable(const std::string& tableName, DatabaseManager&& database) {
	database.dropTable(tableName);
}
