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
#include <QtWidgets/QHBoxLayout>
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
    QWidget *graphWidget;
    QWidget *buttonWidget;
    QLineEdit *meanLineEdit;
    QLineEdit *varianceLineEdit;
    QLineEdit *sampleLineEdit;
    QPushButton *startPushButton;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *CSlabel;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QLabel *Avglabel;
    QLabel *VarianceLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 720);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        graphWidget = new QWidget(centralwidget);
        graphWidget->setObjectName("graphWidget");
        graphWidget->setGeometry(QRect(290, 0, 851, 600));
        buttonWidget = new QWidget(centralwidget);
        buttonWidget->setObjectName("buttonWidget");
        buttonWidget->setGeometry(QRect(0, 0, 291, 451));
        meanLineEdit = new QLineEdit(buttonWidget);
        meanLineEdit->setObjectName("meanLineEdit");
        meanLineEdit->setGeometry(QRect(120, 30, 81, 25));
        varianceLineEdit = new QLineEdit(buttonWidget);
        varianceLineEdit->setObjectName("varianceLineEdit");
        varianceLineEdit->setGeometry(QRect(120, 90, 81, 25));
        sampleLineEdit = new QLineEdit(buttonWidget);
        sampleLineEdit->setObjectName("sampleLineEdit");
        sampleLineEdit->setGeometry(QRect(120, 150, 81, 25));
        startPushButton = new QPushButton(buttonWidget);
        startPushButton->setObjectName("startPushButton");
        startPushButton->setGeometry(QRect(80, 370, 111, 31));
        widget = new QWidget(buttonWidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 10, 107, 181));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(14);
        label->setFont(font);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        verticalLayout->addWidget(label_3);

        CSlabel = new QLabel(centralwidget);
        CSlabel->setObjectName("CSlabel");
        CSlabel->setGeometry(QRect(290, 640, 851, 31));
        CSlabel->setFont(font);
        widget1 = new QWidget(centralwidget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(290, 600, 851, 41));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Avglabel = new QLabel(widget1);
        Avglabel->setObjectName("Avglabel");
        Avglabel->setFont(font);

        horizontalLayout->addWidget(Avglabel);

        VarianceLabel = new QLabel(widget1);
        VarianceLabel->setObjectName("VarianceLabel");
        VarianceLabel->setFont(font);

        horizontalLayout->addWidget(VarianceLabel);

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
        startPushButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Mean", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Variance", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Sample size", nullptr));
        CSlabel->setText(QCoreApplication::translate("MainWindow", "Chi-Squared:", nullptr));
        Avglabel->setText(QCoreApplication::translate("MainWindow", "Average:", nullptr));
        VarianceLabel->setText(QCoreApplication::translate("MainWindow", "Variance:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
