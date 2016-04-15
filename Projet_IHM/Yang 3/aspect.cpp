#include "aspect.h"
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QHBoxLayout>


aspect::aspect()
{


    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);


    /*********BOUTONS *******************/

    QPushButton* bold = new QPushButton(this);
    bold->setIcon(QIcon (":/Icône/bold.png"));
    bold->setFixedSize(30,30);
    bold -> setIconSize(QSize(20,20));
     //connect(enregistrer,SIGNAL(triggered()),this,SLOT(saveFile()));

    QPushButton* underline = new QPushButton(this);
    underline->setIcon(QIcon (":/Icône/underline.png"));
    underline->setFixedSize(30,30);
    underline -> setIconSize(QSize(20,20));
     //connect(enregistrer,SIGNAL(triggered()),this,SLOT(saveFile()));

    QPushButton* italic = new QPushButton(this);
    italic->setIcon(QIcon (":/Icône/italic.png"));
    italic->setFixedSize(30,30);
    italic -> setIconSize(QSize(20,20));
     //connect(enregistrer,SIGNAL(triggered()),this,SLOT(saveFile()));



    this->setStyleSheet(
                "QWidget { background : #bbe0bb;}"
                "QPushButton{  background : #bbe0bb; border: none; }"
                "QPushButton::pressed { background : #90c790; }"
                );


    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(10,10,10,10);
    layout->setSpacing(10);
    layout->addWidget(bold );
    layout->addWidget(underline );
    layout ->addWidget(italic, 0 ,  Qt::AlignLeft);
     centralWidget->setLayout(layout);




}
