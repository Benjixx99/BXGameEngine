#include <iostream>
#include "../Headerfiles/GameEngine.hpp"
#include "../Headerfiles/Tools/Logger.hpp"
#include "../Headerfiles/Common/Paths.hpp"


int main(int argc, char *argv[]) {

	bx::Logger::get().setFilter(">", bx::LogLevel::Debugging);
	bx::GameEngine gameEngine(bx::GameType::TopDown);
	gameEngine.run();

	
	//int input;
	//std::cin >> input;

	return 0;
}