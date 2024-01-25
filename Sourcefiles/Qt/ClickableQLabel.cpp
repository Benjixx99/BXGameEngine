#include "../../Headerfiles/Qt/ClickableQLabel.hpp"
#include "../../Headerfiles/Qt/QtHelpFunctions.hpp"
#include "../../Headerfiles/Tools/Editor/Editor.hpp"

ClickableQLabel::ClickableQLabel(QWidget* parent) : QLabel(parent) {
	connect(this, SIGNAL(clicked()), this, SLOT(labelClicked()));
}

void ClickableQLabel::mousePressEvent(QMouseEvent* mouseEvent) {
	emit clicked();
}

// slots
void ClickableQLabel::labelClicked() {
	
	bx::Editor* editor = static_cast<bx::Editor*>(QtHelpFunctions::getRelative("Editor", this));
	ClickableQLabel* oldClickedLabel = editor->getLastLabelClicked();

	if (oldClickedLabel != nullptr && oldClickedLabel != this) {
		oldClickedLabel->setStyleSheet("");
	}

	this->setStyleSheet("border-style: outset;\n" "border-width: 4px;\n" "border-color: rgb(199, 0, 100);\n");
	editor->setLastLabelClicked(this);
	editor->showSelectedImageSizeAndName();
	editor->apply();
}