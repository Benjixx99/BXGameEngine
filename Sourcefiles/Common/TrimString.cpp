#include "../../Headerfiles/Common/TrimString.hpp"

// -------------------------------------------------------------------------------------------------------------------------- [Left-inplace]
void bx::trimLeft(std::string& input, const std::string& toTrim) {
	bool equal = false, unequal = false;
	int index = 0;

	auto it = std::find_if(input.begin(), input.end(),
		[&equal, &unequal, &index, &toTrim](uchar character) {
			if (equal) { return true; }
			if (unequal) { return false; }
			if (toTrim[index++] != character) { unequal = true; }
			if (index == toTrim.size()) { equal = true; }
			return false;
		});

	if (equal) {
		input.erase(input.begin(), it);
	}
}

void bx::trimLeft(std::string& input) {
	input.erase(input.begin(), std::find_if(input.begin(), input.end(),
		[](uchar character) { return !std::isspace(character); }));
}

void bx::trimLeft_untilAfter(std::string& input, const uchar character) {
	input.erase(0, input.find_first_of(character) + 1);
}

// -------------------------------------------------------------------------------------------------------------------------- [Right-inplace]
void bx::trimRight(std::string& input, const std::string& toTrim) {
	bool equal = false, unequal = false;
	int index = toTrim.size() - 1;

	auto it = std::find_if(input.rbegin(), input.rend(),
		[&equal, &unequal, &index, &toTrim](uchar character) {
			if (equal) { return true; }
			if (unequal) { return false; }
			if (toTrim[index] != character) { unequal = true; }
			if (index-- == 0) { equal = true; }
			return false;
		}).base();

		if (equal) {
			input.erase(it, input.end());
		}
}

void bx::trimRight(std::string& input) {
	input.erase(std::find_if(input.rbegin(), input.rend(),
		[](uchar character) { return !std::isspace(character); }).base(), input.end());
}

void bx::trimRight_untilAfter(std::string& input, const uchar character) {
	input.erase(input.find_last_of(character));
}

// -------------------------------------------------------------------------------------------------------------------------- [Both-inplace]
void bx::trimWhitespace(std::string& input) {
	trimLeft(input);
	trimRight(input);
}
// -------------------------------------------------------------------------------------------------------------------------- [Left-copy]
std::string bx::trimLeft_untilAfter_Copy(std::string input, const uchar character) {
	input.erase(0, input.find_first_of(character) + 1);
	return input;
}

// -------------------------------------------------------------------------------------------------------------------------- [Right-copy]
std::string bx::trimRight_untilAfter_Copy(std::string input, const uchar character) {
	input.erase(input.find_last_of(character));
	return input;
}

