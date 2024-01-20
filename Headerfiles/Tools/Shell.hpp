#pragma once

#include "../SharedDataStructure.hpp"

#include <string>

namespace bx {

	class Shell {
		std::string input;
		bool isRunning = true;
		ShellSharedData& sharedData;
	
		void evaluate();
		void help();
		void quit();

		void evaluate_Database();
		void evaluate_DatabaseDropTable();
		void evaluate_DatabaseShowTable();
		void evaluate_DatabaseUpadate();

		void evaluate_Editor();
		
		void evaluate_Loader();
		void evaluate_LoaderChange();
		void evaluate_showCurrentMode();

		void help_Database();
		void help_Editor();
		void help_Loader();

		void errorUnkown(const std::string& output);
		void errorNameNotSpecified(const std::string& output);
	public:
		Shell(ShellSharedData& sharedData);
		void run();
	};
}