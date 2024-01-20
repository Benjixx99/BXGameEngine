#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>

namespace bx {
	
	static int c_callbackGetEntries(void* data, int numberOfColumns, char** columnValues, char** columnNames);
	static int c_callbackGetEntry(void* data, int numberOfColumns, char** columnValues, char** columnNames);
	static int c_callbackGetValue(void* data, int numberOfColumns, char** columnValues, char** columnNames);

	struct SQLOutput {
		std::vector<std::vector<std::string>> entries;
		std::vector<std::string> entry;
		std::string value = "";
	};

	class DatabaseManager {
		
		friend static int c_callbackGetEntries(void*, int, char**, char**);
		friend static int c_callbackGetEntry(void*, int, char**, char**);
		friend static int c_callbackGetValue(void*, int, char**, char**);

		sqlite3* database = nullptr;
		std::string databaseName = "";
		SQLOutput output;

		void open();
		void close();
		void execute(const std::string& SQL, const std::string action = "", 
			int (*callback)(void*, int, char**, char**) = nullptr);

		int callbackGetEntries(int numberOfColumns, char** columnValues, char** columnNames);
		int callbackGetEntry(int numberOfColumns, char** columnValues);
		int callbackGetColumnValue(char** columnValues);

		void getColumnNames(const std::string& tableName);
		void setColumnNamesForQuery(const std::string& tableName, std::string& SQL);
	public:
		DatabaseManager();
		DatabaseManager(const std::string& databaseName);

		void createTable(const std::string& tableName, const std::vector<std::string>& columnNames);
		void createTable(const std::string& tableName, const std::vector<std::string>& columnNames, 
			const std::vector<bool>& isColumnUnique);
		void dropTable(const std::string& tableName);

		void insertEntry(const std::string& tableName, const std::vector<std::string>& columnValues);
		void insertEntries(const std::string& tableName, const std::vector<std::vector<std::string>>& rows);
		void deleteEntryByID(const std::string& tableName, const std::string& ID);
		void deleteAllEntriesFrom(const std::string& tableName);

		const std::vector<std::vector<std::string>>& selectAllEntriesFrom(const std::string& tableName);
		const std::string& selectFromWhereIsEqual(const std::string& tableName, 
			const std::string& columnName, const std::string& ColumnValue);

		void customSQLQueryWithNoOutput(const std::string& SQL);
		const std::vector<std::vector<std::string>>& customSQLQueryWithEntriesOutput(const std::string& SQL);
		const std::vector<std::string>& customSQLQueryWithEntryOutput(const std::string& SQL);
		const std::string& customSQLQueryWithValueOutput(const std::string& SQL);

		void setDatabaseName(const std::string& name);
		const std::string& getDatabaseName() const;
	};
}