#include "../Headerfiles/Config/Config.hpp"

std::ifstream& operator>> (std::ifstream& file, bx::NPCBehaviorType& type) {
	int behaviorType;
	file >> behaviorType;
	type = static_cast<bx::NPCBehaviorType>(behaviorType);
	return file;
}

std::ofstream& operator<< (std::ofstream& file, const bx::NPCBehaviorType& type) {
	int behaviorType = static_cast<int>(type);
	file << behaviorType;
	return file;
}