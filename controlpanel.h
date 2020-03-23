#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QDockWidget>

namespace Ui {
class ControlPanel;
}

class ControlPanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = 0);
    ~ControlPanel();

private:
    Ui::ControlPanel *ui;
};

#endif // CONTROLPANEL_H
