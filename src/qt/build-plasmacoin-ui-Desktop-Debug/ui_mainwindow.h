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
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
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
    QWidget *verticalLayoutWidget;
    QVBoxLayout *pageContainer;
    QScrollArea *scrollArea;
    QWidget *scrollAreaContent;
    QWidget *contentContainer;
    QVBoxLayout *pageLayout;
    QWidget *address;
    QToolButton *addressCopy;
    QLineEdit *walletAddress;
    QLabel *addressSubtitle;
    QLabel *addressTitle;
    QWidget *rsaKeys;
    QLabel *rsaTitle;
    QToolButton *privKeyShow;
    QLineEdit *publicKey;
    QToolButton *pubKeyCopy;
    QToolButton *pubKeyShow;
    QToolButton *privKeyCopy;
    QLineEdit *privateKey;
    QWidget *pubIPAddr;
    QLabel *pubIPAddrTitle;
    QTextBrowser *publicIPAddress;
    QLabel *pubIPAddrSubtitle;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *icon;
    QMenu *text;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(807, 606);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../assets/plasmacoin-logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon1);
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
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../assets/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        plusSign->setIcon(icon2);
        plusSign->setIconSize(QSize(24, 24));
        minusSign = new QToolButton(mineCoins);
        minusSign->setObjectName(QString::fromUtf8("minusSign"));
        minusSign->setGeometry(QRect(310, 430, 33, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../assets/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        minusSign->setIcon(icon3);
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
        verticalLayoutWidget = new QWidget(loggedIn);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 10, 791, 481));
        pageContainer = new QVBoxLayout(verticalLayoutWidget);
        pageContainer->setObjectName(QString::fromUtf8("pageContainer"));
        pageContainer->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(verticalLayoutWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setMinimumSize(QSize(0, 0));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setFrameShadow(QFrame::Sunken);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        scrollAreaContent = new QWidget();
        scrollAreaContent->setObjectName(QString::fromUtf8("scrollAreaContent"));
        scrollAreaContent->setGeometry(QRect(0, 0, 768, 550));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollAreaContent->sizePolicy().hasHeightForWidth());
        scrollAreaContent->setSizePolicy(sizePolicy1);
        scrollAreaContent->setMinimumSize(QSize(550, 550));
        contentContainer = new QWidget(scrollAreaContent);
        contentContainer->setObjectName(QString::fromUtf8("contentContainer"));
        contentContainer->setGeometry(QRect(0, -10, 791, 551));
        sizePolicy1.setHeightForWidth(contentContainer->sizePolicy().hasHeightForWidth());
        contentContainer->setSizePolicy(sizePolicy1);
        pageLayout = new QVBoxLayout(contentContainer);
        pageLayout->setObjectName(QString::fromUtf8("pageLayout"));
        pageLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        address = new QWidget(contentContainer);
        address->setObjectName(QString::fromUtf8("address"));
        addressCopy = new QToolButton(address);
        addressCopy->setObjectName(QString::fromUtf8("addressCopy"));
        addressCopy->setGeometry(QRect(340, 100, 33, 31));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(addressCopy->sizePolicy().hasHeightForWidth());
        addressCopy->setSizePolicy(sizePolicy2);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../assets/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        addressCopy->setIcon(icon4);
        walletAddress = new QLineEdit(address);
        walletAddress->setObjectName(QString::fromUtf8("walletAddress"));
        walletAddress->setGeometry(QRect(10, 100, 321, 31));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(walletAddress->sizePolicy().hasHeightForWidth());
        walletAddress->setSizePolicy(sizePolicy3);
        walletAddress->setReadOnly(true);
        addressSubtitle = new QLabel(address);
        addressSubtitle->setObjectName(QString::fromUtf8("addressSubtitle"));
        addressSubtitle->setGeometry(QRect(10, 50, 491, 41));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(addressSubtitle->sizePolicy().hasHeightForWidth());
        addressSubtitle->setSizePolicy(sizePolicy4);
        addressTitle = new QLabel(address);
        addressTitle->setObjectName(QString::fromUtf8("addressTitle"));
        addressTitle->setGeometry(QRect(10, 10, 231, 31));
        sizePolicy4.setHeightForWidth(addressTitle->sizePolicy().hasHeightForWidth());
        addressTitle->setSizePolicy(sizePolicy4);

        pageLayout->addWidget(address);

        rsaKeys = new QWidget(contentContainer);
        rsaKeys->setObjectName(QString::fromUtf8("rsaKeys"));
        rsaKeys->setMinimumSize(QSize(0, 0));
        rsaTitle = new QLabel(rsaKeys);
        rsaTitle->setObjectName(QString::fromUtf8("rsaTitle"));
        rsaTitle->setGeometry(QRect(10, 10, 111, 31));
        sizePolicy4.setHeightForWidth(rsaTitle->sizePolicy().hasHeightForWidth());
        rsaTitle->setSizePolicy(sizePolicy4);
        privKeyShow = new QToolButton(rsaKeys);
        privKeyShow->setObjectName(QString::fromUtf8("privKeyShow"));
        privKeyShow->setGeometry(QRect(350, 89, 33, 31));
        sizePolicy2.setHeightForWidth(privKeyShow->sizePolicy().hasHeightForWidth());
        privKeyShow->setSizePolicy(sizePolicy2);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("../assets/no-view.png"), QSize(), QIcon::Normal, QIcon::Off);
        privKeyShow->setIcon(icon5);
        publicKey = new QLineEdit(rsaKeys);
        publicKey->setObjectName(QString::fromUtf8("publicKey"));
        publicKey->setGeometry(QRect(10, 50, 331, 31));
        sizePolicy3.setHeightForWidth(publicKey->sizePolicy().hasHeightForWidth());
        publicKey->setSizePolicy(sizePolicy3);
        publicKey->setReadOnly(true);
        pubKeyCopy = new QToolButton(rsaKeys);
        pubKeyCopy->setObjectName(QString::fromUtf8("pubKeyCopy"));
        pubKeyCopy->setGeometry(QRect(390, 50, 33, 31));
        sizePolicy2.setHeightForWidth(pubKeyCopy->sizePolicy().hasHeightForWidth());
        pubKeyCopy->setSizePolicy(sizePolicy2);
        pubKeyCopy->setIcon(icon4);
        pubKeyShow = new QToolButton(rsaKeys);
        pubKeyShow->setObjectName(QString::fromUtf8("pubKeyShow"));
        pubKeyShow->setGeometry(QRect(350, 50, 33, 31));
        sizePolicy2.setHeightForWidth(pubKeyShow->sizePolicy().hasHeightForWidth());
        pubKeyShow->setSizePolicy(sizePolicy2);
        pubKeyShow->setIcon(icon5);
        privKeyCopy = new QToolButton(rsaKeys);
        privKeyCopy->setObjectName(QString::fromUtf8("privKeyCopy"));
        privKeyCopy->setGeometry(QRect(390, 90, 33, 31));
        sizePolicy2.setHeightForWidth(privKeyCopy->sizePolicy().hasHeightForWidth());
        privKeyCopy->setSizePolicy(sizePolicy2);
        privKeyCopy->setIcon(icon4);
        privateKey = new QLineEdit(rsaKeys);
        privateKey->setObjectName(QString::fromUtf8("privateKey"));
        privateKey->setGeometry(QRect(10, 90, 331, 31));
        sizePolicy3.setHeightForWidth(privateKey->sizePolicy().hasHeightForWidth());
        privateKey->setSizePolicy(sizePolicy3);
        privateKey->setReadOnly(true);

        pageLayout->addWidget(rsaKeys);

        pubIPAddr = new QWidget(contentContainer);
        pubIPAddr->setObjectName(QString::fromUtf8("pubIPAddr"));
        pubIPAddrTitle = new QLabel(pubIPAddr);
        pubIPAddrTitle->setObjectName(QString::fromUtf8("pubIPAddrTitle"));
        pubIPAddrTitle->setGeometry(QRect(10, 10, 201, 31));
        sizePolicy4.setHeightForWidth(pubIPAddrTitle->sizePolicy().hasHeightForWidth());
        pubIPAddrTitle->setSizePolicy(sizePolicy4);
        publicIPAddress = new QTextBrowser(pubIPAddr);
        publicIPAddress->setObjectName(QString::fromUtf8("publicIPAddress"));
        publicIPAddress->setGeometry(QRect(10, 140, 256, 31));
        sizePolicy3.setHeightForWidth(publicIPAddress->sizePolicy().hasHeightForWidth());
        publicIPAddress->setSizePolicy(sizePolicy3);
        pubIPAddrSubtitle = new QLabel(pubIPAddr);
        pubIPAddrSubtitle->setObjectName(QString::fromUtf8("pubIPAddrSubtitle"));
        pubIPAddrSubtitle->setGeometry(QRect(10, 50, 521, 81));
        sizePolicy4.setHeightForWidth(pubIPAddrSubtitle->sizePolicy().hasHeightForWidth());
        pubIPAddrSubtitle->setSizePolicy(sizePolicy4);

        pageLayout->addWidget(pubIPAddr);

        scrollArea->setWidget(scrollAreaContent);

        pageContainer->addWidget(scrollArea);

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
        menubar->setGeometry(QRect(0, 0, 807, 30));
        icon = new QMenu(menubar);
        icon->setObjectName(QString::fromUtf8("icon"));
        icon->setIcon(icon1);
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
        QWidget::setTabOrder(btn_back, blockTransactionList);
        QWidget::setTabOrder(blockTransactionList, textBrowser);

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
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Plasmacoin Client", nullptr));
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
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Address", nullptr));
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
        c_UsernameField->setStatusTip(QCoreApplication::translate("MainWindow", "Your username can contain alphanumeric characters, dashes, underscores, and periods", nullptr));
#endif // QT_CONFIG(statustip)
        c_UsernameField->setPlaceholderText(QCoreApplication::translate("MainWindow", "Username", nullptr));
#if QT_CONFIG(statustip)
        c_PasswordField->setStatusTip(QCoreApplication::translate("MainWindow", "Your password must be at least 6 characters long and contain at least 1 capital letter, 1 special character, and 1 number", nullptr));
#endif // QT_CONFIG(statustip)
        c_PasswordField->setInputMask(QString());
        c_PasswordField->setPlaceholderText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        addressCopy->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        addressSubtitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">Your Plasmacoin address identifies your node as the sender or reciever<br/>in a transaction. It is also the way Plasmacoin is sent to your node.</span></p></body></html>", nullptr));
        addressTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">Your Wallet Address</span></p></body></html>", nullptr));
        rsaTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">RSA Keys</span></p></body></html>", nullptr));
        privKeyShow->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        pubKeyCopy->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        pubKeyShow->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        privKeyCopy->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        pubIPAddrTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">Public IP Address</span></p></body></html>", nullptr));
        pubIPAddrSubtitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">Your public IP address is what is used to send your Plasmacoin to once<br>the block with your transaction(s) is confirmed to the blockchain. Your<br>IP address is neither stored on the blockchain nor directly traceable from<br>a transaction</span></p></body></html>", nullptr));
        icon->setTitle(QCoreApplication::translate("MainWindow", "Plasmacoin UI", nullptr));
        text->setTitle(QCoreApplication::translate("MainWindow", "Plasmacoin Client", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
