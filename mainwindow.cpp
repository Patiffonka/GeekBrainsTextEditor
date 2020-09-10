#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QMdiSubWindow>
#include <QFileInfo>
#include <QPrinter>
#include <QPrintDialog>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    saveAsMode = false;

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

    mdiArea = new QMdiArea(this);

    NewDocument();

    mdiArea->setViewMode(QMdiArea::TabbedView);
    mdiArea->setTabsClosable(true);
    connect (mdiArea, &QMdiArea::subWindowActivated, this, &MainWindow::changePlaineTextWindow);

    layout->addWidget(mdiArea);

    QWidget *wgt = new QWidget(this);
    wgt->setLayout(layout);
    setCentralWidget(wgt);

    setupPalette();
    qApp->setPalette(*whitePalette);

    //setStyleSheet("QTabBar::tab { max-width: 100px; }");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    qDebug()<<"CLOSE APP";
    if (mdiArea->subWindowList().count() > 0)
    {
        bool needSave = false;
        for (int i = 0; i < mdiArea->subWindowList().count(); ++i)
        {
            myTextPlane* textPlane = (myTextPlane*)mdiArea->subWindowList().at(i)->widget();
            if (!textPlane->getIsSaved())
            {
                needSave = true;
                qDebug()<<"Unsaved documents";
                break;
            }
        }

        if (needSave)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, tr("Unsaved documents"), tr("You have unsaved documents. Do you want to save all documents?"),
                                                    QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
            if (reply == QMessageBox::Yes)
            {
                for (int i = 0; i < mdiArea->subWindowList().count(); ++i)
                {
                    myTextPlane* textPlane = (myTextPlane*)mdiArea->subWindowList().at(i)->widget();
                    textPlane->save();
                }
            }
            else if (reply == QMessageBox::No)
            {
                event->accept();
            }
            else if (reply == QMessageBox::Cancel)
            {
                event->ignore();
            }
        } else event->accept();
    } else event->accept();
}

void MainWindow::setupPalette()            //NEED TO SETUP HINTS AND MDIAREA
{
    //DARK
    darkPalette = new QPalette();
    darkPalette->setColor(QPalette::Window, QColor(53,53,53));
    darkPalette->setColor(QPalette::WindowText, Qt::black);
    darkPalette->setColor(QPalette::Base, QColor(25,25,25));
    darkPalette->setColor(QPalette::Text, Qt::gray);

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
    QMdiSubWindow* newSubwindow = mdiArea->addSubWindow(new myTextPlane);
    newSubwindow->show();
    myTextPlane* newPlainText = (myTextPlane*)newSubwindow->widget();
    newPlainText->setIsSaved(true);
    newPlainText->setFileName("unassigned");
    newPlainText->setPtr(newPlainText);
    QString newDocName = tr("New document");
    newPlainText->setNumber(mdiArea->subWindowList().count());
    newDocName += " ";
    newDocName += QString::number(newPlainText->getNumber());
    newPlainText->setWindowTitle(newDocName);
    setWindowTitle(newPlainText->windowTitle());
    connect (newPlainText, &QPlainTextEdit::textChanged, this, &MainWindow::onTextChanged);
    connect (newPlainText, &myTextPlane::closed, this, &MainWindow::planeClosed);
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionNew_triggered()
{
    NewDocument();
}

void MainWindow::on_actionOpen_triggered()
{
    QString newfileName = QFileDialog::getOpenFileName(this, tr("Open"));
    if (newfileName.isEmpty()) return;
    else {

        fileName = newfileName;
        file.setFileName(fileName);
        if (file.open(QIODevice::ReadWrite)) {

            QMdiSubWindow* newSubwindow = mdiArea->addSubWindow(new myTextPlane);
            newSubwindow->show();
            myTextPlane* newPlainText = (myTextPlane*)newSubwindow->widget();
            TextPlains.push_back(newPlainText);

            newPlainText->setFileName(fileName);
            QFileInfo fileInfo(file);
            newPlainText->setWindowTitle(fileInfo.fileName());

            QByteArray ba = file.readAll();
            newPlainText->setPlainText(ba.data());
            newPlainText->moveCursor(QTextCursor::End);
            file.close();
            newPlainText->setIsSaved(true);
            connect (newPlainText, &QPlainTextEdit::textChanged, this, &MainWindow::onTextChanged);
        }
    }
}

void MainWindow::on_actionSave_triggered()
{

    myTextPlane* plainText = (myTextPlane*)mdiArea->activeSubWindow()->widget();

    plainText->save();

    qDebug()<<"ACTION SAVE";

}

void MainWindow::on_actionSave_As_triggered()
{
    myTextPlane* plainText = (myTextPlane*)mdiArea->activeSubWindow()->widget();

    plainText->saveAs();

    qDebug()<<"ACTION SAVE AS";
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
    myTextPlane* planeTextEdit = (myTextPlane*) sender();
    if (planeTextEdit == nullptr)
    {
        qDebug() << "ERROR! planeTextEdit is null";
        return;
    }
    if (planeTextEdit->getIsSaved())
    {
    QString newTitle = planeTextEdit->windowTitle() += "*";
    planeTextEdit->setWindowTitle(newTitle);
    planeTextEdit->setIsSaved(false);
    }
}

void MainWindow::on_actionEnglish_triggered()
{
    translator.load(":/translations/QtLangage_en.qm");
    qApp->installTranslator(&translator);
}

void MainWindow::on_actionRussian_triggered()
{
    translator.load(":/translations/QtLangage_ru.qm");
    qApp->installTranslator(&translator);
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

void MainWindow::planeClosed(QCloseEvent* event)
{
    event->ignore();
    myTextPlane *textPlain = (myTextPlane*)sender();
    qDebug()<<"recieve Plane closed signal (" << textPlain->getFileName() << ")";
    if (textPlain->getIsSaved()) event->accept();
    else
    {
        QMessageBox::StandardButton reply;

        QString question = tr("Do you want to save ");
        question += textPlain->windowTitle();
        question += "?";

        reply = QMessageBox::question(this, tr("Unsaved document"), question,
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
}

void MainWindow::on_actionSave_All_triggered()
{
    qDebug()<<"Save all...";

    if (mdiArea->subWindowList().count() > 0)
    {
        for (int i = 0; i < mdiArea->subWindowList().count(); ++i)
        {

            myTextPlane* textPlane = (myTextPlane*)mdiArea->subWindowList().at(i)->widget();
            textPlane->save();
        }
    }

}

void MainWindow::changePlaineTextWindow()
{
    if ((mdiArea->subWindowList().count()>0) && (mdiArea->isActiveWindow()))
    {
        myTextPlane* textPlane = (myTextPlane*)mdiArea->activeSubWindow()->widget();
        setWindowTitle(textPlane->windowTitle());
    }

}

void MainWindow::on_actionPrint_triggered()
{
    QMdiSubWindow* activeWindow = mdiArea->activeSubWindow();
    if (!activeWindow) return;
    QWidget *wgt = activeWindow->widget();
    QTextEdit* tEdit = (QTextEdit*)wgt;


    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle("Print");
    if (dlg.exec() != QDialog::Accepted) return;
    tEdit->print(&printer);
}
