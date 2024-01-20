#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "../Common/Vector2.hpp"
#include "../Common/CompositeDataTypes.hpp"
#include "../SSC/Coordinates.hpp"

namespace bx {

	namespace Physics {
		Vector2 getOverlap(EntityPointer, EntityPointer);
		Vector2 getPreviousOverlap(EntityPointer, EntityPointer);
		std::pair<bool, bx::Vector2> lineIntersect(const Vector2& p1, const Vector2& p2, 
			const Vector2& p3, const Vector2& p4);
		
		bool entityLineIntersect(const Vector2& p1, const Vector2& p2, EntityPointer entity);
		bool isInside(EntityPointer entity, const Vector2& position);
		bool isInside(const sf::FloatRect& rect, const Vector2& position, const Vector2& offset = (0, 0));
	}
}