/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *Wallet;
    QWidget *Mine;
    QWidget *AddressBook;
    QWidget *Account;
    QWidget *Transactions;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuPlasmacoinUI;
    QMenu *menuPlasmaco;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 791, 31));
        tabWidget->setMaximumSize(QSize(791, 16777215));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setMovable(true);
        Wallet = new QWidget();
        Wallet->setObjectName(QString::fromUtf8("Wallet"));
        tabWidget->addTab(Wallet, QString());
        Mine = new QWidget();
        Mine->setObjectName(QString::fromUtf8("Mine"));
        tabWidget->addTab(Mine, QString());
        AddressBook = new QWidget();
        AddressBook->setObjectName(QString::fromUtf8("AddressBook"));
        tabWidget->addTab(AddressBook, QString());
        Account = new QWidget();
        Account->setObjectName(QString::fromUtf8("Account"));
        tabWidget->addTab(Account, QString());
        Transactions = new QWidget();
        Transactions->setObjectName(QString::fromUtf8("Transactions"));
        tabWidget->addTab(Transactions, QString());
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 30));
        menuPlasmacoinUI = new QMenu(menubar);
        menuPlasmacoinUI->setObjectName(QString::fromUtf8("menuPlasmacoinUI"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../assets/plasmacoin-logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuPlasmacoinUI->setIcon(icon);
        menuPlasmacoinUI->setSeparatorsCollapsible(false);
        menuPlasmaco = new QMenu(menubar);
        menuPlasmaco->setObjectName(QString::fromUtf8("menuPlasmaco"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuPlasmacoinUI->menuAction());
        menubar->addAction(menuPlasmaco->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Wallet), QCoreApplication::translate("MainWindow", "Wallet", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Mine), QCoreApplication::translate("MainWindow", " Mine Coins", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(AddressBook), QCoreApplication::translate("MainWindow", "Address Book", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Account), QCoreApplication::translate("MainWindow", "Account", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Transactions), QCoreApplication::translate("MainWindow", "Transactions", nullptr));
        menuPlasmacoinUI->setTitle(QCoreApplication::translate("MainWindow", "Plasmacoin UI", nullptr));
        menuPlasmaco->setTitle(QCoreApplication::translate("MainWindow", "Plasmacoin UI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
