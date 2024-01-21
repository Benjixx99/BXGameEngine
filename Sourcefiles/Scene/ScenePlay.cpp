#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>

#include <SFML/Audio.hpp>
#include <QtWidgets/qapplication.h>

#include "../../Headerfiles/Scene/ScenePlay.hpp"
#include "../../Headerfiles/Scene/SceneInGameMenu.hpp"
#include "../../Headerfiles/AAD/GridField.hpp"
#include "../../Headerfiles/Common/Paths.hpp"
#include "../../Headerfiles/ECS/EntityMemoryPool.hpp"
#include "../../Headerfiles/PAM/Physics.hpp"


bx::ScenePlay::ScenePlay(GameEngine* gameEngine, const std::string& levelPath) : Scene(gameEngine), levelPath (levelPath) {
	init(levelPath);
}

// -------------------------------------------------------------------------------------------------------------------------- [Init]
// TODO: Add a KeySetting.txt file (for the keyboard)
void bx::ScenePlay::init(const std::string& levelPath) {

	registerAllActions();

	ConfigFiles configFiles(levelPath + "_PlayerConfig.txt", levelPath + "_NPCsConfig.txt", levelPath + "_tilesConfig.txt");

	store.setTileConfigData(configFiles.tilesConfigFile);
	coordinates = Coordinates(game->getWindow().getSize(), GameType::TopDown);
	creation = Creation(&game->getAssets(), &coordinates, &entities);

	ai = SAI(GridField("Ressources/Configfiles/gridFieldConfig.txt", store.getTileConfigData()));
	animation = SAnimation(&game->getAssets());
	camera = SCamera(&game->getWindow());
	render = SRender(&game->getWindow(), game->getAssets().getFont("Consola"));
	loader = SLoader(configFiles, &creation, &state);

	gCollision = GCollision(GCollisionData(&entities, &game->getAssets(), &state, &sound));
	editorActions = EditorActions(game, &entities, &coordinates);
}

// -------------------------------------------------------------------------------------------------------------------------- [Systems]
void bx::ScenePlay::update() {
	entities.update();

	if (!paused) {
		sLoader();
		sMovement();
		sAI();
		sState();
		sCollision();
		sSound();
		sCamera();
	}

	sEditorModus();
	sAnimation();
	sRender();

	currentFrame++;
}

void bx::ScenePlay::sLoader() {
	LoadType& type = game->shellSharedData().loadType;

	if (type == LoadType::Rooms && room.getPreRoom() != room.getRoom()) {
		loader.rooms(room.getRoom(), room.getPreRoom(), store.getTileConfigData(), entities);
	}
	else if (type == LoadType::AllTilesAtOnce) {
		loader.allTilesAtOnce(levelPath + "_tilesConfig.txt");
		type = LoadType::Loaded;
	}
}

// TODO: Change this by the next side-scroll game
void bx::ScenePlay::sMovement() {
	EntityPointer player = state.getPlayer();
	Vector2& playerPosition = player->getComponent<CTransform>().position;
	Vector2& playerVelocity = player->getComponent<CTransform>().velocity;
	Vector2& playerHalfSize = player->getComponent<CBoundingBox>().halfSize;

	player->getComponent<CTransform>().prevPosition = playerPosition;
	player->getComponent<CState>().isRunning = false;

	if (player->getComponent<CInput>().right) {
		playerPosition.x += playerVelocity.x;
		player->getComponent<CTransform>().scale.x = 1;
		player->getComponent<CState>().facing = Direction::Right;
		player->getComponent<CState>().isRunning = true;
	}
	if (player->getComponent<CInput>().left && (playerPosition.x - playerHalfSize.x > 0)) {
		playerPosition.x -= playerVelocity.x;
		player->getComponent<CTransform>().scale.x = -1;
		player->getComponent<CState>().facing = Direction::Left;
		player->getComponent<CState>().isRunning = true;
	}
	if (player->getComponent<CInput>().down) {
		playerPosition.y += playerVelocity.y;
		player->getComponent<CState>().facing = Direction::Down;
		player->getComponent<CTransform>().scale.x = 1;
		player->getComponent<CState>().isRunning = true;
	}
	if (player->getComponent<CInput>().up && (playerPosition.y - playerHalfSize.y > 0)) {
		playerPosition.y -= playerVelocity.y;
		player->getComponent<CState>().facing = Direction::Up;
		player->getComponent<CTransform>().scale.x = 1;
		player->getComponent<CState>().isRunning = true;
	}

	if (player->hasComponent<CGravity>()) {
		Vector2& surfacePosition = standingSurface->getComponent<CTransform>().position;
		Vector2& surfaceHalfSize = standingSurface->getComponent<CBoundingBox>().halfSize;

		if (standingSurface == nullptr) {
			playerPosition.y += playerVelocity.y;
		}
		else if (playerPosition.x + playerHalfSize.x < surfacePosition.x - surfaceHalfSize.x ||
			playerPosition.x - playerHalfSize.x > surfacePosition.x + surfaceHalfSize.x) {
			player->getComponent<CState>().onSurface = false;
		}

		if (player->getComponent<CInput>().up) {
			player->getComponent<CInput>().up = (jumpDuration-- > 0 ? true : false);
			player->getComponent<CState>().onSurface = false;
			released = false;
		}

		if (!player->getComponent<CState>().onSurface && !player->getComponent<CInput>().up) {
			playerPosition.y += player->getComponent<CGravity>().gravitySpeed;
		}
		else if (player->getComponent<CState>().onSurface) {
			jumpDuration = JUMPDURATION;
		}
	}

	for (auto bullet : entities.getEntities("Bullet")) {
		bullet->getComponent<CTransform>().prevPosition = bullet->getComponent<CTransform>().position;

		if (player->getComponent<CState>().facing == Direction::Right) {
			bullet->getComponent<CTransform>().position.x += bullet->getComponent<CTransform>().velocity.x;
		}
		else if (player->getComponent<CState>().facing == Direction::Left) {
			bullet->getComponent<CTransform>().position.x -= bullet->getComponent<CTransform>().velocity.x;
		}
	}

	for (auto sword : entities.getEntities("Sword")) {
		sword->getComponent<CTransform>().prevPosition = sword->getComponent<CTransform>().position;

		if (player->getComponent<CState>().facing == Direction::Right) {
			sword->getComponent<CTransform>().position.x = playerPosition.x + coordinates.getGridSize().x - 5;
			sword->getComponent<CTransform>().position.y = playerPosition.y;
		}
		else if (player->getComponent<CState>().facing == Direction::Left) {
			sword->getComponent<CTransform>().position.x = playerPosition.x - coordinates.getGridSize().x + 5;
			sword->getComponent<CTransform>().position.y = playerPosition.y;
		}
		else if (player->getComponent<CState>().facing == Direction::Up) {
			sword->getComponent<CTransform>().position.y = playerPosition.y - coordinates.getGridSize().y;
			sword->getComponent<CTransform>().position.x = playerPosition.x;
		}
		else if (player->getComponent<CState>().facing == Direction::Down) {
			sword->getComponent<CTransform>().position.y = playerPosition.y + coordinates.getGridSize().y;
			sword->getComponent<CTransform>().position.x = playerPosition.x;
		}
	}
}

void bx::ScenePlay::sAI() {
	for (auto entity : entities.getEntities("NPC")) {
		if (entity->getComponent<CDraggable>().dragging) { continue; }

		if (entity->hasComponent<CPatrol>()) { ai.patrol(entity, coordinates); }
		if (entity->hasComponent<CFollowPrimitive>()) { ai.follow(entity, entities); }
		if (entity->hasComponent<CFollowPath>()) { ai.pathFollowing(entity, coordinates); }
	}
}

void bx::ScenePlay::sState() {
	state.lifeSpan("Sword", entities);
	state.invicibility();
}

void bx::ScenePlay::sCollision() {
	collision.detection(entities, gCollision);
}

void bx::ScenePlay::sAnimation() {
	animation.playerMoving(state.getPlayer());
	animation.playerAttacking(state.getPlayer(), state.getWeapon());
	animation.NPCMoving(entities);
}

void bx::ScenePlay::sSound() {
	sound.pop();
}

void bx::ScenePlay::sRender() {
	if (!paused) { game->getWindow().clear(sf::Color(252, 216, 168)); }
	else { game->getWindow().clear(sf::Color(212, 176, 128)); }
	
	for (auto entity : entities.getEntities()) {
		if (render.getProperty(RenderProperty::drawTexture)) { render.texture(entity, game->getAssets()); }
		if (render.getProperty(RenderProperty::drawHealthBar)) { render.healthBar(entity); }
		if (render.getProperty(RenderProperty::drawCollision)) { render.collision(entity); }
		if (render.getProperty(RenderProperty::drawSightLine)) { render.sightLine(entity); }
	}
	
	if (render.getProperty(RenderProperty::drawGrid)) { render.grid(coordinates); }

	game->getWindow().display();
}

void bx::ScenePlay::sCamera() {
	room.calculateRoom(state.getPlayer()->getComponent<CTransform>().position, game->getWindow().getSize());
	(game->getGameType() == GameType::SideScrolling) ? camera.sideScroll(state.getPlayer()) 
		: camera.topDown(state.getPlayer(), room.getRoom(), room.getPreRoom());
}

void bx::ScenePlay::sEditorModus() {
	EditorSharedData& data = game->editorSharedData();

	if (data.state != EditorState::Open) { return; }

	if (data.tileConfigData.NAME != "" && data.add) {
		data.tileConfigData.GRID = editorActions.getGridPosition(data.tileConfigData.ROOM);

		EntityPointer entity = creation.spawnTile(data.tileConfigData);
		entity->getComponent<CDraggable>().dragging = true;
		editorActions.setDraggingEntity(entity);
		data.tileConfigData.NAME = "";
	}

	if (data.npcConfigData.NAME != "" && data.add) {
		data.npcConfigData.GRID = editorActions.getGridPosition(data.npcConfigData.ROOM);

		EntityPointer entity = (data.npcConfigData.BEHAVIOR == NPCBehaviorType::FollowPrimitive) ?
			creation.spawnNPC(data.npcConfigData, state.getPlayer()) : creation.spawnNPC(data.npcConfigData);

		entity->getComponent<CDraggable>().dragging = true;
		editorActions.setDraggingEntity(entity);
		data.npcConfigData.NAME = "";
		data.npcConfigData.NUMBER_OF_POSITIONS = 0;
		data.npcConfigData.POSITIONS.clear();
	}

	editorActions.setDraggingEnttiyPosition(room.getRoom());

	if (activate.adding && !(activate.adding = false))			{ editorActions.add(creation, state.getPlayer()); }
	if (activate.removing && !(activate.removing = false))		{ editorActions.remove(room.getRoom()); }
	if (activate.drawing && data.add)							{ editorActions.add(creation); }
	if (activate.drawing && data.remove)						{ editorActions.remove(room.getRoom()); }
	if (data.destroy && !(data.destroy = false))				{ editorActions.destroyDraggingEntity(); }
	
	if (!data.draw) { activate.drawing = false; }

	if (data.levelName != "") {
		editorActions.saveLevelDesign(data.levelName);
		data.levelName = "";
	}
}

void bx::ScenePlay::onEnd() {
	game->changeScene("IN-GAME-MENU", std::make_shared<SceneInGameMenu>(game, "/InGameMenuConfig.txt"));
}

void bx::ScenePlay::doAction(const bx::Action& action) {
	if (action.getType() == ActionType::Start)	{ doActionStart(action); }
	else if (action.getType() == ActionType::End) { doActionEnd(action); }
}

void bx::ScenePlay::doActionStart(const Action& action) {
	CInput& input = state.getPlayer()->getComponent<CInput>();

	switch (action.getName()) {
	case ActionName::ToggleTexture:			render.setProperty(!render.getProperty(RenderProperty::drawTexture), RenderProperty::drawTexture);		break;
	case ActionName::ToggleCollision:		render.setProperty(!render.getProperty(RenderProperty::drawCollision), RenderProperty::drawCollision);	break;
	case ActionName::ToggleGrid:			render.setProperty(!render.getProperty(RenderProperty::drawGrid), RenderProperty::drawGrid);			break;
	case ActionName::ToggleSightLine:		render.setProperty(!render.getProperty(RenderProperty::drawSightLine), RenderProperty::drawSightLine);	break;
	case ActionName::ToggleFollowingCamera:	camera.setFollowing(!camera.getFollowing());	break;
	
	case ActionName::Pause:		setPaused(!paused);	break;
	case ActionName::Quit:		onEnd();			break;
	
	case ActionName::Up:	if (state.getPlayer()->getComponent<CState>().onSurface && released) { input.up = true; }	break;
	case ActionName::Down:	input.down = true;	break;
	case ActionName::Left:	input.left = true;	break;
	case ActionName::Right: input.right = true; break;

	case ActionName::Shoot: actionShoot(state.getPlayer()); break;
	case ActionName::Swing: actionSwing(state.getPlayer()); break;
	
	case ActionName::LeftClick:		actionLeftClick(action);	break;
	case ActionName::RightClick:	actionRightClick(action);	break;

	case ActionName::OpenQtWindwon:	actionOpenEditor();			break;
	}
}

void bx::ScenePlay::doActionEnd(const Action& action) {
	CInput& input = state.getPlayer()->getComponent<CInput>();

	switch (action.getName()) {
	case ActionName::Up:	input.up = false; released = true;	break;
	case ActionName::Down:	input.down = false;	break;
	case ActionName::Left:	input.left = false;	break;
	case ActionName::Right: input.right = false; break;
	case ActionName::Shoot: input.shoot = false; break;
	case ActionName::Swing: input.swing = false; break;
	}
}

void bx::ScenePlay::actionShoot(EntityPointer player) {
	if (!player->getComponent<CInput>().shoot) { creation.spawnBullet(EntityPointer(entities.addEntity("Bullet")), player); }
	player->getComponent<CInput>().shoot = true;
}

void bx::ScenePlay::actionSwing(EntityPointer player) {
	if (!player->getComponent<CInput>().swing) {
		if (state.getWeapon() == nullptr) {
			state.setWeapon(creation.spawnSword(EntityPointer(entities.addEntity("Sword")), player));
			sound.pushAndPlay(game->getAssets().getSoundBuffer("SwungSword"));
		}
	}
	player->getComponent<CInput>().swing = true;
}

void bx::ScenePlay::actionLeftClick(const Action& action) {
	EditorSharedData& data = game->editorSharedData();

	if (data.state != EditorState::Open) { return; }

	if (data.selectTargetPosition && !(data.selectTargetPosition = false)) {
		data.npcConfigData.TARGET = editorActions.getGridPosition(data.npcConfigData.ROOM);
		data.clickedTarget = true;
		return;
	}

	if (data.selectPatrolPosition && !(data.selectPatrolPosition = false)) {
		data.npcConfigData.POSITIONS.push_back(editorActions.getGridPosition(data.npcConfigData.ROOM));
		data.clickedPatrol = true;
		return;
	}

	if (data.add)		{ activate.adding = !activate.adding; }
	if (data.draw)		{ activate.drawing = !activate.drawing; }
	if (data.remove)	{ activate.removing = !activate.removing; }
	if (data.drag)		{ editorActions.dragAndDrop(); }
}

void bx::ScenePlay::actionRightClick(const Action& action) {
	for (auto& entity : entities.getEntities()) {
		std::cout << entity->getTag() << "\n";
	}
}

void bx::ScenePlay::actionOpenEditor() {
	game->shellSharedData().openEditor = true;
}

void bx::ScenePlay::registerAllActions() {
	registerAction(sf::Keyboard::P, ActionName::Pause);
	registerAction(sf::Keyboard::Escape, ActionName::Quit);
	registerAction(sf::Keyboard::T, ActionName::ToggleTexture);
	registerAction(sf::Keyboard::C, ActionName::ToggleCollision);
	registerAction(sf::Keyboard::G, ActionName::ToggleGrid);
	registerAction(sf::Keyboard::V, ActionName::ToggleSightLine);
	registerAction(sf::Keyboard::Y, ActionName::ToggleFollowingCamera);
	registerAction(sf::Keyboard::W, ActionName::Up);
	registerAction(sf::Keyboard::S, ActionName::Down);
	registerAction(sf::Keyboard::A, ActionName::Left);
	registerAction(sf::Keyboard::D, ActionName::Right);
	//registerAction(sf::Keyboard::Space, ActionName::Shoot);
	registerAction(sf::Keyboard::Space, ActionName::Swing);
	registerAction(sf::Keyboard::Q, ActionName::OpenQtWindwon);
}
