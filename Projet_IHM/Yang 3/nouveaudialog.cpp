#include "nouveaudialog.h"

NouveauDialog::NouveauDialog()

{
    QWidget *widget = new QWidget();
    this->setCentralWidget(widget);

    setWindowTitle(tr("Nouveau"));
    setFixedSize(450,200);
    //setWindowFlags(Qt::WindowStaysOnTopHint);
    //setWindowFlags(Qt::FramelessWindowHint|Qt::Popup);

    type=new QButtonGroup;
    /*
    label=new QLabel(tr("Choose a type:"));    
    section=new QPushButton(tr("&Section"));
    note=new QPushButton(tr("&Note"));
    type->addButton(section,1);
    type->addButton(note,2);*/
    groupBox = new QGroupBox(tr("C&hoose a type"));
    noteRadioButton = new QRadioButton(tr("&Note"));
    childNoteRadioButton = new QRadioButton(tr("&Child Note"));
    type->addButton(noteRadioButton,1);
    type->addButton(childNoteRadioButton,2);


    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
    groupBoxLayout->addWidget(noteRadioButton);
    groupBoxLayout->addWidget(childNoteRadioButton);
    groupBox->setLayout(groupBoxLayout);

    finish=new QPushButton(tr("&Ok"));
    //closeButton=new QPushButton(tr("&Close"));

    lineLabel=new QLabel(tr("input the name:"));
    lineEdit = new QLineEdit();
    lineLabel->setBuddy(lineEdit);

    browseButton = new QPushButton(tr("&Browse..."));
    directoryComboBox = createComboBox(QDir::currentPath());
    directoryLabel = new QLabel(tr("Directory:"));

    path = directoryComboBox->currentText();

    QGridLayout* typeLayout=new QGridLayout;
    typeLayout->addWidget(groupBox,0,0,1,2);
    //typeLayout->addWidget(label);
    //typeLayout->addWidget(note);
    //typeLayout->addWidget(section);
    typeLayout->addWidget(lineLabel,1,0);
    typeLayout->addWidget(lineEdit,1,1);
    typeLayout->addWidget(directoryLabel,2,0);
    typeLayout->addWidget(directoryComboBox,2,1);
    typeLayout->addWidget(browseButton,2,2);
    typeLayout->addWidget(finish,3,1,1,1);

    connect(finish,SIGNAL(clicked()),this,SLOT(close()) );

    centralWidget()->setLayout(typeLayout);

   // nouveauSectionAct= new QAction(tr("&"),this);
   //nouveauSectionAct->setObjectName(tr("insertRowAct"));
}
NouveauDialog::~NouveauDialog()
{

}

QComboBox *NouveauDialog::createComboBox(const QString &text)
{
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->addItem(text);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5) || defined(Q_WS_SIMULATOR)
    comboBox->setMinimumContentsLength(3);
#endif
    return comboBox;
}
