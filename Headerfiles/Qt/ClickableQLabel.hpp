#pragma once

#include <QtWidgets/QLabel>

class ClickableQLabel : public QLabel {
	Q_OBJECT
private:
	void mousePressEvent(QMouseEvent* mouseEvent);
signals:
	void clicked();
public:
	ClickableQLabel(QWidget* parent = nullptr);
public slots:
	void labelClicked();
};