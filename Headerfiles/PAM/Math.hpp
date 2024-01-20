#pragma once

#include "../Common/Vector2.hpp"

namespace bx {
	namespace Math {
		double euclideanDistance(const Vector2& state, const Vector2& target) {
			return state.distance(target);
		}

		double manhattanDistance(const Vector2& state, const Vector2& target) {
			return std::abs(state.x + target.x + state.y + target.y);
		}

		double diagonalManhattanDistance(const Vector2& state, const Vector2& target) {
			Vector2 vertex(state.x, target.y);
			double tempMin = std::min(std::abs(target.x - vertex.x), std::abs(vertex.y - state.y));
			Vector2 point1(vertex.x, std::abs(vertex.y - tempMin));
			Vector2 point2(std::abs(vertex.x + tempMin), vertex.y);
			return (point1.distance(point2) + std::abs(target.x - point2.x) + std::abs(point1.y - state.y));
		}
	}
}