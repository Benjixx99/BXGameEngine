#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>
#include <string>

namespace QtHelpFunctions {
	QObject* getRelative(const std::string& name, const QObject* _this);
	void notification(const std::string& output, QLabel* const _this, const bool error = false);
}