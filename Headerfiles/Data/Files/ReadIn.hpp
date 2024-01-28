#pragma once

#include <fstream>
#include "../../Config/AnimationConfig.hpp"
#include "../../Config/Config.hpp"
#include "../../Config/MenuConfig.hpp"
#include "../../Load/LoadUniforms.hpp"

namespace bx {

	using VectorStringPair = std::vector<std::pair<std::string, std::string>>;

	namespace ReadIn {
		PlayerConfigData& playerData(std::ifstream& file, PlayerConfigData& playerConfig);
		NPCConfigData& NPCData(std::ifstream& file, NPCConfigData& enemyConfig);
		TileConfigData& tileData(std::ifstream& file, TileConfigData& tileConfig);
		Vector2& gridFieldData(std::ifstream& file, Vector2& size);
		void floatUniformData(std::ifstream& file, FloatUniformVector& fuv);
		void textureUniformData(std::ifstream& file, TextureUniformVector& tuv);
		void menuData(std::ifstream& file, MenuConfigData& menu);
		void animationsData(std::ifstream& file, std::vector<AnimationConfigData>& animationsConfig);
		void keyboardLayout(std::ifstream& file, VectorStringPair& keyActionPairs);
	}
}