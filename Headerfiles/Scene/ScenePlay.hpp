#pragma once

#include "Scene.hpp"
#include "../Systems/SLoader.hpp"
#include "../Systems/SState.hpp"
#include "../ECS/Entity.hpp"
#include "../SSC/Creation.hpp"
#include "../SSC/RoomManager.hpp"
#include "../Config/Config.hpp"
#include "../Data/StoreConfigData.hpp"
#include "../SharedDataStructure.hpp"

#include "../Tools/Editor/EdtiorActions.hpp"
#include "../../Game/Headerfiles/GCollision.hpp"


namespace bx {

	constexpr size_t JUMPDURATION = 16;
	constexpr size_t SHOOTDURATION = 60;

	struct Activate {
		bool adding = false;
		bool drawing = false;
		bool removing = false;
	};

	class ScenePlay : public Scene {
		SLoader loader;
		SState state;
		Creation creation;
		RoomManager room;
		StoreConfigData store;
		EntityPointer standingSurface = nullptr;	// Move this to the class CGravity

		EditorActions editorActions;
		Activate activate;

		GCollision gCollision;

		const std::string levelPath;

		int jumpDuration = JUMPDURATION;
		int shootDuration = SHOOTDURATION;
		bool released = true;	// Maybe can get rid of it
		
		void init(const std::string& levelPath);

		// Systems
		void sEditorModus();
		void sLoader();
		void sMovement();
		void sAI();
		void sState();
		void sCollision();
		void sAnimation();
		void sSound();
		void sRender();
		void sCamera();
		
		void onEnd();
		void doAction(const Action& action);
		void doActionStart(const Action& action);
		void doActionEnd(const Action& action);

		void actionShoot(EntityPointer player);
		void actionSwing(EntityPointer player);
		void actionLeftClick(const Action& action);
		void actionRightClick(const Action& action);
		void actionOpenEditor();

		void registerAllActions();

	public:
		ScenePlay(GameEngine* gameEngine, const std::string& levelPath);
		void update();
	};
}