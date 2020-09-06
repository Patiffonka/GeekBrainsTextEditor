#ifndef TOOLSWIDGET_H
#define TOOLSWIDGET_H

#include <QWidget>

class toolsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit toolsWidget(QWidget *parent = nullptr);

signals:
    void buttonSignal(QString text);

private slots:
    void on_Button1_Released();
    void on_Button2_Released();
    void on_Button3_Released();
};

#endif // TOOLSWIDGET_H
