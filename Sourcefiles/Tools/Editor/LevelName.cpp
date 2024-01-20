#include "../../../Headerfiles/Tools/Editor/LevelName.hpp"
#include "../../../Headerfiles/Qt/QtHelpFunctions.hpp"
#include "../../../Headerfiles/Common/CheckIf.hpp"

bx::LevelName::LevelName(QWidget* parent) : QDialog(parent) {
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	ui.setupUi(this);
	ui.mfra_TitleBarDialog->setRelativeName("LevelName");
}

bx::LevelName::~LevelName() {}

std::string bx::LevelName::getLevelName() const {
	return ui.le_inputLevelName->text().toStdString();
}

bool bx::LevelName::isCancelled() const {
	return cancelled;
}

void bx::LevelName::cancel() {
	cancelled = true;
	this->close();
}

void bx::LevelName::ok() {
	std::string input = ui.le_inputLevelName->text().toStdString();
	if (CheckIf::allCharacters_AlphaNumeric(input) && input != "") { this->close(); }
	else if (input == "")	{ QtHelpFunctions::notification("[ERROR]: Empty name not allowed!", ui.lbl_Notification, true); }
	else					{ QtHelpFunctions::notification("[ERROR]: No special characters allowed!", ui.lbl_Notification, true); }
}
