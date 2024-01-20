#pragma once

#include "../Common/Vector2.hpp"
#include "../Common/CompositeDataTypes.hpp"

namespace bx {

	enum class GameType : unsigned char {
		SideScrolling,
		TopDown
	};

	class Coordinates {
		GameType gameType;
		Vector2 gridSize{ 64, 64 };
		Vector2 windowSize;

		Vector2 gridToMidPixelFromBottomLeft(const Vector2& size, const Vector2& gridPosition);
		Vector2 midPixelToGridFromBottomLeft(const Vector2& size, const Vector2& position);

		Vector2 gridToMidPixelFromTopLeft(const Vector2& size, const Vector2& gridPosition);
		Vector2 midPixelToGridFromTopLeft(const Vector2& size, const Vector2& position);
		
		Vector2 addRoomCoordinateToGrid(const Vector2& roomCoordinate, const Vector2& gridPosition);
		Vector2 subRoomCoordinateToGrid(const Vector2& roomCoordinate, const Vector2& gridPosition);
	public:
		Coordinates();
		Coordinates(const Vector2& windowSize, GameType gameType);

		Vector2 computePosition(const Vector2& size, const Vector2& gridPosition, const Vector2& roomCoordiante = { 0, 0 });
		Vector2 computePosition(EntityPointer entity, const Vector2& gridPosition, const Vector2& roomCoordiante = { 0, 0 });

		Vector2 computeGridPosition(const Vector2& size, const Vector2& position, const Vector2& roomCoordiante = { 0, 0 });
		Vector2 computeGridPosition(EntityPointer entity, const Vector2& position, const Vector2& roomCoordiante = { 0, 0 });
		Vector2 computeGridPosition(EntityPointer entity);
		
		Vector2 windowToGameWorld(const Vector2& position, const Vector2& viewPosition);

		const Vector2& getGridSize() const;
		size_t getWidth() const;
		size_t getHeight() const;
	};
}