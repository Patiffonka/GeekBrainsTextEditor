#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTranslator>
#include <QMdiArea>
#include <mytextplane.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QPlainTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionQuit_triggered();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionHelp_triggered();
    void onTextChanged();
    void on_actionEnglish_triggered();
    void on_actionRussian_triggered();
    void on_actionDefault_triggered();
    void on_actionDark_triggered();
    void planeClosed(QCloseEvent* event);

    void on_actionSave_All_triggered();
    void changePlaineTextWindow();

    void on_actionPrint_triggered();

private:
    Ui::MainWindow *ui;
    QString windowtitle;
    QString fileName;               //REMOVE
    QFile file;                     //remove
    QString str;
    QPlainTextEdit *plainTextEdit; //REMOVE
    QTranslator translator;
    bool isSaved;                   //REMOVE
    QPalette* darkPalette;
    QPalette* whitePalette;
    QMdiArea* mdiArea;
    QList<myTextPlane*> TextPlains;
    QMdiSubWindow* activeWindow;
    bool saveAsMode;

    void NewDocument();
    void closeEvent(QCloseEvent *event) override;
    void setupPalette();

protected:
    void changeEvent(QEvent* event) override;

};
#endif // MAINWINDOW_H
