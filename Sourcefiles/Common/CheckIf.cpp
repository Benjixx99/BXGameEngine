#include "../../Headerfiles/Common/CheckIf.hpp"

bool bx::CheckIf::allCharacters_Alphabetic(const std::string& input) {
	for (char character : input) {
		if (!(character >= 'a' && character <= 'z' || character >= 'A' && character <= 'Z')) {
			return false;
		}
	}
	return true;
}

bool bx::CheckIf::allCharacters_Numeric(const std::string& input) {
	for (char character : input) {
		if (!(character >= '0' && character <= '9')) {
			return false;
		}
	}
	return true;
}

bool bx::CheckIf::allCharacters_AlphaNumeric(const std::string& input) {
	for (char character : input) {
		if (!(character >= 'a' && character <= 'z' || character >= 'A' && character <= 'Z' || character >= '0' && character <= '9')) {
			return false;
		}
	}
	return true;
}

bool bx::CheckIf::allCharacters_SpecialCharacters(const std::string& input) {
	for (char character : input) {
		if (!(character >= '!' && character <= '/' || character >= ':' && character <= '@' || 
			character >= '[' && character <= '`' || character >= '{' && character <= '~')) {
			return false;
		}
	}
	return true;
}

bool bx::CheckIf::oneCharacter_Alphabetic(const std::string& input) {
	for (char character : input) {
		if (character >= 'a' && character <= 'z' || character >= 'A' && character <= 'Z') {
			return true;
		}
	}
	return false;
}

bool bx::CheckIf::oneCharacter_Numeric(const std::string& input) {
	for (char character : input) {
		if (character >= '0' && character <= '9') {
			return true;
		}
	}
	return false;
}

bool bx::CheckIf::oneCharacter_AlphaNumeric(const std::string& input) {
	for (char character : input) {
		if (character >= 'a' && character <= 'z' || character >= 'A' && character <= 'Z' || character >= '0' && character <= '9') {
			return true;
		}
	}
	return false;
}

bool bx::CheckIf::oneCharacter_SpecialCharacter(const std::string& input) {
	for (char character : input) {
		if (character >= '!' && character <= '/' || character >= ':' && character <= '@' ||
			character >= '[' && character <= '`' || character >= '{' && character <= '~') {
			return true;
		}
	}
	return false;
}
