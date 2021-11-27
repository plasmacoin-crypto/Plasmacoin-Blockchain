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
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
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
    QWidget *AddressBookTab;
    QWidget *Transactions;
    QWidget *Account;
    QWidget *Settings;
    QStackedWidget *stackedWidget;
    QWidget *wallet;
    QLCDNumber *usdollars;
    QLCDNumber *plasmacoins;
    QWidget *mineCoins;
    QPushButton *btn_mine;
    QListWidget *transactionList;
    QListWidget *blockTransactionList;
    QTextBrowser *blockSize;
    QToolButton *plusSign;
    QToolButton *minusSign;
    QWidget *addressBook;
    QTableWidget *contactsList;
    QLineEdit *nameField;
    QLabel *contactImage;
    QLabel *addrBookSub2;
    QDateEdit *birthday;
    QLabel *addrBookSub3;
    QToolButton *btn_addContact;
    QPushButton *btn_edit;
    QPushButton *btn_delete;
    QLabel *addrBookSub1;
    QLineEdit *usernameField;
    QLineEdit *addressField;
    QLabel *usernameDisplay;
    QLabel *addressDisplay;
    QLabel *nameDisplay;
    QDialogButtonBox *btndiag_confirm;
    QWidget *transactions;
    QTextBrowser *textBrowser;
    QDialogButtonBox *buttonBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *amountLabel;
    QLineEdit *amountLineEdit;
    QWidget *account;
    QStackedWidget *accountView;
    QWidget *signIn;
    QLineEdit *s_EmailField;
    QPushButton *btn_signIn;
    QLabel *signInTitle;
    QLineEdit *s_PasswordField;
    QPushButton *btn_create;
    QWidget *banner1;
    QLabel *bannerText1;
    QWidget *signUp;
    QLabel *createTitle;
    QPushButton *btn_signUp;
    QPushButton *btn_back;
    QLineEdit *c_EmailField;
    QLineEdit *c_UsernameField;
    QLineEdit *c_PasswordField;
    QWidget *banner2;
    QLabel *bannerText2;
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
    QWidget *settings;
    QLabel *settingsTitle;
    QWidget *rsaKeyPath;
    QToolButton *btn_reset;
    QPushButton *btn_choosePath;
    QTextBrowser *rsaKeyView;
    QLabel *rsaKeyTitle;
    QLabel *rsaKeySubtitle;
    QWidget *changePassword;
    QLabel *chgPsswdTitle;
    QLabel *chgPsswdSubtitle;
    QLineEdit *currPassField;
    QLineEdit *newPassField;
    QPushButton *btn_confirm;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1262, 872);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../../../../.designer/assets/plasmacoin-logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setIconSize(QSize(200, 100));
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 1251, 31));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMaximumSize(QSize(1401, 31));
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
        AddressBookTab = new QWidget();
        AddressBookTab->setObjectName(QString::fromUtf8("AddressBookTab"));
        tabWidget->addTab(AddressBookTab, QString());
        Transactions = new QWidget();
        Transactions->setObjectName(QString::fromUtf8("Transactions"));
        tabWidget->addTab(Transactions, QString());
        Account = new QWidget();
        Account->setObjectName(QString::fromUtf8("Account"));
        tabWidget->addTab(Account, QString());
        Settings = new QWidget();
        Settings->setObjectName(QString::fromUtf8("Settings"));
        tabWidget->addTab(Settings, QString());
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setEnabled(true);
        stackedWidget->setGeometry(QRect(-10, 30, 1261, 821));
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
        btn_mine->setGeometry(QRect(840, 730, 84, 31));
        transactionList = new QListWidget(mineCoins);
        transactionList->setObjectName(QString::fromUtf8("transactionList"));
        transactionList->setGeometry(QRect(40, 80, 611, 651));
        transactionList->setFocusPolicy(Qt::NoFocus);
        blockTransactionList = new QListWidget(mineCoins);
        blockTransactionList->setObjectName(QString::fromUtf8("blockTransactionList"));
        blockTransactionList->setGeometry(QRect(690, 240, 551, 471));
        blockSize = new QTextBrowser(mineCoins);
        blockSize->setObjectName(QString::fromUtf8("blockSize"));
        blockSize->setGeometry(QRect(690, 730, 141, 31));
        plusSign = new QToolButton(mineCoins);
        plusSign->setObjectName(QString::fromUtf8("plusSign"));
        plusSign->setGeometry(QRect(590, 730, 33, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../../../../../.designer/assets/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        plusSign->setIcon(icon1);
        plusSign->setIconSize(QSize(24, 24));
        minusSign = new QToolButton(mineCoins);
        minusSign->setObjectName(QString::fromUtf8("minusSign"));
        minusSign->setGeometry(QRect(620, 730, 33, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../../../../../.designer/assets/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        minusSign->setIcon(icon2);
        minusSign->setIconSize(QSize(24, 24));
        stackedWidget->addWidget(mineCoins);
        addressBook = new QWidget();
        addressBook->setObjectName(QString::fromUtf8("addressBook"));
        contactsList = new QTableWidget(addressBook);
        if (contactsList->columnCount() < 2)
            contactsList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        contactsList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        contactsList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        contactsList->setObjectName(QString::fromUtf8("contactsList"));
        contactsList->setGeometry(QRect(30, 40, 531, 711));
        contactsList->setFocusPolicy(Qt::NoFocus);
        contactsList->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        contactsList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        contactsList->setSelectionMode(QAbstractItemView::SingleSelection);
        contactsList->setSelectionBehavior(QAbstractItemView::SelectRows);
        contactsList->setRowCount(0);
        contactsList->setColumnCount(2);
        contactsList->horizontalHeader()->setCascadingSectionResizes(true);
        contactsList->horizontalHeader()->setDefaultSectionSize(132);
        contactsList->horizontalHeader()->setStretchLastSection(true);
        contactsList->verticalHeader()->setStretchLastSection(false);
        nameField = new QLineEdit(addressBook);
        nameField->setObjectName(QString::fromUtf8("nameField"));
        nameField->setGeometry(QRect(840, 100, 391, 31));
        contactImage = new QLabel(addressBook);
        contactImage->setObjectName(QString::fromUtf8("contactImage"));
        contactImage->setGeometry(QRect(650, 40, 151, 151));
        contactImage->setPixmap(QPixmap(QString::fromUtf8("../assets/contact-default.png")));
        addrBookSub2 = new QLabel(addressBook);
        addrBookSub2->setObjectName(QString::fromUtf8("addrBookSub2"));
        addrBookSub2->setGeometry(QRect(660, 310, 91, 41));
        addrBookSub2->setStyleSheet(QString::fromUtf8("text-align: center"));
        birthday = new QDateEdit(addressBook);
        birthday->setObjectName(QString::fromUtf8("birthday"));
        birthday->setEnabled(true);
        birthday->setGeometry(QRect(660, 440, 110, 32));
        birthday->setFocusPolicy(Qt::NoFocus);
        birthday->setReadOnly(false);
        birthday->setCalendarPopup(true);
        addrBookSub3 = new QLabel(addressBook);
        addrBookSub3->setObjectName(QString::fromUtf8("addrBookSub3"));
        addrBookSub3->setGeometry(QRect(660, 400, 91, 41));
        addrBookSub3->setStyleSheet(QString::fromUtf8("text-align: center"));
        btn_addContact = new QToolButton(addressBook);
        btn_addContact->setObjectName(QString::fromUtf8("btn_addContact"));
        btn_addContact->setGeometry(QRect(530, 760, 31, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../assets/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_addContact->setIcon(icon3);
        btn_addContact->setIconSize(QSize(24, 24));
        btn_edit = new QPushButton(addressBook);
        btn_edit->setObjectName(QString::fromUtf8("btn_edit"));
        btn_edit->setGeometry(QRect(780, 520, 101, 34));
        btn_edit->setChecked(false);
        btn_edit->setFlat(false);
        btn_delete = new QPushButton(addressBook);
        btn_delete->setObjectName(QString::fromUtf8("btn_delete"));
        btn_delete->setGeometry(QRect(900, 520, 101, 34));
        addrBookSub1 = new QLabel(addressBook);
        addrBookSub1->setObjectName(QString::fromUtf8("addrBookSub1"));
        addrBookSub1->setGeometry(QRect(660, 220, 101, 41));
        addrBookSub1->setStyleSheet(QString::fromUtf8("text-align: center"));
        usernameField = new QLineEdit(addressBook);
        usernameField->setObjectName(QString::fromUtf8("usernameField"));
        usernameField->setGeometry(QRect(660, 260, 461, 32));
        addressField = new QLineEdit(addressBook);
        addressField->setObjectName(QString::fromUtf8("addressField"));
        addressField->setGeometry(QRect(660, 350, 461, 32));
        usernameDisplay = new QLabel(addressBook);
        usernameDisplay->setObjectName(QString::fromUtf8("usernameDisplay"));
        usernameDisplay->setGeometry(QRect(660, 260, 461, 31));
        addressDisplay = new QLabel(addressBook);
        addressDisplay->setObjectName(QString::fromUtf8("addressDisplay"));
        addressDisplay->setGeometry(QRect(660, 350, 461, 31));
        nameDisplay = new QLabel(addressBook);
        nameDisplay->setObjectName(QString::fromUtf8("nameDisplay"));
        nameDisplay->setGeometry(QRect(840, 100, 391, 31));
        btndiag_confirm = new QDialogButtonBox(addressBook);
        btndiag_confirm->setObjectName(QString::fromUtf8("btndiag_confirm"));
        btndiag_confirm->setGeometry(QRect(750, 520, 174, 34));
        btndiag_confirm->setOrientation(Qt::Horizontal);
        btndiag_confirm->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        stackedWidget->addWidget(addressBook);
        transactions = new QWidget();
        transactions->setObjectName(QString::fromUtf8("transactions"));
        textBrowser = new QTextBrowser(transactions);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(40, 20, 341, 31));
        buttonBox = new QDialogButtonBox(transactions);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(40, 110, 174, 34));
        buttonBox->setFocusPolicy(Qt::StrongFocus);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        formLayoutWidget = new QWidget(transactions);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(40, 70, 341, 41));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        amountLabel = new QLabel(formLayoutWidget);
        amountLabel->setObjectName(QString::fromUtf8("amountLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, amountLabel);

        amountLineEdit = new QLineEdit(formLayoutWidget);
        amountLineEdit->setObjectName(QString::fromUtf8("amountLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, amountLineEdit);

        stackedWidget->addWidget(transactions);
        account = new QWidget();
        account->setObjectName(QString::fromUtf8("account"));
        accountView = new QStackedWidget(account);
        accountView->setObjectName(QString::fromUtf8("accountView"));
        accountView->setGeometry(QRect(0, 20, 1261, 801));
        signIn = new QWidget();
        signIn->setObjectName(QString::fromUtf8("signIn"));
        s_EmailField = new QLineEdit(signIn);
        s_EmailField->setObjectName(QString::fromUtf8("s_EmailField"));
        s_EmailField->setGeometry(QRect(230, 380, 241, 31));
        s_EmailField->setClearButtonEnabled(true);
        btn_signIn = new QPushButton(signIn);
        btn_signIn->setObjectName(QString::fromUtf8("btn_signIn"));
        btn_signIn->setGeometry(QRect(250, 500, 81, 31));
        signInTitle = new QLabel(signIn);
        signInTitle->setObjectName(QString::fromUtf8("signInTitle"));
        signInTitle->setGeometry(QRect(130, 230, 451, 81));
        s_PasswordField = new QLineEdit(signIn);
        s_PasswordField->setObjectName(QString::fromUtf8("s_PasswordField"));
        s_PasswordField->setGeometry(QRect(230, 420, 241, 31));
        s_PasswordField->setEchoMode(QLineEdit::Password);
        s_PasswordField->setClearButtonEnabled(true);
        btn_create = new QPushButton(signIn);
        btn_create->setObjectName(QString::fromUtf8("btn_create"));
        btn_create->setGeometry(QRect(350, 500, 81, 31));
        banner1 = new QWidget(signIn);
        banner1->setObjectName(QString::fromUtf8("banner1"));
        banner1->setGeometry(QRect(650, 40, 591, 721));
        banner1->setStyleSheet(QString::fromUtf8("background-color: rgb(115, 233, 255);\n"
"border: 4px solid rgb(115, 233, 255);\n"
"border-radius: 4px"));
        bannerText1 = new QLabel(banner1);
        bannerText1->setObjectName(QString::fromUtf8("bannerText1"));
        bannerText1->setGeometry(QRect(0, 0, 591, 721));
        bannerText1->setStyleSheet(QString::fromUtf8(""));
        accountView->addWidget(signIn);
        signUp = new QWidget();
        signUp->setObjectName(QString::fromUtf8("signUp"));
        createTitle = new QLabel(signUp);
        createTitle->setObjectName(QString::fromUtf8("createTitle"));
        createTitle->setGeometry(QRect(60, 190, 611, 101));
        btn_signUp = new QPushButton(signUp);
        btn_signUp->setObjectName(QString::fromUtf8("btn_signUp"));
        btn_signUp->setGeometry(QRect(250, 510, 81, 31));
        btn_back = new QPushButton(signUp);
        btn_back->setObjectName(QString::fromUtf8("btn_back"));
        btn_back->setGeometry(QRect(350, 510, 81, 31));
        c_EmailField = new QLineEdit(signUp);
        c_EmailField->setObjectName(QString::fromUtf8("c_EmailField"));
        c_EmailField->setGeometry(QRect(230, 350, 241, 31));
        c_EmailField->setClearButtonEnabled(true);
        c_UsernameField = new QLineEdit(signUp);
        c_UsernameField->setObjectName(QString::fromUtf8("c_UsernameField"));
        c_UsernameField->setGeometry(QRect(230, 390, 241, 31));
        c_UsernameField->setClearButtonEnabled(true);
        c_PasswordField = new QLineEdit(signUp);
        c_PasswordField->setObjectName(QString::fromUtf8("c_PasswordField"));
        c_PasswordField->setGeometry(QRect(230, 430, 241, 31));
        c_PasswordField->setEchoMode(QLineEdit::Password);
        c_PasswordField->setClearButtonEnabled(true);
        banner2 = new QWidget(signUp);
        banner2->setObjectName(QString::fromUtf8("banner2"));
        banner2->setGeometry(QRect(650, 40, 591, 721));
        banner2->setStyleSheet(QString::fromUtf8("background-color: rgb(115, 233, 255);\n"
"border: 4px solid rgb(115, 233, 255);\n"
"border-radius: 4px"));
        bannerText2 = new QLabel(banner2);
        bannerText2->setObjectName(QString::fromUtf8("bannerText2"));
        bannerText2->setGeometry(QRect(0, 0, 591, 721));
        bannerText2->setStyleSheet(QString::fromUtf8(""));
        accountView->addWidget(signUp);
        loggedIn = new QWidget();
        loggedIn->setObjectName(QString::fromUtf8("loggedIn"));
        verticalLayoutWidget = new QWidget(loggedIn);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 0, 1251, 791));
        pageContainer = new QVBoxLayout(verticalLayoutWidget);
        pageContainer->setObjectName(QString::fromUtf8("pageContainer"));
        pageContainer->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(verticalLayoutWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setMinimumSize(QSize(0, 0));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setFrameShadow(QFrame::Sunken);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        scrollAreaContent = new QWidget();
        scrollAreaContent->setObjectName(QString::fromUtf8("scrollAreaContent"));
        scrollAreaContent->setGeometry(QRect(0, 0, 550, 550));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollAreaContent->sizePolicy().hasHeightForWidth());
        scrollAreaContent->setSizePolicy(sizePolicy2);
        scrollAreaContent->setMinimumSize(QSize(550, 550));
        contentContainer = new QWidget(scrollAreaContent);
        contentContainer->setObjectName(QString::fromUtf8("contentContainer"));
        contentContainer->setGeometry(QRect(0, 0, 631, 671));
        sizePolicy2.setHeightForWidth(contentContainer->sizePolicy().hasHeightForWidth());
        contentContainer->setSizePolicy(sizePolicy2);
        pageLayout = new QVBoxLayout(contentContainer);
        pageLayout->setObjectName(QString::fromUtf8("pageLayout"));
        pageLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        address = new QWidget(contentContainer);
        address->setObjectName(QString::fromUtf8("address"));
        addressCopy = new QToolButton(address);
        addressCopy->setObjectName(QString::fromUtf8("addressCopy"));
        addressCopy->setGeometry(QRect(340, 100, 33, 31));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(addressCopy->sizePolicy().hasHeightForWidth());
        addressCopy->setSizePolicy(sizePolicy3);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../../../../../../../../../../.designer/assets/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        addressCopy->setIcon(icon4);
        walletAddress = new QLineEdit(address);
        walletAddress->setObjectName(QString::fromUtf8("walletAddress"));
        walletAddress->setGeometry(QRect(10, 100, 321, 31));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(walletAddress->sizePolicy().hasHeightForWidth());
        walletAddress->setSizePolicy(sizePolicy4);
        walletAddress->setReadOnly(true);
        addressSubtitle = new QLabel(address);
        addressSubtitle->setObjectName(QString::fromUtf8("addressSubtitle"));
        addressSubtitle->setGeometry(QRect(10, 50, 491, 41));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(addressSubtitle->sizePolicy().hasHeightForWidth());
        addressSubtitle->setSizePolicy(sizePolicy5);
        addressTitle = new QLabel(address);
        addressTitle->setObjectName(QString::fromUtf8("addressTitle"));
        addressTitle->setGeometry(QRect(10, 10, 231, 31));
        sizePolicy5.setHeightForWidth(addressTitle->sizePolicy().hasHeightForWidth());
        addressTitle->setSizePolicy(sizePolicy5);

        pageLayout->addWidget(address);

        rsaKeys = new QWidget(contentContainer);
        rsaKeys->setObjectName(QString::fromUtf8("rsaKeys"));
        rsaKeys->setMinimumSize(QSize(0, 0));
        rsaTitle = new QLabel(rsaKeys);
        rsaTitle->setObjectName(QString::fromUtf8("rsaTitle"));
        rsaTitle->setGeometry(QRect(10, 10, 111, 31));
        sizePolicy5.setHeightForWidth(rsaTitle->sizePolicy().hasHeightForWidth());
        rsaTitle->setSizePolicy(sizePolicy5);
        privKeyShow = new QToolButton(rsaKeys);
        privKeyShow->setObjectName(QString::fromUtf8("privKeyShow"));
        privKeyShow->setGeometry(QRect(350, 89, 33, 31));
        sizePolicy3.setHeightForWidth(privKeyShow->sizePolicy().hasHeightForWidth());
        privKeyShow->setSizePolicy(sizePolicy3);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("../../../../../../../../../../.designer/assets/no-view.png"), QSize(), QIcon::Normal, QIcon::Off);
        privKeyShow->setIcon(icon5);
        publicKey = new QLineEdit(rsaKeys);
        publicKey->setObjectName(QString::fromUtf8("publicKey"));
        publicKey->setGeometry(QRect(10, 50, 331, 31));
        sizePolicy4.setHeightForWidth(publicKey->sizePolicy().hasHeightForWidth());
        publicKey->setSizePolicy(sizePolicy4);
        publicKey->setReadOnly(true);
        pubKeyCopy = new QToolButton(rsaKeys);
        pubKeyCopy->setObjectName(QString::fromUtf8("pubKeyCopy"));
        pubKeyCopy->setGeometry(QRect(390, 50, 33, 31));
        sizePolicy3.setHeightForWidth(pubKeyCopy->sizePolicy().hasHeightForWidth());
        pubKeyCopy->setSizePolicy(sizePolicy3);
        pubKeyCopy->setIcon(icon4);
        pubKeyShow = new QToolButton(rsaKeys);
        pubKeyShow->setObjectName(QString::fromUtf8("pubKeyShow"));
        pubKeyShow->setGeometry(QRect(350, 50, 33, 31));
        sizePolicy3.setHeightForWidth(pubKeyShow->sizePolicy().hasHeightForWidth());
        pubKeyShow->setSizePolicy(sizePolicy3);
        pubKeyShow->setIcon(icon5);
        privKeyCopy = new QToolButton(rsaKeys);
        privKeyCopy->setObjectName(QString::fromUtf8("privKeyCopy"));
        privKeyCopy->setGeometry(QRect(390, 90, 33, 31));
        sizePolicy3.setHeightForWidth(privKeyCopy->sizePolicy().hasHeightForWidth());
        privKeyCopy->setSizePolicy(sizePolicy3);
        privKeyCopy->setIcon(icon4);
        privateKey = new QLineEdit(rsaKeys);
        privateKey->setObjectName(QString::fromUtf8("privateKey"));
        privateKey->setGeometry(QRect(10, 90, 331, 31));
        sizePolicy4.setHeightForWidth(privateKey->sizePolicy().hasHeightForWidth());
        privateKey->setSizePolicy(sizePolicy4);
        privateKey->setReadOnly(true);

        pageLayout->addWidget(rsaKeys);

        pubIPAddr = new QWidget(contentContainer);
        pubIPAddr->setObjectName(QString::fromUtf8("pubIPAddr"));
        pubIPAddrTitle = new QLabel(pubIPAddr);
        pubIPAddrTitle->setObjectName(QString::fromUtf8("pubIPAddrTitle"));
        pubIPAddrTitle->setGeometry(QRect(10, 10, 201, 31));
        sizePolicy5.setHeightForWidth(pubIPAddrTitle->sizePolicy().hasHeightForWidth());
        pubIPAddrTitle->setSizePolicy(sizePolicy5);
        publicIPAddress = new QTextBrowser(pubIPAddr);
        publicIPAddress->setObjectName(QString::fromUtf8("publicIPAddress"));
        publicIPAddress->setGeometry(QRect(10, 140, 256, 31));
        sizePolicy4.setHeightForWidth(publicIPAddress->sizePolicy().hasHeightForWidth());
        publicIPAddress->setSizePolicy(sizePolicy4);
        pubIPAddrSubtitle = new QLabel(pubIPAddr);
        pubIPAddrSubtitle->setObjectName(QString::fromUtf8("pubIPAddrSubtitle"));
        pubIPAddrSubtitle->setGeometry(QRect(10, 50, 521, 81));
        sizePolicy5.setHeightForWidth(pubIPAddrSubtitle->sizePolicy().hasHeightForWidth());
        pubIPAddrSubtitle->setSizePolicy(sizePolicy5);

        pageLayout->addWidget(pubIPAddr);

        scrollArea->setWidget(scrollAreaContent);

        pageContainer->addWidget(scrollArea);

        accountView->addWidget(loggedIn);
        stackedWidget->addWidget(account);
        settings = new QWidget();
        settings->setObjectName(QString::fromUtf8("settings"));
        settingsTitle = new QLabel(settings);
        settingsTitle->setObjectName(QString::fromUtf8("settingsTitle"));
        settingsTitle->setGeometry(QRect(30, 20, 91, 41));
        rsaKeyPath = new QWidget(settings);
        rsaKeyPath->setObjectName(QString::fromUtf8("rsaKeyPath"));
        rsaKeyPath->setGeometry(QRect(30, 60, 431, 101));
        btn_reset = new QToolButton(rsaKeyPath);
        btn_reset->setObjectName(QString::fromUtf8("btn_reset"));
        btn_reset->setGeometry(QRect(370, 60, 33, 31));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("../../../../../../.designer/assets/reset.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_reset->setIcon(icon6);
        btn_choosePath = new QPushButton(rsaKeyPath);
        btn_choosePath->setObjectName(QString::fromUtf8("btn_choosePath"));
        btn_choosePath->setGeometry(QRect(260, 60, 101, 31));
        rsaKeyView = new QTextBrowser(rsaKeyPath);
        rsaKeyView->setObjectName(QString::fromUtf8("rsaKeyView"));
        rsaKeyView->setGeometry(QRect(0, 60, 251, 31));
        rsaKeyTitle = new QLabel(rsaKeyPath);
        rsaKeyTitle->setObjectName(QString::fromUtf8("rsaKeyTitle"));
        rsaKeyTitle->setGeometry(QRect(0, 0, 101, 31));
        rsaKeySubtitle = new QLabel(rsaKeyPath);
        rsaKeySubtitle->setObjectName(QString::fromUtf8("rsaKeySubtitle"));
        rsaKeySubtitle->setGeometry(QRect(0, 30, 431, 31));
        changePassword = new QWidget(settings);
        changePassword->setObjectName(QString::fromUtf8("changePassword"));
        changePassword->setGeometry(QRect(30, 170, 561, 231));
        chgPsswdTitle = new QLabel(changePassword);
        chgPsswdTitle->setObjectName(QString::fromUtf8("chgPsswdTitle"));
        chgPsswdTitle->setGeometry(QRect(0, 10, 141, 31));
        sizePolicy5.setHeightForWidth(chgPsswdTitle->sizePolicy().hasHeightForWidth());
        chgPsswdTitle->setSizePolicy(sizePolicy5);
        chgPsswdSubtitle = new QLabel(changePassword);
        chgPsswdSubtitle->setObjectName(QString::fromUtf8("chgPsswdSubtitle"));
        chgPsswdSubtitle->setGeometry(QRect(0, 40, 551, 61));
        sizePolicy5.setHeightForWidth(chgPsswdSubtitle->sizePolicy().hasHeightForWidth());
        chgPsswdSubtitle->setSizePolicy(sizePolicy5);
        currPassField = new QLineEdit(changePassword);
        currPassField->setObjectName(QString::fromUtf8("currPassField"));
        currPassField->setGeometry(QRect(0, 110, 241, 31));
        currPassField->setEchoMode(QLineEdit::Password);
        currPassField->setClearButtonEnabled(true);
        newPassField = new QLineEdit(changePassword);
        newPassField->setObjectName(QString::fromUtf8("newPassField"));
        newPassField->setGeometry(QRect(0, 150, 241, 31));
        newPassField->setEchoMode(QLineEdit::Password);
        newPassField->setClearButtonEnabled(true);
        btn_confirm = new QPushButton(changePassword);
        btn_confirm->setObjectName(QString::fromUtf8("btn_confirm"));
        btn_confirm->setGeometry(QRect(0, 190, 81, 31));
        stackedWidget->addWidget(settings);
        MainWindow->setCentralWidget(centralwidget);
        stackedWidget->raise();
        tabWidget->raise();
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(blockSize, btn_mine);
        QWidget::setTabOrder(btn_mine, s_EmailField);
        QWidget::setTabOrder(s_EmailField, s_PasswordField);
        QWidget::setTabOrder(s_PasswordField, btn_signIn);
        QWidget::setTabOrder(btn_signIn, btn_create);
        QWidget::setTabOrder(btn_create, c_EmailField);
        QWidget::setTabOrder(c_EmailField, c_UsernameField);
        QWidget::setTabOrder(c_UsernameField, c_PasswordField);
        QWidget::setTabOrder(c_PasswordField, btn_signUp);
        QWidget::setTabOrder(btn_signUp, btn_back);
        QWidget::setTabOrder(btn_back, blockTransactionList);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        stackedWidget->setCurrentIndex(2);
        accountView->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Plasmacoin Client", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Wallet), QCoreApplication::translate("MainWindow", "Wallet", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Mine), QCoreApplication::translate("MainWindow", " Mine Coins", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(AddressBookTab), QCoreApplication::translate("MainWindow", "Address Book", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Transactions), QCoreApplication::translate("MainWindow", "Transactions", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Account), QCoreApplication::translate("MainWindow", "Account", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Settings), QCoreApplication::translate("MainWindow", "Settings", nullptr));
        btn_mine->setText(QCoreApplication::translate("MainWindow", "Mine", nullptr));
        plusSign->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        minusSign->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        QTableWidgetItem *___qtablewidgetitem = contactsList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = contactsList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Address", nullptr));
        contactImage->setText(QString());
        addrBookSub2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Address</span></p></body></html>", nullptr));
        birthday->setDisplayFormat(QCoreApplication::translate("MainWindow", "M/d/yyyy", nullptr));
        addrBookSub3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Birthday</span></p></body></html>", nullptr));
        btn_addContact->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        btn_edit->setText(QCoreApplication::translate("MainWindow", "Edit Contact", nullptr));
        btn_delete->setText(QCoreApplication::translate("MainWindow", "Delete Contact", nullptr));
        addrBookSub1->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Username</span></p></body></html>", nullptr));
        usernameDisplay->setText(QString());
        addressDisplay->setText(QString());
        nameDisplay->setText(QString());
        amountLabel->setText(QCoreApplication::translate("MainWindow", "Amount", nullptr));
        amountLineEdit->setText(QString());
        s_EmailField->setPlaceholderText(QCoreApplication::translate("MainWindow", "Email Address", nullptr));
        btn_signIn->setText(QCoreApplication::translate("MainWindow", "Sign In", nullptr));
        signInTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt;\">Sign in to your Plasmacoin Account</span></p></body></html>", nullptr));
        s_PasswordField->setPlaceholderText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        btn_create->setText(QCoreApplication::translate("MainWindow", "Create...", nullptr));
        bannerText1->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; color:#000000;\">Welcome Back!</span></p><p align=\"center\"><span style=\" font-size:24pt; color:#000000;\">Please sign in to continue.</span><span style=\" color:#000000;\"><br/></span></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/><br/></p><p align=\"center\"><img src=\":/assets/plasmacoin-banner.png\" width=\"550\" height=\"150\"/></p></body></html>", nullptr));
        createTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt;\">Create your Plasmacoin account</span></p></body></html>", nullptr));
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
        bannerText2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\">What is my account for?</span></p><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\">Your Plasmacoin account registers you for the desktop app.<br/>This registers your computer as a Plasmacoin node and also<br/>gives you access to the offical Plasmacoin software wallet.</span></p><p align=\"center\"><span style=\" color:#000000;\"><br/></span></p><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\">Credentials</span></p><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\">Once you 're signed in, you'll have access to your public and<br/>private keys, as well as your Plasmacoin address, which is what<br/>you'll use to send and recieve transactions.</span></p><p align=\"center\"><span style=\" color:#000000;\"><br/></span></p><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\">Address Book</span></p><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\""
                        ">With your account, you can access the built-in address book,<br/>which allows you to save the addresses of other Plasmacoin<br/>users.</span></p><p align=\"center\"><br/></p><p align=\"center\"><img src=\":/newPrefix/plasmacoin-banner.png\" width=\"550\" height=\"150\"/></p></body></html>", nullptr));
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
        settingsTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">Settings</span></p></body></html>", nullptr));
        btn_reset->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        btn_choosePath->setText(QCoreApplication::translate("MainWindow", "Choose Path...", nullptr));
        rsaKeyTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; text-decoration: underline;\">RSA Key Path</span></p></body></html>", nullptr));
        rsaKeySubtitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Choose the path where your RSA public-private key pair will be stored.</p></body></html>", nullptr));
        chgPsswdTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; text-decoration: underline;\">Change Password</span></p></body></html>", nullptr));
        chgPsswdSubtitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Change the password for your Plasmacoin Account. Remember that your password<br/>must be at least 6 characters long and contain at least 1 capital letter, 1 special character,<br/>and 1 number.</p></body></html>", nullptr));
        currPassField->setInputMask(QString());
        currPassField->setPlaceholderText(QCoreApplication::translate("MainWindow", "Current Password", nullptr));
        newPassField->setInputMask(QString());
        newPassField->setPlaceholderText(QCoreApplication::translate("MainWindow", "New Password", nullptr));
        btn_confirm->setText(QCoreApplication::translate("MainWindow", "Confirm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
