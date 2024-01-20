#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <map>

#include "Animation.hpp"

namespace bx {

	class Assets {
		using MapTexture =		std::map<std::string, sf::Texture>;
		using MapAnimation =	std::map<std::string, Animation>;
		using MapSoundBuffer =	std::map<std::string, sf::SoundBuffer>;
		using MapFont =			std::map<std::string, sf::Font>;
		using MapShader =		std::map<std::string, sf::Shader>;

		MapTexture textures;
		MapAnimation animations;
		MapSoundBuffer soundBuffer;
		MapFont fonts;
		MapShader shaders;

	public:
		sf::Texture& getTexture(const std::string&);
		Animation& getAnimation(const std::string&);
		sf::SoundBuffer& getSoundBuffer(const std::string&);
		sf::Font& getFont(const std::string&);
		sf::Shader& getShader(const std::string&);

		void setTexture(const std::string&, const sf::Texture&);
		void setAnimation(const std::string&, const Animation&);
		void setSoundBuffer(const std::string&, const sf::SoundBuffer&);
		void setFont(const std::string&, const sf::Font&);
		void setShader(const std::string&, const std::string&);
	};
}