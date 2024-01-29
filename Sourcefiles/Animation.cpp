#include "../Headerfiles/Animation.hpp"

bx::Animation::Animation() {}

bx::Animation::Animation(const std::string& name, const bx::Vector2& size) : name (name), size (size) {}

bx::Animation::Animation(const std::string& name, const bx::Vector2& size, const sf::Texture& texture) : name(name), size (size) {
	sprite.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	sprite.setTexture(texture);
}

bx::Animation::Animation(const std::string& name, const bx::Vector2& size, const sf::Texture& texture, size_t frameCount, size_t speed)
	: name(name), size (size), numberOfFrams(frameCount), speed(speed) {
	sprite.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	sprite.setTexture(texture);
}

void bx::Animation::update(bool repeat, const Vector2& viewSize) {
	if (repeat) {
		if (speed == 0) { speed = 10; }
		sprite.setTextureRect(sf::IntRect(sf::Vector2i(currentFrame / speed * viewSize.x, 0), sf::Vector2i(viewSize.x, viewSize.y)));
	}
	else {
		sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(viewSize.x, viewSize.y)));
	}

	currentFrame++;

	if (currentFrame == numberOfFrams * speed) {
		currentFrame = 0;
	}
}

bool bx::Animation::hasEnded() {
	return currentFrame == numberOfFrams * speed -1;
}

sf::Sprite& bx::Animation::getSprite() {
	return sprite;
}

const bx::Vector2& bx::Animation::getSize() const  {
	return size;
}

const std::string& bx::Animation::getName() const {
	return name;
}

void bx::Animation::setName(const std::string& newName) {
	name = newName;
}
