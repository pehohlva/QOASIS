#ifndef UI_FORMS_H
#define UI_FORMS_H

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QComboBox>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QSpinBox>
#include <QToolButton>


#include <QAbstractTextDocumentLayout>
#include <QAction>
#include <QApplication>
#include <QBuffer>
#include <QButtonGroup>
#include <QCloseEvent>
#include <QColorDialog>
#include <QComboBox>
#include <QDateTime>
#include <QDebug>
#include <QDesktopWidget>
#include <QDialog>
#include <QDir>
#include <QDomDocument>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QImage>
#include <QInputDialog>
#include <QKeySequence>
#include <QLabel>
#include <QMarginsF>
#include <QMenu>
#include <QMimeData>
#include <QMimeDatabase>
#include <QMimeType>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QPoint>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QProcess>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QShortcut>
#include <QSlider>
#include <QSpinBox>
#include <QTextBrowser>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextDocumentFragment>
#include <QTextEdit>
#include <QTextFormat>
#include <QTextFrame>
#include <QTextFrameFormat>
#include <QTextImageFormat>
#include <QTimer>
#include <QVBoxLayout>
#include <QVariant>
#include <QWidget>
#include <QtCore>
#include <QtGui>



static inline QString BiteorMega(int peso) {
  QString humanread;
  double canno = peso / 1024;
  int sale = canno;
  if (peso > 0) {
    if (canno < 1) {
      sale = 1;
    }
  }

  if (sale < 1025) {
    humanread = QString("KB:%1").arg(sale);
    return humanread;
  }

  float megad = sale / 1024;

  if (megad < 1025) {
    humanread = QString("MB:%1").arg(megad);
    return humanread;
  } else {
    humanread = QString("GB:1+");
  }

  return humanread;
}

static inline QImage GreyScale(QImage income) {

  QImage base = income.convertToFormat(QImage::Format_RGB32);
  for (int y = 0; y < base.height(); ++y) {
    for (int x = 0; x < base.width(); ++x) {
      int pixel = base.pixel(x, y);
      int gray = qGray(pixel);
      int alpha = qAlpha(pixel);
      base.setPixel(x, y, qRgba(gray, gray, gray, alpha));
    }
  }

  return base;
}

static inline QString BraketName(QString braket) {
  QString name = braket;
  QRegExp expression("color=[\"\'](.*)[\"\']", Qt::CaseInsensitive);

  int iPosition = 0;
  while ((iPosition = expression.indexIn(braket, iPosition)) != -1) {
    name = expression.cap(1);
    iPosition += expression.matchedLength();
  }
  return name;
}

//// generierte ui form ende

class Ui_Interface {
public:
  QGridLayout *gridLayout;
  QScrollArea *scrolla;
  QGroupBox *groupBox_2;
  QGridLayout *gridLayout1;
  QLabel *label_7;
  QLabel *imgcoo;
  QLabel *imginfo;
  QGroupBox *groupBox;
  QGridLayout *gridLayout2;
  QHBoxLayout *hboxLayout;
  QVBoxLayout *vboxLayout;
  QHBoxLayout *hboxLayout1;
  QLabel *label;
  QSpinBox *spinBox_3;
  QSlider *horizontalSlider;
  QHBoxLayout *hboxLayout2;
  QLabel *label_3;
  QSpinBox *spinBox;
  QSlider *horizontalSlider_2;
  QHBoxLayout *hboxLayout3;
  QLabel *label_2;
  QSpinBox *spinBox_2;
  QSlider *horizontalSlider_3;
  QVBoxLayout *vboxLayout1;
  QPushButton *pushButton;
  QPushButton *pushButton_2;
  QHBoxLayout *hboxLayout4;
  QLabel *label_8;
  QSpinBox *qualvalue;
  QHBoxLayout *hboxLayout5;
  QLabel *label_4;
  QComboBox *comboBox_2;
  QHBoxLayout *hboxLayout6;
  QLabel *label_5;
  QComboBox *comboBox;
  QHBoxLayout *hboxLayout7;
  QLabel *label_6;
  QSpinBox *spinBox_4;

  void setupUi(QDialog *Interface) {
    Interface->setObjectName(QString::fromUtf8("Interface"));
    gridLayout = new QGridLayout(Interface);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(9);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    scrolla = new QScrollArea(Interface);
    scrolla->setWidgetResizable(true);
    scrolla->setMinimumSize(QSize(0, 300));
    gridLayout->addWidget(scrolla, 2, 0, 1, 1);
    groupBox_2 = new QGroupBox(Interface);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    groupBox_2->setMaximumSize(QSize(16777215, 89));
    gridLayout1 = new QGridLayout(groupBox_2);
    gridLayout1->setSpacing(6);
    gridLayout1->setMargin(9);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    label_7 = new QLabel(groupBox_2);
    label_7->setObjectName(QString::fromUtf8("label_7"));
    label_7->setTextFormat(Qt::PlainText);
    gridLayout1->addWidget(label_7, 0, 0, 2, 2);
    imgcoo = new QLabel(groupBox_2);
    imgcoo->setObjectName(QString::fromUtf8("imgcoo"));
    imgcoo->setTextFormat(Qt::PlainText);
    gridLayout1->addWidget(imgcoo, 1, 1, 1, 1);
    imginfo = new QLabel(groupBox_2);
    imginfo->setObjectName(QString::fromUtf8("imginfo"));
    imginfo->setTextFormat(Qt::PlainText);
    gridLayout1->addWidget(imginfo, 2, 0, 1, 2);
    gridLayout->addWidget(groupBox_2, 1, 0, 1, 1);
    groupBox = new QGroupBox(Interface);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setMaximumSize(QSize(16777215, 220));
    gridLayout2 = new QGridLayout(groupBox);
    gridLayout2->setSpacing(6);
    gridLayout2->setMargin(9);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    vboxLayout = new QVBoxLayout();
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    label = new QLabel(groupBox);
    label->setObjectName(QString::fromUtf8("label"));
    label->setTextFormat(Qt::PlainText);
    hboxLayout1->addWidget(label);
    spinBox_3 = new QSpinBox(groupBox);
    spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
    spinBox_3->setMaximum(360);
    spinBox_3->setMinimum(1);
    hboxLayout1->addWidget(spinBox_3);
    horizontalSlider = new QSlider(groupBox);
    horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
    horizontalSlider->setMinimum(1);
    horizontalSlider->setMaximum(360);
    horizontalSlider->setOrientation(Qt::Horizontal);
    horizontalSlider->setTickPosition(QSlider::TicksBothSides);
    hboxLayout1->addWidget(horizontalSlider);
    vboxLayout->addLayout(hboxLayout1);
    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    label_3 = new QLabel(groupBox);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setTextFormat(Qt::PlainText);
    hboxLayout2->addWidget(label_3);
    spinBox = new QSpinBox(groupBox);
    spinBox->setObjectName(QString::fromUtf8("spinBox"));
    spinBox->setMaximum(3000);
    hboxLayout2->addWidget(spinBox);
    horizontalSlider_2 = new QSlider(groupBox);
    horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
    horizontalSlider_2->setMaximum(3000);
    horizontalSlider_2->setOrientation(Qt::Horizontal);
    horizontalSlider_2->setTickPosition(QSlider::TicksAbove);
    hboxLayout2->addWidget(horizontalSlider_2);
    vboxLayout->addLayout(hboxLayout2);
    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    label_2 = new QLabel(groupBox);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setTextFormat(Qt::PlainText);
    hboxLayout3->addWidget(label_2);
    spinBox_2 = new QSpinBox(groupBox);
    spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
    spinBox_2->setMaximum(3000);
    hboxLayout3->addWidget(spinBox_2);
    horizontalSlider_3 = new QSlider(groupBox);
    horizontalSlider_3->setObjectName(QString::fromUtf8("horizontalSlider_3"));
    horizontalSlider_3->setMaximum(3000);
    horizontalSlider_3->setOrientation(Qt::Horizontal);
    horizontalSlider_3->setTickPosition(QSlider::TicksAbove);
    hboxLayout3->addWidget(horizontalSlider_3);
    vboxLayout->addLayout(hboxLayout3);
    hboxLayout->addLayout(vboxLayout);
    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setMargin(0);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    pushButton = new QPushButton(groupBox);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    vboxLayout1->addWidget(pushButton);
    pushButton_2 = new QPushButton(groupBox);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    vboxLayout1->addWidget(pushButton_2);
    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setMargin(0);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    label_8 = new QLabel(groupBox);
    label_8->setObjectName(QString::fromUtf8("label_8"));
    label_8->setTextFormat(Qt::PlainText);
    hboxLayout4->addWidget(label_8);
    qualvalue = new QSpinBox(groupBox);
    qualvalue->setObjectName(QString::fromUtf8("qualvalue"));
    qualvalue->setMaximum(100);
    qualvalue->setMinimum(20);
    qualvalue->setValue(75);
    hboxLayout4->addWidget(qualvalue);
    vboxLayout1->addLayout(hboxLayout4);
    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setSpacing(6);
    hboxLayout5->setMargin(0);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    label_4 = new QLabel(groupBox);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    hboxLayout5->addWidget(label_4);
    comboBox_2 = new QComboBox(groupBox);
    comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
    hboxLayout5->addWidget(comboBox_2);
    vboxLayout1->addLayout(hboxLayout5);
    hboxLayout6 = new QHBoxLayout();
    hboxLayout6->setSpacing(6);
    hboxLayout6->setMargin(0);
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    label_5 = new QLabel(groupBox);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setTextFormat(Qt::PlainText);
    hboxLayout6->addWidget(label_5);
    comboBox = new QComboBox(groupBox);
    comboBox->setObjectName(QString::fromUtf8("comboBox"));
    hboxLayout6->addWidget(comboBox);
    vboxLayout1->addLayout(hboxLayout6);
    hboxLayout7 = new QHBoxLayout();
    hboxLayout7->setSpacing(6);
    hboxLayout7->setMargin(0);
    hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
    label_6 = new QLabel(groupBox);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setTextFormat(Qt::PlainText);
    hboxLayout7->addWidget(label_6);
    spinBox_4 = new QSpinBox(groupBox);
    spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));
    spinBox_4->setMaximum(360);
    hboxLayout7->addWidget(spinBox_4);
    vboxLayout1->addLayout(hboxLayout7);
    hboxLayout->addLayout(vboxLayout1);
    gridLayout2->addLayout(hboxLayout, 0, 0, 1, 1);
    gridLayout->addWidget(groupBox, 0, 0, 1, 1);
    retranslateUi(Interface);

    QSize size(651, 606);
    size = size.expandedTo(Interface->minimumSizeHint());
    Interface->resize(size);

    QObject::connect(horizontalSlider, SIGNAL(sliderMoved(int)), spinBox_3,
                     SLOT(setValue(int)));
    QObject::connect(horizontalSlider_2, SIGNAL(sliderMoved(int)), spinBox,
                     SLOT(setValue(int)));
    QObject::connect(horizontalSlider_3, SIGNAL(sliderMoved(int)), spinBox_2,
                     SLOT(setValue(int)));
    QObject::connect(spinBox_3, SIGNAL(valueChanged(int)), horizontalSlider,
                     SLOT(setValue(int)));
    QObject::connect(spinBox, SIGNAL(valueChanged(int)), horizontalSlider_2,
                     SLOT(setValue(int)));
    QObject::connect(spinBox_2, SIGNAL(valueChanged(int)), horizontalSlider_3,
                     SLOT(setValue(int)));

    QMetaObject::connectSlotsByName(Interface);
  } // setupUi

  void retranslateUi(QDialog *Interface) {
    Interface->setWindowTitle(
        QApplication::translate("Interface", "Dialog", 0, 0));
    groupBox_2->setTitle(
        QApplication::translate("Interface", "Image info", 0, 0));
    label_7->setText(
        QApplication::translate("Interface", "Crop coordinate", 0, 0));
    imgcoo->setText(QApplication::translate("Interface", "....", 0, 0));
    imginfo->setText(QApplication::translate("Interface", "...", 0, 0));
    groupBox->setTitle(
        QApplication::translate("Interface", "Image manipulation", 0, 0));
    label->setText(QApplication::translate("Interface", "Zoom:", 0, 0));
    label_3->setText(QApplication::translate("Interface", "Width:", 0, 0));
    label_2->setText(QApplication::translate("Interface", "Height:", 0, 0));
    pushButton->setText(QApplication::translate("Interface", "Save", 0, 0));
    pushButton_2->setText(QApplication::translate("Interface", "Crop", 0, 0));
    label_8->setText(
        QApplication::translate("Interface", "Quality on Save:", 0, 0));
    label_4->setText(
        QApplication::translate("Interface", "Filter apply:", 0, 0));
    label_5->setText(
        QApplication::translate("Interface", "Color selector:", 0, 0));
    label_6->setText(QApplication::translate("Interface", "Rotate:", 0, 0));
    Q_UNUSED(Interface);
  } // retranslateUi
};

namespace Ui {
class Interface : public Ui_Interface {};
} // namespace Ui





class Ui_Table_Setting
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout1;
    QHBoxLayout *hboxLayout;
    QLabel *label_3;
    QSpinBox *vborder;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout1;
    QLabel *label_6;
    QSpinBox *largotable;
    QSpacerItem *spacerItem1;
    QHBoxLayout *hboxLayout2;
    QLabel *label;
    QDoubleSpinBox *tapadding;
    QSpacerItem *spacerItem2;
    QHBoxLayout *hboxLayout3;
    QLabel *label_5;
    QComboBox *xalign;
    QSpacerItem *spacerItem3;
    QHBoxLayout *hboxLayout4;
    QLabel *label_2;
    QDoubleSpinBox *taspacing;
    QSpacerItem *spacerItem4;
    QHBoxLayout *hboxLayout5;
    QLabel *label_4;
    QToolButton *tablecolor;
    QSpacerItem *spacerItem5;
    QHBoxLayout *hboxLayout6;
    QSpacerItem *spacerItem6;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *Table_Setting)
    {
    Table_Setting->setObjectName(QString::fromUtf8("Table_Setting"));
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(0));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(Table_Setting->sizePolicy().hasHeightForWidth());
    Table_Setting->setSizePolicy(sizePolicy);
    Table_Setting->setMinimumSize(QSize(16, 280));
    Table_Setting->setMaximumSize(QSize(16777215, 280));
    Table_Setting->setWindowIcon(QIcon(QString::fromUtf8(":/img/table.png")));
    gridLayout = new QGridLayout(Table_Setting);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(9);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    groupBox = new QGroupBox(Table_Setting);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    gridLayout1 = new QGridLayout(groupBox);
    gridLayout1->setSpacing(6);
    gridLayout1->setMargin(9);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    label_3 = new QLabel(groupBox);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setTextFormat(Qt::PlainText);

    hboxLayout->addWidget(label_3);

    vborder = new QSpinBox(groupBox);
    vborder->setObjectName(QString::fromUtf8("vborder"));

    hboxLayout->addWidget(vborder);

    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem);


    gridLayout1->addLayout(hboxLayout, 1, 0, 1, 1);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    label_6 = new QLabel(groupBox);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setTextFormat(Qt::PlainText);

    hboxLayout1->addWidget(label_6);

    largotable = new QSpinBox(groupBox);
    largotable->setObjectName(QString::fromUtf8("largotable"));
    largotable->setMaximum(100);
    largotable->setMinimum(10);
    largotable->setValue(10);

    hboxLayout1->addWidget(largotable);

    spacerItem1 = new QSpacerItem(282, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem1);


    gridLayout1->addLayout(hboxLayout1, 0, 0, 1, 1);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    label = new QLabel(groupBox);
    label->setObjectName(QString::fromUtf8("label"));
    label->setTextFormat(Qt::PlainText);

    hboxLayout2->addWidget(label);

    tapadding = new QDoubleSpinBox(groupBox);
    tapadding->setObjectName(QString::fromUtf8("tapadding"));
    tapadding->setDecimals(1);
    tapadding->setMaximum(10);

    hboxLayout2->addWidget(tapadding);

    spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout2->addItem(spacerItem2);


    gridLayout1->addLayout(hboxLayout2, 2, 0, 1, 1);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    label_5 = new QLabel(groupBox);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setTextFormat(Qt::PlainText);

    hboxLayout3->addWidget(label_5);

    xalign = new QComboBox(groupBox);
    xalign->setObjectName(QString::fromUtf8("xalign"));

    hboxLayout3->addWidget(xalign);

    spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout3->addItem(spacerItem3);


    gridLayout1->addLayout(hboxLayout3, 5, 0, 1, 1);

    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setMargin(0);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    label_2 = new QLabel(groupBox);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setTextFormat(Qt::PlainText);

    hboxLayout4->addWidget(label_2);

    taspacing = new QDoubleSpinBox(groupBox);
    taspacing->setObjectName(QString::fromUtf8("taspacing"));
    taspacing->setDecimals(1);
    taspacing->setMaximum(10);

    hboxLayout4->addWidget(taspacing);

    spacerItem4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout4->addItem(spacerItem4);


    gridLayout1->addLayout(hboxLayout4, 3, 0, 1, 1);

    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setSpacing(6);
    hboxLayout5->setMargin(0);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    label_4 = new QLabel(groupBox);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setTextFormat(Qt::PlainText);

    hboxLayout5->addWidget(label_4);

    tablecolor = new QToolButton(groupBox);
    tablecolor->setObjectName(QString::fromUtf8("tablecolor"));

    hboxLayout5->addWidget(tablecolor);

    spacerItem5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout5->addItem(spacerItem5);


    gridLayout1->addLayout(hboxLayout5, 4, 0, 1, 1);


    gridLayout->addWidget(groupBox, 0, 0, 1, 1);

    hboxLayout6 = new QHBoxLayout();
    hboxLayout6->setSpacing(6);
    hboxLayout6->setMargin(0);
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    spacerItem6 = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout6->addItem(spacerItem6);

    okButton = new QPushButton(Table_Setting);
    okButton->setObjectName(QString::fromUtf8("okButton"));

    hboxLayout6->addWidget(okButton);

    cancelButton = new QPushButton(Table_Setting);
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

    hboxLayout6->addWidget(cancelButton);


    gridLayout->addLayout(hboxLayout6, 1, 0, 1, 1);


    retranslateUi(Table_Setting);

    QSize size(561, 280);
    size = size.expandedTo(Table_Setting->minimumSizeHint());
    Table_Setting->resize(size);

    QObject::connect(okButton, SIGNAL(clicked()), Table_Setting, SLOT(accept()));
    QObject::connect(cancelButton, SIGNAL(clicked()), Table_Setting, SLOT(reject()));

    QMetaObject::connectSlotsByName(Table_Setting);
    } // setupUi

    void retranslateUi(QDialog *Table_Setting)
    {
    Table_Setting->setWindowTitle(QApplication::translate("Table_Setting", "Table setting & Propriety", 0, 0));
    groupBox->setTitle(QApplication::translate("Table_Setting", "Table setting:", 0, 0));
    label_3->setText(QApplication::translate("Table_Setting", "Border:", 0, 0));
    label_6->setText(QApplication::translate("Table_Setting", "Table setting widht:", 0, 0));
    largotable->setSuffix(QApplication::translate("Table_Setting", "%", 0, 0));
    largotable->setPrefix(QString());
    label->setText(QApplication::translate("Table_Setting", "CellPadding:", 0, 0));
    label_5->setText(QApplication::translate("Table_Setting", "Table Align:", 0, 0));
    label_2->setText(QApplication::translate("Table_Setting", "CellSpacing:", 0, 0));
    label_4->setText(QApplication::translate("Table_Setting", "BackgroundColor:", 0, 0));
    tablecolor->setText(QApplication::translate("Table_Setting", "...", 0, 0));
    okButton->setText(QApplication::translate("Table_Setting", "OK", 0, 0));
    cancelButton->setText(QApplication::translate("Table_Setting", "Cancel", 0, 0));
    Q_UNUSED(Table_Setting);
    } // retranslateUi

};

namespace Ui {
    class Table_Setting: public Ui_Table_Setting {};
} // namespace Ui




#endif // UI_FORMS_H
