#pragma once

#include "Config/Config.hpp"
#include "Systems/SLoader.hpp"

namespace bx {

	enum class EditorState : uchar {
		None,
		Open,
		Hidden,
	};

	enum class LoadType : int {
		Loaded,
		Rooms,
		AllTilesAtOnce,
		PlayerCentered,
		Checkpoints
	};

	struct EditorSharedData {
		EditorState state = EditorState::None;
		TileConfigData tileConfigData;
		NPCConfigData npcConfigData;
		std::string levelName = "";

		bool add = false;
		bool drag = false;
		bool draw = false;
		bool remove = false;
		
		bool destroy = false;

		bool selectTargetPosition = false;
		bool selectPatrolPosition = false;
		bool clickedTarget = false;
		bool clickedPatrol = false;
	};

	struct ShellSharedData {
		std::string databaseName = "";
		bool deleteDatabase = false;
		bool showDatabase = false;
		bool updateDatabase = false;

		bool openEditor = false;
		
		LoadType loadType = LoadType::Rooms;
	};
}