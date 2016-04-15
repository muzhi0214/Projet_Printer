#include "fichier.h"
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include<QTextEdit>
#include <QAction>


fichier::fichier()
{


    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);


    /*********BOUTONS *******************/

    QPushButton* undo = new QPushButton(this);
    undo->setIcon(QIcon (":/Icône/undo.png"));
    undo->setFixedSize(30,30);
    undo -> setIconSize(QSize(20,20));
     //connect(enregistrer,SIGNAL(triggered()),this,SLOT(saveFile()));

    QPushButton* redo = new QPushButton(this);
    redo->setIcon(QIcon (":/Icône/redo.png"));
    redo->setFixedSize(30,30);
    redo -> setIconSize(QSize(20,20));
     //connect(enregistrer,SIGNAL(triggered()),this,SLOT(saveFile()));

    QPushButton* open = new QPushButton(this);
    open->setIcon(QIcon (":/Icône/open.png"));
    open->setFixedSize(30,30);
    open -> setIconSize(QSize(20,20));
     //connect(enregistrer,SIGNAL(triggered()),this,SLOT(saveFile()));

    QPushButton* save = new QPushButton(this);
    save->setIcon(QIcon (":/Icône/save.png"));
    save->setFixedSize(30,30);
    save -> setIconSize(QSize(20,20));
     //connect(enregistrer,SIGNAL(triggered()),this,SLOT(saveFile()));


    this->setStyleSheet(
                "QWidget { background : #bbe0bb;}"
                "QPushButton{  background : #bbe0bb; border: none; }"
                "QPushButton::pressed { background : #90c790; }"
                );


    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(10,10,10,10);
    layout->setSpacing(10);
    layout->addWidget(undo );
    layout ->addWidget(redo );
    layout ->addWidget(open );
    layout ->addWidget(save, 0 ,  Qt::AlignLeft);
     centralWidget->setLayout(layout);




}
