#pragma once

#include <string>
#include "../Common/PrimitiveDatatypes.hpp"

namespace bx {

	class AnimationConfigData {
	public:
		std::string textureName;
		uint numberOfFrames;
		uint animationSpeed;
	};
}