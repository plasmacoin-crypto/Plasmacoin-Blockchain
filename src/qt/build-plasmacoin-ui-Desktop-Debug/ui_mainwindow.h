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
#include <QtWidgets/QToolButton>
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
    QWidget *Transactions;
    QWidget *Account;
    QStackedWidget *stackedWidget;
    QWidget *wallet;
    QLCDNumber *usdollars;
    QLCDNumber *plasmacoins;
    QWidget *mineCoins;
    QPushButton *btn_mine;
    QListWidget *transactionList;
    QToolButton *plusSign;
    QToolButton *minusSign;
    QListWidget *blockTransactionList;
    QTextBrowser *blockSize;
    QWidget *addressBook;
    QDialogButtonBox *buttonBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *amountLabel;
    QLineEdit *amountLineEdit;
    QTextBrowser *textBrowser;
    QTableWidget *tableWidget;
    QWidget *transactions;
    QWidget *account;
    QStackedWidget *accountView;
    QWidget *signIn;
    QLineEdit *s_EmailField;
    QPushButton *btn_signIn;
    QLabel *signInTitle;
    QLineEdit *s_PasswordField;
    QPushButton *btn_create;
    QWidget *signUp;
    QLabel *createTitle;
    QPushButton *btn_signUp;
    QPushButton *btn_back;
    QLineEdit *c_EmailField;
    QLineEdit *c_UsernameField;
    QLineEdit *c_PasswordField;
    QWidget *loggedIn;
    QLabel *label;
    QTextBrowser *textBrowser_2;
    QTextBrowser *textBrowser_3;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
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
        tabWidget->setFocusPolicy(Qt::NoFocus);
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
        Transactions = new QWidget();
        Transactions->setObjectName(QString::fromUtf8("Transactions"));
        tabWidget->addTab(Transactions, QString());
        Account = new QWidget();
        Account->setObjectName(QString::fromUtf8("Account"));
        tabWidget->addTab(Account, QString());
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
        btn_mine->setGeometry(QRect(520, 430, 84, 31));
        transactionList = new QListWidget(mineCoins);
        transactionList->setObjectName(QString::fromUtf8("transactionList"));
        transactionList->setGeometry(QRect(30, 30, 311, 401));
        transactionList->setFocusPolicy(Qt::NoFocus);
        plusSign = new QToolButton(mineCoins);
        plusSign->setObjectName(QString::fromUtf8("plusSign"));
        plusSign->setGeometry(QRect(280, 430, 33, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../assets/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        plusSign->setIcon(icon1);
        plusSign->setIconSize(QSize(24, 24));
        minusSign = new QToolButton(mineCoins);
        minusSign->setObjectName(QString::fromUtf8("minusSign"));
        minusSign->setGeometry(QRect(310, 430, 33, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../assets/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        minusSign->setIcon(icon2);
        minusSign->setIconSize(QSize(24, 24));
        blockTransactionList = new QListWidget(mineCoins);
        blockTransactionList->setObjectName(QString::fromUtf8("blockTransactionList"));
        blockTransactionList->setGeometry(QRect(390, 140, 351, 281));
        blockSize = new QTextBrowser(mineCoins);
        blockSize->setObjectName(QString::fromUtf8("blockSize"));
        blockSize->setGeometry(QRect(390, 430, 121, 31));
        stackedWidget->addWidget(mineCoins);
        addressBook = new QWidget();
        addressBook->setObjectName(QString::fromUtf8("addressBook"));
        buttonBox = new QDialogButtonBox(addressBook);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(380, 130, 174, 34));
        buttonBox->setFocusPolicy(Qt::StrongFocus);
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
        tableWidget->setFocusPolicy(Qt::NoFocus);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget->setColumnCount(2);
        stackedWidget->addWidget(addressBook);
        transactions = new QWidget();
        transactions->setObjectName(QString::fromUtf8("transactions"));
        stackedWidget->addWidget(transactions);
        account = new QWidget();
        account->setObjectName(QString::fromUtf8("account"));
        accountView = new QStackedWidget(account);
        accountView->setObjectName(QString::fromUtf8("accountView"));
        accountView->setGeometry(QRect(0, 20, 801, 491));
        signIn = new QWidget();
        signIn->setObjectName(QString::fromUtf8("signIn"));
        s_EmailField = new QLineEdit(signIn);
        s_EmailField->setObjectName(QString::fromUtf8("s_EmailField"));
        s_EmailField->setGeometry(QRect(290, 210, 241, 31));
        s_EmailField->setClearButtonEnabled(true);
        btn_signIn = new QPushButton(signIn);
        btn_signIn->setObjectName(QString::fromUtf8("btn_signIn"));
        btn_signIn->setGeometry(QRect(310, 330, 81, 31));
        signInTitle = new QLabel(signIn);
        signInTitle->setObjectName(QString::fromUtf8("signInTitle"));
        signInTitle->setGeometry(QRect(230, 110, 371, 81));
        s_PasswordField = new QLineEdit(signIn);
        s_PasswordField->setObjectName(QString::fromUtf8("s_PasswordField"));
        s_PasswordField->setGeometry(QRect(290, 250, 241, 31));
        s_PasswordField->setEchoMode(QLineEdit::Password);
        s_PasswordField->setClearButtonEnabled(true);
        btn_create = new QPushButton(signIn);
        btn_create->setObjectName(QString::fromUtf8("btn_create"));
        btn_create->setGeometry(QRect(410, 330, 81, 31));
        accountView->addWidget(signIn);
        signUp = new QWidget();
        signUp->setObjectName(QString::fromUtf8("signUp"));
        createTitle = new QLabel(signUp);
        createTitle->setObjectName(QString::fromUtf8("createTitle"));
        createTitle->setGeometry(QRect(220, 80, 381, 81));
        btn_signUp = new QPushButton(signUp);
        btn_signUp->setObjectName(QString::fromUtf8("btn_signUp"));
        btn_signUp->setGeometry(QRect(310, 330, 81, 31));
        btn_back = new QPushButton(signUp);
        btn_back->setObjectName(QString::fromUtf8("btn_back"));
        btn_back->setGeometry(QRect(410, 330, 81, 31));
        c_EmailField = new QLineEdit(signUp);
        c_EmailField->setObjectName(QString::fromUtf8("c_EmailField"));
        c_EmailField->setGeometry(QRect(290, 170, 241, 31));
        c_EmailField->setClearButtonEnabled(true);
        c_UsernameField = new QLineEdit(signUp);
        c_UsernameField->setObjectName(QString::fromUtf8("c_UsernameField"));
        c_UsernameField->setGeometry(QRect(290, 210, 241, 31));
        c_UsernameField->setClearButtonEnabled(true);
        c_PasswordField = new QLineEdit(signUp);
        c_PasswordField->setObjectName(QString::fromUtf8("c_PasswordField"));
        c_PasswordField->setGeometry(QRect(290, 250, 241, 31));
        c_PasswordField->setEchoMode(QLineEdit::Password);
        c_PasswordField->setClearButtonEnabled(true);
        accountView->addWidget(signUp);
        loggedIn = new QWidget();
        loggedIn->setObjectName(QString::fromUtf8("loggedIn"));
        label = new QLabel(loggedIn);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 80, 121, 41));
        textBrowser_2 = new QTextBrowser(loggedIn);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(30, 120, 331, 31));
        textBrowser_3 = new QTextBrowser(loggedIn);
        textBrowser_3->setObjectName(QString::fromUtf8("textBrowser_3"));
        textBrowser_3->setGeometry(QRect(30, 160, 331, 31));
        toolButton = new QToolButton(loggedIn);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(370, 120, 33, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../assets/no-view.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon3);
        toolButton_2 = new QToolButton(loggedIn);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        toolButton_2->setGeometry(QRect(370, 160, 33, 31));
        toolButton_2->setIcon(icon3);
        toolButton_3 = new QToolButton(loggedIn);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        toolButton_3->setGeometry(QRect(410, 120, 33, 31));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../assets/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_3->setIcon(icon4);
        toolButton_4 = new QToolButton(loggedIn);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));
        toolButton_4->setGeometry(QRect(410, 160, 33, 31));
        toolButton_4->setIcon(icon4);
        accountView->addWidget(loggedIn);
        stackedWidget->addWidget(account);
        MainWindow->setCentralWidget(centralwidget);
        stackedWidget->raise();
        tabWidget->raise();
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 30));
        icon = new QMenu(menubar);
        icon->setObjectName(QString::fromUtf8("icon"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("../assets/plasmacoin-logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon->setIcon(icon5);
        icon->setSeparatorsCollapsible(false);
        text = new QMenu(menubar);
        text->setObjectName(QString::fromUtf8("text"));
        MainWindow->setMenuBar(menubar);
        QWidget::setTabOrder(plusSign, minusSign);
        QWidget::setTabOrder(minusSign, blockSize);
        QWidget::setTabOrder(blockSize, btn_mine);
        QWidget::setTabOrder(btn_mine, amountLineEdit);
        QWidget::setTabOrder(amountLineEdit, buttonBox);
        QWidget::setTabOrder(buttonBox, s_EmailField);
        QWidget::setTabOrder(s_EmailField, s_PasswordField);
        QWidget::setTabOrder(s_PasswordField, btn_signIn);
        QWidget::setTabOrder(btn_signIn, btn_create);
        QWidget::setTabOrder(btn_create, c_EmailField);
        QWidget::setTabOrder(c_EmailField, c_UsernameField);
        QWidget::setTabOrder(c_UsernameField, c_PasswordField);
        QWidget::setTabOrder(c_PasswordField, btn_signUp);
        QWidget::setTabOrder(btn_signUp, btn_back);
        QWidget::setTabOrder(btn_back, toolButton);
        QWidget::setTabOrder(toolButton, toolButton_3);
        QWidget::setTabOrder(toolButton_3, toolButton_2);
        QWidget::setTabOrder(toolButton_2, toolButton_4);
        QWidget::setTabOrder(toolButton_4, blockTransactionList);
        QWidget::setTabOrder(blockTransactionList, textBrowser_2);
        QWidget::setTabOrder(textBrowser_2, textBrowser_3);
        QWidget::setTabOrder(textBrowser_3, textBrowser);

        menubar->addAction(icon->menuAction());
        menubar->addAction(text->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        stackedWidget->setCurrentIndex(0);
        accountView->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Wallet), QCoreApplication::translate("MainWindow", "Wallet", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Mine), QCoreApplication::translate("MainWindow", " Mine Coins", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(AddressBook), QCoreApplication::translate("MainWindow", "Address Book", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Transactions), QCoreApplication::translate("MainWindow", "Transactions", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Account), QCoreApplication::translate("MainWindow", "Account", nullptr));
        btn_mine->setText(QCoreApplication::translate("MainWindow", "Mine", nullptr));
        plusSign->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        minusSign->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        amountLabel->setText(QCoreApplication::translate("MainWindow", "Amount", nullptr));
        amountLineEdit->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        s_EmailField->setPlaceholderText(QCoreApplication::translate("MainWindow", "Email Address", nullptr));
        btn_signIn->setText(QCoreApplication::translate("MainWindow", "Sign In", nullptr));
        signInTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">Sign in to your Plasmacoin Account</span></p></body></html>", nullptr));
        s_PasswordField->setPlaceholderText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        btn_create->setText(QCoreApplication::translate("MainWindow", "Create...", nullptr));
        createTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">Create your Plasmacoin account</span></p></body></html>", nullptr));
        btn_signUp->setText(QCoreApplication::translate("MainWindow", "Sign Up", nullptr));
        btn_back->setText(QCoreApplication::translate("MainWindow", "Go Back...", nullptr));
        c_EmailField->setPlaceholderText(QCoreApplication::translate("MainWindow", "Email Address", nullptr));
#if QT_CONFIG(statustip)
        c_UsernameField->setStatusTip(QCoreApplication::translate("MainWindow", "Your username can contain alphanumeric characters and the following special characters: #, $, &, *, -", nullptr));
#endif // QT_CONFIG(statustip)
        c_UsernameField->setPlaceholderText(QCoreApplication::translate("MainWindow", "Username", nullptr));
#if QT_CONFIG(statustip)
        c_PasswordField->setStatusTip(QCoreApplication::translate("MainWindow", "Your password must be at least 6 characters long and contain at least 1 capital letter and 1 special character", nullptr));
#endif // QT_CONFIG(statustip)
        c_PasswordField->setInputMask(QString());
        c_PasswordField->setPlaceholderText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt;\">RSA Keys</span></p></body></html>", nullptr));
        toolButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_2->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_3->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_4->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        icon->setTitle(QCoreApplication::translate("MainWindow", "Plasmacoin UI", nullptr));
        text->setTitle(QCoreApplication::translate("MainWindow", "Plasmacoin UI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
