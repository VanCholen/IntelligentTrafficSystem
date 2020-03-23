#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include <QWidget>
#include <QPushButton>
namespace Ui {
class LeftWidget;
}

class LeftWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LeftWidget(QWidget *parent = 0);
    ~LeftWidget();

private:
    Ui::LeftWidget *ui;


public:
    QPushButton* getBtnCarControl();
    QPushButton* getBtnCarLacation();
    QPushButton* getBtnDataMonitor();
    QPushButton* getBtnHome();
    QPushButton* getBtnRoadControl();
};

#endif // LEFTWIDGET_H
