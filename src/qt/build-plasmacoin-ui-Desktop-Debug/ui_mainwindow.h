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
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
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
    QLCDNumber *usdollars;
    QLCDNumber *plasmacoins;
    QWidget *mineCoins;
    QPushButton *btn_mine;
    QListWidget *transactionList;
    QWidget *addressBook;
    QDialogButtonBox *buttonBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *amountLabel;
    QLineEdit *amountLineEdit;
    QTextBrowser *textBrowser;
    QTableWidget *tableWidget;
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
        tabWidget->setMovable(false);
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
        usdollars = new QLCDNumber(wallet);
        usdollars->setObjectName(QString::fromUtf8("usdollars"));
        usdollars->setGeometry(QRect(520, 60, 241, 71));
        usdollars->setSmallDecimalPoint(false);
        usdollars->setDigitCount(5);
        usdollars->setMode(QLCDNumber::Dec);
        usdollars->setSegmentStyle(QLCDNumber::Filled);
        plasmacoins = new QLCDNumber(wallet);
        plasmacoins->setObjectName(QString::fromUtf8("plasmacoins"));
        plasmacoins->setGeometry(QRect(30, 60, 241, 71));
        plasmacoins->setLayoutDirection(Qt::LeftToRight);
        plasmacoins->setSmallDecimalPoint(false);
        plasmacoins->setDigitCount(5);
        plasmacoins->setMode(QLCDNumber::Dec);
        plasmacoins->setSegmentStyle(QLCDNumber::Filled);
        stackedWidget->addWidget(wallet);
        mineCoins = new QWidget();
        mineCoins->setObjectName(QString::fromUtf8("mineCoins"));
        btn_mine = new QPushButton(mineCoins);
        btn_mine->setObjectName(QString::fromUtf8("btn_mine"));
        btn_mine->setGeometry(QRect(30, 470, 88, 34));
        transactionList = new QListWidget(mineCoins);
        transactionList->setObjectName(QString::fromUtf8("transactionList"));
        transactionList->setGeometry(QRect(30, 30, 311, 401));
        stackedWidget->addWidget(mineCoins);
        addressBook = new QWidget();
        addressBook->setObjectName(QString::fromUtf8("addressBook"));
        buttonBox = new QDialogButtonBox(addressBook);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(380, 130, 174, 34));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        formLayoutWidget = new QWidget(addressBook);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(380, 90, 341, 41));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        amountLabel = new QLabel(formLayoutWidget);
        amountLabel->setObjectName(QString::fromUtf8("amountLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, amountLabel);

        amountLineEdit = new QLineEdit(formLayoutWidget);
        amountLineEdit->setObjectName(QString::fromUtf8("amountLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, amountLineEdit);

        textBrowser = new QTextBrowser(addressBook);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(380, 40, 341, 31));
        tableWidget = new QTableWidget(addressBook);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(30, 40, 311, 421));
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget->setColumnCount(2);
        stackedWidget->addWidget(addressBook);
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
        btn_mine->setText(QCoreApplication::translate("MainWindow", "Mine", nullptr));
        amountLabel->setText(QCoreApplication::translate("MainWindow", "Amount", nullptr));
        amountLineEdit->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        icon->setTitle(QCoreApplication::translate("MainWindow", "Plasmacoin UI", nullptr));
        text->setTitle(QCoreApplication::translate("MainWindow", "Plasmacoin UI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
