#ifndef TOGGLE_H
#define TOGGLE_H

#include <QCheckBox>
#include <string>
#include <QWidget>
#include <QtGui>
#include <QLabel>
#include <QStyleOption>
#include <QtCore>
#include <QFont>

using namespace std;

class QioToggle : public QCheckBox {
    Q_OBJECT

    public:
        QioToggle(int width = 60, string bgColor = "#777", string circleColor = "#DDD", string activeColor = "#42f554");
    
    private:
        //QCheckBox *ioToggle = new QCheckBox();
        //QLabel *textBox = new QLabel(this);
        QString _bgColor;
        QString _circleColor;
        QString _activeColor;
        QEasingCurve animationCurve;
        QPropertyAnimation *anim;
        int circlePosition;
        Q_PROPERTY(int circlePos READ circleGet WRITE circleSet)

        void paintEvent(QPaintEvent *);
        bool hitButton(QPoint pos);
        int circleGet();
        void circleSet(int pos);
        void startTransition();

        void mousePressEvent(QMouseEvent *event);
        QTimer *toggleTimer;
};

#endif