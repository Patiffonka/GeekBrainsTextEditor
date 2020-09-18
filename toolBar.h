#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QObject>
#include <QWidget>
#include <QMenuBar>

class toolBar : public QMenuBar
{
    Q_OBJECT
public:
    toolBar();

private slots:
    void alignLeft();
    void alignRight();
    void alignCenter();
    void font();

signals:
    void alignLeftSignal();
    void alignRightSignal();
    void alignCenterSignal();
    void fontSignal();
};

#endif // TOOLBAR_H
