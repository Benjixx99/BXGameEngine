#include "../../Headerfiles/Tools/Shell.hpp"
#include "../../Headerfiles/Common/Paths.hpp"
#include "../../Headerfiles/Common/TrimString.hpp"
#include "../../Headerfiles/DatabaseManager.hpp"
#include "../../Headerfiles/DatabaseFunctions.hpp"

#include <iostream>

bx::Shell::Shell(ShellSharedData& sharedData) : sharedData (sharedData) {}

void bx::Shell::evaluate() {
	if (input.find("database") == 0)	{ evaluate_Database(); }
	else if (input.find("editor") == 0)		{ evaluate_Editor(); }
	else if (input.find("loader") == 0)		{ evaluate_Loader(); }
	else if (input.find("help") == 0)		{ help(); }
	else if (input.find("quit") == 0)		{ quit(); }
	else if (input == "")					{}
	else { errorUnkown("command"); }
}

void bx::Shell::help() {
	std::cout	<< "Available commands:\n\n"
				<< "database\n"
				<< "editor\n"
				<< "help\n"
				<< "loader\n"
				<< "quit\n";
}

void bx::Shell::quit() {
	isRunning = false;
}

// -------------------------------------------------------------------------------------------------------------------------- [Evaluate]
void bx::Shell::evaluate_Database() {
	trimLeft(input, "database");
	trimLeft(input);

	if (input.find("-d") == 0 || input.find("--drop") == 0)			{ evaluate_DatabaseDropTable(); }
	else if (input.find("-s") == 0 || input.find("--show") == 0)	{ evaluate_DatabaseShowTable(); }
	else if (input.find("-u") == 0 || input.find("--update") == 0)	{ evaluate_DatabaseUpadate(); }
	else if (input.find("--help") == 0 || input == "") { help_Database(); }
	else { errorUnkown("option"); }
}

void bx::Shell::evaluate_DatabaseDropTable() {
	if (input.find("-d") == 0) { trimLeft(input, "-d="); }
	else { trimLeft(input, "--drop="); }

	try {
		std::string tableName = trimRight_untilAfter_Copy(input, ' ');
		trimLeft_untilAfter(input, ' ');
		DatabaseFunctions::showTable(tableName, DatabaseManager(Paths::databases + "/" + input));
		std::cout << "Dropped table\n";
	}
	catch (const std::exception&) {
		errorNameNotSpecified("database");
	}
}

void bx::Shell::evaluate_DatabaseShowTable() {
	if (input.find("-s") == 0) { trimLeft(input, "-s="); }
	else { trimLeft(input, "--show="); }

	try {
		std::string tableName = trimRight_untilAfter_Copy(input, ' ');
		trimLeft_untilAfter(input, ' ');
		DatabaseFunctions::showTable(tableName, DatabaseManager(Paths::databases + "/" + input));
	}
	catch (const std::exception&) {
		errorNameNotSpecified("database");
	}
}

void bx::Shell::evaluate_DatabaseUpadate() {
	if (input.find("-u") == 0) { trimLeft(input, "-u"); }
	else { trimLeft(input, "--update"); }

	try {
		trimLeft(input);
		DatabaseFunctions::updateDatabase(DatabaseManager(Paths::databases + "/" + input), DatabaseType::Assets);
		std::cout << "Updated database\n";
	}
	catch (const std::exception&) {
		errorNameNotSpecified("database");
	}
}


void bx::Shell::evaluate_Editor() {
	trimLeft(input, "editor");
	trimLeft(input);

	if (input.find("-o") == 0 || input.find("--open") == 0) { sharedData.openEditor = true; }
	else if (input.find("--help") == 0 || input == "") { help_Editor(); }
	else { errorUnkown("option"); }
}


void bx::Shell::evaluate_Loader() {
	trimLeft(input, "loader");
	trimLeft(input);

	if (input.find("-c") == 0 || input.find("--change") == 0)	{ evaluate_LoaderChange(); }
	else if (input.find("-m") == 0 || input.find("--mode") == 0) { evaluate_showCurrentMode(); }
	else if (input.find("--help") == 0 || input == "")			{ help_Loader(); }
	else { errorUnkown("option"); }
}

void bx::Shell::evaluate_LoaderChange() {
	if (input.find("-c") == 0) { trimLeft(input, "-c="); }
	else { trimLeft(input, "--change="); }

	if (input.find("all") == 0) { sharedData.loadType = LoadType::AllTilesAtOnce; std::cout << "Changed to All\n"; }
	else if (input.find("rooms") == 0) { sharedData.loadType = LoadType::Rooms;  std::cout << "Changed to Rooms\n"; }
	else { errorUnkown("type"); }
}

void bx::Shell::evaluate_showCurrentMode() {
	if (input.find("-m") == 0) { trimLeft(input, "-m"); }
	else { trimLeft(input, "--mode"); }

	std::cout << "Current Mode: ";

	switch (sharedData.loadType) {
	case LoadType::Rooms:			std::cout << "Rooms\n"; break;
	case LoadType::Loaded: 
	case LoadType::AllTilesAtOnce:	std::cout << "All\n"; break;
	}
}

// -------------------------------------------------------------------------------------------------------------------------- [Help]
void bx::Shell::help_Database() {
	std::cout	<< "Usage: database [OPTION]... DATABASE\n\n"
				<< "-d, --drop=TABLE\tdelete the entire table\n"
				<< "                \tTABLE is the name of a table of the database\n"
				<< "-s, --show=TABLE\tshow the content of the table\n"
				<< "                \tTABLE is the name of a table of the database\n"
				<< "-u, --update	\tupdate the database\n"
				<< "    --help	\tdisplay this help\n";
}

void bx::Shell::help_Editor() {
	std::cout	<< "Usage: editor [OPTION]...\n\n"
				<< "-o, --open	\topen the BX Game Engine\n"
				<< "    --help	\tdisplay this help\n";
}

void bx::Shell::help_Loader() {
	std::cout	<< "Usage: loader [OPTION]...\n\n"
				<< "-c, --change=TYPE\tchange the way to laod the content\n"
				<< "-m, --mode\t\tshow the current mode of the loader\n"
				<< "                 \tTYPE is 'all' or 'rooms'\n"
				<< "    --help\t\tdisplay this help\n";
}

// -------------------------------------------------------------------------------------------------------------------------- [Error]
void bx::Shell::errorUnkown(const std::string& output) {
	std::cerr << "Unkown " << output << ": " << input << "\n";
}

void bx::Shell::errorNameNotSpecified(const std::string& output) {
	std::cerr << "Specify no " << output << " name!\n";
}

// -------------------------------------------------------------------------------------------------------------------------- [Run]
void bx::Shell::run() {
	std::cout << "BX Game Engine Shell\nType 'help' for more information.\n";

	while (isRunning) {
		std::cout << "\nBX >> ";
		std::getline(std::cin, input);
		evaluate();
	}
}
