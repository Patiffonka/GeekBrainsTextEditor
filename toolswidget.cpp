#include "toolswidget.h"
#include <QPushButton>
#include <QGridLayout>
#include <qdebug.h>
#include <QLabel>

toolsWidget::toolsWidget(QWidget *parent) : QWidget(parent)
{
    int button_size = 50;
    int margin =10;

    QGridLayout *layout = new QGridLayout(this);

    QLabel *label = new QLabel(tr("ASKII ART"), this);

    QFrame *line;
    line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    QFrame *line2;

    line2 = new QFrame(this);
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);

    QPushButton *b1 = new QPushButton(tr("WORLD"), this);
    QPushButton *b2 = new QPushButton(tr("CAT"), this);
    QPushButton *b3 = new QPushButton(tr("GEEK BRAINS"), this);


    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(10);

    layout->addWidget(label, 0,0,1,2);
    layout->addWidget(line, 1,0,1,2);
    layout->addWidget(b1, 2,0,1,1);
    layout->addWidget(b2, 2,1,1,1);
    layout->addWidget(b3, 3,0,1,2);
    layout->addWidget(line2, 4,0,1,2);

    label->setAlignment(Qt::AlignHCenter);
    b1->setMaximumWidth(button_size);
    b1->setMinimumWidth(button_size);
    b2->setMaximumWidth(button_size);
    b2->setMinimumWidth(button_size);
    b3->setMaximumWidth(button_size*2+margin);
    b3->setMinimumWidth(button_size*2+margin);

    connect(b1, SIGNAL(released()), this, SLOT(on_Button1_Released()));
    connect(b2, SIGNAL(released()), this, SLOT(on_Button2_Released()));
    connect(b3, SIGNAL(released()), this, SLOT(on_Button3_Released()));
}

void toolsWidget::on_Button1_Released()
{
    QString text = "╔╗╔╗╔═╗╔╗─╔╗─╔═╗     ╔╦═╦╗╔═╗╔═╗╔╗─╔══╗\n"
                   "║╚╝║║╦╝║║─║║─║║║     ║║║║║║║║║╬║║║─╚╗╗║\n"
                   "║╔╗║║╩╗║╚╗║╚╗║║║     ║║║║║║║║║╗╣║╚╗╔╩╝║\n"
                   "╚╝╚╝╚═╝╚═╝╚═╝╚═╝     ╚═╩═╝╚═╝╚╩╝╚═╝╚══╝";


    emit buttonSignal(text);
}

void toolsWidget::on_Button2_Released()
{

    QString text =
            "▒▒▒▒▒▒▒▒█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█ \n"
            "▒▒▒▒▒▒▒█░▒▒▒▒▒▒▒▓▒▒▓▒▒▒▒▒▒▒░█ \n"
            "▒▒▒▒▒▒▒█░▒▒▓▒▒▒▒▒▒▒▒▒▄▄▒▓▒▒░█░▄▄ \n"
            "▒▒▄▀▀▄▄█░▒▒▒▒▒▒▓▒▒▒▒█░░▀▄▄▄▄▄▀░░█ \n"
            "▒▒█░░░░█░▒▒▒▒▒▒▒▒▒▒▒█░░░░░░░░░░░█ \n"
            "▒▒▒▀▀▄▄█░▒▒▒▒▓▒▒▒▓▒█░░░█▒░░░░█▒░░█ \n"
            "▒▒▒▒▒▒▒█░▒▓▒▒▒▒▓▒▒▒█░░░░░░░▀░░░░░█ \n"
            "▒▒▒▒▒▄▄█░▒▒▒▓▒▒▒▒▒▒▒█░░█▄▄█▄▄█░░█ \n"
            "▒▒▒▒█░░░█▄▄▄▄▄▄▄▄▄▄█░█▄▄▄▄▄▄▄▄▄█ \n"
            "▒▒▒▒█▄▄█░░█▄▄█░░░░░░█▄▄█░░█▄▄█";
    emit buttonSignal(text);
}

void toolsWidget::on_Button3_Released()
{
    QString text =
                "╔═╗──────╔╗─     ╔╗────────╔╗────╔═╗\n"
                "║╬║╔═╗╔═╗║╠╗     ║╚╗╔╦╗╔═╗─╠╣╔═╦╗║═╣\n"
                "╠╗║║╩╣║╩╣║═╣     ║╬║║╔╝║╬╚╗║║║║║║╠═║\n"
                "╚═╝╚═╝╚═╝╚╩╝     ╚═╝╚╝─╚══╝╚╝╚╩═╝╚═╝";
    emit buttonSignal(text);
}
