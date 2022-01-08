/********************************************************************************
** Form generated from reading UI file 'macos.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
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
    QHBoxLayout *horizontalLayout_24;
    QTabWidget *tabWidget;
    QWidget *Wallet;
    QVBoxLayout *verticalLayout_7;
    QLCDNumber *usdollars;
    QLCDNumber *plasmacoins;
    QWidget *Mine;
    QHBoxLayout *horizontalLayout_25;
    QWidget *transactions;
    QVBoxLayout *verticalLayout;
    QListWidget *transactionList;
    QHBoxLayout *mineLayout1;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *plusSign;
    QToolButton *minusSign;
    QWidget *userBlock;
    QVBoxLayout *verticalLayout_3;
    QListWidget *blockTransactionList;
    QHBoxLayout *mineLayout2;
    QSpacerItem *horizontalSpacer;
    QTextBrowser *blockSize;
    QPushButton *btn_mine;
    QWidget *AddressBookTab;
    QHBoxLayout *horizontalLayout_8;
    QWidget *addressBook;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *contactsList;
    QHBoxLayout *buttonLayout;
    QToolButton *btn_addContact;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *btn_filler;
    QWidget *contactInfo;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *field1;
    QLabel *contactImage;
    QSpacerItem *horizontalSpacer_11;
    QLineEdit *nameField;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *field2;
    QLabel *addrBookSub1;
    QSpacerItem *horizontalSpacer_7;
    QLineEdit *usernameField;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *field3;
    QLabel *addrBookSub2;
    QSpacerItem *horizontalSpacer_13;
    QLineEdit *addressField;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *field4;
    QSpacerItem *horizontalSpacer_9;
    QLabel *addrBookSub3;
    QSpacerItem *horizontalSpacer_12;
    QDateEdit *birthday;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *dialogLayout;
    QDialogButtonBox *btndiag_confirm;
    QSpacerItem *verticalSpacer;
    QWidget *Transactions;
    QHBoxLayout *horizontalLayout_9;
    QWidget *contactsView;
    QVBoxLayout *verticalLayout_5;
    QLabel *trxnsHeading1;
    QListWidget *contacts;
    QSpacerItem *horizontalSpacer_30;
    QWidget *makeTransactions;
    QVBoxLayout *verticalLayout_10;
    QWidget *dialogs;
    QVBoxLayout *verticalLayout_9;
    QLabel *trxnsHeading1_2;
    QSpacerItem *verticalSpacer_4;
    QLineEdit *selectedContact;
    QLineEdit *messageField;
    QLabel *charCount;
    QHBoxLayout *selectionLayout;
    QWidget *selectors;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *amountView;
    QLabel *amountLabel;
    QSpacerItem *horizontalSpacer_15;
    QDoubleSpinBox *amountSelector;
    QHBoxLayout *feeView;
    QLabel *feeLabel;
    QSpacerItem *horizontalSpacer_16;
    QDoubleSpinBox *feeSelector;
    QHBoxLayout *totalView;
    QLabel *totalLabel;
    QSpacerItem *horizontalSpacer_17;
    QLineEdit *total;
    QSpacerItem *horizontalSpacer_14;
    QDialogButtonBox *btndiag_send;
    QVBoxLayout *spacerLayout1;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_18;
    QWidget *trxnLogView;
    QVBoxLayout *verticalLayout_6;
    QLabel *trxnsHeading2;
    QListWidget *transactionLog;
    QWidget *Account;
    QHBoxLayout *horizontalLayout_16;
    QStackedWidget *accountView;
    QWidget *signIn;
    QHBoxLayout *horizontalLayout_17;
    QSpacerItem *horizontalSpacer_20;
    QWidget *widget_8;
    QVBoxLayout *verticalLayout_18;
    QSpacerItem *verticalSpacer_6;
    QLabel *signInTitle;
    QSpacerItem *verticalSpacer_8;
    QVBoxLayout *verticalLayout_17;
    QLineEdit *s_EmailField;
    QLineEdit *s_PasswordField;
    QSpacerItem *verticalSpacer_7;
    QPushButton *btn_signIn;
    QPushButton *btn_create;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *horizontalSpacer_21;
    QWidget *widget_9;
    QVBoxLayout *verticalLayout_20;
    QWidget *banner1;
    QVBoxLayout *verticalLayout_21;
    QLabel *bannerText1;
    QSpacerItem *horizontalSpacer_22;
    QWidget *signUp;
    QHBoxLayout *horizontalLayout_18;
    QSpacerItem *horizontalSpacer_23;
    QWidget *widget_10;
    QVBoxLayout *verticalLayout_13;
    QSpacerItem *verticalSpacer_11;
    QLabel *createTitle;
    QSpacerItem *verticalSpacer_10;
    QVBoxLayout *verticalLayout_12;
    QLineEdit *c_EmailField;
    QLineEdit *c_UsernameField;
    QLineEdit *c_PasswordField;
    QSpacerItem *verticalSpacer_9;
    QPushButton *btn_signUp;
    QPushButton *btn_back;
    QSpacerItem *verticalSpacer_12;
    QSpacerItem *horizontalSpacer_25;
    QWidget *widget_11;
    QVBoxLayout *verticalLayout_16;
    QWidget *banner2;
    QVBoxLayout *verticalLayout_15;
    QLabel *bannerText2;
    QSpacerItem *horizontalSpacer_24;
    QWidget *loggedIn;
    QHBoxLayout *horizontalLayout_15;
    QVBoxLayout *pageContainer;
    QScrollArea *scrollArea;
    QWidget *scrollAreaContent;
    QHBoxLayout *horizontalLayout_22;
    QSpacerItem *horizontalSpacer_26;
    QWidget *contentContainer;
    QVBoxLayout *pageLayout;
    QWidget *address;
    QVBoxLayout *verticalLayout_22;
    QLabel *addressTitle;
    QLabel *addressSubtitle;
    QHBoxLayout *horizontalLayout_19;
    QLineEdit *walletAddress;
    QToolButton *addressCopy;
    QWidget *rsaKeys;
    QVBoxLayout *verticalLayout_19;
    QLabel *rsaTitle;
    QHBoxLayout *horizontalLayout_20;
    QLineEdit *publicKey;
    QToolButton *pubKeyShow;
    QToolButton *pubKeyCopy;
    QHBoxLayout *horizontalLayout_21;
    QLineEdit *privateKey;
    QToolButton *privKeyShow;
    QToolButton *privKeyCopy;
    QWidget *pubIPAddr;
    QVBoxLayout *verticalLayout_24;
    QLabel *pubIPAddrTitle;
    QLabel *pubIPAddrSubtitle;
    QTextBrowser *publicIPAddress;
    QSpacerItem *horizontalSpacer_27;
    QWidget *Settings;
    QVBoxLayout *verticalLayout_28;
    QLabel *settingsTitle;
    QGridLayout *gridLayout_2;
    QWidget *rsaKeyPath;
    QVBoxLayout *verticalLayout_25;
    QLabel *rsaKeyTitle;
    QLabel *rsaKeySubtitle;
    QHBoxLayout *horizontalLayout_23;
    QTextBrowser *rsaKeyView;
    QPushButton *btn_choosePath;
    QToolButton *btn_reset;
    QSpacerItem *verticalSpacer_13;
    QWidget *changePassword;
    QVBoxLayout *verticalLayout_27;
    QLabel *chgPsswdTitle;
    QLabel *chgPsswdSubtitle;
    QVBoxLayout *verticalLayout_26;
    QLineEdit *currPassField;
    QLineEdit *newPassField;
    QPushButton *btn_confirm;
    QSpacerItem *verticalSpacer_14;
    QSpacerItem *horizontalSpacer_28;
    QSpacerItem *horizontalSpacer_29;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1309, 980);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../../../../../../../../../../../../../../../../.designer/assets/plasmacoin-logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setIconSize(QSize(200, 100));
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_24 = new QHBoxLayout(centralwidget);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        horizontalLayout_24->setContentsMargins(0, -1, 0, -1);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMaximumSize(QSize(16777215, 16777215));
        tabWidget->setFocusPolicy(Qt::NoFocus);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        Wallet = new QWidget();
        Wallet->setObjectName(QString::fromUtf8("Wallet"));
        verticalLayout_7 = new QVBoxLayout(Wallet);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        usdollars = new QLCDNumber(Wallet);
        usdollars->setObjectName(QString::fromUtf8("usdollars"));
        usdollars->setSmallDecimalPoint(false);
        usdollars->setDigitCount(5);
        usdollars->setMode(QLCDNumber::Dec);
        usdollars->setSegmentStyle(QLCDNumber::Filled);

        verticalLayout_7->addWidget(usdollars);

        plasmacoins = new QLCDNumber(Wallet);
        plasmacoins->setObjectName(QString::fromUtf8("plasmacoins"));
        plasmacoins->setLayoutDirection(Qt::LeftToRight);
        plasmacoins->setSmallDecimalPoint(false);
        plasmacoins->setDigitCount(5);
        plasmacoins->setMode(QLCDNumber::Dec);
        plasmacoins->setSegmentStyle(QLCDNumber::Filled);

        verticalLayout_7->addWidget(plasmacoins);

        tabWidget->addTab(Wallet, QString());
        Mine = new QWidget();
        Mine->setObjectName(QString::fromUtf8("Mine"));
        horizontalLayout_25 = new QHBoxLayout(Mine);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        transactions = new QWidget(Mine);
        transactions->setObjectName(QString::fromUtf8("transactions"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(transactions->sizePolicy().hasHeightForWidth());
        transactions->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(transactions);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        transactionList = new QListWidget(transactions);
        transactionList->setObjectName(QString::fromUtf8("transactionList"));
        sizePolicy.setHeightForWidth(transactionList->sizePolicy().hasHeightForWidth());
        transactionList->setSizePolicy(sizePolicy);
        transactionList->setFocusPolicy(Qt::NoFocus);

        verticalLayout->addWidget(transactionList);

        mineLayout1 = new QHBoxLayout();
        mineLayout1->setObjectName(QString::fromUtf8("mineLayout1"));
        mineLayout1->setSizeConstraint(QLayout::SetFixedSize);
        mineLayout1->setContentsMargins(0, -1, 1, -1);
        horizontalSpacer_2 = new QSpacerItem(40, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        mineLayout1->addItem(horizontalSpacer_2);

        plusSign = new QToolButton(transactions);
        plusSign->setObjectName(QString::fromUtf8("plusSign"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(plusSign->sizePolicy().hasHeightForWidth());
        plusSign->setSizePolicy(sizePolicy2);
        plusSign->setMaximumSize(QSize(16777215, 34));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../../../../../../../../../../../../../../../../../.designer/assets/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        plusSign->setIcon(icon1);
        plusSign->setIconSize(QSize(24, 24));

        mineLayout1->addWidget(plusSign);

        minusSign = new QToolButton(transactions);
        minusSign->setObjectName(QString::fromUtf8("minusSign"));
        sizePolicy2.setHeightForWidth(minusSign->sizePolicy().hasHeightForWidth());
        minusSign->setSizePolicy(sizePolicy2);
        minusSign->setMaximumSize(QSize(16777215, 34));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../../../../../../../../../../../../../../../../../.designer/assets/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        minusSign->setIcon(icon2);
        minusSign->setIconSize(QSize(24, 24));

        mineLayout1->addWidget(minusSign);


        verticalLayout->addLayout(mineLayout1);


        horizontalLayout_25->addWidget(transactions);

        userBlock = new QWidget(Mine);
        userBlock->setObjectName(QString::fromUtf8("userBlock"));
        sizePolicy.setHeightForWidth(userBlock->sizePolicy().hasHeightForWidth());
        userBlock->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(userBlock);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        blockTransactionList = new QListWidget(userBlock);
        blockTransactionList->setObjectName(QString::fromUtf8("blockTransactionList"));

        verticalLayout_3->addWidget(blockTransactionList);

        mineLayout2 = new QHBoxLayout();
        mineLayout2->setObjectName(QString::fromUtf8("mineLayout2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        mineLayout2->addItem(horizontalSpacer);

        blockSize = new QTextBrowser(userBlock);
        blockSize->setObjectName(QString::fromUtf8("blockSize"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(blockSize->sizePolicy().hasHeightForWidth());
        blockSize->setSizePolicy(sizePolicy3);
        blockSize->setMaximumSize(QSize(200, 30));

        mineLayout2->addWidget(blockSize);

        btn_mine = new QPushButton(userBlock);
        btn_mine->setObjectName(QString::fromUtf8("btn_mine"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(btn_mine->sizePolicy().hasHeightForWidth());
        btn_mine->setSizePolicy(sizePolicy4);

        mineLayout2->addWidget(btn_mine);


        verticalLayout_3->addLayout(mineLayout2);


        horizontalLayout_25->addWidget(userBlock);

        tabWidget->addTab(Mine, QString());
        AddressBookTab = new QWidget();
        AddressBookTab->setObjectName(QString::fromUtf8("AddressBookTab"));
        horizontalLayout_8 = new QHBoxLayout(AddressBookTab);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        addressBook = new QWidget(AddressBookTab);
        addressBook->setObjectName(QString::fromUtf8("addressBook"));
        verticalLayout_2 = new QVBoxLayout(addressBook);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        contactsList = new QTableWidget(addressBook);
        if (contactsList->columnCount() < 2)
            contactsList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        contactsList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        contactsList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        contactsList->setObjectName(QString::fromUtf8("contactsList"));
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

        verticalLayout_2->addWidget(contactsList);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        btn_addContact = new QToolButton(addressBook);
        btn_addContact->setObjectName(QString::fromUtf8("btn_addContact"));
        QSizePolicy sizePolicy5(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(btn_addContact->sizePolicy().hasHeightForWidth());
        btn_addContact->setSizePolicy(sizePolicy5);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../../../../../../../../../../../../../.designer/assets/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_addContact->setIcon(icon3);
        btn_addContact->setIconSize(QSize(24, 24));

        buttonLayout->addWidget(btn_addContact);

        horizontalSpacer_3 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(horizontalSpacer_3);

        btn_filler = new QToolButton(addressBook);
        btn_filler->setObjectName(QString::fromUtf8("btn_filler"));
        btn_filler->setEnabled(false);
        sizePolicy2.setHeightForWidth(btn_filler->sizePolicy().hasHeightForWidth());
        btn_filler->setSizePolicy(sizePolicy2);
        btn_filler->setIcon(icon3);
        btn_filler->setIconSize(QSize(24, 24));

        buttonLayout->addWidget(btn_filler);


        verticalLayout_2->addLayout(buttonLayout);


        horizontalLayout_8->addWidget(addressBook);

        contactInfo = new QWidget(AddressBookTab);
        contactInfo->setObjectName(QString::fromUtf8("contactInfo"));
        contactInfo->setEnabled(true);
        sizePolicy3.setHeightForWidth(contactInfo->sizePolicy().hasHeightForWidth());
        contactInfo->setSizePolicy(sizePolicy3);
        verticalLayout_4 = new QVBoxLayout(contactInfo);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, -1, -1, 10);
        field1 = new QHBoxLayout();
        field1->setObjectName(QString::fromUtf8("field1"));
        contactImage = new QLabel(contactInfo);
        contactImage->setObjectName(QString::fromUtf8("contactImage"));
        sizePolicy2.setHeightForWidth(contactImage->sizePolicy().hasHeightForWidth());
        contactImage->setSizePolicy(sizePolicy2);
        contactImage->setPixmap(QPixmap(QString::fromUtf8("../../assets/contact-default.png")));

        field1->addWidget(contactImage);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        field1->addItem(horizontalSpacer_11);

        nameField = new QLineEdit(contactInfo);
        nameField->setObjectName(QString::fromUtf8("nameField"));
        nameField->setEnabled(true);
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(nameField->sizePolicy().hasHeightForWidth());
        nameField->setSizePolicy(sizePolicy6);
        nameField->setMaximumSize(QSize(425, 30));

        field1->addWidget(nameField);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        field1->addItem(horizontalSpacer_10);


        verticalLayout_4->addLayout(field1);

        field2 = new QHBoxLayout();
        field2->setObjectName(QString::fromUtf8("field2"));
        addrBookSub1 = new QLabel(contactInfo);
        addrBookSub1->setObjectName(QString::fromUtf8("addrBookSub1"));
        sizePolicy2.setHeightForWidth(addrBookSub1->sizePolicy().hasHeightForWidth());
        addrBookSub1->setSizePolicy(sizePolicy2);
        addrBookSub1->setMaximumSize(QSize(70, 16777215));
        addrBookSub1->setStyleSheet(QString::fromUtf8("text-align: center"));

        field2->addWidget(addrBookSub1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        field2->addItem(horizontalSpacer_7);

        usernameField = new QLineEdit(contactInfo);
        usernameField->setObjectName(QString::fromUtf8("usernameField"));
        usernameField->setEnabled(true);
        QSizePolicy sizePolicy7(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(usernameField->sizePolicy().hasHeightForWidth());
        usernameField->setSizePolicy(sizePolicy7);
        usernameField->setMaximumSize(QSize(500, 30));

        field2->addWidget(usernameField);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        field2->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(field2);

        field3 = new QHBoxLayout();
        field3->setObjectName(QString::fromUtf8("field3"));
        addrBookSub2 = new QLabel(contactInfo);
        addrBookSub2->setObjectName(QString::fromUtf8("addrBookSub2"));
        QSizePolicy sizePolicy8(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(addrBookSub2->sizePolicy().hasHeightForWidth());
        addrBookSub2->setSizePolicy(sizePolicy8);
        addrBookSub2->setMaximumSize(QSize(70, 16777215));
        addrBookSub2->setStyleSheet(QString::fromUtf8("text-align: center"));

        field3->addWidget(addrBookSub2);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        field3->addItem(horizontalSpacer_13);

        addressField = new QLineEdit(contactInfo);
        addressField->setObjectName(QString::fromUtf8("addressField"));
        addressField->setEnabled(true);
        sizePolicy7.setHeightForWidth(addressField->sizePolicy().hasHeightForWidth());
        addressField->setSizePolicy(sizePolicy7);
        addressField->setMaximumSize(QSize(500, 30));

        field3->addWidget(addressField);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        field3->addItem(horizontalSpacer_6);


        verticalLayout_4->addLayout(field3);

        field4 = new QHBoxLayout();
        field4->setObjectName(QString::fromUtf8("field4"));
        horizontalSpacer_9 = new QSpacerItem(0, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        field4->addItem(horizontalSpacer_9);

        addrBookSub3 = new QLabel(contactInfo);
        addrBookSub3->setObjectName(QString::fromUtf8("addrBookSub3"));
        sizePolicy2.setHeightForWidth(addrBookSub3->sizePolicy().hasHeightForWidth());
        addrBookSub3->setSizePolicy(sizePolicy2);
        addrBookSub3->setMaximumSize(QSize(70, 16777215));
        addrBookSub3->setStyleSheet(QString::fromUtf8("text-align: center"));

        field4->addWidget(addrBookSub3);

        horizontalSpacer_12 = new QSpacerItem(50, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        field4->addItem(horizontalSpacer_12);

        birthday = new QDateEdit(contactInfo);
        birthday->setObjectName(QString::fromUtf8("birthday"));
        birthday->setEnabled(true);
        sizePolicy7.setHeightForWidth(birthday->sizePolicy().hasHeightForWidth());
        birthday->setSizePolicy(sizePolicy7);
        birthday->setMaximumSize(QSize(127, 32));
        birthday->setFocusPolicy(Qt::NoFocus);
        birthday->setReadOnly(false);
        birthday->setCalendarPopup(true);

        field4->addWidget(birthday);

        horizontalSpacer_8 = new QSpacerItem(373, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        field4->addItem(horizontalSpacer_8);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        field4->addItem(horizontalSpacer_5);


        verticalLayout_4->addLayout(field4);

        dialogLayout = new QHBoxLayout();
        dialogLayout->setObjectName(QString::fromUtf8("dialogLayout"));
        dialogLayout->setSizeConstraint(QLayout::SetNoConstraint);
        btndiag_confirm = new QDialogButtonBox(contactInfo);
        btndiag_confirm->setObjectName(QString::fromUtf8("btndiag_confirm"));
        sizePolicy7.setHeightForWidth(btndiag_confirm->sizePolicy().hasHeightForWidth());
        btndiag_confirm->setSizePolicy(sizePolicy7);
        btndiag_confirm->setOrientation(Qt::Horizontal);
        btndiag_confirm->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        dialogLayout->addWidget(btndiag_confirm);


        verticalLayout_4->addLayout(dialogLayout);

        verticalSpacer = new QSpacerItem(20, 500, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_4->addItem(verticalSpacer);


        horizontalLayout_8->addWidget(contactInfo);

        tabWidget->addTab(AddressBookTab, QString());
        Transactions = new QWidget();
        Transactions->setObjectName(QString::fromUtf8("Transactions"));
        horizontalLayout_9 = new QHBoxLayout(Transactions);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        contactsView = new QWidget(Transactions);
        contactsView->setObjectName(QString::fromUtf8("contactsView"));
        sizePolicy.setHeightForWidth(contactsView->sizePolicy().hasHeightForWidth());
        contactsView->setSizePolicy(sizePolicy);
        verticalLayout_5 = new QVBoxLayout(contactsView);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        trxnsHeading1 = new QLabel(contactsView);
        trxnsHeading1->setObjectName(QString::fromUtf8("trxnsHeading1"));

        verticalLayout_5->addWidget(trxnsHeading1);

        contacts = new QListWidget(contactsView);
        contacts->setObjectName(QString::fromUtf8("contacts"));

        verticalLayout_5->addWidget(contacts);


        horizontalLayout_9->addWidget(contactsView);

        horizontalSpacer_30 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_30);

        makeTransactions = new QWidget(Transactions);
        makeTransactions->setObjectName(QString::fromUtf8("makeTransactions"));
        QSizePolicy sizePolicy9(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(makeTransactions->sizePolicy().hasHeightForWidth());
        makeTransactions->setSizePolicy(sizePolicy9);
        verticalLayout_10 = new QVBoxLayout(makeTransactions);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        dialogs = new QWidget(makeTransactions);
        dialogs->setObjectName(QString::fromUtf8("dialogs"));
        sizePolicy.setHeightForWidth(dialogs->sizePolicy().hasHeightForWidth());
        dialogs->setSizePolicy(sizePolicy);
        verticalLayout_9 = new QVBoxLayout(dialogs);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        trxnsHeading1_2 = new QLabel(dialogs);
        trxnsHeading1_2->setObjectName(QString::fromUtf8("trxnsHeading1_2"));

        verticalLayout_9->addWidget(trxnsHeading1_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_4);

        selectedContact = new QLineEdit(dialogs);
        selectedContact->setObjectName(QString::fromUtf8("selectedContact"));
        sizePolicy9.setHeightForWidth(selectedContact->sizePolicy().hasHeightForWidth());
        selectedContact->setSizePolicy(sizePolicy9);
        selectedContact->setMaximumSize(QSize(16777215, 50));
        selectedContact->setReadOnly(true);

        verticalLayout_9->addWidget(selectedContact);

        messageField = new QLineEdit(dialogs);
        messageField->setObjectName(QString::fromUtf8("messageField"));
        sizePolicy9.setHeightForWidth(messageField->sizePolicy().hasHeightForWidth());
        messageField->setSizePolicy(sizePolicy9);
        messageField->setMaximumSize(QSize(16777215, 50));

        verticalLayout_9->addWidget(messageField);

        charCount = new QLabel(dialogs);
        charCount->setObjectName(QString::fromUtf8("charCount"));
        sizePolicy.setHeightForWidth(charCount->sizePolicy().hasHeightForWidth());
        charCount->setSizePolicy(sizePolicy);
        charCount->setMaximumSize(QSize(16777215, 8));

        verticalLayout_9->addWidget(charCount);


        verticalLayout_10->addWidget(dialogs);

        selectionLayout = new QHBoxLayout();
        selectionLayout->setObjectName(QString::fromUtf8("selectionLayout"));
        selectors = new QWidget(makeTransactions);
        selectors->setObjectName(QString::fromUtf8("selectors"));
        sizePolicy.setHeightForWidth(selectors->sizePolicy().hasHeightForWidth());
        selectors->setSizePolicy(sizePolicy);
        verticalLayout_8 = new QVBoxLayout(selectors);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        amountView = new QHBoxLayout();
        amountView->setObjectName(QString::fromUtf8("amountView"));
        amountLabel = new QLabel(selectors);
        amountLabel->setObjectName(QString::fromUtf8("amountLabel"));
        QSizePolicy sizePolicy10(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(amountLabel->sizePolicy().hasHeightForWidth());
        amountLabel->setSizePolicy(sizePolicy10);

        amountView->addWidget(amountLabel);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        amountView->addItem(horizontalSpacer_15);

        amountSelector = new QDoubleSpinBox(selectors);
        amountSelector->setObjectName(QString::fromUtf8("amountSelector"));
        QSizePolicy sizePolicy11(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(amountSelector->sizePolicy().hasHeightForWidth());
        amountSelector->setSizePolicy(sizePolicy11);
        amountSelector->setMaximumSize(QSize(16777215, 30));
        amountSelector->setLayoutDirection(Qt::LeftToRight);
        amountSelector->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        amountSelector->setDecimals(10);
        amountSelector->setMaximum(100.000000000000000);
        amountSelector->setValue(0.000000000000000);

        amountView->addWidget(amountSelector);


        verticalLayout_8->addLayout(amountView);

        feeView = new QHBoxLayout();
        feeView->setObjectName(QString::fromUtf8("feeView"));
        feeLabel = new QLabel(selectors);
        feeLabel->setObjectName(QString::fromUtf8("feeLabel"));
        sizePolicy11.setHeightForWidth(feeLabel->sizePolicy().hasHeightForWidth());
        feeLabel->setSizePolicy(sizePolicy11);

        feeView->addWidget(feeLabel);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        feeView->addItem(horizontalSpacer_16);

        feeSelector = new QDoubleSpinBox(selectors);
        feeSelector->setObjectName(QString::fromUtf8("feeSelector"));
        sizePolicy11.setHeightForWidth(feeSelector->sizePolicy().hasHeightForWidth());
        feeSelector->setSizePolicy(sizePolicy11);
        feeSelector->setMaximumSize(QSize(16777215, 30));
        feeSelector->setDecimals(5);
        feeSelector->setMaximum(2.000000000000000);
        feeSelector->setSingleStep(0.000010000000000);

        feeView->addWidget(feeSelector);


        verticalLayout_8->addLayout(feeView);

        totalView = new QHBoxLayout();
        totalView->setObjectName(QString::fromUtf8("totalView"));
        totalLabel = new QLabel(selectors);
        totalLabel->setObjectName(QString::fromUtf8("totalLabel"));
        sizePolicy11.setHeightForWidth(totalLabel->sizePolicy().hasHeightForWidth());
        totalLabel->setSizePolicy(sizePolicy11);

        totalView->addWidget(totalLabel);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        totalView->addItem(horizontalSpacer_17);

        total = new QLineEdit(selectors);
        total->setObjectName(QString::fromUtf8("total"));
        sizePolicy11.setHeightForWidth(total->sizePolicy().hasHeightForWidth());
        total->setSizePolicy(sizePolicy11);
        total->setMaximumSize(QSize(16777215, 30));
        total->setReadOnly(true);

        totalView->addWidget(total);


        verticalLayout_8->addLayout(totalView);


        selectionLayout->addWidget(selectors);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        selectionLayout->addItem(horizontalSpacer_14);

        btndiag_send = new QDialogButtonBox(makeTransactions);
        btndiag_send->setObjectName(QString::fromUtf8("btndiag_send"));
        QSizePolicy sizePolicy12(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy12.setHorizontalStretch(0);
        sizePolicy12.setVerticalStretch(0);
        sizePolicy12.setHeightForWidth(btndiag_send->sizePolicy().hasHeightForWidth());
        btndiag_send->setSizePolicy(sizePolicy12);
        btndiag_send->setOrientation(Qt::Vertical);
        btndiag_send->setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Reset);

        selectionLayout->addWidget(btndiag_send);


        verticalLayout_10->addLayout(selectionLayout);

        spacerLayout1 = new QVBoxLayout();
        spacerLayout1->setObjectName(QString::fromUtf8("spacerLayout1"));
        spacerLayout1->setContentsMargins(-1, -1, -1, 0);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        spacerLayout1->addItem(verticalSpacer_3);

        verticalSpacer_2 = new QSpacerItem(40, 525, QSizePolicy::Minimum, QSizePolicy::Preferred);

        spacerLayout1->addItem(verticalSpacer_2);


        verticalLayout_10->addLayout(spacerLayout1);


        horizontalLayout_9->addWidget(makeTransactions);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_18);

        trxnLogView = new QWidget(Transactions);
        trxnLogView->setObjectName(QString::fromUtf8("trxnLogView"));
        sizePolicy.setHeightForWidth(trxnLogView->sizePolicy().hasHeightForWidth());
        trxnLogView->setSizePolicy(sizePolicy);
        verticalLayout_6 = new QVBoxLayout(trxnLogView);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        trxnsHeading2 = new QLabel(trxnLogView);
        trxnsHeading2->setObjectName(QString::fromUtf8("trxnsHeading2"));

        verticalLayout_6->addWidget(trxnsHeading2);

        transactionLog = new QListWidget(trxnLogView);
        transactionLog->setObjectName(QString::fromUtf8("transactionLog"));

        verticalLayout_6->addWidget(transactionLog);


        horizontalLayout_9->addWidget(trxnLogView);

        tabWidget->addTab(Transactions, QString());
        Account = new QWidget();
        Account->setObjectName(QString::fromUtf8("Account"));
        horizontalLayout_16 = new QHBoxLayout(Account);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        accountView = new QStackedWidget(Account);
        accountView->setObjectName(QString::fromUtf8("accountView"));
        signIn = new QWidget();
        signIn->setObjectName(QString::fromUtf8("signIn"));
        horizontalLayout_17 = new QHBoxLayout(signIn);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_20);

        widget_8 = new QWidget(signIn);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        verticalLayout_18 = new QVBoxLayout(widget_8);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_18->addItem(verticalSpacer_6);

        signInTitle = new QLabel(widget_8);
        signInTitle->setObjectName(QString::fromUtf8("signInTitle"));

        verticalLayout_18->addWidget(signInTitle);

        verticalSpacer_8 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_18->addItem(verticalSpacer_8);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(-1, 0, -1, 0);
        s_EmailField = new QLineEdit(widget_8);
        s_EmailField->setObjectName(QString::fromUtf8("s_EmailField"));
        QSizePolicy sizePolicy13(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy13.setHorizontalStretch(0);
        sizePolicy13.setVerticalStretch(0);
        sizePolicy13.setHeightForWidth(s_EmailField->sizePolicy().hasHeightForWidth());
        s_EmailField->setSizePolicy(sizePolicy13);
        s_EmailField->setMaximumSize(QSize(16777215, 35));
        s_EmailField->setClearButtonEnabled(true);

        verticalLayout_17->addWidget(s_EmailField);

        s_PasswordField = new QLineEdit(widget_8);
        s_PasswordField->setObjectName(QString::fromUtf8("s_PasswordField"));
        sizePolicy9.setHeightForWidth(s_PasswordField->sizePolicy().hasHeightForWidth());
        s_PasswordField->setSizePolicy(sizePolicy9);
        s_PasswordField->setMaximumSize(QSize(16777215, 35));
        s_PasswordField->setEchoMode(QLineEdit::Password);
        s_PasswordField->setClearButtonEnabled(true);

        verticalLayout_17->addWidget(s_PasswordField);

        verticalSpacer_7 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_17->addItem(verticalSpacer_7);

        btn_signIn = new QPushButton(widget_8);
        btn_signIn->setObjectName(QString::fromUtf8("btn_signIn"));
        sizePolicy12.setHeightForWidth(btn_signIn->sizePolicy().hasHeightForWidth());
        btn_signIn->setSizePolicy(sizePolicy12);

        verticalLayout_17->addWidget(btn_signIn);

        btn_create = new QPushButton(widget_8);
        btn_create->setObjectName(QString::fromUtf8("btn_create"));
        sizePolicy12.setHeightForWidth(btn_create->sizePolicy().hasHeightForWidth());
        btn_create->setSizePolicy(sizePolicy12);

        verticalLayout_17->addWidget(btn_create);


        verticalLayout_18->addLayout(verticalLayout_17);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_18->addItem(verticalSpacer_5);


        horizontalLayout_17->addWidget(widget_8);

        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_21);

        widget_9 = new QWidget(signIn);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        verticalLayout_20 = new QVBoxLayout(widget_9);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        banner1 = new QWidget(widget_9);
        banner1->setObjectName(QString::fromUtf8("banner1"));
        banner1->setStyleSheet(QString::fromUtf8("background-color: rgb(115, 233, 255);\n"
"border: 4px solid rgb(115, 233, 255);\n"
"border-radius: 4px"));
        verticalLayout_21 = new QVBoxLayout(banner1);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        bannerText1 = new QLabel(banner1);
        bannerText1->setObjectName(QString::fromUtf8("bannerText1"));
        bannerText1->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_21->addWidget(bannerText1);


        verticalLayout_20->addWidget(banner1);


        horizontalLayout_17->addWidget(widget_9);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_22);

        accountView->addWidget(signIn);
        signUp = new QWidget();
        signUp->setObjectName(QString::fromUtf8("signUp"));
        horizontalLayout_18 = new QHBoxLayout(signUp);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_23);

        widget_10 = new QWidget(signUp);
        widget_10->setObjectName(QString::fromUtf8("widget_10"));
        verticalLayout_13 = new QVBoxLayout(widget_10);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_11);

        createTitle = new QLabel(widget_10);
        createTitle->setObjectName(QString::fromUtf8("createTitle"));

        verticalLayout_13->addWidget(createTitle);

        verticalSpacer_10 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_13->addItem(verticalSpacer_10);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        c_EmailField = new QLineEdit(widget_10);
        c_EmailField->setObjectName(QString::fromUtf8("c_EmailField"));
        sizePolicy9.setHeightForWidth(c_EmailField->sizePolicy().hasHeightForWidth());
        c_EmailField->setSizePolicy(sizePolicy9);
        c_EmailField->setMaximumSize(QSize(16777215, 35));
        c_EmailField->setClearButtonEnabled(true);

        verticalLayout_12->addWidget(c_EmailField);

        c_UsernameField = new QLineEdit(widget_10);
        c_UsernameField->setObjectName(QString::fromUtf8("c_UsernameField"));
        sizePolicy9.setHeightForWidth(c_UsernameField->sizePolicy().hasHeightForWidth());
        c_UsernameField->setSizePolicy(sizePolicy9);
        c_UsernameField->setMaximumSize(QSize(16777215, 35));
        c_UsernameField->setClearButtonEnabled(true);

        verticalLayout_12->addWidget(c_UsernameField);

        c_PasswordField = new QLineEdit(widget_10);
        c_PasswordField->setObjectName(QString::fromUtf8("c_PasswordField"));
        sizePolicy9.setHeightForWidth(c_PasswordField->sizePolicy().hasHeightForWidth());
        c_PasswordField->setSizePolicy(sizePolicy9);
        c_PasswordField->setMaximumSize(QSize(16777215, 35));
        c_PasswordField->setEchoMode(QLineEdit::Password);
        c_PasswordField->setClearButtonEnabled(true);

        verticalLayout_12->addWidget(c_PasswordField);

        verticalSpacer_9 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_12->addItem(verticalSpacer_9);

        btn_signUp = new QPushButton(widget_10);
        btn_signUp->setObjectName(QString::fromUtf8("btn_signUp"));
        sizePolicy12.setHeightForWidth(btn_signUp->sizePolicy().hasHeightForWidth());
        btn_signUp->setSizePolicy(sizePolicy12);

        verticalLayout_12->addWidget(btn_signUp);

        btn_back = new QPushButton(widget_10);
        btn_back->setObjectName(QString::fromUtf8("btn_back"));
        sizePolicy12.setHeightForWidth(btn_back->sizePolicy().hasHeightForWidth());
        btn_back->setSizePolicy(sizePolicy12);

        verticalLayout_12->addWidget(btn_back);


        verticalLayout_13->addLayout(verticalLayout_12);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_12);


        horizontalLayout_18->addWidget(widget_10);

        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_25);

        widget_11 = new QWidget(signUp);
        widget_11->setObjectName(QString::fromUtf8("widget_11"));
        verticalLayout_16 = new QVBoxLayout(widget_11);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        banner2 = new QWidget(widget_11);
        banner2->setObjectName(QString::fromUtf8("banner2"));
        banner2->setStyleSheet(QString::fromUtf8("background-color: rgb(115, 233, 255);\n"
"border: 4px solid rgb(115, 233, 255);\n"
"border-radius: 4px"));
        verticalLayout_15 = new QVBoxLayout(banner2);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        bannerText2 = new QLabel(banner2);
        bannerText2->setObjectName(QString::fromUtf8("bannerText2"));
        bannerText2->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_15->addWidget(bannerText2);


        verticalLayout_16->addWidget(banner2);


        horizontalLayout_18->addWidget(widget_11);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_24);

        accountView->addWidget(signUp);
        loggedIn = new QWidget();
        loggedIn->setObjectName(QString::fromUtf8("loggedIn"));
        horizontalLayout_15 = new QHBoxLayout(loggedIn);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        pageContainer = new QVBoxLayout();
        pageContainer->setObjectName(QString::fromUtf8("pageContainer"));
        scrollArea = new QScrollArea(loggedIn);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setEnabled(true);
        sizePolicy3.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy3);
        scrollArea->setMinimumSize(QSize(0, 0));
        scrollArea->setStyleSheet(QString::fromUtf8("QScrollArea { background: transparent; }\n"
"QScrollArea > QWidget > QWidget { background: transparent; }\n"
"QScrollArea > QWidget > QScrollBar { background: palette(base); }"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setFrameShadow(QFrame::Plain);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        scrollAreaContent = new QWidget();
        scrollAreaContent->setObjectName(QString::fromUtf8("scrollAreaContent"));
        scrollAreaContent->setEnabled(true);
        scrollAreaContent->setGeometry(QRect(0, 0, 1253, 856));
        QSizePolicy sizePolicy14(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy14.setHorizontalStretch(0);
        sizePolicy14.setVerticalStretch(0);
        sizePolicy14.setHeightForWidth(scrollAreaContent->sizePolicy().hasHeightForWidth());
        scrollAreaContent->setSizePolicy(sizePolicy14);
        scrollAreaContent->setMinimumSize(QSize(550, 550));
        scrollAreaContent->setAutoFillBackground(false);
        horizontalLayout_22 = new QHBoxLayout(scrollAreaContent);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        horizontalSpacer_26 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_26);

        contentContainer = new QWidget(scrollAreaContent);
        contentContainer->setObjectName(QString::fromUtf8("contentContainer"));
        sizePolicy14.setHeightForWidth(contentContainer->sizePolicy().hasHeightForWidth());
        contentContainer->setSizePolicy(sizePolicy14);
        pageLayout = new QVBoxLayout(contentContainer);
        pageLayout->setObjectName(QString::fromUtf8("pageLayout"));
        pageLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        address = new QWidget(contentContainer);
        address->setObjectName(QString::fromUtf8("address"));
        address->setEnabled(true);
        verticalLayout_22 = new QVBoxLayout(address);
        verticalLayout_22->setObjectName(QString::fromUtf8("verticalLayout_22"));
        addressTitle = new QLabel(address);
        addressTitle->setObjectName(QString::fromUtf8("addressTitle"));
        sizePolicy12.setHeightForWidth(addressTitle->sizePolicy().hasHeightForWidth());
        addressTitle->setSizePolicy(sizePolicy12);

        verticalLayout_22->addWidget(addressTitle);

        addressSubtitle = new QLabel(address);
        addressSubtitle->setObjectName(QString::fromUtf8("addressSubtitle"));
        sizePolicy12.setHeightForWidth(addressSubtitle->sizePolicy().hasHeightForWidth());
        addressSubtitle->setSizePolicy(sizePolicy12);

        verticalLayout_22->addWidget(addressSubtitle);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        walletAddress = new QLineEdit(address);
        walletAddress->setObjectName(QString::fromUtf8("walletAddress"));
        sizePolicy12.setHeightForWidth(walletAddress->sizePolicy().hasHeightForWidth());
        walletAddress->setSizePolicy(sizePolicy12);
        walletAddress->setMaximumSize(QSize(16777215, 30));
        walletAddress->setReadOnly(true);

        horizontalLayout_19->addWidget(walletAddress);

        addressCopy = new QToolButton(address);
        addressCopy->setObjectName(QString::fromUtf8("addressCopy"));
        sizePolicy2.setHeightForWidth(addressCopy->sizePolicy().hasHeightForWidth());
        addressCopy->setSizePolicy(sizePolicy2);
        addressCopy->setMaximumSize(QSize(34, 34));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../../../../../../../../../../../../../../../../../../../../../../.designer/assets/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        addressCopy->setIcon(icon4);

        horizontalLayout_19->addWidget(addressCopy);


        verticalLayout_22->addLayout(horizontalLayout_19);


        pageLayout->addWidget(address);

        rsaKeys = new QWidget(contentContainer);
        rsaKeys->setObjectName(QString::fromUtf8("rsaKeys"));
        rsaKeys->setMinimumSize(QSize(0, 0));
        verticalLayout_19 = new QVBoxLayout(rsaKeys);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        rsaTitle = new QLabel(rsaKeys);
        rsaTitle->setObjectName(QString::fromUtf8("rsaTitle"));
        sizePolicy12.setHeightForWidth(rsaTitle->sizePolicy().hasHeightForWidth());
        rsaTitle->setSizePolicy(sizePolicy12);

        verticalLayout_19->addWidget(rsaTitle);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        publicKey = new QLineEdit(rsaKeys);
        publicKey->setObjectName(QString::fromUtf8("publicKey"));
        sizePolicy12.setHeightForWidth(publicKey->sizePolicy().hasHeightForWidth());
        publicKey->setSizePolicy(sizePolicy12);
        publicKey->setMaximumSize(QSize(16777215, 30));
        publicKey->setReadOnly(true);

        horizontalLayout_20->addWidget(publicKey);

        pubKeyShow = new QToolButton(rsaKeys);
        pubKeyShow->setObjectName(QString::fromUtf8("pubKeyShow"));
        sizePolicy2.setHeightForWidth(pubKeyShow->sizePolicy().hasHeightForWidth());
        pubKeyShow->setSizePolicy(sizePolicy2);
        pubKeyShow->setMaximumSize(QSize(34, 34));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("../../../../../../../../../../../../../../../../../../../../../../.designer/assets/no-view.png"), QSize(), QIcon::Normal, QIcon::Off);
        pubKeyShow->setIcon(icon5);

        horizontalLayout_20->addWidget(pubKeyShow);

        pubKeyCopy = new QToolButton(rsaKeys);
        pubKeyCopy->setObjectName(QString::fromUtf8("pubKeyCopy"));
        sizePolicy2.setHeightForWidth(pubKeyCopy->sizePolicy().hasHeightForWidth());
        pubKeyCopy->setSizePolicy(sizePolicy2);
        pubKeyCopy->setMaximumSize(QSize(34, 34));
        pubKeyCopy->setIcon(icon4);

        horizontalLayout_20->addWidget(pubKeyCopy);


        verticalLayout_19->addLayout(horizontalLayout_20);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        privateKey = new QLineEdit(rsaKeys);
        privateKey->setObjectName(QString::fromUtf8("privateKey"));
        sizePolicy12.setHeightForWidth(privateKey->sizePolicy().hasHeightForWidth());
        privateKey->setSizePolicy(sizePolicy12);
        privateKey->setMaximumSize(QSize(16777215, 30));
        privateKey->setReadOnly(true);

        horizontalLayout_21->addWidget(privateKey);

        privKeyShow = new QToolButton(rsaKeys);
        privKeyShow->setObjectName(QString::fromUtf8("privKeyShow"));
        sizePolicy2.setHeightForWidth(privKeyShow->sizePolicy().hasHeightForWidth());
        privKeyShow->setSizePolicy(sizePolicy2);
        privKeyShow->setMaximumSize(QSize(34, 34));
        privKeyShow->setIcon(icon5);

        horizontalLayout_21->addWidget(privKeyShow);

        privKeyCopy = new QToolButton(rsaKeys);
        privKeyCopy->setObjectName(QString::fromUtf8("privKeyCopy"));
        sizePolicy2.setHeightForWidth(privKeyCopy->sizePolicy().hasHeightForWidth());
        privKeyCopy->setSizePolicy(sizePolicy2);
        privKeyCopy->setMaximumSize(QSize(34, 34));
        privKeyCopy->setIcon(icon4);

        horizontalLayout_21->addWidget(privKeyCopy);


        verticalLayout_19->addLayout(horizontalLayout_21);


        pageLayout->addWidget(rsaKeys);

        pubIPAddr = new QWidget(contentContainer);
        pubIPAddr->setObjectName(QString::fromUtf8("pubIPAddr"));
        verticalLayout_24 = new QVBoxLayout(pubIPAddr);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        pubIPAddrTitle = new QLabel(pubIPAddr);
        pubIPAddrTitle->setObjectName(QString::fromUtf8("pubIPAddrTitle"));
        sizePolicy12.setHeightForWidth(pubIPAddrTitle->sizePolicy().hasHeightForWidth());
        pubIPAddrTitle->setSizePolicy(sizePolicy12);

        verticalLayout_24->addWidget(pubIPAddrTitle);

        pubIPAddrSubtitle = new QLabel(pubIPAddr);
        pubIPAddrSubtitle->setObjectName(QString::fromUtf8("pubIPAddrSubtitle"));
        sizePolicy12.setHeightForWidth(pubIPAddrSubtitle->sizePolicy().hasHeightForWidth());
        pubIPAddrSubtitle->setSizePolicy(sizePolicy12);

        verticalLayout_24->addWidget(pubIPAddrSubtitle);

        publicIPAddress = new QTextBrowser(pubIPAddr);
        publicIPAddress->setObjectName(QString::fromUtf8("publicIPAddress"));
        QSizePolicy sizePolicy15(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy15.setHorizontalStretch(0);
        sizePolicy15.setVerticalStretch(0);
        sizePolicy15.setHeightForWidth(publicIPAddress->sizePolicy().hasHeightForWidth());
        publicIPAddress->setSizePolicy(sizePolicy15);
        publicIPAddress->setMaximumSize(QSize(16777215, 30));

        verticalLayout_24->addWidget(publicIPAddress);


        pageLayout->addWidget(pubIPAddr);


        horizontalLayout_22->addWidget(contentContainer);

        horizontalSpacer_27 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_27);

        scrollArea->setWidget(scrollAreaContent);

        pageContainer->addWidget(scrollArea);


        horizontalLayout_15->addLayout(pageContainer);

        accountView->addWidget(loggedIn);

        horizontalLayout_16->addWidget(accountView);

        tabWidget->addTab(Account, QString());
        Settings = new QWidget();
        Settings->setObjectName(QString::fromUtf8("Settings"));
        verticalLayout_28 = new QVBoxLayout(Settings);
        verticalLayout_28->setObjectName(QString::fromUtf8("verticalLayout_28"));
        settingsTitle = new QLabel(Settings);
        settingsTitle->setObjectName(QString::fromUtf8("settingsTitle"));

        verticalLayout_28->addWidget(settingsTitle);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        rsaKeyPath = new QWidget(Settings);
        rsaKeyPath->setObjectName(QString::fromUtf8("rsaKeyPath"));
        verticalLayout_25 = new QVBoxLayout(rsaKeyPath);
        verticalLayout_25->setObjectName(QString::fromUtf8("verticalLayout_25"));
        rsaKeyTitle = new QLabel(rsaKeyPath);
        rsaKeyTitle->setObjectName(QString::fromUtf8("rsaKeyTitle"));

        verticalLayout_25->addWidget(rsaKeyTitle);

        rsaKeySubtitle = new QLabel(rsaKeyPath);
        rsaKeySubtitle->setObjectName(QString::fromUtf8("rsaKeySubtitle"));

        verticalLayout_25->addWidget(rsaKeySubtitle);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        rsaKeyView = new QTextBrowser(rsaKeyPath);
        rsaKeyView->setObjectName(QString::fromUtf8("rsaKeyView"));
        sizePolicy12.setHeightForWidth(rsaKeyView->sizePolicy().hasHeightForWidth());
        rsaKeyView->setSizePolicy(sizePolicy12);
        rsaKeyView->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_23->addWidget(rsaKeyView);

        btn_choosePath = new QPushButton(rsaKeyPath);
        btn_choosePath->setObjectName(QString::fromUtf8("btn_choosePath"));
        sizePolicy12.setHeightForWidth(btn_choosePath->sizePolicy().hasHeightForWidth());
        btn_choosePath->setSizePolicy(sizePolicy12);
        btn_choosePath->setMaximumSize(QSize(16777215, 32));

        horizontalLayout_23->addWidget(btn_choosePath);

        btn_reset = new QToolButton(rsaKeyPath);
        btn_reset->setObjectName(QString::fromUtf8("btn_reset"));
        sizePolicy11.setHeightForWidth(btn_reset->sizePolicy().hasHeightForWidth());
        btn_reset->setSizePolicy(sizePolicy11);
        btn_reset->setMaximumSize(QSize(34, 34));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("../../../../../../../../../../../../../../../../../../.designer/assets/reset.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_reset->setIcon(icon6);

        horizontalLayout_23->addWidget(btn_reset);


        verticalLayout_25->addLayout(horizontalLayout_23);

        verticalSpacer_13 = new QSpacerItem(20, 700, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_25->addItem(verticalSpacer_13);


        gridLayout_2->addWidget(rsaKeyPath, 0, 2, 1, 1);

        changePassword = new QWidget(Settings);
        changePassword->setObjectName(QString::fromUtf8("changePassword"));
        verticalLayout_27 = new QVBoxLayout(changePassword);
        verticalLayout_27->setObjectName(QString::fromUtf8("verticalLayout_27"));
        chgPsswdTitle = new QLabel(changePassword);
        chgPsswdTitle->setObjectName(QString::fromUtf8("chgPsswdTitle"));
        sizePolicy12.setHeightForWidth(chgPsswdTitle->sizePolicy().hasHeightForWidth());
        chgPsswdTitle->setSizePolicy(sizePolicy12);

        verticalLayout_27->addWidget(chgPsswdTitle);

        chgPsswdSubtitle = new QLabel(changePassword);
        chgPsswdSubtitle->setObjectName(QString::fromUtf8("chgPsswdSubtitle"));
        sizePolicy12.setHeightForWidth(chgPsswdSubtitle->sizePolicy().hasHeightForWidth());
        chgPsswdSubtitle->setSizePolicy(sizePolicy12);

        verticalLayout_27->addWidget(chgPsswdSubtitle);

        verticalLayout_26 = new QVBoxLayout();
        verticalLayout_26->setObjectName(QString::fromUtf8("verticalLayout_26"));
        currPassField = new QLineEdit(changePassword);
        currPassField->setObjectName(QString::fromUtf8("currPassField"));
        sizePolicy12.setHeightForWidth(currPassField->sizePolicy().hasHeightForWidth());
        currPassField->setSizePolicy(sizePolicy12);
        currPassField->setMaximumSize(QSize(16777215, 30));
        currPassField->setEchoMode(QLineEdit::Password);
        currPassField->setClearButtonEnabled(true);

        verticalLayout_26->addWidget(currPassField);

        newPassField = new QLineEdit(changePassword);
        newPassField->setObjectName(QString::fromUtf8("newPassField"));
        sizePolicy12.setHeightForWidth(newPassField->sizePolicy().hasHeightForWidth());
        newPassField->setSizePolicy(sizePolicy12);
        newPassField->setMaximumSize(QSize(16777215, 30));
        newPassField->setEchoMode(QLineEdit::Password);
        newPassField->setClearButtonEnabled(true);

        verticalLayout_26->addWidget(newPassField);

        btn_confirm = new QPushButton(changePassword);
        btn_confirm->setObjectName(QString::fromUtf8("btn_confirm"));
        sizePolicy12.setHeightForWidth(btn_confirm->sizePolicy().hasHeightForWidth());
        btn_confirm->setSizePolicy(sizePolicy12);

        verticalLayout_26->addWidget(btn_confirm);

        verticalSpacer_14 = new QSpacerItem(20, 600, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_26->addItem(verticalSpacer_14);


        verticalLayout_27->addLayout(verticalLayout_26);


        gridLayout_2->addWidget(changePassword, 0, 1, 1, 1);

        horizontalSpacer_28 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_28, 0, 3, 1, 1);

        horizontalSpacer_29 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_29, 0, 0, 1, 1);


        verticalLayout_28->addLayout(gridLayout_2);

        tabWidget->addTab(Settings, QString());

        horizontalLayout_24->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(4);
        accountView->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Plasmacoin Client", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Wallet), QCoreApplication::translate("MainWindow", "Wallet", nullptr));
        plusSign->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        minusSign->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        btn_mine->setText(QCoreApplication::translate("MainWindow", "Mine", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Mine), QCoreApplication::translate("MainWindow", "Mine Coins", nullptr));
        QTableWidgetItem *___qtablewidgetitem = contactsList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = contactsList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Address", nullptr));
        btn_addContact->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        btn_filler->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        contactImage->setText(QString());
        addrBookSub1->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Username</span></p></body></html>", nullptr));
        addrBookSub2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Address</span></p></body></html>", nullptr));
        addrBookSub3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Birthday</span></p></body></html>", nullptr));
        birthday->setDisplayFormat(QCoreApplication::translate("MainWindow", "M/d/yyyy", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(AddressBookTab), QCoreApplication::translate("MainWindow", "Address Book", nullptr));
        trxnsHeading1->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">Contacts</span></p></body></html>", nullptr));
        trxnsHeading1_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">Make Transactions</span></p></body></html>", nullptr));
        selectedContact->setText(QString());
        charCount->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"right\"><span style=\" font-size:8pt;\">0/200</span></p></body></html>", nullptr));
        amountLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"right\">Amount</p></body></html>", nullptr));
        feeLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"right\">Fee</p></body></html>", nullptr));
        totalLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"right\">Total</p></body></html>", nullptr));
        trxnsHeading2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">Transaction Log</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Transactions), QCoreApplication::translate("MainWindow", "Transactions", nullptr));
        signInTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt;\">Sign in to your Plasmacoin Account</span></p></body></html>", nullptr));
        s_EmailField->setPlaceholderText(QCoreApplication::translate("MainWindow", "Email Address", nullptr));
        s_PasswordField->setPlaceholderText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        btn_signIn->setText(QCoreApplication::translate("MainWindow", "Sign In", nullptr));
        btn_create->setText(QCoreApplication::translate("MainWindow", "Create...", nullptr));
        bannerText1->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; color:#000000;\">Welcome Back!</span></p><p align=\"center\"><span style=\" font-size:24pt; color:#000000;\">Please sign in to continue.</span><span style=\" color:#000000;\"><br/></span></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/><br/></p><p align=\"center\"><img src=\":/assets/plasmacoin-banner.png\" width=\"550\" height=\"150\"/></p></body></html>", nullptr));
        createTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt;\">Create your Plasmacoin account</span></p></body></html>", nullptr));
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
        btn_signUp->setText(QCoreApplication::translate("MainWindow", "Sign Up", nullptr));
        btn_back->setText(QCoreApplication::translate("MainWindow", "Go Back...", nullptr));
        bannerText2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\">What is my account for?</span></p><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\">Your Plasmacoin account registers you for the desktop app.<br/>This registers your computer as a Plasmacoin node and also<br/>gives you access to the offical Plasmacoin software wallet.</span></p><p align=\"center\"><span style=\" color:#000000;\"><br/></span></p><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\">Credentials</span></p><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\">Once you 're signed in, you'll have access to your public and<br/>private keys, as well as your Plasmacoin address, which is what<br/>you'll use to send and recieve transactions.</span></p><p align=\"center\"><span style=\" color:#000000;\"><br/></span></p><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\">Address Book</span></p><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\""
                        ">With your account, you can access the built-in address book,<br/>which allows you to save the addresses of other Plasmacoin<br/>users.</span></p><p align=\"center\"><br/></p><p align=\"center\"><img src=\":/newPrefix/plasmacoin-banner.png\" width=\"550\" height=\"150\"/></p></body></html>", nullptr));
        addressTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">Your Wallet Address</span></p></body></html>", nullptr));
        addressSubtitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">Your Plasmacoin address identifies your node as the sender or reciever<br/>in a transaction. It is also the way Plasmacoin is sent to your node.</span></p></body></html>", nullptr));
        addressCopy->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        rsaTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">RSA Keys</span></p></body></html>", nullptr));
        pubKeyShow->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        pubKeyCopy->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        privKeyShow->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        privKeyCopy->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        pubIPAddrTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">Public IP Address</span></p></body></html>", nullptr));
        pubIPAddrSubtitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">Your public IP address is what is used to send your Plasmacoin to once<br>the block with your transaction(s) is confirmed to the blockchain. Your<br>IP address is neither stored on the blockchain nor directly traceable from<br>a transaction</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Account), QCoreApplication::translate("MainWindow", "Account", nullptr));
        settingsTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt;\">Settings</span></p></body></html>", nullptr));
        rsaKeyTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; text-decoration: underline;\">RSA Key Path</span></p></body></html>", nullptr));
        rsaKeySubtitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Choose the path where your RSA public-private key pair will be stored.</p></body></html>", nullptr));
        btn_choosePath->setText(QCoreApplication::translate("MainWindow", "Choose Path...", nullptr));
        btn_reset->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        chgPsswdTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; text-decoration: underline;\">Change Password</span></p></body></html>", nullptr));
        chgPsswdSubtitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Change the password for your Plasmacoin Account. Remember that your password<br/>must be at least 6 characters long and contain at least 1 capital letter, 1 special character,<br/>and 1 number.</p></body></html>", nullptr));
        currPassField->setInputMask(QString());
        currPassField->setPlaceholderText(QCoreApplication::translate("MainWindow", "Current Password", nullptr));
        newPassField->setInputMask(QString());
        newPassField->setPlaceholderText(QCoreApplication::translate("MainWindow", "New Password", nullptr));
        btn_confirm->setText(QCoreApplication::translate("MainWindow", "Confirm", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Settings), QCoreApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
