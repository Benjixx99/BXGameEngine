#include "../Headerfiles/Assets.hpp"

sf::Texture& bx::Assets::getTexture(const std::string& tag) {
	if (textures.find(tag) == textures.end()) { std::cerr << "[ERROR]: Texture '" << tag << "' not found in Assets!\n"; }
	return textures[tag];
}

bx::Animation& bx::Assets::getAnimation(const std::string& tag) {
	return animations[tag];
}

sf::SoundBuffer& bx::Assets::getSoundBuffer(const std::string& tag) {
	if (soundBuffer.find(tag) == soundBuffer.end()) { std::cerr << "[ERROR]: Sound '" << tag << "' not found in Assets!\n"; }
	return soundBuffer[tag];
}

sf::Font& bx::Assets::getFont(const std::string& tag) {
	if (fonts.find(tag) == fonts.end()) { std::cerr << "[ERROR]: Font '" << tag << "' not found in Assets!\n"; }
	return fonts[tag];
}

sf::Shader& bx::Assets::getShader(const std::string& tag) {	
	if (shaders.find(tag) == shaders.end()) { std::cerr << "[ERROR]: Shader '" << tag << "' not found in Assets!\n"; }
	return shaders[tag];
}

void bx::Assets::setTexture(const std::string& name, const sf::Texture& texture) {
	textures[name] = texture;
}

void bx::Assets::setAnimation(const std::string& name, const Animation& animation) {
	animations[name] = animation;
}

void bx::Assets::setSoundBuffer(const std::string& name, const sf::SoundBuffer& soundbuffer) {
	soundBuffer[name] = soundbuffer;
}

void bx::Assets::setFont(const std::string& name, const sf::Font& font) {
	fonts[name] = font;
}

void bx::Assets::setShader(const std::string& name, const std::string& filePath) {
	if (!shaders[name].loadFromFile(filePath, sf::Shader::Fragment)) {
		std::cerr << "[ERROR]: Something went wrong with loading a shader from a file!\n";
		return;
	}
}
