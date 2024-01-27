#include <iostream>
#include "../Headerfiles/GameEngine.hpp"
#include "../Headerfiles/Tools/Logger.hpp"


int main(int argc, char *argv[]) {

	bx::Logger::get().setFilter("<", bx::LogLevel::Tracing);
	bx::GameEngine gameEngine(bx::GameType::TopDown);
	gameEngine.run();


	//int input;
	//std::cin >> input;

	return 0;
}