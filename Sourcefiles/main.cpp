#include <iostream>
#include "../Headerfiles/GameEngine.hpp"

int main(int argc, char *argv[]) {

	bx::GameEngine gameEngine(bx::GameType::TopDown);
	gameEngine.run();

	//int input;
	//std::cin >> input;

	return 0;
}