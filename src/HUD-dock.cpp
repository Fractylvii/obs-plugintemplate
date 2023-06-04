#include "HUD-dock.hpp"
#include <obs-frontend-api.h>
#include <obs-module.h>
#include <obs.hpp>
#include <util/util.hpp>
#include <util/base.h>

HudWidget::HudWidget(QWidget *parent) : QDockWidget("Preach HUD Dock", parent) {
    this->parent = parent;

    //button widget to be added to a dock layout
    QWidget *widgetTest = new QWidget();
    //this->button->setText("Press me!");

    textBox->setFrameStyle(QFrame::NoFrame);
    textBox->setStyleSheet("font-weight: bold; color: gray");
    textBox->setFont(parent->font());
    textBox->setText("Disabled");
    textBox->adjustSize();

    for(QScreen *availScreen : QGuiApplication::screens()) { // Potential: If user adds a new screen while OBS is on? 
        screenChoice->addItem(availScreen->name());
    }

    //Creation of dock layout
    QHBoxLayout *layout = new QHBoxLayout();
    //layout->addWidget(this->button);
    layout->addWidget(this->ioToggle);
    layout->addWidget(this->textBox);
    layout->addWidget(this->screenChoice);
    layout->addWidget(this->sceneChoice);

    //Must let layout or will not function
    widgetTest->setLayout(layout);

    setWidget(widgetTest);

    setVisible(true); //Hides widget
    setFloating(false); //Will not be docked on first open (widgets position will be remembered on future app openings)
    resize(300, 300); //Size of window

    //Slot used to connect UI event to a function in the code.
    //Widget in question(button widget), Signal/Event to cause event to occur (the click), Slot which receives that signal/event (ButtonClickedResp())
    //QObject::connect(button, SIGNAL(clicked()), SLOT(ButtonClickedResp()));
    bool success = QObject::connect(ioToggle, SIGNAL(stateChanged(int)), SLOT(ioToggleClickedResp()));
    //QObject::connect(sceneChoice, SIGNAL(QComboBox::dataChanged(int)), SLOT(loadScenes(this)));
    Q_ASSERT(success);
}

//Function called when the widget is deleted
HudWidget::~HudWidget() {
    releaseScenes();
}

//Function that occurs on button click event
void HudWidget::ButtonClickedResp() {
    QMessageBox::information(this, "Info", "You clicked on a box!");
}

void HudWidget::ioToggleClickedResp() {
    if(this->ioToggle->isChecked()){
        this->textBox->setText("Enabled");
        this->textBox->setStyleSheet("font-weight: bold; color: #42f554");
        QMessageBox::information(this, "Info", "You checked the toggle! (ON)");
    }
    else {
        this->textBox->setText("Disabled");
        this->textBox->setStyleSheet("font-weight: bold; color: gray");
        QMessageBox::information(this, "Info", "You checked the toggle! (OFF)");
    }
}

void HudWidget::addSceneItem(obs_source_t *source) {
    sceneChoice->addItem(obs_source_get_name(source));
}

void HudWidget::loadScenes() {
    sceneChoice->clear();
	obs_frontend_get_scenes(&scenes);
	for (size_t i = 0; i < scenes.sources.num; i++) {
		obs_source_t *source = scenes.sources.array[i];
		this->addSceneItem(source);
	}
}

void HudWidget::releaseScenes() {
    obs_frontend_source_list_free(&scenes);
}