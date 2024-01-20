#include "../../Headerfiles/SSC/Coordinates.hpp"

bx::Coordinates::Coordinates() {}

bx::Coordinates::Coordinates(const Vector2& windowSize, GameType gameType) 
	: windowSize (windowSize), gameType (gameType) {}

bx::Vector2 bx::Coordinates::gridToMidPixelFromBottomLeft(const Vector2& size, const Vector2& gridPosition) {
	int positionX = gridPosition.x * gridSize.x + size.x / 2;
	int positionY = gridPosition.y * gridSize.y - size.y / 2;
	return Vector2(positionX, positionY);
}

bx::Vector2 bx::Coordinates::midPixelToGridFromBottomLeft(const Vector2& size, const Vector2& position) {
	int positionX = (position.x - size.x / 2) / gridSize.x;
	int positionY = (getHeight() - position.y - size.y / 2) / gridSize.y;
	return Vector2(positionX, positionY);
}

bx::Vector2 bx::Coordinates::gridToMidPixelFromTopLeft(const Vector2& size, const Vector2& gridPosition) {
	int positionX = gridPosition.x * gridSize.x + size.x / 2;
	int positionY = gridPosition.y * gridSize.y + size.y / 2;
	return Vector2(positionX, positionY);
}

bx::Vector2 bx::Coordinates::midPixelToGridFromTopLeft(const Vector2& size, const Vector2& position) {
	int positionX = (position.x - size.x / 2) / gridSize.x;
	int positionY = (position.y - size.y / 2) / gridSize.y;
	return Vector2(positionX, positionY);
}

bx::Vector2 bx::Coordinates::addRoomCoordinateToGrid(const Vector2& roomCoordinate, const Vector2& gridPosition) {
	size_t gridWidth = getWidth() / getGridSize().x, gridHeight = getHeight() / getGridSize().y;
	return Vector2(gridPosition.x + (gridWidth * roomCoordinate.x), (gridPosition.y + (gridHeight * roomCoordinate.y)));
}

bx::Vector2 bx::Coordinates::subRoomCoordinateToGrid(const Vector2& roomCoordinate, const Vector2& gridPosition) {
	Vector2 position = gridPosition;
	if (roomCoordinate.x != 0) { position.x -= getWidth() / getGridSize().x * roomCoordinate.x; }
	if (roomCoordinate.y != 0) { position.y -= getHeight() / getGridSize().y * roomCoordinate.y; }
	return position;
}


bx::Vector2 bx::Coordinates::computePosition(const Vector2& size, const Vector2& gridPosition, const Vector2& roomCoordiante) {
	Vector2 position;

	if (gameType == GameType::SideScrolling) {
		position = gridToMidPixelFromBottomLeft(size, gridPosition);
	}
	else if (gameType == GameType::TopDown) {
		position = gridToMidPixelFromTopLeft(size, addRoomCoordinateToGrid(roomCoordiante, gridPosition));
	}
	return position;
}

bx::Vector2 bx::Coordinates::computePosition(EntityPointer entity, const Vector2& gridPosition, const Vector2& roomCoordiante) {
	return computePosition(entity->getComponent<CAnimation>().animation.getSize(), gridPosition, roomCoordiante);
}

bx::Vector2 bx::Coordinates::computeGridPosition(const Vector2& size, const Vector2& position, const Vector2& roomCoordiante) {
	Vector2 gridPosition;
	if (gameType == GameType::SideScrolling) {
		gridPosition = midPixelToGridFromBottomLeft(size, position);
	}
	else if (gameType == GameType::TopDown) {
		gridPosition = subRoomCoordinateToGrid(roomCoordiante, midPixelToGridFromTopLeft(size, position));
	}
	return gridPosition;
}

bx::Vector2 bx::Coordinates::computeGridPosition(EntityPointer entity, const Vector2& position, const Vector2& roomCoordiante) {
	return computeGridPosition(entity->getComponent<CAnimation>().animation.getSize(), position, roomCoordiante);
}

bx::Vector2 bx::Coordinates::computeGridPosition(EntityPointer entity) {
	return computeGridPosition(entity->getComponent<CAnimation>().animation.getSize(), entity->getComponent<CTransform>().position, 
		entity->getComponent<CTransform>().roomCoordinate);
}


bx::Vector2 bx::Coordinates::windowToGameWorld(const Vector2& position, const Vector2& viewPosition) {
	return(Vector2(viewPosition.x - getWidth() / 2 + position.x, viewPosition.y - getHeight() / 2 + position.y));
}

const bx::Vector2& bx::Coordinates::getGridSize() const {
	return gridSize;
}

size_t bx::Coordinates::getWidth() const {
	return windowSize.x;
}

size_t bx::Coordinates::getHeight() const {
	return windowSize.y;
}
