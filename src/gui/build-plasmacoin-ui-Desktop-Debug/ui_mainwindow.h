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
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
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
    QStackedWidget *stackedWidget;
    QWidget *wallet;
    QLCDNumber *USDollars;
    QLCDNumber *Plasmacoins;
    QWidget *mine_coins;
    QPushButton *pushButton;
    QListWidget *transactionList;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *icon;
    QMenu *text;

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
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 30, 801, 531));
        stackedWidget->setLayoutDirection(Qt::LeftToRight);
        wallet = new QWidget();
        wallet->setObjectName(QString::fromUtf8("wallet"));
        USDollars = new QLCDNumber(wallet);
        USDollars->setObjectName(QString::fromUtf8("USDollars"));
        USDollars->setGeometry(QRect(520, 60, 241, 71));
        USDollars->setSmallDecimalPoint(false);
        USDollars->setDigitCount(5);
        USDollars->setMode(QLCDNumber::Dec);
        USDollars->setSegmentStyle(QLCDNumber::Filled);
        Plasmacoins = new QLCDNumber(wallet);
        Plasmacoins->setObjectName(QString::fromUtf8("Plasmacoins"));
        Plasmacoins->setGeometry(QRect(30, 60, 241, 71));
        Plasmacoins->setLayoutDirection(Qt::LeftToRight);
        Plasmacoins->setSmallDecimalPoint(false);
        Plasmacoins->setDigitCount(5);
        Plasmacoins->setMode(QLCDNumber::Dec);
        Plasmacoins->setSegmentStyle(QLCDNumber::Filled);
        stackedWidget->addWidget(wallet);
        mine_coins = new QWidget();
        mine_coins->setObjectName(QString::fromUtf8("mine_coins"));
        pushButton = new QPushButton(mine_coins);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 470, 88, 34));
        transactionList = new QListWidget(mine_coins);
        transactionList->setObjectName(QString::fromUtf8("transactionList"));
        transactionList->setGeometry(QRect(30, 30, 311, 401));
        stackedWidget->addWidget(mine_coins);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 30));
        icon = new QMenu(menubar);
        icon->setObjectName(QString::fromUtf8("icon"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../assets/plasmacoin-logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon->setIcon(icon1);
        icon->setSeparatorsCollapsible(false);
        text = new QMenu(menubar);
        text->setObjectName(QString::fromUtf8("text"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(icon->menuAction());
        menubar->addAction(text->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        stackedWidget->setCurrentIndex(1);


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
        pushButton->setText(QCoreApplication::translate("MainWindow", "Mine", nullptr));
        icon->setTitle(QCoreApplication::translate("MainWindow", "Plasmacoin UI", nullptr));
        text->setTitle(QCoreApplication::translate("MainWindow", "Plasmacoin UI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
