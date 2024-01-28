#pragma once

#include <string>
#include "Common/Vector2.hpp"
#include "Common/PrimitiveDatatypes.hpp"

namespace bx {

	enum class ActionName : ushort {
		Select,
		Pause,
		Save,
		Quit,
		
		ToggleTexture,
		ToggleCollision,
		ToggleGrid,
		ToggleSightLine,
		ToggleFollowingCamera,
		
		Up,
		Down,
		Left,
		Right,
		
		Shoot,
		Swing,
		
		LeftClick,
		MiddleClick,
		RightClick,
		MouseMove,

		OpenQtWindwon,
		
		NONE
	};

	enum class ActionType : uchar {
		Start,
		End,
		NONE
	};

	class Action {
		ActionName name = ActionName::NONE;
		ActionType type = ActionType::NONE;
		Vector2 position = { 0, 0 };

	public:

		Action();
		Action(const ActionName name, const ActionType type);
		Action(const ActionName name, const ActionType type, const Vector2& position);

		const ActionName getName() const;
		const ActionType getType() const;
		const Vector2& getPosition() const;
	};
}