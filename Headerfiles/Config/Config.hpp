#pragma once

#include <vector>
#include "../Common/Vector2.hpp"
#include "../Common/CompositeDataTypes.hpp"
#include "../SSC/Coordinates.hpp"

#include <fstream>

namespace bx {

	enum class NPCBehaviorType {
		FollowPath,
		FollowPrimitive,
		Patrol,
		NONE
	};

	class PlayerConfigData {
	public:
		Vector2 ROOM { 0, 0 };
		Vector2 GRID { 0, 0 };
		Vector2 SPEED { 0, 0 };
		Vector2 SIZE { 64, 64 };
		double GRAVITY = 0;
		int HEALTH = 5;

		PlayerConfigData() {}
		PlayerConfigData(EntityPointer entity, Coordinates& coordinates) {
			ROOM = entity->getComponent<CTransform>().roomCoordinate;
			GRID = coordinates.computeGridPosition(entity, entity->getComponent<CTransform>().position, ROOM);
			SPEED = entity->getComponent<CTransform>().velocity;
			SIZE = entity->getComponent<CBoundingBox>().size;
			HEALTH = entity->getComponent<CHealth>().max;

			if (entity->hasComponent<CGravity>()) {
				GRAVITY = entity->getComponent<CGravity>().gravitySpeed;
			}
		}
	};

	class NPCConfigData {
	public:
		std::string NAME = "";
		NPCBehaviorType BEHAVIOR = NPCBehaviorType::NONE;
		Vector2 ROOM { 0, 0 };
		Vector2 GRID { 0, 0 };
		Vector2 SPEED { 0, 0 };
		Vector2 TARGET { 0, 0 };
		std::vector<Vector2> POSITIONS;
		int BLOCK_MOVEMENT = 1;
		int BLOCK_VISION = 0;
		int HEALTH = 4;
		int DAMAGE = 1;
		int NUMBER_OF_POSITIONS = 0;

		NPCConfigData() {}
		NPCConfigData(EntityPointer entity, Coordinates& coordinates) {
			NAME = entity->getComponent<CAnimation>().animation.getName();
			ROOM = entity->getComponent<CTransform>().roomCoordinate;
			GRID = coordinates.computeGridPosition(entity, entity->getComponent<CTransform>().position, ROOM);
			SPEED = entity->getComponent<CTransform>().velocity;
			HEALTH = entity->getComponent<CHealth>().max;
			DAMAGE = entity->getComponent<CDamage>().damage;
			BLOCK_MOVEMENT = entity->getComponent<CBoundingBox>().blockMovement;
			BLOCK_VISION = entity->getComponent<CBoundingBox>().blockVision;

			if (entity->hasComponent<CPatrol>()) {
				BEHAVIOR = NPCBehaviorType::Patrol;
				POSITIONS = entity->getComponent<CPatrol>().positions;
				NUMBER_OF_POSITIONS = POSITIONS.size();
			}
			else if (entity->hasComponent<CFollowPrimitive>()) {
				BEHAVIOR = NPCBehaviorType::FollowPrimitive;
			}
			else if (entity->hasComponent<CFollowPath>()) {
				BEHAVIOR = NPCBehaviorType::FollowPath;
				TARGET = entity->getComponent<CFollowPath>().target;
			}
		}
	};

	class TileConfigData {
	public:
		std::string NAME = "";
		Vector2 ROOM { 0, 0 };
		Vector2 GRID { 0, 0 };
		int BLOCK_MOVEMENT = 0;
		int BLOCK_VISION = 0;
		
		TileConfigData () {}
		TileConfigData(EntityPointer entity, Coordinates& coordinates) {
			NAME = entity->getTag();
			ROOM = entity->getComponent<CTransform>().roomCoordinate;
			GRID = coordinates.computeGridPosition(entity, entity->getComponent<CTransform>().position, ROOM);
			BLOCK_MOVEMENT = entity->getComponent<CBoundingBox>().blockMovement;
			BLOCK_VISION = entity->getComponent<CBoundingBox>().blockVision;
		}
	};
}

std::ifstream& operator>> (std::ifstream& file, bx::NPCBehaviorType& type);
std::ofstream& operator<< (std::ofstream& file, const bx::NPCBehaviorType& type);
