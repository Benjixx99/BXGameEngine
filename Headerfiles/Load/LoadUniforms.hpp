#pragma once 

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>

namespace bx {

	struct FloatUniform {
		std::string name;
		std::vector<float> values;
		FloatUniform() {}
		FloatUniform(const std::string& name, const std::vector<float>& values)
			: name (name), values (values) {}
	};

	struct TextureUniform {
		std::string name;
		std::string texture;
		TextureUniform() {}
		TextureUniform(const std::string& name, const std::string& texture) 
			: name (name), texture (texture) {}
	};

	using FloatUniformVector = std::vector<FloatUniform>;
	using TextureUniformVector = std::vector<TextureUniform>;

	namespace LoadUniforms {
		void loadUniforms(const std::string& configFile, FloatUniformVector& fuv);
		void loadUniforms(const std::string& configFile, TextureUniformVector& tuv);
		void loadUniforms(const std::string& configFile, FloatUniformVector& fuv, TextureUniformVector& tuv);
	}
}