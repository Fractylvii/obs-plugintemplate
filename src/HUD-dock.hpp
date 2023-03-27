#ifndef TEST_H
#define TEST_H

#include <QDockWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>

class HudWidget : public QDockWidget {
	Q_OBJECT

	public:
		explicit HudWidget(QWidget *parent = nullptr);
		~HudWidget();

	private:
		void buttonClicked();
		QWidget *parent = nullptr;
		QPushButton *button = new QPushButton();

	private slots:
	void ButtonClickedResp();
};

#endif