#include "../../../Headerfiles/Tools/Editor/EdtiorActions.hpp"
#include "../../../Headerfiles/PAM/Physics.hpp"
#include "../../../Headerfiles/Config/Config.hpp"
#include "../../../Headerfiles/Data/Files/WriteOut.hpp"
#include "../../../Headerfiles/Save.hpp"

bx::EditorActions::EditorActions() {}

bx::EditorActions::EditorActions(GameEngine* game, EntityManager* entities, Coordinates* coordinates)
: game (game), entities (entities), coordinates (coordinates) {}

bx::Vector2 bx::EditorActions::getMousePositionInGameWorld() {
	return coordinates->windowToGameWorld(sf::Mouse::getPosition(game->getWindow()), game->getWindow().getView().getCenter());
}

bool bx::EditorActions::isOccupied() {
	Vector2 position = coordinates->computeGridPosition(draggingEntity);
	for (const auto entity : entities->getEntities()) {
		if (entity->getId() == draggingEntity->getId() || entity->hasComponent<CMobile>()) { continue; }

		if (position == coordinates->computeGridPosition(entity)) {
			if (draggingEntity->getTag() == entity->getTag()) {
				return true;
			}
			else {
				entity->destroy();
			}
		}
	}
	return false;
}

void bx::EditorActions::alignDrop(EntityPointer entity) {
	Vector2& entityPosition = entity->getComponent<CTransform>().position;
	Vector2 entitySize = entity->getComponent<CAnimation>().animation.getSize();
	Vector2 gridPosition = coordinates->computeGridPosition(entity, entityPosition);

	entityPosition = coordinates->computePosition(entity, gridPosition);
	entity->getComponent<CTransform>().prevPosition = entityPosition;
}

void bx::EditorActions::dragAndDrop() {
	Vector2 position = getMousePositionInGameWorld();
	for (auto entity : entities->getEntities()) {
		if (entity->hasComponent<CDraggable>() && Physics::isInside(entity, position)) {
			entity->getComponent<CDraggable>().dragging = !entity->getComponent<CDraggable>().dragging;

			if (entity->getComponent<CDraggable>().dragging) {
				setDraggingEntity(entity);
				return;
			}
			else {
				alignDrop(draggingEntity);
				draggingEntity = nullptr;
				return;
			}
		}
	}
}

void bx::EditorActions::add(Creation& creation, EntityPointer player) {
	if (!isOccupied()) {
		if (draggingEntity->getComponent<CType>().type == EntityType::Tile) {
			creation.spawnTile(TileConfigData(draggingEntity, *coordinates));
		}
		else if (draggingEntity->getComponent<CType>().type == EntityType::NPC) {
			creation.spawnNPC(NPCConfigData(draggingEntity, *coordinates), player);
		}
	}
}

void bx::EditorActions::remove(const Vector2& roomCoordinate) {
	Vector2 position = getMousePositionInGameWorld();
	position = coordinates->computeGridPosition(Vector2(0, 0), position, roomCoordinate);

	for (auto entity : entities->getEntities()) {
		if (entity->hasComponent<CInput>()) { continue; }

		if (position == coordinates->computeGridPosition(entity)) {
			entity->destroy();
			return;
		}
	}
}


void bx::EditorActions::undo() {
	
}

void bx::EditorActions::redo() {

}

void bx::EditorActions::saveLevelDesign(const std::string& levelName) {
	Save save(levelName);
	save.level(*entities, *coordinates);
}

bx::Vector2 bx::EditorActions::getGridPosition(const Vector2& roomCoordinate) {
	return coordinates->computeGridPosition(Vector2(0, 0), getMousePositionInGameWorld(), roomCoordinate);
}

void bx::EditorActions::setDraggingEnttiyPosition(const Vector2& roomCoordinate) {
	if (draggingEntity == nullptr) { return; }
	draggingEntity->getComponent<CTransform>().prevPosition = draggingEntity->getComponent<CTransform>().position;
	draggingEntity->getComponent<CTransform>().position = getMousePositionInGameWorld();
	draggingEntity->getComponent<CTransform>().roomCoordinate = roomCoordinate;
}

void bx::EditorActions::setDraggingEntity(EntityPointer entity) {
		destroyDraggingEntity();
		draggingEntity = entity;
}

void bx::EditorActions::destroyDraggingEntity() {
	if (draggingEntity != nullptr) {
		draggingEntity->destroy();
		draggingEntity = nullptr;
	}
}
