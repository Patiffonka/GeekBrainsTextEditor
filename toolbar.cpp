#include "toolBar.h"
#include <QAction>
#include <QIcon>
#include <QDebug>


toolBar::toolBar()
{
    QMenuBar* toolbar = new QMenuBar(this);

    QAction* alignLeft = new QAction (tr("Align Left"), this);
    QAction* alignRight = new QAction (tr("Align Right"), this);
    QAction* alignCenter = new QAction (tr("Align Center"), this);
    QAction* font = new QAction (tr("Font"), this);

    QList<QAction*> ToolbarActionList = {
        alignLeft, alignRight, alignCenter, font
    };

    QIcon alignleftIcon(":/img/img/align_left.png");
    QIcon alignRightIcon(":/img/img/align_right.png");
    QIcon alignCenterIcon(":/img/img/align_center.png");
    QIcon fontIcon(":/img/img/font.png");


    alignLeft->setIcon(alignleftIcon);
    alignRight->setIcon(alignRightIcon);
    alignCenter->setIcon(alignCenterIcon);
    font->setIcon(fontIcon);

    toolbar->addActions(ToolbarActionList);

    connect (alignLeft, &QAction::triggered, this, &toolBar::alignLeft);
    connect (alignRight, &QAction::triggered, this, &toolBar::alignRight);
    connect (alignCenter, &QAction::triggered, this, &toolBar::alignCenter);
    connect (font, &QAction::triggered, this, &toolBar::font);
}

void toolBar::alignLeft()
{
    qDebug() << "alignLeft Action";
    emit alignLeftSignal();
}

void toolBar::alignRight()
{
    qDebug() << "alignRight Action";
    emit alignRightSignal();
}

void toolBar::alignCenter()
{
    qDebug() << "alignCenter Action";
    emit alignCenterSignal();
}

void toolBar::font()
{
    qDebug() << "font Action";
    emit fontSignal();
}
