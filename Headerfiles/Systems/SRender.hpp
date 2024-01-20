#pragma once

#include <SFML/Graphics.hpp>
#include "../Common/CompositeDataTypes.hpp"
#include "../SSC/coordinates.hpp"
#include "../Assets.hpp"

namespace bx {

	enum class RenderProperty : int {
		drawTexture,
		drawHealthBar,
		drawCollision,
		drawGrid,
		drawSightLine,
		drawEditor,
		LAST
	};

	class SRender {
		std::vector<bool> properties;
		sf::RenderWindow* window = nullptr;
		sf::Text gridText;
		sf::Clock clock;

		void drawLine(const Vector2& p1, const Vector2& p2);
		void drawWithShader(EntityPointer entity, Assets& assets);
	public:
		SRender();
		SRender(sf::RenderWindow* window, sf::Font& font);

		void texture(EntityPointer entity, Assets& assets);
		void healthBar(EntityPointer entity);
		void collision(EntityPointer entity);
		void grid(const Coordinates& coordinates);
		void sightLine(EntityPointer entity);

		void setProperty(bool draw, RenderProperty property);
		bool getProperty(RenderProperty property) const;
	};
}