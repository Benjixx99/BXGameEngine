#pragma once

#include <string>

namespace bx {

	namespace CheckIf {
		bool allCharacters_Alphabetic(const std::string& input);
		bool allCharacters_Numeric(const std::string& input);
		bool allCharacters_AlphaNumeric(const std::string& input);
		bool allCharacters_SpecialCharacters(const std::string& input);

		bool oneCharacter_Alphabetic(const std::string& input);
		bool oneCharacter_Numeric(const std::string& input);
		bool oneCharacter_AlphaNumeric(const std::string& input);
		bool oneCharacter_SpecialCharacter(const std::string& input);
	};
}