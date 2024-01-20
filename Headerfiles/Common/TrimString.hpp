#pragma once

#include "PrimitiveDatatypes.hpp"
#include <string>

namespace bx {

	void trimLeft(std::string& input, const std::string& toTrim);
	void trimLeft(std::string& input);
	void trimLeft_untilAfter(std::string& input, const uchar character);

	void trimRight(std::string& input, const std::string& toTrim);
	void trimRight(std::string& input);
	void trimRight_untilAfter(std::string& input, const uchar character);
	
	void trimWhitespace(std::string& input);

	std::string trimLeft_untilAfter_Copy(std::string input, const uchar character);
	std::string trimRight_untilAfter_Copy(std::string input, const uchar character);
}