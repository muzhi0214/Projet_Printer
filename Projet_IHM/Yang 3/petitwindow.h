#ifndef PETITWINDOW_H
#define PETITWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

class petitwindow : public QMainWindow
{
public:
    petitwindow();
    QTextEdit* text;
};

#endif // PETITWINDOW_H
