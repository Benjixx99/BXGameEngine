#include "../Headerfiles/DatabaseManager.hpp"
#include "../Headerfiles/Common/Paths.hpp"
#include "../Headerfiles/Tools/Logger.hpp"


bx::DatabaseManager::DatabaseManager() {}

bx::DatabaseManager::DatabaseManager(const std::string& databaseName) : databaseName (databaseName) {}

void bx::DatabaseManager::open() {
	if (sqlite3_open(databaseName.c_str(), &database)) {
		Logger::get().log(LogLevel::Warning, "Opening database wasn't successful!", __FILE__, __LINE__, Paths::logs + "/Database.log");
		return;
	}
	output.entries.clear();
	output.entry.clear();
	output.value.clear();
}

void bx::DatabaseManager::close() {
	sqlite3_close(database);
}

void bx::DatabaseManager::execute(const std::string& SQL, const std::string action, int (*callback)(void*, int, char**, char**)) {
	open();
	char* errorMessage;
	if (sqlite3_exec(database, SQL.c_str(), callback, this, &errorMessage)) {
		std::string message =  action + " wasn't successful! " + errorMessage;
		Logger::get().log(LogLevel::Warning, message, __FILE__, __LINE__, Paths::logs + "/Database.log");
		//std::cerr << "SQL: " << SQL << "\n";
		sqlite3_free(errorMessage);
	}
	else {
		Logger::get().log(LogLevel::Info, action + " was successful", __FILE__, __LINE__, Paths::logs + "/Database.log");
	}
	close();
}


int bx::DatabaseManager::callbackGetEntries(int numberOfColumns, char** columnValues, char** columnNames) {
	std::vector<std::string> row;
	for (int i = 0; i < numberOfColumns; ++i) {
		row.push_back((columnValues[i]) ? columnValues[i] : "NULL");
	}
	output.entries.push_back(row);
	return 0;
}

int bx::DatabaseManager::callbackGetEntry(int numberOfColumns, char** columnValues) {
	for (int i = 0; i < numberOfColumns; ++i) {
		output.entry.push_back((columnValues[i]) ? columnValues[i] : "NULL");
	}
	return 0;
}

int bx::DatabaseManager::callbackGetColumnValue(char** columnValues) {
	output.value = (columnValues[0]) ? columnValues[0] : "NULL";
	return 0;
}


void bx::DatabaseManager::getColumnNames(const std::string& tableName) {
	std::string SQL = "SELECT name FROM pragma_table_info('" + tableName + "');";
	execute(SQL, "SELECT FROM", c_callbackGetEntry);
}

void bx::DatabaseManager::setColumnNamesForQuery(const std::string& tableName, std::string& SQL) {
	getColumnNames(tableName);
	SQL = "INSERT INTO " + tableName + " (";
	for (int i = 0; i < output.entry.size(); ++i) {
		SQL += (i != output.entry.size() - 1) ? "'" + output.entry[i] + "'," : "'" + output.entry[i] + "') VALUES (";
	}
}


void bx::DatabaseManager::createTable(const std::string& tableName, const std::vector<std::string>& columnNames) {
	std::string SQL =	"CREATE TABLE " + tableName + " (";
	for (int i = 0; i < columnNames.size(); ++i) {
		SQL += (i != columnNames.size() - 1) ? "'" + columnNames[i] + "' TEXT NOT NULL, " : "'" + columnNames[i] + "' TEXT NOT NULL);";
	}
	execute(SQL, ("CREATE TABLE " + tableName));
}

void bx::DatabaseManager::createTable(const std::string& tableName, const std::vector<std::string>& columnNames, const std::vector<bool>& isColumnUnique) {
	std::string SQL = "CREATE TABLE " + tableName + " (";
	for (int i = 0; i < columnNames.size(); ++i) {
		SQL += "'" + columnNames[i] + "' TEXT NOT NULL ";
		SQL += (isColumnUnique[i]) ? "UNIQUE" : "";
		SQL += (i != columnNames.size() - 1) ? ", " : ");";
	}
	execute(SQL, ("CREATE TABLE with UNIQUE " + tableName));
}

void bx::DatabaseManager::dropTable(const std::string& tableName) {
	execute(("DROP TABLE " + tableName + ";"), ("DROP TABLE " + tableName));
}

void bx::DatabaseManager::insertEntry(const std::string& tableName, const std::vector<std::string>& columnValues)  {
	std::string SQL;
	setColumnNamesForQuery(tableName, SQL);

	for (int i = 0; i < columnValues.size(); ++i) {
		SQL += (i != columnValues.size() - 1) ? "'" + columnValues[i] + "'," : "'" + columnValues[i] + "');";
	}
	execute(SQL, ("INSERT ENTRY INTO " + tableName));
}

void bx::DatabaseManager::insertEntries(const std::string& tableName, const std::vector<std::vector<std::string>>& rows) {
	std::string SQL;
	setColumnNamesForQuery(tableName, SQL);

	for (int i = 0; i < rows.size(); ++i) {
		std::vector<std::string> columnValues = rows[i];
		for (int j = 0; j < columnValues.size(); ++j) {
			SQL += (j != columnValues.size() - 1) ? "'" + columnValues[j] + "'," : "'" + columnValues[j] + "')";
		}
		SQL += (i != rows.size() - 1) ? ",(" : ";";
	}
	execute(SQL, ("INSERT ENTRIES INTO " + tableName));
}

void bx::DatabaseManager::deleteEntryByID(const std::string& tableName, const std::string& ID) {
	execute(("DELETE FROM " + tableName + " WHERE ROWID = " + ID + ";"), ("DELETE ENTRY WITH ID: " + ID));
}

void bx::DatabaseManager::deleteAllEntriesFrom(const std::string& tableName) {
	execute(("DELETE FROM " + tableName + ";"), ("DELETE ENTIRES FROM " + tableName));
}

const std::vector<std::vector<std::string>>& bx::DatabaseManager::selectAllEntriesFrom(const std::string& tableName) {
	execute(("SELECT * FROM " + tableName + ";"), ("SELECT FROM " + tableName), c_callbackGetEntries);
	return output.entries;
}

const std::string& bx::DatabaseManager::selectFromWhereIsEqual(const std::string& tableName, const std::string& columnName, const std::string& ColumnValue) {
	std::string SQL = "SELECT " + columnName + " FROM " + tableName + " WHERE " + columnName + " = '" + ColumnValue + "';";
	execute(SQL, ("SELECT FROM " + tableName + " WHERE"), c_callbackGetValue);
	return output.value;
}


void bx::DatabaseManager::customSQLQueryWithNoOutput(const std::string& SQL) {
	execute(SQL, "Custom SQL Query");
}

const std::vector<std::vector<std::string>>& bx::DatabaseManager::customSQLQueryWithEntriesOutput(const std::string& SQL) {
	execute(SQL, "Custom SQL Query", c_callbackGetEntries);
	return output.entries;
}

const std::vector<std::string>& bx::DatabaseManager::customSQLQueryWithEntryOutput(const std::string& SQL) {
	execute(SQL, "Custom SQL Query", c_callbackGetEntry);
	return output.entry;
}

const std::string& bx::DatabaseManager::customSQLQueryWithValueOutput(const std::string& SQL) {
	execute(SQL, "Custom SQL Query", c_callbackGetValue);
	return output.value;
}


void bx::DatabaseManager::setDatabaseName(const std::string& name) {
	databaseName = name;
}

const std::string& bx::DatabaseManager::getDatabaseName() const {
	return databaseName;
}


int bx::c_callbackGetEntries(void* data, int numberOfColumns, char** columnValues, char** columnNames) {
	bx::DatabaseManager* databaseManager = reinterpret_cast<bx::DatabaseManager*>(data);
	return databaseManager->callbackGetEntries(numberOfColumns, columnValues, columnNames);
}

int bx::c_callbackGetEntry(void* data, int numberOfColumns, char** columnValues, char** columnNames) {
	bx::DatabaseManager* databaseManager = reinterpret_cast<bx::DatabaseManager*>(data);
	return databaseManager->callbackGetEntry(numberOfColumns, columnValues);
}

int bx::c_callbackGetValue(void* data, int numberOfColumns, char** columnValues, char** columnNames) {
	bx::DatabaseManager* databaseManager = reinterpret_cast<bx::DatabaseManager*>(data);
	return databaseManager->callbackGetColumnValue(columnValues);
}
