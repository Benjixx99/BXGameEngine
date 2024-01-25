#include "../../Headerfiles/Load/LoadUniforms.hpp"
#include "../../Headerfiles/Data/Files/ReadIn.hpp"
#include <fstream>

void bx::LoadUniforms::loadUniforms(const std::string& configFile, FloatUniformVector& fuv) {
	std::ifstream file(configFile);
	ReadIn::floatUniformData(file, fuv);
}

void bx::LoadUniforms::loadUniforms(const std::string& configFile, TextureUniformVector& tuv) {
	std::ifstream file(configFile);
	ReadIn::textureUniformData(file, tuv);
}

void bx::LoadUniforms::loadUniforms(const std::string& configFile, FloatUniformVector& fuv, TextureUniformVector& tuv) {
	std::ifstream file(configFile);
	ReadIn::floatUniformData(file, fuv);
	file.seekg(0, std::ios::beg);
	ReadIn::textureUniformData(file, tuv);
}