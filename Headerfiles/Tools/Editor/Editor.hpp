#pragma once

#include <QtWidgets/QWidget>
#include "ui_Editor.h"

#include "../../Qt/ClickableQLabel.hpp"
#include "../../Qt/MovableQFrame.hpp"

#include "../../Config/Config.hpp"
#include "../../SharedDataStructure.hpp"

// TODO: Add a tab to config rendering 
// TODO: Add a tab to show the content of log files
// TODO: Add a tab in which one can see the details of an entity -> click on it and get the information
// TODO: Add a view possibility for NPCs data
// TODO: Add a 'fly view' on the window. Loose from the player

namespace bx {

	enum class MainTab {
		Level_Design,
		Configuration
	};

	enum class ShowImagesTab {
		Tiles,
		NPCs
	};

	enum class NPCsBehavior {
		FollowPath,
		FollowPrimitive,
		Patrol
	};

	struct WidgetSize {
		uint top = 0;
		uint left = 0;
	};

	struct LastClickedLabels {
		ClickableQLabel* clbl_Tiles = nullptr;
		ClickableQLabel* clbl_NPCs = nullptr;
	};

	class Editor : public QWidget {
		Q_OBJECT
	private:
		void init();
		void setLabelAndCalculateNextLabelPosition(const std::vector<std::string>& entry, 
			QFrame* fra_Show, WidgetSize& size);
		WidgetSize& calculateLeftAndTop(WidgetSize& size);
		
		std::string getNPCsBehaviorName();

		void clickedOnButton(QPushButton* button, bool& selected);
		void selectButton(QPushButton* button, bool& selected);
		void unselectButton(QPushButton* button, bool& selected);
		
		bool event(QEvent* event);
	public:
		Editor(EditorSharedData& sharedData, QWidget* parent = nullptr);
		~Editor();

		void setLastLabelClicked(ClickableQLabel* label);
		ClickableQLabel* getLastLabelClicked();
		void showSelectedImageSizeAndName();

	public slots:
		void apply();
		void customHide();
		void saveLevel();
		void addPatrolPosition();
		void selectPatrolPosition();
		void selectTargetPosition();
		void resetData();

		void add();
		void drag();
		void draw();
		void remove();
	private:
		Ui::Editor ui;
		LastClickedLabels lastClickedLabels;
		const uint boxWidth = 68, boxHeight = 68;
		const uint MAXWIDTH = 272;

		EditorSharedData& sharedData;
	};
}