/********************************************************************************
** Form generated from reading UI file 'optimal_path_planning.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIMAL_PATH_PLANNING_H
#define UI_OPTIMAL_PATH_PLANNING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_optimal_path_planningClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *pushButton;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *spinBox;
    QLabel *label_5;
    QSpinBox *spinBox_2;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QPushButton *pushButton_2;
    QLabel *label_10;
    QPushButton *pushButton_3;
    QTextBrowser *textBrowser;
    QLabel *label_16;
    QPushButton *pushButton_4;
    QLabel *label_11;
    QLabel *label_12;
    QTextBrowser *textBrowser_4;
    QLabel *label_17;
    QPushButton *pushButton_5;

    void setupUi(QMainWindow *optimal_path_planningClass)
    {
        if (optimal_path_planningClass->objectName().isEmpty())
            optimal_path_planningClass->setObjectName("optimal_path_planningClass");
        optimal_path_planningClass->resize(817, 670);
        optimal_path_planningClass->setMinimumSize(QSize(817, 670));
        optimal_path_planningClass->setMaximumSize(QSize(817, 670));
        centralWidget = new QWidget(optimal_path_planningClass);
        centralWidget->setObjectName("centralWidget");
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 817, 435));
        label->setPixmap(QPixmap(QString::fromUtf8(":/optimal_path_planning/1.jpg")));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(120, 630, 101, 31));
        QFont font;
        font.setPointSize(12);
        pushButton->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 445, 100, 30));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 480, 100, 30));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 515, 100, 30));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(100, 515, 42, 30));
        spinBox->setMaximum(23);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(140, 515, 30, 30));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);
        spinBox_2 = new QSpinBox(centralWidget);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setGeometry(QRect(170, 515, 42, 30));
        spinBox_2->setMaximum(59);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(210, 515, 30, 30));
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(100, 445, 140, 30));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(100, 480, 140, 30));
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(690, 445, 111, 30));
        label_9->setFont(font);
        label_9->setAlignment(Qt::AlignCenter);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(120, 590, 101, 31));
        pushButton_2->setFont(font);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(610, 445, 100, 30));
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignCenter);
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(12, 590, 51, 31));
        pushButton_3->setFont(font);
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(340, 490, 460, 161));
        QFont font1;
        font1.setPointSize(11);
        textBrowser->setFont(font1);
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(240, 445, 100, 30));
        label_16->setFont(font);
        label_16->setAlignment(Qt::AlignCenter);
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(12, 630, 101, 31));
        pushButton_4->setFont(font);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 550, 100, 30));
        label_11->setFont(font);
        label_11->setAlignment(Qt::AlignCenter);
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(100, 550, 140, 30));
        label_12->setFont(font);
        label_12->setAlignment(Qt::AlignCenter);
        textBrowser_4 = new QTextBrowser(centralWidget);
        textBrowser_4->setObjectName("textBrowser_4");
        textBrowser_4->setGeometry(QRect(340, 445, 271, 35));
        textBrowser_4->setFont(font1);
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(60, 590, 51, 31));
        label_17->setFont(font);
        label_17->setAlignment(Qt::AlignCenter);
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(240, 490, 100, 30));
        pushButton_5->setFont(font);
        optimal_path_planningClass->setCentralWidget(centralWidget);

        retranslateUi(optimal_path_planningClass);
        QObject::connect(pushButton_2, SIGNAL(clicked()), optimal_path_planningClass, SLOT(Adjust()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), optimal_path_planningClass, SLOT(Delete()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), optimal_path_planningClass, SLOT(ShowLandmark()));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), optimal_path_planningClass, SLOT(updateWT()));
        QObject::connect(pushButton, SIGNAL(clicked()), optimal_path_planningClass, SLOT(affirm()));
        QObject::connect(pushButton_5, SIGNAL(clicked()), optimal_path_planningClass, SLOT(change()));

        QMetaObject::connectSlotsByName(optimal_path_planningClass);
    } // setupUi

    void retranslateUi(QMainWindow *optimal_path_planningClass)
    {
        optimal_path_planningClass->setWindowTitle(QCoreApplication::translate("optimal_path_planningClass", "optimal_path_planning", nullptr));
        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("optimal_path_planningClass", "\347\241\256\350\256\244\345\207\272\350\241\214", nullptr));
        label_2->setText(QCoreApplication::translate("optimal_path_planningClass", "\350\265\267\345\247\213\344\275\215\347\275\256\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("optimal_path_planningClass", "\347\233\256\346\240\207\344\275\215\347\275\256\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("optimal_path_planningClass", "\345\207\272\350\241\214\346\227\266\351\227\264\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("optimal_path_planningClass", "\346\227\266", nullptr));
        label_6->setText(QCoreApplication::translate("optimal_path_planningClass", "\345\210\206", nullptr));
        label_7->setText(QCoreApplication::translate("optimal_path_planningClass", "\350\257\267\347\202\271\345\207\273\345\234\260\345\233\276", nullptr));
        label_8->setText(QCoreApplication::translate("optimal_path_planningClass", "\350\257\267\347\202\271\345\207\273\345\234\260\345\233\276", nullptr));
        label_9->setText(QCoreApplication::translate("optimal_path_planningClass", "\345\260\217\351\233\252\357\274\21425\345\272\246", nullptr));
        pushButton_2->setText(QCoreApplication::translate("optimal_path_planningClass", "\350\260\203\346\225\264\350\256\276\347\275\256", nullptr));
        label_10->setText(QCoreApplication::translate("optimal_path_planningClass", "\345\207\272\350\241\214\346\260\224\345\200\231\357\274\232", nullptr));
        pushButton_3->setText(QCoreApplication::translate("optimal_path_planningClass", "\345\205\263\351\227\255", nullptr));
        label_16->setText(QCoreApplication::translate("optimal_path_planningClass", "\344\270\255\351\200\224\344\275\215\347\275\256\357\274\232", nullptr));
        pushButton_4->setText(QCoreApplication::translate("optimal_path_planningClass", "\345\210\240\351\231\244\344\270\255\351\200\224\347\202\271", nullptr));
        label_11->setText(QCoreApplication::translate("optimal_path_planningClass", "\345\275\223\345\211\215\350\256\276\347\275\256\357\274\232", nullptr));
        label_12->setText(QCoreApplication::translate("optimal_path_planningClass", "\350\265\267\345\247\213\344\275\215\347\275\256", nullptr));
        textBrowser_4->setHtml(QCoreApplication::translate("optimal_path_planningClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        label_17->setText(QCoreApplication::translate("optimal_path_planningClass", "\345\234\260 \346\240\207", nullptr));
        pushButton_5->setText(QCoreApplication::translate("optimal_path_planningClass", "\346\233\264\346\224\271\350\247\204\345\210\222", nullptr));
    } // retranslateUi

};

namespace Ui {
    class optimal_path_planningClass: public Ui_optimal_path_planningClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIMAL_PATH_PLANNING_H
