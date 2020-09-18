#include "mytextplane.h"
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QMenu>


myTextPlane::myTextPlane()
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    filename = "undefined";
    isSaved = false;
    ptr = this;
    number = -1;
}

void myTextPlane::closeEvent(QCloseEvent *event)
{

    qDebug()<<"CLOSED";
    emit closed(event);
}

void myTextPlane::save()
{
    qDebug()<<"SAVE";
    if (!isSaved)
    {
        if (filename != "unassigned") {
            setWindowTitle(filename);
            file.setFileName(filename);
            if (file.open(QIODevice::WriteOnly))
            {
                QString str = toPlainText();
                QByteArray ba = str.toUtf8();
                if (file.write(ba, ba.length())!= -1)
                {
                    QFileInfo fileInfo(file);
                    setWindowTitle(fileInfo.fileName());
                    file.close();
                    isSaved = true;
                }
                else
                {
                    QMessageBox msgBox;
                    msgBox.setText(tr("Can't write file"));
                    msgBox.exec();
                }
            }
        } else saveAs();
    } else qDebug() << "Already saved";
}

void myTextPlane::saveAs()
{
    qDebug()<< filename;

    QString outputFileName = tr("New document(");
    outputFileName += QString::number(number);
    outputFileName += ").txt";
    QString newFileName = QFileDialog::getSaveFileName(this, tr("Save File"), outputFileName);
    if (newFileName.isEmpty()) return;
    else
    {
        isSaved = false;
        setFileName(newFileName);
        qDebug()<<filename;
        save();
    }
}

void myTextPlane::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu* menu = createStandardContextMenu(event->pos());
    QList<QAction*> actions = menu->actions();
    int position = 0;

    //Copy format Action button
    for (int i=0; i<actions.count(); ++i)
    {
        if (menu->actions().at(i)->objectName() == "edit-paste")
        {
            position = i;
            break;
        }
    }
    QAction* copyFormatAction = new QAction("Copy Format");
    QAction* pasteFormatAction = new QAction("Paste Format");
    menu->insertAction(actions[position+1], copyFormatAction);
    menu->insertAction(actions[position+1], pasteFormatAction);
    connect (copyFormatAction, &QAction::triggered, this, &myTextPlane::copyFormat);
    connect (pasteFormatAction, &QAction::triggered, this, &myTextPlane::pasteFormat);

    QAction* choosedAction = menu->exec(event->globalPos());
}

void myTextPlane::copyFormatSlot()
{
    emit copyFormat();
}

void myTextPlane::pasteFormatSlot()
{
    emit pasteFormat();
}













