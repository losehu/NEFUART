/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *read_param;
    QAction *save_param;
    QWidget *centralwidget;
    QComboBox *uart1;
    QLabel *label_uart1;
    QPushButton *open1;
    QTableWidget *mdc_table;
    QPushButton *read;
    QPushButton *write;
    QProgressBar *progressBar;
    QLabel *label;
    QPushButton *pushButton;
    QTextBrowser *wel2;
    QTextBrowser *wel1;
    QLabel *label_2;
    QLabel *label_4;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(845, 677);
        read_param = new QAction(MainWindow);
        read_param->setObjectName(QString::fromUtf8("read_param"));
        save_param = new QAction(MainWindow);
        save_param->setObjectName(QString::fromUtf8("save_param"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        uart1 = new QComboBox(centralwidget);
        uart1->setObjectName(QString::fromUtf8("uart1"));
        uart1->setGeometry(QRect(10, 20, 151, 22));
        label_uart1 = new QLabel(centralwidget);
        label_uart1->setObjectName(QString::fromUtf8("label_uart1"));
        label_uart1->setGeometry(QRect(0, 0, 54, 12));
        open1 = new QPushButton(centralwidget);
        open1->setObjectName(QString::fromUtf8("open1"));
        open1->setGeometry(QRect(180, 20, 75, 23));
        mdc_table = new QTableWidget(centralwidget);
        if (mdc_table->columnCount() < 3)
            mdc_table->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        mdc_table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        mdc_table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        mdc_table->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (mdc_table->rowCount() < 15)
            mdc_table->setRowCount(15);
        mdc_table->setObjectName(QString::fromUtf8("mdc_table"));
        mdc_table->setGeometry(QRect(10, 100, 303, 494));
        mdc_table->setRowCount(15);
        mdc_table->setColumnCount(3);
        mdc_table->verticalHeader()->setVisible(false);
        read = new QPushButton(centralwidget);
        read->setObjectName(QString::fromUtf8("read"));
        read->setEnabled(false);
        read->setGeometry(QRect(20, 60, 75, 23));
        write = new QPushButton(centralwidget);
        write->setObjectName(QString::fromUtf8("write"));
        write->setEnabled(false);
        write->setGeometry(QRect(100, 60, 75, 23));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 600, 201, 23));
        progressBar->setValue(24);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(770, 610, 54, 12));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(230, 70, 75, 23));
        wel2 = new QTextBrowser(centralwidget);
        wel2->setObjectName(QString::fromUtf8("wel2"));
        wel2->setGeometry(QRect(440, 60, 221, 32));
        QFont font;
        font.setPointSize(14);
        wel2->setFont(font);
        wel2->setReadOnly(false);
        wel1 = new QTextBrowser(centralwidget);
        wel1->setObjectName(QString::fromUtf8("wel1"));
        wel1->setGeometry(QRect(440, 20, 221, 32));
        wel1->setFont(font);
        wel1->setReadOnly(false);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(340, 20, 91, 31));
        label_2->setFont(font);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(340, 60, 91, 31));
        label_4->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 845, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(save_param);
        menu->addAction(read_param);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "UVK5/6\345\206\231\351\242\221\350\275\257\344\273\266", nullptr));
        read_param->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226\351\205\215\347\275\256", nullptr));
#if QT_CONFIG(tooltip)
        read_param->setToolTip(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226\351\205\215\347\275\256", nullptr));
#endif // QT_CONFIG(tooltip)
        save_param->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\351\205\215\347\275\256", nullptr));
#if QT_CONFIG(tooltip)
        save_param->setToolTip(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\351\205\215\347\275\256", nullptr));
#endif // QT_CONFIG(tooltip)
        label_uart1->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\2431\357\274\232", nullptr));
        open1->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        QTableWidgetItem *___qtablewidgetitem = mdc_table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = mdc_table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "MDC ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = mdc_table->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\350\201\224\347\263\273\344\272\272\345\220\215\347\247\260", nullptr));
        read->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226", nullptr));
        write->setText(QCoreApplication::translate("MainWindow", "\345\206\231\345\205\245", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "V0.1", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "test", nullptr));
        wel2->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        wel1->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\254\242\350\277\216\345\255\227\347\254\2461\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\346\254\242\350\277\216\345\255\227\347\254\2462\357\274\232", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
