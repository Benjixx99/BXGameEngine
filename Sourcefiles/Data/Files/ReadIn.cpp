#include "../../../Headerfiles/Data/Files/ReadIn.hpp"
#include "../../../Headerfiles/Common/TrimString.hpp"
#include "../../../Headerfiles/Common/Paths.hpp"
#include "../../../Headerfiles/Tools/Logger.hpp"

void readInPlayerInt(std::ifstream& file, bx::PlayerConfigData& playerConfig) {
	std::string command;
	int value;
	file >> command >> value;

	if (command == "SpawnGridPositionX")		{ playerConfig.GRID.x = value; }
	else if (command == "SpawnGridPositionY")	{ playerConfig.GRID.y = value; }
	else if (command == "SpawnRoomX")			{ playerConfig.ROOM.x = value; }
	else if (command == "SpawnRoomY")			{ playerConfig.ROOM.y = value; }
	else if (command == "SizeX")				{ playerConfig.SIZE.x = value; }
	else if (command == "SizeY")				{ playerConfig.SIZE.y = value; }
	else if (command == "MaxHealth")			{ playerConfig.HEALTH = value; }
	else { bx::Logger::get().log(bx::LogLevel::Warning, "Unkown int type!", "ReadIn.cpp", __LINE__); }
}

void readInPlayerDouble(std::ifstream& file, bx::PlayerConfigData& playerConfig) {
	std::string command;
	double value;
	file >> command >> value;

	if (command == "SpeedX")		{ playerConfig.SPEED.x = value; }
	else if (command == "SpeedY")	{ playerConfig.SPEED.y = value; }
	else if (command == "Gravity")	{ playerConfig.GRAVITY = value; }
	else { bx::Logger::get().log(bx::LogLevel::Warning, "Unknown double type!", "ReadIn.cpp", __LINE__); }
}

std::vector<float>& readInFloats(std::ifstream& file, int number, std::vector<float>& values) {
	if (number <= 0) { return values; }
	float value;
	file >> value;
	values.push_back(value);
	readInFloats(file, --number, values);
}

void readInUniformFloat(std::ifstream& file, bx::FloatUniformVector& fuv) {
	std::string name;
	float value;
	file >> name >> value;
	fuv.push_back(bx::FloatUniform(name, std::vector<float>(value)));
}

void readInUniformVec(std::ifstream& file, bx::FloatUniformVector& fuv) {
	std::string name;
	std::vector<float> values;
	int number;
	file >> name >> number;
	fuv.push_back(bx::FloatUniform(name, readInFloats(file, number, values)));
}

void readInUniformTexture(std::ifstream& file, bx::TextureUniformVector& tuv) {
	std::string name, texture;
	file >> name >> texture;
	tuv.push_back(bx::TextureUniform(name, texture));
}

void readInMenuString(std::ifstream& file, bx::MenuConfigData& menu) {
	std::string command, name;
	file >> command;
	getline(file, name);
	bx::trimWhitespace(name);

	if (command == "Header") { menu.headerText = name; }
	else if (command == "MenuItem") { menu.menuItemTexts.push_back(name); }
	else if (command == "Footer") { menu.footerText = name; }
	else if (command == "Font") { menu.fontName = name; }
	else { bx::Logger::get().log(bx::LogLevel::Warning, "Unknown string type!", "ReadIn.cpp", __LINE__); }
}

void readInMenuInt(std::ifstream& file, bx::MenuConfigData& menu) {
	std::string command;
	int value;
	file >> command >> value;

	if (command == "HeaderSpaceFromTop") { menu.headerSpaceFromTop = value; }
	else if (command == "HeaderSpaceFromLeft") { menu.headerSpaceFromLeft = value; }
	
	else if (command == "MenuItemSpaceFromHeader") { menu.menuItemSpaceFromHeader = value; }
	else if (command == "MenuItemSpaceFromLeft") { menu.menuItemSpaceFromLeft = value; }
	else if (command == "SpaceBetweenMenuItems") { menu.spaceBetweenMenuItems = value; }
	
	else if (command == "FooterSpaceFromBottom") { menu.footerSpaceFromBottom = value; }
	else if (command == "FooterSpaceFromLeft") { menu.footerSpaceFromLeft = value; }

	else if (command == "HeaderFontSize") { menu.headerFontSize = value; }
	else if (command == "HeaderOutlineThickness") { menu.headerOutlineThickness = value; }
	
	else if (command == "MenuItemFontSize") { menu.menuItemFontSize = value; }
	else if (command == "MenuItemOutlineThickness") { menu.menuItemOutlineThickness = value; }
	
	else if (command == "FooterFontSize") { menu.footerFontSize = value; }
	else if (command == "FooterOutlineThickness") { menu.footerOutlineThickness = value; }
	
	else { bx::Logger::get().log(bx::LogLevel::Warning, "Unknown int type!", "ReadIn.cpp", __LINE__); }
}

void readInMenuColor(std::ifstream& file, bx::MenuConfigData& menu) {
	std::string command;
	int red, green, blue;
	file >> command >> red >> green >> blue;
	sf::Color color(red, green, blue);

	if (command == "Background") { menu.colors[bx::ColorType::Background] = color; }
	else if (command == "HeaderFont") { menu.colors[bx::ColorType::HeaderFont] = color; }
	else if (command == "HeaderOutline") { menu.colors[bx::ColorType::HeaderOutline] = color; }
	else if (command == "MenuItemFont") { menu.colors[bx::ColorType::MenuItemFont] = color; }
	else if (command == "MenuItemOutline") { menu.colors[bx::ColorType::MenuItemOutline] = color; }
	else if (command == "SelectedMenuItemFont") { menu.colors[bx::ColorType::SelectedMenuItemFont] = color; }
	else if (command == "SelectedMenuItemOutline") { menu.colors[bx::ColorType::SelectedMenuItemOutline] = color; }
	else if (command == "FooterFont") { menu.colors[bx::ColorType::FooterFont] = color; }
	else if (command == "FooterOutline") { menu.colors[bx::ColorType::FooterOutline] = color; }
	else { bx::Logger::get().log(bx::LogLevel::Warning, "Unknown color type!", "ReadIn.cpp", __LINE__); }
}

void readInAnimationInt(std::ifstream& file, bx::AnimationConfigData& animationConfig) {
	std::string command;
	int value;
	file >> command >> value;

	if (command == "NumberOfFrames") { animationConfig.numberOfFrames = value; }
	else if (command == "AnimationSpeed") { animationConfig.animationSpeed = value; }
	else { bx::Logger::get().log(bx::LogLevel::Warning, "Unknown int type!", "ReadIn.cpp", __LINE__); }
}

void readInAnimationString(std::ifstream& file, bx::AnimationConfigData& animationConfig) {
	std::string command, name;
	file >> command >> name;

	if (command == "TextureName") { animationConfig.textureName = name; }
	else { bx::Logger::get().log(bx::LogLevel::Warning, "Unknown string type!", "ReadIn.cpp", __LINE__); }
}


bx::PlayerConfigData& bx::ReadIn::playerData(std::ifstream& file, PlayerConfigData& playerConfig) {
	std::string command;

	while (file >> command) {
		if (command == "Int")			{ readInPlayerInt(file, playerConfig); }
		else if (command == "Double")	{ readInPlayerDouble(file, playerConfig); }
		else { bx::Logger::get().log(bx::LogLevel::Warning, "Unknown int type!", "ReadIn.cpp", __LINE__); }
	}

	return playerConfig;
}

bx::NPCConfigData& bx::ReadIn::NPCData(std::ifstream& file, NPCConfigData& enemyConfig) {
	int behaviorType;
	file >> enemyConfig.NAME >> enemyConfig.ROOM.x >> enemyConfig.ROOM.y >> enemyConfig.GRID.x >> enemyConfig.GRID.y
		>> enemyConfig.BLOCK_MOVEMENT >> enemyConfig.BLOCK_VISION >> enemyConfig.HEALTH >> enemyConfig.DAMAGE;
	file >> enemyConfig.BEHAVIOR >> enemyConfig.SPEED.x;

	enemyConfig.SPEED.y = enemyConfig.SPEED.x;

	if (enemyConfig.BEHAVIOR == NPCBehaviorType::Patrol) {
		file >> enemyConfig.NUMBER_OF_POSITIONS;

		Vector2 position;
		while (enemyConfig.NUMBER_OF_POSITIONS-- > 0) {
			file >> position.x >> position.y;
			enemyConfig.POSITIONS.push_back(position);
		}
	}

	if (enemyConfig.BEHAVIOR == NPCBehaviorType::FollowPath) {
		file >> enemyConfig.TARGET.x >> enemyConfig.TARGET.y;
	}

	return enemyConfig;
}

bx::TileConfigData& bx::ReadIn::tileData(std::ifstream& file, TileConfigData& tileConfig) {
	file >> tileConfig.NAME >> tileConfig.ROOM.x >> tileConfig.ROOM.y >> tileConfig.GRID.x >> tileConfig.GRID.y
		>> tileConfig.BLOCK_MOVEMENT >> tileConfig.BLOCK_VISION;
	return tileConfig;
}

bx::Vector2& bx::ReadIn::gridFieldData(std::ifstream& file, Vector2& size) {
	file >> size.x >> size.y;
	return size;
}

void bx::ReadIn::floatUniformData(std::ifstream& file, FloatUniformVector& fuv) {
	std::string command;
	if (!(file >> command)) { return; }

	if (command == "float")		{ readInUniformFloat(file, fuv); }
	else if (command == "vec")	{ readInUniformVec(file, fuv); }
	else { bx::Logger::get().log(bx::LogLevel::Warning, "Expected: float or vec!", "ReadIn.cpp", __LINE__); }
	floatUniformData(file, fuv);
}

void bx::ReadIn::textureUniformData(std::ifstream& file, TextureUniformVector& tuv) {
	std::string command;
	if (!(file >> command)) { return; }

	if (command == "texture")	{ readInUniformTexture(file, tuv); }
	else { bx::Logger::get().log(bx::LogLevel::Warning, "Expected: texture!", "ReadIn.cpp", __LINE__); }
	textureUniformData(file, tuv);
}

void bx::ReadIn::menuData(std::ifstream& file, MenuConfigData& menu) {
	std::string command;
	if (!(file >> command)) { return; }

	if (command == "String")		{ readInMenuString(file, menu); }
	else if (command == "Int")		{ readInMenuInt(file, menu); }
	else if (command == "Color")	{ readInMenuColor(file, menu); }
	else { bx::Logger::get().log(bx::LogLevel::Warning, "Expected: String, Int or Color!", "ReadIn.cpp", __LINE__); }
	menuData(file, menu);
}

void bx::ReadIn::animationsData(std::ifstream& file, std::vector<AnimationConfigData>& animationsConfig) {
	AnimationConfigData data;
	std::string command;
	
	while (file >> command) {
		
		if (command == "String") { readInAnimationString(file, data); }
		else if (command == "Int")			{ readInAnimationInt(file, data); }
		else if (command == "End")		{ animationsConfig.push_back(data); }
		else { bx::Logger::get().log(bx::LogLevel::Warning, "Expected: String or Int!", "ReadIn.cpp", __LINE__); }
	}
}

void bx::ReadIn::keyboardLayout(std::ifstream& file, VectorStringPair& keyActionPairs) {
	std::string command, keyValue, actionName;

	while (file >> keyValue) {
		getline(file, actionName);
		trimWhitespace(actionName);
		keyActionPairs.push_back(std::pair(keyValue, actionName));
	}
}
