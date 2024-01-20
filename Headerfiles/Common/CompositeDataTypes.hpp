#pragma once

#include <memory>
#include <vector>
#include <map>
#include <string>

#include "../ECS/Entity.hpp"

namespace bx {

	using VectorString = std::vector<std::string>;
	using EntityPointer = std::shared_ptr<Entity>;
	using EntityVector = std::vector<EntityPointer>;
	using EntityMap = std::map<std::string, EntityVector>;
}