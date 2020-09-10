#include "mytextplane.h"
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>

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













