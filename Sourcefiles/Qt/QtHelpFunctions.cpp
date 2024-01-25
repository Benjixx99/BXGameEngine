#include "../../Headerfiles/Qt/QtHelpFunctions.hpp"

QObject* QtHelpFunctions::getRelative(const std::string& name, const QObject* _this) {
	QObject* parent = _this->parent();
	QObject* out = nullptr;

	while (out == nullptr || out->objectName().toStdString() != name) {
		out = parent;
		parent = parent->parent();
	}
	return out;
}

void QtHelpFunctions::notification(const std::string& output, QLabel* const _this, const bool error) {
	_this->setText(QString::fromStdString(output));
	if (!error) { _this->setStyleSheet("color: rgb(41, 197, 51);"); }	// Green
	else		{ _this->setStyleSheet("color: rgb(202, 38, 41);"); }	// Red
}
