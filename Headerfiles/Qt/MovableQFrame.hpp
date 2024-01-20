#pragma once

#include <QtWidgets/QFrame>

class MovableQFrame : public QFrame {
	Q_OBJECT
private:
	void mousePressEvent(QMouseEvent* mouseEvent);
	void mouseMoveEvent(QMouseEvent* mouseEvent);
public:
	MovableQFrame(QWidget* parent = nullptr);
	void setRelativeName(const std::string& name);
	std::string getRelativeName() const;
private:
	QPoint lastMousePosition;
	QPoint lastWindowsPosition;
	std::string relativeName = "";
};