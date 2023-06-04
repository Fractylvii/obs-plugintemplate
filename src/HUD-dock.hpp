#ifndef HUDDOCK_H
#define HUDDOCK_H

#include <QDockWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include <obs-frontend-api.h>
#include <obs-module.h>
#include "plugin-macros.generated.hpp"

#include "QioToggle.hpp"

class HudWidget : public QDockWidget {
	Q_OBJECT

	public:
		explicit HudWidget(QWidget *parent = nullptr);
		void addSceneItem(obs_source_t *source);
		~HudWidget();
		//QPushButton *button = new QPushButton();
		void loadScenes();
		void releaseScenes();

	private:
		QWidget *parent = nullptr;
		//QPushButton *button = new QPushButton(); //Test button
		QioToggle *ioToggle = new QioToggle(); // On/off toggle button
		QLabel *textBox = new QLabel(this);
		QComboBox *screenChoice = new QComboBox(); //Drop-down to choose which monitor to display HUD on
		QComboBox *sceneChoice = new QComboBox();

		struct obs_frontend_source_list scenes = {};

	private slots:
	void ButtonClickedResp();
	void ioToggleClickedResp();
};

#endif