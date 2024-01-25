#include "../../Headerfiles/Qt/MovableQFrame.hpp"
#include "../../Headerfiles/Qt/QtHelpFunctions.hpp"
#include "../../Headerfiles/Tools/Editor/Editor.hpp"

MovableQFrame::MovableQFrame(QWidget* parent) : QFrame(parent) {}

void MovableQFrame::setRelativeName(const std::string& name) {
	relativeName = name;
}

std::string MovableQFrame::getRelativeName() const {
	return relativeName;
}

void MovableQFrame::mousePressEvent(QMouseEvent* mouseEvent) {
	bx::Editor* editor = static_cast<bx::Editor*>(QtHelpFunctions::getRelative(relativeName, this));
	lastMousePosition = QCursor::pos();
	lastWindowsPosition = editor->pos();
}


void MovableQFrame::mouseMoveEvent(QMouseEvent* mouseEvent) {
	if (Qt::LeftButton) {
		bx::Editor* editor = static_cast<bx::Editor*>(QtHelpFunctions::getRelative(relativeName, this));
		editor->move(lastWindowsPosition + QCursor::pos() - lastMousePosition);
	}
}