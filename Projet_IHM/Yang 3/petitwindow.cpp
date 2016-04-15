#include "petitwindow.h"
#include <QPushButton>
#include <QTextEdit>

petitwindow::petitwindow()
{

    text = new QTextEdit("Coucou je suis une QMainWindow", this);
    /**
     this->setStyleSheet( " QTextEdit { background : yellow; border : none;} ");

     setWindowFlags(Qt::FramelessWindowHint);

     **/

    setCentralWidget(text);



}
