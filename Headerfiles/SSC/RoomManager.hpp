#pragma once

#include "../Common/Vector2.hpp"

namespace bx {

	class RoomManager {
		Vector2 room { 0, 0 };
		Vector2 preRoom { 10, 10 };
	public:
		RoomManager();
		void calculateRoom(const Vector2& playerPosition, const Vector2& windowSize);
		const Vector2& getRoom() const;
		const Vector2& getPreRoom() const;
	};
}