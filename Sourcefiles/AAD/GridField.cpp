#include "../../Headerfiles/AAD/GridField.hpp"
#include "../../Headerfiles/Data/Files/ReadIn.hpp"
#include "../../Headerfiles/Config/Config.hpp"
#include <fstream>

bx::GridField::GridField() {}

bx::GridField::GridField(const std::string& filePath, const TileConfigDataVector& tileConfigData) {
	std::ifstream file(filePath);
	ReadIn::gridFieldData(file, fieldSize);
	setGridField();

	for (auto config : tileConfigData) {
		Vector2 absoluteGridPosition((config.ROOM.x) * fieldSize.x + config.GRID.x, (config.ROOM.y) * fieldSize.y + config.GRID.y);
		setOccupied(absoluteGridPosition, config.BLOCK_MOVEMENT);
	}
}

void bx::GridField::setGridField() {
	field.resize(fieldSize.x);
	for (auto& column : field) {
		column.resize(fieldSize.y);
	}
}

void bx::GridField::setOccupied(const Vector2& gridPosition, bool occupied) {
	field[gridPosition.x][gridPosition.y].occupied = occupied;
}

bool bx::GridField::getOccupied(const Vector2& gridPosition) {
	return field[gridPosition.x][gridPosition.y].occupied;
}

const bx::Vector2 bx::GridField::getFieldSize() const {
	return fieldSize;
}