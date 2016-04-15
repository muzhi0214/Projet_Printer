#ifndef NOUVEAUDIALOG_H
#define NOUVEAUDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QString>
#include <QMainWindow>
#include <QPushButton>
#include <QLayout>
#include <QComboBox>
#include <QAction>
#include <QButtonGroup>
#include <QLineEdit>
#include <QDir>
#include <QFileDialog>
#include <QRadioButton>
#include <QGroupBox>
#include <QString>

class NouveauDialog : public QMainWindow
{
public:
    NouveauDialog();
    ~NouveauDialog();
    QButtonGroup *type;
    QPushButton *finish;
    QPushButton *browseButton;
    //QPushButton *closeButton;
    QString s;
    QLineEdit *lineEdit;

    QComboBox *directoryComboBox;
    QDir currentDir;

    QRadioButton *noteRadioButton;
    QRadioButton *childNoteRadioButton;

    QString path;

signals:
    //void nouveauSection();
    //void nouveauNote();

private:
    QLabel *label;
    //QPushButton *section;
    //QPushButton *note;
    QLabel *lineLabel;
    QLabel *directoryLabel;

    QGroupBox *groupBox;


    QComboBox *createComboBox(const QString &text = QString());


};

#endif // NOUVEAUDIALOG_H
