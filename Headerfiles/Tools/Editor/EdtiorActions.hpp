#pragma once

#include "../../SSC/Coordinates.hpp"
#include "../../SSC/Creation.hpp"
#include "../../ECS/EntityManager.hpp"
#include "../../GameEngine.hpp"

namespace bx {

	class EditorActions {
		GameEngine* game = nullptr;
		EntityManager* entities = nullptr;
		Coordinates* coordinates = nullptr;
		EntityPointer draggingEntity = nullptr;

		Vector2 getMousePositionInGameWorld();
		bool isOccupied();
		void alignDrop(EntityPointer entity);
	public:
		EditorActions();
		EditorActions(GameEngine* game, EntityManager* entities, Coordinates* coordinates);

		void dragAndDrop();
		
		void add(Creation& creation, EntityPointer player = nullptr);
		void remove(const Vector2& roomCoordinate);

		void undo();
		void redo();

		void saveLevelDesign(const std::string& levelName);

		Vector2 getGridPosition(const Vector2& roomCoordinate);

		void setDraggingEnttiyPosition(const Vector2& roomCoordinate);
		void setDraggingEntity(EntityPointer entity);
		void destroyDraggingEntity();
	};
}