#include "HUD-dock.hpp"

HudWidget::HudWidget(QWidget *parent) : QDockWidget("Preach HUD Dock", parent) {
    this->parent = parent;

    //button widget to be added to a dock layout
    QWidget *widget = new QWidget();
    this->button->setText("Press me!");

    //Creation of dock layout
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(this->button);

    //Must let layout or will not function
    widget->setLayout(layout);

    setWidget(widget);

    setVisible(false); //Hides widget
    setFloating(true); //Will not be docked on first open (widgets position will be remembered on future app openings)
    resize(300, 300); //Size of window

    //Slot used to connect UI event to a function in the code.
    //Widget in question(button widget), Signal/Event to cause event to occur (the click), Slot which receives that signal/event (ButtonClickedResp())
    QObject::connect(button, SIGNAL(clicked()), SLOT(ButtonClickedResp()));
}

//Function called when the widget is deleted
HudWidget::~HudWidget() {

}

//Function that occurs on button click event
void HudWidget::ButtonClickedResp() {
    QMessageBox::information(this, "Info", "You clicked on a box!");
}