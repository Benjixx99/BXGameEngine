#include "../../Headerfiles/SSC/RoomManager.hpp"
#include "../Headerfiles/Common/Paths.hpp"
#include "../Headerfiles/Tools/Logger.hpp"

bx::RoomManager::RoomManager() {}

void bx::RoomManager::calculateRoom(const Vector2& playerPosition, const Vector2& windowSize) {
	preRoom = room;

	if (playerPosition.x <= windowSize.x * room.x)				{ --room.x; } // Left
	else if (playerPosition.x >= windowSize.x * (room.x + 1))	{ ++room.x; } // Right
	else if (playerPosition.y <= windowSize.y * room.y)			{ --room.y; } // Up
	else if (playerPosition.y >= windowSize.y * (room.y + 1))	{ ++room.y; } // Down
	
	if (preRoom != room) { Logger::get().log(LogLevel::Tracing, "Room: " + room.toString(), "Room", __LINE__); }
}

const bx::Vector2& bx::RoomManager::getRoom() const {
	return room;
}

const bx::Vector2& bx::RoomManager::getPreRoom() const {
	return preRoom;
}