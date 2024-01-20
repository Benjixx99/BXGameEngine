#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stack>

#include "Entity.hpp"
#include "../Common/Vector2.hpp"
#include "../Common/PrimitiveDatatypes.hpp"
#include "../Animation.hpp"
#include "../Load/LoadUniforms.hpp"

namespace bx {

	class Entity;
	class Node;

	enum class Direction : uchar {
		Right,
		Left,
		Up,
		Down
	};

	enum class EntityType : uchar {
		Player,
		NPC,
		Tile,
		Weapon,
		Unknown
	};

	class Component {
	public:
		bool has = false;
	};

	class CType : public Component {
	public:
		EntityType type = EntityType::Unknown;

		CType() {}
		CType(EntityType type) : type(type) {}
	};

	class CTransform : public Component {
	public:
		Vector2 position = { 0.0, 0.0 };
		Vector2 prevPosition = { 0.0, 0.0 };
		Vector2 roomCoordinate = { 0, 0 };
		Vector2 scale = { 1.0, 1.0 };
		Vector2 velocity = { 0.0, 0.0 };
		double angle = 0.0;

		CTransform() {}
		CTransform(const Vector2& position) : position (position), prevPosition(position) {}
		CTransform(const Vector2& position, const Vector2& velocity) 
			: position (position), prevPosition(position), velocity (velocity) {}
		CTransform(const Vector2& position, const Vector2& roomCoordinate, const Vector2& velocity)
			: position(position), prevPosition(position), roomCoordinate(roomCoordinate), velocity(velocity) {}
		CTransform(const Vector2& position, const Vector2& velocity, double angle)
			: position (position), prevPosition (position), velocity (velocity), angle (angle) {}
	};

	class CBoundingBox : public Component {
	public:
		Vector2 size = { 0.0, 0.0 };
		Vector2 halfSize = { 0.0, 0.0 };
		bool blockMovement = false;
		bool blockVision = false;

		CBoundingBox() {}
		CBoundingBox(const Vector2& size) : size(size), halfSize(size.x / 2, size.y / 2) {}
		CBoundingBox(const Vector2& size, bool blockMovement, bool blockVision) 
			: size (size), halfSize(size.x / 2, size.y / 2), blockMovement (blockMovement),
				blockVision (blockVision) {}
	};

	// TODO: Think about to use a flag system instead of many bools
	class CInput : public Component {
	public:
		bool up = false;
		bool down = false;
		bool right = false;
		bool left = false;
		bool swing = false;
		bool shoot = false;
		bool shrink = false;
		bool slowMotion = false;
	};

	class CLifespan : public Component {
	public:
		uint remainingLifespan = 0;
		uint totalLifespane = 0;

		CLifespan() {}
		CLifespan(uint total) : remainingLifespan (total), totalLifespane (total) {}
	};

	class CAnimation : public Component {
	public:
		Animation animation;
		bool repeat = false;

		CAnimation() {}
		CAnimation(const Animation& animation, bool repeat) : animation(animation), repeat(repeat) {}
	};

	class CGravity : public Component {
	public:
		double gravitySpeed = 0.1;

		CGravity() {}
		CGravity(double gravitySpeed): gravitySpeed (gravitySpeed) {}
	};

	class CState : public Component {
	public:
		Direction facing = Direction::Right;
		bool onSurface = true;
		bool isRunning = false;
		bool isAttacking = false;

		CState() {}
		CState(Direction facing, bool isAttacking = false) : facing (facing), isAttacking (isAttacking) {}
	};

	class CMobile : public Component {
	public:

	};

	class CHealth : public Component {
	public:
		uint max = 1;
		uint current = 1;

		CHealth() {}
		CHealth(uint max) : max (max), current (max) {}
	};

	class CDamage : public Component {
	public:
		uint damage = 0;

		CDamage() {}
		CDamage(uint damage) : damage (damage) {}
	};

	class CInvincibility : public Component {
	public:
		uint iframes = 0;

		CInvincibility() {}
		CInvincibility(uint iframes) : iframes (iframes) {}
	};

	class CShader : public Component {
	public:
		std::string name;
		FloatUniformVector floatUniforms;
		TextureUniformVector textureUniforms;

		CShader() {}
		CShader(const std::string& name, const FloatUniformVector& floatUniforms)
			: name (name), floatUniforms (floatUniforms) {}
		CShader(const std::string& name, const TextureUniformVector& textureUniforms)
			: name(name), textureUniforms (textureUniforms) {}
		CShader(const std::string& name, const FloatUniformVector& floatUniforms, const TextureUniformVector& textureUniforms)
			: name(name), floatUniforms(floatUniforms), textureUniforms (textureUniforms) {}
	};

	class CPatrol : public Component {
	public:
		std::vector<Vector2> positions;
		uint currentPosition  = 0;

		CPatrol() {}
		CPatrol(const std::vector<Vector2>& positions) : positions (positions) {}
	};

	class CFollowPrimitive : public Component {
	public:
		std::shared_ptr<Entity> targetEntity;
		Vector2 home = { 0.0 ,0.0 };

		CFollowPrimitive() {}
		CFollowPrimitive(std::shared_ptr<Entity> targetEntity, const Vector2& home) : targetEntity (targetEntity), home(home) {}
	};

	class CFollowPath : public Component {
	public:
		Vector2 target;
		Vector2 home;
		std::stack<std::shared_ptr<Node>> nodes;

		CFollowPath() {}
		CFollowPath(const Vector2& target, const Vector2& home) : target (target), home (home) {}
	};

	class CDraggable : public Component {
	public:
		bool dragging = false;

		CDraggable() {}
		CDraggable(bool dragging) : dragging (dragging) {}
	};
}