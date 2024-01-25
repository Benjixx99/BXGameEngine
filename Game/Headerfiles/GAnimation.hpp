#pragma once

#include "../../Headerfiles/Common/CompositeDataTypes.hpp"
#include "../../Headerfiles/Assets.hpp"

namespace Game {

	namespace GAnimation {
		void NPCMoving(bx::EntityPointer entity, bx::Assets* assets);
		void NPCAttacking(bx::EntityPointer entity, bx::Assets* assets);
	}
}