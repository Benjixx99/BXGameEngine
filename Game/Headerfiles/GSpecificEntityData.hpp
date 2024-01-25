#pragma once

#include "../../Headerfiles/Common/CompositeDataTypes.hpp"

namespace Game {

	namespace GSpecificEntityData {
		void playerGameSpecificData(bx::EntityPointer entity);
		void swordGameSpecificData(bx::EntityPointer entity);
		void bulletGameSpecificData(bx::EntityPointer entity);
		void NPCGameSpecificData(bx::EntityPointer entity);
		void tileGameSpecificData(bx::EntityPointer entity);
	}
}