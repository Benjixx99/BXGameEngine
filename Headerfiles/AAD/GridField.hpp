#pragma once

#include "../Common/CompositeDataTypes.hpp"
#include "../Data/StoreConfigData.hpp"

namespace bx {

	// With this GridField it isn't possible to use negative numbers
	class GridField {

		struct Cell {
			bool occupied = false;
		};

		// The first vector is for the width
		// The second vector is for the height
		// This version needs more memory but is less complex
		using Field = std::vector<std::vector<Cell>>;

		Field field;
		Vector2 fieldSize { 1000, 1000 };

	public:
		GridField();
		GridField(const std::string& filePath, const TileConfigDataVector& tileConfigData);

		void setGridField();
		void setOccupied(const Vector2& gridPosition, bool occupied);
		bool getOccupied(const Vector2& gridPosition);
		const Vector2 getFieldSize() const;
	};
}