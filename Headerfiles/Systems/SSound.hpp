#pragma once

#include <deque>
#include <SFML/Audio.hpp>

namespace bx {

	class SSound {
		std::deque<sf::Sound> sounds;
	public:
		SSound();

		void pushAndPlay(sf::SoundBuffer& buffer);
		void pop();

	};
}