#include "../../Headerfiles/SSC/RoomManager.hpp"

bx::RoomManager::RoomManager() {}

void bx::RoomManager::calculateRoom(const Vector2& playerPosition, const Vector2& windowSize) {
	preRoom = room;

	if (playerPosition.x <= windowSize.x * room.x)				{ --room.x; std::cout << "Room:	" << room; } // Left
	else if (playerPosition.x >= windowSize.x * (room.x + 1))	{ ++room.x; std::cout << "Room:	" << room; } // Right
	else if (playerPosition.y <= windowSize.y * room.y)			{ --room.y; std::cout << "Room:	" << room; } // Up
	else if (playerPosition.y >= windowSize.y * (room.y + 1))	{ ++room.y; std::cout << "Room:	" << room; } // Down
}

const bx::Vector2& bx::RoomManager::getRoom() const {
	return room;
}

const bx::Vector2& bx::RoomManager::getPreRoom() const {
	return preRoom;
}