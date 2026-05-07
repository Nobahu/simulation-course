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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QWidget *MatrixWidget;
    QTableWidget *tableWidget;
    QLabel *label_2;
    QPushButton *pushButton;
    QLabel *label_3;
    QLineEdit *daynum_lineEdit;
    QLabel *label_4;
    QLineEdit *delay_lineEdit;
    QWidget *GraphicWidget;
    QWidget *StatsWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1149, 720);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setDocumentMode(false);
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 201, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Bitstream Charter")});
        font.setPointSize(16);
        font.setBold(true);
        label->setFont(font);
        MatrixWidget = new QWidget(centralwidget);
        MatrixWidget->setObjectName("MatrixWidget");
        MatrixWidget->setGeometry(QRect(-1, 9, 391, 651));
        tableWidget = new QTableWidget(MatrixWidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem5);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 90, 371, 121));
        label_2 = new QLabel(MatrixWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 60, 201, 21));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Bitstream Charter")});
        font1.setPointSize(14);
        font1.setBold(true);
        label_2->setFont(font1);
        pushButton = new QPushButton(MatrixWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(90, 410, 191, 25));
        label_3 = new QLabel(MatrixWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 270, 181, 21));
        label_3->setFont(font1);
        daynum_lineEdit = new QLineEdit(MatrixWidget);
        daynum_lineEdit->setObjectName("daynum_lineEdit");
        daynum_lineEdit->setGeometry(QRect(190, 271, 51, 20));
        label_4 = new QLabel(MatrixWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 310, 181, 21));
        label_4->setFont(font1);
        delay_lineEdit = new QLineEdit(MatrixWidget);
        delay_lineEdit->setObjectName("delay_lineEdit");
        delay_lineEdit->setGeometry(QRect(190, 310, 51, 20));
        GraphicWidget = new QWidget(centralwidget);
        GraphicWidget->setObjectName("GraphicWidget");
        GraphicWidget->setGeometry(QRect(390, 10, 361, 651));
        StatsWidget = new QWidget(centralwidget);
        StatsWidget->setObjectName("StatsWidget");
        StatsWidget->setGeometry(QRect(750, 10, 391, 651));
        MainWindow->setCentralWidget(centralwidget);
        MatrixWidget->raise();
        label->raise();
        GraphicWidget->raise();
        StatsWidget->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1149, 22));
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
        label->setText(QCoreApplication::translate("MainWindow", "MarkovWeatherApp", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\320\257\321\201\320\275\320\276", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\273\320\260\321\207\320\275\320\276", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\201\320\274\321\203\321\200\320\275\320\276", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\320\257\321\201\320\275\320\276", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\273\320\260\321\207\320\275\320\276", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\201\320\274\321\203\321\200\320\275\320\276", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\202\321\200\320\270\321\206\320\260 \320\277\320\265\321\200\320\265\321\205\320\276\320\264\320\276\320\262", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\264\320\275\320\265\320\271", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\265\321\200\320\266\320\272\320\260 \320\262 \320\274\321\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
