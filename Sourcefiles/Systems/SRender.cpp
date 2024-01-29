#include "../../Headerfiles/Systems/SRender.hpp"

bx::SRender::SRender() {}

bx::SRender::SRender(sf::RenderWindow* window, sf::Font& font) : window (window) {
	properties.resize(static_cast<int>(RenderProperty::LAST));
	for (auto p : properties) { p = false; }
	setProperty(true, RenderProperty::drawTexture);
	setProperty(true, RenderProperty::drawHealthBar);

	gridText.setFont(font);
	gridText.setCharacterSize(14);
	gridText.setFillColor(sf::Color::White);

	clock.restart();
}

void bx::SRender::drawLine(const Vector2& p1, const Vector2& p2) {
	sf::Vertex line[2] = { sf::Vertex(sf::Vector2f(p1.x, p1.y)), sf::Vertex(sf::Vector2f(p2.x, p2.y)) };
	window->draw(line, 2, sf::Lines);
}

void bx::SRender::drawWithShader(EntityPointer entity, Assets& assets) {
	sf::Shader& shader = assets.getShader(entity->getComponent<CShader>().name);
	Vector2 entityPosition = entity->getComponent<CTransform>().position;

	shader.setUniform("u_resolution", sf::Glsl::Vec2(entityPosition.x, entityPosition.y));
	shader.setUniform("u_time", clock.getElapsedTime().asSeconds());
	
	for (auto u : entity->getComponent<CShader>().floatUniforms) {
		if (u.values.size() == 1)	{ shader.setUniform(u.name, u.values[0]); }
		else if (u.values.size() == 2) { shader.setUniform(u.name, sf::Glsl::Vec2(u.values[0], u.values[1])); }
		else if (u.values.size() == 3) { shader.setUniform(u.name, sf::Glsl::Vec3(u.values[0], u.values[1], u.values[2])); }
		else if (u.values.size() == 4) { shader.setUniform(u.name, sf::Glsl::Vec4(u.values[0], u.values[1], u.values[2], u.values[3])); }
	}

	for (auto u : entity->getComponent<CShader>().textureUniforms) {
		shader.setUniform(u.name, assets.getTexture(u.texture));
	}

	window->draw(entity->getComponent<CAnimation>().animation.getSprite(), &shader);
}

void bx::SRender::texture(EntityPointer entity, Assets& assets) {

	if (entity->hasComponent<CAnimation>()) {
		auto& transform = entity->getComponent<CTransform>();
		auto& animation = entity->getComponent<CAnimation>().animation;
		animation.getSprite().setPosition(transform.position.x, transform.position.y);
		animation.getSprite().setScale(transform.scale.x, transform.scale.y);
		
		sf::Color color = animation.getSprite().getColor();
		color.a = (entity->getTag() == "Player" && entity->hasComponent<CInvincibility>()) ? 20 : 255;
		animation.getSprite().setColor(color);

		if (entity->hasComponent<CShader>())	{ drawWithShader(entity, assets); }
		else									{ window->draw(animation.getSprite()); }
		
		if (entity->getTag() == "Player") {
			if (entity->hasComponent<CShader>()) { window->draw(animation.getSprite(), &assets.getShader(entity->getComponent<CShader>().name)); }
			else { window->draw(animation.getSprite()); }
		}
	}
}

void bx::SRender::healthBar(EntityPointer entity) {
	if (!entity->hasComponent<CHealth>()) { return; }

	sf::RectangleShape rect;
	Vector2 entitySize = entity->getComponent<CBoundingBox>().size;
	Vector2 entityPosition = entity->getComponent<CTransform>().position - entitySize / 2;
	int maxCells = entity->getComponent<CHealth>().max;
	int barWidth = 100, barheight = 10, distanceToEntity = 30;

	for (int cell = 0; cell < maxCells; ++cell) {
		rect.setSize(sf::Vector2f(barWidth / maxCells, barheight));
		rect.setOutlineThickness(2);
		rect.setOutlineColor(sf::Color::Black);
		rect.setPosition(sf::Vector2f((entityPosition.x + ((barWidth / maxCells) * cell) - ((barWidth - entitySize.x) / 2)),
			entityPosition.y - distanceToEntity));
		rect.setFillColor((cell >= entity->getComponent<CHealth>().current ?
			sf::Color::Red : sf::Color::Green));

		window->draw(rect);
	}
}

void bx::SRender::collision(EntityPointer entity) {
	if (entity->hasComponent<CBoundingBox>()) {

		auto& box = entity->getComponent<CBoundingBox>();
		auto& transform = entity->getComponent<CTransform>();
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(box.size.x - 1, box.size.y - 1));
		rect.setOrigin(sf::Vector2f(box.halfSize.x, box.halfSize.y));
		rect.setPosition(transform.position.x, transform.position.y);
		rect.setFillColor(sf::Color(0, 0, 0, 0));

		if (box.blockMovement && box.blockVision) {
			rect.setOutlineColor(sf::Color(44, 110, 59));
		}
		else if (box.blockMovement) {
			rect.setOutlineColor(sf::Color(0, 0, 172));
		}
		else if (box.blockVision) {
			rect.setOutlineColor(sf::Color(104, 194, 188));
		}
		else {
			rect.setOutlineColor(sf::Color(200, 0, 0));
		}

		rect.setOutlineThickness(4);

		if (entity->getTag() == "Player" && entity->hasComponent<CInvincibility>()) {
			rect.setOutlineColor(sf::Color(0, 0, 220));
			rect.setOutlineThickness(6);
		}

		window->draw(rect);
	}
}

// Work on the grid system
void bx::SRender::grid(const Coordinates& coordinates) {
	float leftX = window->getView().getCenter().x - coordinates.getWidth() - 2;
	float rightX = leftX + coordinates.getWidth() + coordinates.getGridSize().x + coordinates.getWidth() / 2;
	float nextGridX = leftX - ((int)leftX % (int)coordinates.getGridSize().x);

	for (float x = nextGridX; x < rightX; x += coordinates.getGridSize().x) {
		drawLine(Vector2(x, 0), Vector2(x, coordinates.getHeight()));
	}

	for (float y = 0; y < coordinates.getHeight(); y += coordinates.getGridSize().y) {
		drawLine(Vector2(leftX, coordinates.getHeight() - y), Vector2(rightX, coordinates.getHeight() - y));

		for (float x = nextGridX; x < rightX; x += coordinates.getGridSize().x) {
			std::string xCell = std::to_string((int)x / (int)coordinates.getGridSize().x);
			std::string yCell = std::to_string((int)y / (int)coordinates.getGridSize().y);
			gridText.setString("(" + xCell + "," + yCell + ")");
			gridText.setPosition(x + 3, y + 2);
			gridText.setFillColor(sf::Color::Black);
			window->draw(gridText);
		}
	}
}

void bx::SRender::sightLine(EntityPointer entity) {
	if (!entity->hasComponent<CFollowPrimitive>()) { return; }
	drawLine(entity->getComponent<CTransform>().position,
		entity->getComponent<CFollowPrimitive>().targetEntity->getComponent<CTransform>().position);
}

void bx::SRender::setProperty(bool draw, RenderProperty property) {
	properties[static_cast<int>(property)] = draw;
}

bool bx::SRender::getProperty(RenderProperty property) const {
	return properties[static_cast<int>(property)];
}