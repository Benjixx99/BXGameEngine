#include "../../../Headerfiles/Tools/Editor/Editor.hpp"
#include "../../../Headerfiles/Tools/Editor/LevelName.hpp"
#include "../../../Headerfiles/Qt/QtHelpFunctions.hpp"

#include "../../../Headerfiles/Common/Paths.hpp"
#include "../../../Headerfiles/Common/CheckIf.hpp"
#include "../../../Headerfiles/DatabaseManager.hpp"

#include <iostream>

bx::Editor::Editor(EditorSharedData& sharedData, QWidget* parent) : sharedData (sharedData), QWidget(parent) {
	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	ui.setupUi(this);
	ui.mfra_TitleBarEditor->setRelativeName("Editor");
	init();
}

bx::Editor::~Editor() {}

void bx::Editor::init() {
	DatabaseManager assetsDatabase(Paths::databases + "/AssetsDatabase.db");
	WidgetSize tilesSize,  playerSize, NPCsSize;
	const uint offset = 25;

	for (const auto& entry : assetsDatabase.selectAllEntriesFrom("Textures")) {
		if (entry[2] == "Tiles")		{ setLabelAndCalculateNextLabelPosition(entry, ui.fra_ShowTiles, tilesSize); }
		else if (entry[2] == "NPCs")	{ setLabelAndCalculateNextLabelPosition(entry, ui.fra_ShowNPCs, NPCsSize);  }
		else { continue; }
	}

	ui.wid_ShowTiles->setFixedHeight(tilesSize.top + boxHeight + offset);
	ui.wid_ShowNPCs->setFixedHeight(NPCsSize.top + boxHeight + offset);
	ui.tw_ShowImages->setCurrentIndex(static_cast<int>(ShowImagesTab::Tiles));
	
	selectButton(ui.btn_Drag, sharedData.drag);

	ClickableQLabel* firstLabel = static_cast<ClickableQLabel*>(ui.fra_ShowTiles->children()[0]);
	firstLabel->labelClicked();
}

void bx::Editor::setLabelAndCalculateNextLabelPosition(const std::vector<std::string>& entry, QFrame* fra_Show, WidgetSize& size) {
	QImage image(QString::fromStdString(entry[1]));
	ClickableQLabel* lbl_clickable = new ClickableQLabel(fra_Show);
	lbl_clickable->setGeometry(QRect(size.left, size.top, boxWidth, boxHeight));
	lbl_clickable->setObjectName(QString::fromStdString(entry[0]));
	lbl_clickable->setPixmap(QPixmap::fromImage(image));
	lbl_clickable->show();
	calculateLeftAndTop(size);
}

bx::WidgetSize& bx::Editor::calculateLeftAndTop(WidgetSize& size) {
	size.left = size.left = (size.left + boxWidth) % MAXWIDTH;
	size.top = size.top += (size.left == 0) ? boxHeight : 0;
	return size;
}

std::string bx::Editor::getNPCsBehaviorName() {
	switch (ui.cob_NPCsBehavior->currentIndex()) {
	case static_cast<int>(NPCsBehavior::FollowPath):		return "FollowPath";
	case static_cast<int>(NPCsBehavior::FollowPrimitive):	return "FollowPrimitive";
	case static_cast<int>(NPCsBehavior::Patrol):			return "Patrol";
	}
}

void bx::Editor::clickedOnButton(QPushButton* button, bool& selected) {
	if (!selected)	{ selectButton(button, selected); }
	else			{ unselectButton(button, selected); }
}

void bx::Editor::selectButton(QPushButton* button, bool& selected) {
	button->setStyleSheet("background-color: rgb(214,214,214);");
	selected = true;
	apply();
}

void bx::Editor::unselectButton(QPushButton* button, bool& selected) {
	button->setStyleSheet("");
	selected = false;
}

bool bx::Editor::event(QEvent* event) {
	if (event->type() == QEvent::Show) {
		ui.tw_Main->setCurrentIndex(static_cast<int>(MainTab::Level_Design));
		ui.tw_ShowImages->setCurrentIndex(static_cast<int>(ShowImagesTab::Tiles));
		this->show();
		return true;
	}

	if (sharedData.clickedTarget && !(sharedData.clickedTarget = false)) {
		int x = sharedData.npcConfigData.TARGET.x, y = sharedData.npcConfigData.TARGET.y;
		QtHelpFunctions::notification("Selected target position: " + std::to_string(x) + " : " + std::to_string(y), ui.lbl_Notification);
		return true;
	}

	if (sharedData.clickedPatrol && !(sharedData.clickedPatrol = false)) {
		int x = sharedData.npcConfigData.POSITIONS.back().x, y = sharedData.npcConfigData.POSITIONS.back().y;
		QtHelpFunctions::notification("Selected patrol position: " + std::to_string(x) + " : " + std::to_string(y),	ui.lbl_Notification);
		return true;
	}

	return QWidget::event(event);
}

void bx::Editor::setLastLabelClicked(ClickableQLabel* label) {
	switch (ui.tw_ShowImages->currentIndex()) {
	case static_cast<int>(ShowImagesTab::Tiles):	lastClickedLabels.clbl_Tiles = label; return;
	case static_cast<int>(ShowImagesTab::NPCs):		lastClickedLabels.clbl_NPCs = label; return;
	}
}

ClickableQLabel* bx::Editor::getLastLabelClicked() {
	switch (ui.tw_ShowImages->currentIndex()) {
	case static_cast<int>(ShowImagesTab::Tiles):	return lastClickedLabels.clbl_Tiles;
	case static_cast<int>(ShowImagesTab::NPCs):		return lastClickedLabels.clbl_NPCs;
	}
}

void bx::Editor::showSelectedImageSizeAndName() {
	ClickableQLabel* clbl_last = getLastLabelClicked();
	QString width = QString::number(clbl_last->pixmap().size().width());
	QString height = QString::number(clbl_last->pixmap().size().height());
	ui.lbl_ShowSelectedImageSize->setText(width + " : " + height);
	ui.lbl_ShowSelectedImageName->setText(clbl_last->objectName());
}

// SLOTS 
void bx::Editor::apply() {	
	if (ui.tw_ShowImages->currentIndex() == static_cast<int>(ShowImagesTab::Tiles)) {
		if (sharedData.add && lastClickedLabels.clbl_Tiles != nullptr) {
			sharedData.tileConfigData.NAME = lastClickedLabels.clbl_Tiles->objectName().toStdString();
			sharedData.tileConfigData.BLOCK_MOVEMENT = ui.chb_TilesBlockMovement->isChecked();
			sharedData.tileConfigData.BLOCK_VISION = ui.chb_TilesBlockSight->isChecked();

			QtHelpFunctions::notification("Add Tile", ui.lbl_Notification);
		}
		else if (sharedData.remove) {
			QtHelpFunctions::notification("Remove Tile", ui.lbl_Notification);
		}
		else if (sharedData.add && lastClickedLabels.clbl_Tiles == nullptr) {
			QtHelpFunctions::notification("[ERROR]: No Tile selected!", ui.lbl_Notification, true);
			return;
		}
	}
	else if (ui.tw_ShowImages->currentIndex() == static_cast<int>(ShowImagesTab::NPCs)) {
		if (lastClickedLabels.clbl_NPCs != nullptr) {
			sharedData.npcConfigData.NAME = lastClickedLabels.clbl_NPCs->objectName().toStdString();
			sharedData.npcConfigData.BEHAVIOR = static_cast<NPCBehaviorType>(ui.cob_NPCsBehavior->currentIndex());

			sharedData.npcConfigData.DAMAGE = ui.sb_NPCsDamage->value();
			sharedData.npcConfigData.HEALTH = ui.sb_NPCsMaxHealth->value();
			sharedData.npcConfigData.SPEED = ui.sb_NPCsSpeed->value();
			sharedData.npcConfigData.BLOCK_MOVEMENT = ui.chb_NPCsBlockMovement->isChecked();
			sharedData.npcConfigData.BLOCK_VISION = ui.chb_NPCsBlockSight->isChecked();

			QtHelpFunctions::notification("Add NPC", ui.lbl_Notification);
		}
		else if (sharedData.remove) {
			QtHelpFunctions::notification("Remove NPC", ui.lbl_Notification);
		}
		else {
			QtHelpFunctions::notification("[ERROR]: No NPC selected!", ui.lbl_Notification, true);
			return;
		}
	}

	if (sharedData.drag) {
		QtHelpFunctions::notification("Drag Item", ui.lbl_Notification);
	}
}

void bx::Editor::customHide() {
	this->hide();
	sharedData.state = EditorState::Hidden;
}

void bx::Editor::saveLevel() {
	LevelName levelName;
	levelName.show();
	levelName.exec();
	sharedData.levelName = (!levelName.isCancelled()) ? levelName.getLevelName() : "";
}

void bx::Editor::addPatrolPosition() {
	std::string XInput = ui.le_NPCsXPosition->text().toStdString(), YInput = ui.le_NPCsYPosition->text().toStdString();

	if (CheckIf::allCharacters_Numeric(XInput) && CheckIf::allCharacters_Numeric(YInput) && XInput != "" && YInput != "") {
		sharedData.npcConfigData.POSITIONS.push_back(Vector2(ui.le_NPCsXPosition->text().toDouble(), ui.le_NPCsYPosition->text().toDouble()));
		++sharedData.npcConfigData.NUMBER_OF_POSITIONS;
		QtHelpFunctions::notification("Added Patrol Grid Position " + XInput + " : " + YInput, ui.lbl_Notification);
	}
	else {
		QtHelpFunctions::notification("[ERROR]: Adding Patrol Grid Position failed, wrong input!", ui.lbl_Notification, true);
	}

	ui.le_NPCsXPosition->setText("");
	ui.le_NPCsYPosition->setText("");
}

void bx::Editor::selectPatrolPosition() {
	sharedData.selectPatrolPosition = true;
}

void bx::Editor::selectTargetPosition() {
	sharedData.selectTargetPosition = true;
}

void bx::Editor::resetData() {
	if (ui.tw_ShowImages->currentIndex() == static_cast<int>(ShowImagesTab::Tiles)) {
		unselectButton(ui.btn_Add, sharedData.add);
		unselectButton(ui.btn_remove, sharedData.remove);
		unselectButton(ui.btn_Draw, sharedData.draw);
		ui.btn_Draw->setEnabled(false);
	}
	else if (ui.tw_ShowImages->currentIndex() == static_cast<int>(ShowImagesTab::NPCs)) {
		unselectButton(ui.btn_Add, sharedData.add);
		unselectButton(ui.btn_remove, sharedData.remove);
		ui.btn_Draw->setEnabled(true);
	}
	sharedData.destroy = true;
}

void bx::Editor::add() {
	unselectButton(ui.btn_Drag, sharedData.drag);
	unselectButton(ui.btn_remove, sharedData.remove);
	clickedOnButton(ui.btn_Add, sharedData.add);
	if (!sharedData.add) { sharedData.destroy = true; }
}

void bx::Editor::drag() {
	unselectButton(ui.btn_Add, sharedData.add);
	unselectButton(ui.btn_Draw, sharedData.draw);
	unselectButton(ui.btn_remove, sharedData.remove);
	clickedOnButton(ui.btn_Drag, sharedData.drag);
	sharedData.destroy = true;
}

void bx::Editor::draw() {
	unselectButton(ui.btn_Drag, sharedData.drag);
	clickedOnButton(ui.btn_Draw, sharedData.draw);
}

void bx::Editor::remove() {
	unselectButton(ui.btn_Add, sharedData.add);
	unselectButton(ui.btn_Drag, sharedData.drag);
	clickedOnButton(ui.btn_remove, sharedData.remove);
	sharedData.destroy = true;
}

