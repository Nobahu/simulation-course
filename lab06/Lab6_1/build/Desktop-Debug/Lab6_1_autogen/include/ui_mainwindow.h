/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *textWidget;
    QLabel *exprnumlabel;
    QPushButton *startPushButton_2;
    QLineEdit *probLineEdit_1;
    QLineEdit *probLineEdit_2;
    QLineEdit *probLineEdit_3;
    QLineEdit *probLineEdit_4;
    QLineEdit *probLineEdit_5;
    QLineEdit *numexprLineEdit;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *problabel_1;
    QLabel *problabel_2;
    QLabel *problabel_3;
    QLabel *problabel_4;
    QLabel *problabel_5;
    QComboBox *comboBox;
    QPushButton *autoPushButton;
    QWidget *graphWidget;
    QLabel *Avglabel;
    QLabel *VarianceLabel;
    QLabel *CSlabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 720);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        textWidget = new QWidget(centralwidget);
        textWidget->setObjectName("textWidget");
        textWidget->setGeometry(QRect(0, 0, 331, 491));
        exprnumlabel = new QLabel(textWidget);
        exprnumlabel->setObjectName("exprnumlabel");
        exprnumlabel->setGeometry(QRect(10, 350, 191, 31));
        QFont font;
        font.setPointSize(14);
        exprnumlabel->setFont(font);
        startPushButton_2 = new QPushButton(textWidget);
        startPushButton_2->setObjectName("startPushButton_2");
        startPushButton_2->setGeometry(QRect(90, 420, 131, 31));
        probLineEdit_1 = new QLineEdit(textWidget);
        probLineEdit_1->setObjectName("probLineEdit_1");
        probLineEdit_1->setGeometry(QRect(80, 20, 113, 25));
        probLineEdit_2 = new QLineEdit(textWidget);
        probLineEdit_2->setObjectName("probLineEdit_2");
        probLineEdit_2->setGeometry(QRect(80, 80, 113, 25));
        probLineEdit_3 = new QLineEdit(textWidget);
        probLineEdit_3->setObjectName("probLineEdit_3");
        probLineEdit_3->setGeometry(QRect(80, 140, 113, 25));
        probLineEdit_4 = new QLineEdit(textWidget);
        probLineEdit_4->setObjectName("probLineEdit_4");
        probLineEdit_4->setGeometry(QRect(80, 200, 113, 25));
        probLineEdit_5 = new QLineEdit(textWidget);
        probLineEdit_5->setObjectName("probLineEdit_5");
        probLineEdit_5->setGeometry(QRect(80, 270, 113, 25));
        numexprLineEdit = new QLineEdit(textWidget);
        numexprLineEdit->setObjectName("numexprLineEdit");
        numexprLineEdit->setGeometry(QRect(210, 350, 113, 31));
        layoutWidget = new QWidget(textWidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 0, 55, 311));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        problabel_1 = new QLabel(layoutWidget);
        problabel_1->setObjectName("problabel_1");
        problabel_1->setFont(font);

        verticalLayout_2->addWidget(problabel_1);

        problabel_2 = new QLabel(layoutWidget);
        problabel_2->setObjectName("problabel_2");
        problabel_2->setFont(font);

        verticalLayout_2->addWidget(problabel_2);

        problabel_3 = new QLabel(layoutWidget);
        problabel_3->setObjectName("problabel_3");
        problabel_3->setFont(font);

        verticalLayout_2->addWidget(problabel_3);

        problabel_4 = new QLabel(layoutWidget);
        problabel_4->setObjectName("problabel_4");
        problabel_4->setFont(font);

        verticalLayout_2->addWidget(problabel_4);

        problabel_5 = new QLabel(layoutWidget);
        problabel_5->setObjectName("problabel_5");
        problabel_5->setFont(font);

        verticalLayout_2->addWidget(problabel_5);

        comboBox = new QComboBox(textWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(211, 20, 111, 25));
        autoPushButton = new QPushButton(textWidget);
        autoPushButton->setObjectName("autoPushButton");
        autoPushButton->setGeometry(QRect(210, 270, 111, 25));
        graphWidget = new QWidget(centralwidget);
        graphWidget->setObjectName("graphWidget");
        graphWidget->setGeometry(QRect(330, 0, 781, 491));
        Avglabel = new QLabel(centralwidget);
        Avglabel->setObjectName("Avglabel");
        Avglabel->setGeometry(QRect(330, 490, 422, 39));
        Avglabel->setFont(font);
        VarianceLabel = new QLabel(centralwidget);
        VarianceLabel->setObjectName("VarianceLabel");
        VarianceLabel->setGeometry(QRect(760, 490, 421, 39));
        VarianceLabel->setFont(font);
        CSlabel = new QLabel(centralwidget);
        CSlabel->setObjectName("CSlabel");
        CSlabel->setGeometry(QRect(330, 530, 851, 31));
        CSlabel->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1280, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        exprnumlabel->setText(QCoreApplication::translate("MainWindow", "Num of experiments", nullptr));
        startPushButton_2->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        problabel_1->setText(QCoreApplication::translate("MainWindow", "Prob1", nullptr));
        problabel_2->setText(QCoreApplication::translate("MainWindow", "Prob2", nullptr));
        problabel_3->setText(QCoreApplication::translate("MainWindow", "Prob3", nullptr));
        problabel_4->setText(QCoreApplication::translate("MainWindow", "Prob4", nullptr));
        problabel_5->setText(QCoreApplication::translate("MainWindow", "Prob5", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Uniform_distr", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Custom", nullptr));

        autoPushButton->setText(QCoreApplication::translate("MainWindow", "Auto", nullptr));
        Avglabel->setText(QCoreApplication::translate("MainWindow", "Average:", nullptr));
        VarianceLabel->setText(QCoreApplication::translate("MainWindow", "Variance:", nullptr));
        CSlabel->setText(QCoreApplication::translate("MainWindow", "Chi-Squared:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
