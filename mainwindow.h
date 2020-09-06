#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTranslator>

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
    void on_tool_signal(QString text);
    void on_actionDefault_triggered();
    void on_actionDark_triggered();

private:
    Ui::MainWindow *ui;
    QString windowtitle;
    QString fileName;
    QFile file;
    QString str;
    QPlainTextEdit *plainTextEdit;
    QTranslator translator;
    bool isSaved;
    QPalette* darkPalette;
    QPalette* whitePalette;

    void NewDocument();
    void closeEvent(QCloseEvent *event) override;
    void setupPalette();

protected:
    void changeEvent(QEvent* event) override;

};
#endif // MAINWINDOW_H
