#pragma once

#include <SFML/Graphics/Text.hpp>
#include <string>
#include <map>
#include <memory>

#include "../ECS/EntityManager.hpp"
#include "../SSC/Coordinates.hpp"
#include "../Systems/SAI.hpp"
#include "../Systems/SAnimation.hpp"
#include "../Systems/SCamera.hpp"
#include "../Systems/SCollision.hpp"
#include "../Systems/SRender.hpp"
#include "../Systems/SSound.hpp"
#include "../Common/Vector2.hpp"
#include "../GameEngine.hpp"
#include "../Action.hpp"

namespace bx {

	class GameEngine;

	class Scene {
		using ActionMap = std::map<int, ActionName>;

	protected:
		GameEngine* game = nullptr;
		EntityManager entities;
		ActionMap actionMap;
		Coordinates coordinates;
		
		SAI ai;
		SAnimation animation;
		SCamera camera;
		SCollision collision;
		SRender render;
		SSound sound;
		
		size_t currentFrame = 0;

		bool drawing = false;
		bool paused = false;
		bool hasEnded = false;

		void setPaused(bool pause);
		virtual void onEnd() = 0;

	public:
		Scene();
		Scene(GameEngine* gameEngine);

		virtual void update() = 0;
		virtual void sRender() = 0;
		virtual void doAction(const Action& action) = 0;

		void registerAction(int inputKey, const ActionName name);

		size_t getCurrentFrame() const;
		bool getHasEnded() const;
		const ActionMap& getActionMap() const;
	};
}