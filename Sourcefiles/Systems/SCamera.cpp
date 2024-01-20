#include "../../Headerfiles/Systems/SCamera.hpp"
#include <SFML/Graphics.hpp>


bx::SCamera::SCamera() {}

bx::SCamera::SCamera(sf::RenderWindow* window)
	: window (window) {}

void bx::SCamera::sideScroll(EntityPointer player) {
	Vector2& position = player->getComponent<CTransform>().position;
	float windowCenterX = std::max(window->getSize().x / 2.0f, static_cast<float>(position.x));
	sf::View view = window->getView();
	view.setCenter(windowCenterX, window->getSize().y - view.getCenter().y);
	window->setView(view);
}

void bx::SCamera::topDown(EntityPointer player, const Vector2& room, const Vector2& preRoom) {
	sf::View view = window->getView();
	Vector2 playerPosition = player->getComponent<CTransform>().position;

	if (following) {
		view.setCenter(playerPosition.x, playerPosition.y);
	}
	else {
		size_t height = window->getSize().y, width = window->getSize().x;
		view.setCenter(width * (room.x + 0.5), height * (room.y + 0.5));

		if (preRoom.x - 1 == room.x)		{ view.setCenter(sf::Vector2f(width * (room.x - 0.5), height * (room.y + 0.5))); } // Left
		else if (preRoom.x + 1 == room.x)	{ view.setCenter(sf::Vector2f(width * (room.x + 1.5), height * (room.y + 0.5))); } // Right
		else if (preRoom.y - 1 == room.y)	{ view.setCenter(sf::Vector2f(width * (room.x + 0.5), height * (room.y - 0.5))); } // Up
		else if (preRoom.y + 1 == room.y)	{ view.setCenter(sf::Vector2f(width * (room.x + 0.5), height * (room.y + 1.5))); } // Down
	}
	window->setView(view);
}

void bx::SCamera::setFollowing(bool value) {
	following = value;
}

bool bx::SCamera::getFollowing() const {
	return following;
}