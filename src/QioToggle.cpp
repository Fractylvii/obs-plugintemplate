#include "QioToggle.hpp"

QioToggle::QioToggle(int width, string bgColor, string circleColor, string activeColor) {
    //Default Parameters
    setFixedSize(width, 28);
    setCursor(Qt::PointingHandCursor);

    //Colors
    _bgColor = QString::fromStdString(bgColor);
    _circleColor = QString::fromStdString(circleColor);
    _activeColor = QString::fromStdString(activeColor);
    animationCurve = QEasingCurve::OutQuint;
    circlePosition = 3;
    this->toggleTimer = new QTimer(this);
    this->setText("HUD Overlay: Disabled");

    //Create animation
    anim = new QPropertyAnimation(this, "circlePos", this);
    anim->setEasingCurve(animationCurve);
    anim->setDuration(500); //time in ms
}

void QioToggle::paintEvent(QPaintEvent *) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    p.setRenderHint(QPainter::Antialiasing);

    p.setPen(Qt::NoPen);

    //Draw rectangle
    QRect rect = QRect(0, 0, width(), height());

    //Draw Circle
    if(!(isChecked())) {
        //Draw BG (off)
        p.setBrush(QColor(_bgColor));
        p.drawRoundedRect(0, 0, width(), height(), height()/2, height()/2);

        //Draw Circle (off)
        p.setBrush(QColor(_circleColor));
        p.drawEllipse(circlePosition, 3, 22, 22);
    }
    else {
        //Draw BG (on)
        p.setBrush(QColor(_activeColor));
        p.drawRoundedRect(0, 0, width(), height(), height()/2, height()/2);

        //Draw Circle (on)
        p.setBrush(QColor(_circleColor));
        p.drawEllipse(circlePosition, 3, 22, 22);
    }
    //End Draw
    p.end();

    /*textBox->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    textBox->setText("Hud Toggleeeeee\nsecond lineeeeee");
    textBox->setAlignment(Qt::AlignBottom);
    textBox->adjustSize();*/
}


bool QioToggle::hitButton(QPoint pos) {
    return contentsRect().contains(pos);
}


int QioToggle::circleGet() {
    return circlePosition;
}

void QioToggle::circleSet(int pos) {
    circlePosition = pos;
    update();
}

void QioToggle::startTransition() {
    if(this->isChecked()) {
        anim->setStartValue(circleGet());
        anim->setEndValue(width()-26);
    }
    else {
        anim->setStartValue(circleGet());
        anim->setEndValue(3);
    }
    anim->start();
}

void QioToggle::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && !(toggleTimer->isActive())) {
        toggle();
        startTransition();
        toggleTimer->setSingleShot(true);
        toggleTimer->start(500);
    }
}