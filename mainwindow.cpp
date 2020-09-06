#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include "toolswidget.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fileName = "unassigned";
    isSaved = true;

    //Translation menu setup
    windowtitle = tr("New file");
    this->setWindowTitle(windowtitle);

    ui->menuFile->setTitle(tr("File"));
    ui->menuHelp->setTitle(tr("Help"));
    ui->menuLanguage->setTitle(tr("Language"));
    ui->actionNew->setText(tr("New"));
    ui->actionOpen->setText(tr("Open"));
    ui->actionSave->setText(tr("Save"));
    ui->actionSave_As->setText(tr("Save As"));
    ui->actionQuit->setText(tr("Quit"));
    ui->actionEnglish->setText(tr("English"));
    ui->actionRussian->setText(tr("Russian"));
    ui->actionHelp->setText(tr("Help"));

    QHBoxLayout *layout = new QHBoxLayout(this);

    plainTextEdit = new QPlainTextEdit(this);
    connect(plainTextEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

//#Tool menu for another lession
//    toolsWidget *tools = new toolsWidget(this);

    layout->addWidget(plainTextEdit);

//    layout->addWidget(tools);
//    connect (tools, SIGNAL(buttonSignal(QString)), this, SLOT(on_tool_signal(QString)));

    QWidget *wgt = new QWidget(this);
    wgt->setLayout(layout);
    setCentralWidget(wgt);

    setupPalette();
    qApp->setPalette(*whitePalette);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (!isSaved)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Unsaved document"), tr("All unsaved changes will be lost.\nDo you want save document?"),
                                    QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if (reply == QMessageBox::Yes)
        {
            on_actionSave_triggered();
            event->accept();
        }
        else if (reply == QMessageBox::No)
        {
            event->accept();
        }
        else if (reply == QMessageBox::Cancel)
        {
            event->ignore();
        }
    }
    else event->accept();
}

void MainWindow::setupPalette()
{
    //DARK
    darkPalette = new QPalette();
    darkPalette->setColor(QPalette::Window, QColor(53,53,53));
    darkPalette->setColor(QPalette::WindowText, Qt::white);
    darkPalette->setColor(QPalette::Base, QColor(25,25,25));
    darkPalette->setColor(QPalette::Text, Qt::white);

    //WHITE
    whitePalette = new QPalette();
    whitePalette->setColor(QPalette::Window, QColor(240,240,240));
    whitePalette->setColor(QPalette::WindowText, Qt::black);
    whitePalette->setColor(QPalette::Base, Qt::white);
    whitePalette->setColor(QPalette::Text, Qt::black);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NewDocument()
{
    plainTextEdit->clear();
    fileName = "unassigned";
    isSaved = true;
    windowtitle = tr("New file");
    this->setWindowTitle(windowtitle);
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionNew_triggered()
{
    if (!isSaved)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Unsaved document"), tr("All unsaved changes will be lost.\nAre you sure you want to create new document?"),
                                    QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QMessageBox::StandardButton reply2;
            reply2 = QMessageBox::question(this, tr("Unsaved document"), tr("Do you want to save document?"),
                                        QMessageBox::Yes|QMessageBox::No);
            if (reply2 == QMessageBox::Yes)
            {
                on_actionSave_triggered();
                NewDocument();
            }
            else NewDocument();
        } else return;
    } else NewDocument();
}

void MainWindow::on_actionOpen_triggered()
{
    QString newfileName = QFileDialog::getOpenFileName(this, tr("Open"));
    if (newfileName.isEmpty()) return;
    else {
        fileName = newfileName;
        file.setFileName(fileName);
        if (file.open(QIODevice::ReadWrite)) {
            QByteArray ba = file.readAll();
            plainTextEdit->setPlainText(ba.data());
            plainTextEdit->moveCursor(QTextCursor::End);
            windowtitle = fileName;
            this->setWindowTitle(windowtitle);
            file.close();
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    if (!isSaved) {
        if (fileName != "unassigned"){
            windowtitle = fileName;
            this->setWindowTitle(windowtitle);
            file.setFileName(fileName);
            if (file.open(QIODevice::WriteOnly)){

                str = plainTextEdit->toPlainText();
                QByteArray ba = str.toUtf8();

                if (file.write(ba, ba.length())!= -1) {
                    this->setWindowTitle(windowtitle);
                    file.close();
                    isSaved = true;
                } else

                {
                    QMessageBox msgBox;
                    msgBox.setText(tr("Can't write file"));
                    msgBox.exec();
                }

            }

        } else MainWindow::on_actionSave_As_triggered();

    } else qDebug() << "Already saved";

}

void MainWindow::on_actionSave_As_triggered()
{
    QString newFileName = QFileDialog::getSaveFileName(this, tr("Save File"), "NewText.txt");
    if (newFileName.isEmpty()) return;
    else {
        isSaved = false;
        fileName = newFileName;
        on_actionSave_triggered();
    }
}

void MainWindow::on_actionHelp_triggered()
{
    QString helpMsg;
    QString helpFileName = ":/hlp/help.txt";
    QFile helpFile(helpFileName);
    if (helpFile.open(QIODevice::ReadOnly)){
        QByteArray ba = helpFile.readAll();
        helpMsg = ba.data();
    } else helpMsg = tr("Can't open help");
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Help"));
    msgBox.setText(helpMsg);
    msgBox.exec();
}

void MainWindow::onTextChanged()
{
    if (isSaved)
    {
    windowtitle += "*";
    this->setWindowTitle(windowtitle);
    isSaved = false;
    }
}


void MainWindow::on_actionEnglish_triggered()
{
    qDebug() << "English";
    translator.load(":/translations/QtLangage_en.qm");
    qApp->installTranslator(&translator);
}

void MainWindow::on_actionRussian_triggered()
{
    qDebug() << "Russian";
    translator.load(":/translations/QtLangage_ru.qm");
    qApp->installTranslator(&translator);
}

void MainWindow::on_tool_signal(QString text)
{
    plainTextEdit->appendPlainText(text);
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
        windowtitle = tr("New file");
        this->setWindowTitle(windowtitle);
    }
}


void MainWindow::on_actionDefault_triggered()
{
    qApp->setPalette(*whitePalette);
}

void MainWindow::on_actionDark_triggered()
{
    qApp->setPalette(*darkPalette);
}
