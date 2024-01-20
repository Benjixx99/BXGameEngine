#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include "Common/Vector2.hpp"

namespace bx {

	class Animation {
		sf::Sprite sprite;
		std::string name = "NONE";
		Vector2 size { 0, 0 };
		size_t numberOfFrams = 0;
		size_t speed = 1;
		int currentFrame = 0;
		
	public:
		Animation();
		Animation(const std::string& name, const bx::Vector2& size);
		Animation(const std::string& name, const bx::Vector2& size, const sf::Texture& texture);
		Animation(const std::string& name, const bx::Vector2& size, const sf::Texture& texture, 
			size_t frameCount, size_t speed);

		void update(bool repeat, const Vector2& viewSize = { 64, 64 });
		bool hasEnded();
		sf::Sprite& getSprite();
		const Vector2& getSize() const;
		const std::string& getName() const;
		void setName(const std::string& newName);
	};
}