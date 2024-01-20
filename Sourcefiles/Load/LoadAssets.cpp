#include "../../Headerfiles/Load/LoadAssets.hpp"
#include "../../Headerfiles/Config/Config.hpp"
#include "../../Headerfiles/Common/Paths.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

void bx::LoadAssets::all(Assets& assets, DatabaseManager&& database) {
	fonts(assets, std::move(database));
	textures(assets, std::move(database));
	sounds(assets, std::move(database));
	shaders(assets, std::move(database));
	animations(assets);
}

void bx::LoadAssets::fonts(Assets& assets, DatabaseManager&& database) {
	for (const auto& entry : database.selectAllEntriesFrom("Fonts")) {
		sf::Font font;
		if (!font.loadFromFile(entry[1])) {
			std::cerr << "[ERROR]: Loading the font wasn't successful!\n";
		}
		assets.setFont(entry[0], font);
	}
}

void bx::LoadAssets::textures(Assets& assets, DatabaseManager&& database) {
	for (const auto& entry : database.selectAllEntriesFrom("Textures")) {
		sf::Texture texture;
		if (!texture.loadFromFile(entry[1])) {
			std::cerr << "[ERROR]: Loading the texture wasn't successful!\n";
		}
		texture.setSmooth(true);
		assets.setTexture(entry[0], texture);
	}
}

void bx::LoadAssets::sounds(Assets& assets, DatabaseManager&& database) {
	for (const auto& entry : database.selectAllEntriesFrom("Sounds")) {
		sf::SoundBuffer soundBuffer;
		if (!soundBuffer.loadFromFile(entry[1])) {
			std::cerr << "[ERROR]: Loading the sound wasn't successful!\n";
		}
		assets.setSoundBuffer(entry[0], soundBuffer);
	}
}

void bx::LoadAssets::shaders(Assets& assets, DatabaseManager&& database) {
	for (const auto& entry : database.selectAllEntriesFrom("Shaders")) {
		assets.setShader(entry[0], entry[1]);
	}
}

void bx::LoadAssets::animations(Assets& assets) {
	std::string name;
	size_t numberOfFrams, animationSpeed;
	std::ifstream file(Paths::assetsConfigFiles + "/animationsConfig.txt");

	while (file >> name) {
		file >> numberOfFrams >> animationSpeed;
		Vector2 animationSize(assets.getTexture(name).getSize());
		assets.setAnimation(name, Animation(name, Vector2(64, 64), assets.getTexture(name), numberOfFrams, animationSpeed));
	}
}
