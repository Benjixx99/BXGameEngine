#pragma once

#include <QtWidgets/QWidget>
#include "ui_LevelNameDialog.h"

#include "../../Qt/MovableQFrame.hpp"

namespace bx {

	class LevelName : public QDialog {
		Q_OBJECT
	private:

	public:
		LevelName(QWidget* parent = nullptr);
		~LevelName();
		std::string getLevelName() const;
		bool isCancelled() const;
	public slots:
		void ok();
		void cancel();
	private:
		Ui::LevelName ui;
		bool cancelled = false;
	};
}