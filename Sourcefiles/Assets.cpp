#include "../Headerfiles/Assets.hpp"
#include "../Headerfiles/Common/Paths.hpp"
#include "../Headerfiles/Tools/Logger.hpp"

sf::Texture& bx::Assets::getTexture(const std::string& tag) {
	if (textures.find(tag) == textures.end()) {
		Logger::get().log(LogLevel::Error, "Texture '" + tag + "' not found!", __FILE__, __LINE__, Paths::logs + "/Assets.log");
	}
	return textures[tag];
}

bx::Animation& bx::Assets::getAnimation(const std::string& tag) {
	return animations[tag];
}

sf::SoundBuffer& bx::Assets::getSoundBuffer(const std::string& tag) {
	if (soundBuffer.find(tag) == soundBuffer.end()) {
		Logger::get().log(LogLevel::Error, "Sound '" + tag + "' not found!", __FILE__, __LINE__, Paths::logs + "/Assets.log");
	}
	return soundBuffer[tag];
}

sf::Font& bx::Assets::getFont(const std::string& tag) {
	if (fonts.find(tag) == fonts.end()) { 
		Logger::get().log(LogLevel::Error, "Font '" + tag + "' not found!", __FILE__, __LINE__, Paths::logs + "/Assets.log");
	}
	return fonts[tag];
}

sf::Shader& bx::Assets::getShader(const std::string& tag) {	
	if (shaders.find(tag) == shaders.end()) {
		Logger::get().log(LogLevel::Error, "Shader '" + tag + "' not found!", __FILE__, __LINE__, Paths::logs + "/Assets.log");
	}
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
		Logger::get().log(LogLevel::Error, "Shader loading failed!", __FILE__, __LINE__, Paths::logs + "/Assets.log");
		return;
	}
}
