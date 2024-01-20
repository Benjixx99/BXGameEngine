#pragma once

#include "../DatabaseManager.hpp"
#include "../Assets.hpp"

namespace bx {

	namespace LoadAssets {
		void all(Assets& assets, DatabaseManager&& database);
		void fonts(Assets& assets, DatabaseManager&& database);
		void textures(Assets& assets, DatabaseManager&& database);
		void sounds(Assets& assets, DatabaseManager&& database);
		void shaders(Assets& assets, DatabaseManager&& database);
		void animations(Assets& assets);
	}
}