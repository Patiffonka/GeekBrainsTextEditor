#ifndef MYTEXTPLANE_H
#define MYTEXTPLANE_H

#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>
#include <QFile>

class myTextPlane : public QPlainTextEdit
{
    Q_OBJECT

public:
    myTextPlane();

    QFile file;
    void setFileName(QString name) {filename = name;}
    void setIsSaved (bool value) {isSaved = value;}
    QString getFileName() {return filename;}
    bool getIsSaved() {return isSaved;}
    void closeEvent(QCloseEvent *event) override;
    void setPtr(myTextPlane* newPtr) { ptr = newPtr; }
    myTextPlane* getPtr() { return ptr; }
    void save();
    void saveAs();
    void setNumber(int n) {number = n;}
    int getNumber() {return number;}

private:
    QString filename;
    bool isSaved;
    myTextPlane* ptr;
    int number;
    void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
    void copyFormatSlot();
    void pasteFormatSlot();

signals:
    void closed(QCloseEvent*);
    void copyFormat();
    void pasteFormat();
};

#endif // MYTEXTPLANE_H
