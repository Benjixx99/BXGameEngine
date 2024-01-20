#include "../../Headerfiles/Systems/SSound.hpp"

bx::SSound::SSound() {}

void bx::SSound::pushAndPlay(sf::SoundBuffer& buffer) {
	sounds.push_front(sf::Sound(buffer));
	sounds.front().play();
}

void bx::SSound::pop() {
	if (!sounds.empty() && sounds.back().getStatus() == sf::Sound::Status::Stopped) {
		sounds.pop_back();
	}
}