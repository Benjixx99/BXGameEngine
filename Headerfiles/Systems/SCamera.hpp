#pragma once

#include "../Common/Vector2.hpp"
#include "../SSC/Coordinates.hpp"

namespace bx {

	class SCamera {
		sf::RenderWindow* window = nullptr;
		bool following = false;

	public:
		SCamera();
		SCamera(sf::RenderWindow* window);

		void sideScroll(EntityPointer player);
		void topDown(EntityPointer player, const Vector2& room, const Vector2& preRoom);
		void setFollowing(bool value);
		bool getFollowing() const;
	};
}