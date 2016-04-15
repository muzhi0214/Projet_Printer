#include "petitwindow.h"
#include <QPushButton>
#include <QTextEdit>

petitwindow::petitwindow()
{

     QTextEdit* text = new QTextEdit("Coucou je suis une QMainWindow", this);

    setCentralWidget(text);



}
