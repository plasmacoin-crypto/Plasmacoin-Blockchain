QT += core gui network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../transaction.cpp ../../node.cpp ../../block.cpp ../../blockchain.cpp \
    ../../receipt.cpp ../../rsa-fs.cpp ../../dat-fs.cpp ../../transmitter.cpp \
    ../../shared-mem.cpp ../../parse-json.cpp ../../validation.cpp ../../hashing.cpp \
    ../../dssize.cpp ../../utility.cpp ../../utility.tpp ../../rsautil.cpp \
    ../../merkle-helpers.cpp ../../mining.cpp \
    \
    main.cpp mainwindow.cpp transaction-list.cpp  mining-status.cpp recipient-list.cpp \
    firebase-auth.cpp account-pages.cpp mining-dialog.cpp transaction-manager.cpp \
    connections.cpp address-book.cpp contact.cpp transaction-view.cpp block-view.cpp \
    blockchain-viewer.cpp wallet-page.cpp wallet.cpp
    #\
    #../../../netdial/netdial.go ../../../netlisten/netlisten.go \
    #../../../netutils/compression.go ../../../netutils/netutils.go ../../../netutils/parser.go \
    #../../../handler/handler.go ../../../daemon/pcnetworkd.go ../../../daemon/pcnetworkd.h \
    #../../../daemon/daemon.cpp

HEADERS += \
    ../../transaction.hpp ../../node.hpp ../../block.hpp ../../blockchain.hpp \
    ../../receipt.hpp ../../merkle-helpers.h ../../rsa-fs.hpp ../../dat-fs.hpp \
    ../../transmitter.hpp ../../shared-mem.hpp ../../parse-json.hpp \
    ../../validation.hpp ../../hashing.hpp ../../dssize.hpp ../../utility.hpp \
    ../../rsautil.hpp ../../sync-request.hpp ../../user-query.hpp ../../signature.hpp \
    ../../merkle-helpers.h ../../idcode.hpp ../../pending-trxn.hpp ../../mining.hpp \
    ../../removal-request.hpp \
    \
    mainwindow.h transaction-list.h  mining-status.h recipient-list.h \
    firebase-auth.h account-pages.h mining-dialog.h transaction-manager.h \
    connections.hpp address-book.h contact.h transaction-view.h block-view.h \
    blockchain-viewer.h wallet-page.h wallet.h ui.h \

FORMS += \
    ui/linux.ui \
    ui/macos.ui \
    ui/miningdialog.ui

BASE_OBJ = \
  transaction.o \
  node.o \
  block.o \
  blockchain.o \
  receipt.o \
  merkle-helpers.o \
  rsa-fs.o \
  dat-fs.o \
  transmitter.o \
  shared-mem.o \
  parse-json.o \
  validation.o \
  hashing.o \
  dssize.o \
  utility.o \
  rsautil.o

INCLUDEPATH = ../../ ../../../daemon ../plasmacoin-client /usr/lib /usr/local /usr/local/plasmacoin /usr/src /usr/local/lib/plasmacoin /opt/homebrew/Cellar/boost/1.78.0_1/include

macx:LIBPLASMACOIN = -L/usr/local/lib/plasmacoin
unix:!macx:LIBPLASMACOIN = -L/usr/lib/plasmacoin

unix:!macx:QTLIBS = /usr/lib/libQt5Widgets.so /usr/lib/libQt5Gui.so /usr/lib/libQt5Network.so /usr/lib/libQt5Concurrent.so /usr/lib/libQt5Core.so

GOLIBS = $${LIBPLASMACOIN} -lpcnetworkd
GOFLAGS = -buildmode c-shared

macx:DAEMON_LIBS = $${GOLIBS} -lplasmacoin -lpthread -L/opt/homebrew/Cellar/boost/1.78.0_1/lib/ -lboost_system
unix:!macx:DAEMON_LIBS = $${GOLIBS} -lplasmacoin -lpthread -L/usr/lib/ -lboost_system $${QTLIBS}

macx:LIBS += $${GOLIBS} -L/usr/lib -lpthread -L/usr/local/cryptopp -lcryptopp
unix:!macx:LIBS += $${GOLIBS} -L/usr/lib -lpthread -L/usr/src/cryptopp -lcryptopp

# Build the network daemon object
daemon.target = daemon.o
daemon.commands = $(CXX) -c $(CXXFLAGS) $(INCPATH) -o daemon.o ../../../daemon/daemon.cpp
daemon.depends = ../../../daemon/daemon.cpp

# Build the network daemon executable
pcnetworkd.target = pcnetworkd
pcnetworkd.commands = $(LINK) $(LFLAGS) -o pcnetworkd daemon.o $(OBJCOMP) $${DAEMON_LIBS} $${QTLIBS}
pcnetworkd.depends = daemon.o

NEWLINE = $$escape_expand(\n\t)

macx {
  GO = /opt/homebrew/bin/go
  HEADER_DIR = /usr/local/plasmacoin

  libpcnetworkd.target = libpcnetworkd.dylib
  libpcnetworkd.commands = \
    $(MKDIR) ../../../lib /usr/local/lib/plasmacoin $${NEWLINE} \
    $${GO} build $${GOFLAGS} -o ../../../daemon/libpcnetworkd.dylib ../../../daemon/pcnetworkd.go $${NEWLINE} \
    $(MOVE) ../../../daemon/libpcnetworkd.h ../../../daemon/pcnetworkd.h $${NEWLINE} \
    $(MOVE) ../../../daemon/libpcnetworkd.dylib ../../../lib $${NEWLINE} \
    $(INSTALL_FILE) ../../../lib/libpcnetworkd.dylib /usr/local/lib/plasmacoin
  libpcnetworkd.depends = ../../../daemon/pcnetworkd.go

  libplasmacoin.target = libplasmacoin.dylib
  libplasmacoin.commands = \
    $(MKDIR) $${HEADER_DIR} $${NEWLINE} \
    $(CXX) -shared $${BASE_OBJ} -F/opt/homebrew/lib -L/usr/local/cryptopp -L/usr/local/lib/plasmacoin -o ../../../lib/libplasmacoin.dylib -lcryptopp -lpcnetworkd -framework QtCore $${NEWLINE} \
    $(INSTALL_FILE) ../../../lib/libplasmacoin.dylib /usr/local/lib/plasmacoin $${NEWLINE} \
    $${NEWLINE} \
    $(eval STANDALONE_HEADERS = ../../merkle-helpers.h ../../cryptopp-sha256-libs.h ../../../daemon/pcnetworkd.h) $${NEWLINE} \
    $(eval HEADERS := $(filter-out merkle-helpers.o, $${BASE_OBJ})) $${NEWLINE} \
    $(eval HEADERS := $(HEADERS:%o=../../%hpp)) $${NEWLINE} \
    $(eval HEADERS += $(STANDALONE_HEADERS)) $${NEWLINE} \
    $${NEWLINE} \
    $(COPY_FILE) $(HEADERS) $${HEADER_DIR}
  libplasmacoin.depends = $${BASE_OBJ}
}

unix:!macx {
  GO = /usr/bin/go
  HEADER_DIR = /usr/include/plasmacoin

  libpcnetworkd.target = libpcnetworkd.so
  libpcnetworkd.commands = \
    $(MKDIR) ../../../lib /usr/lib/plasmacoin $${NEWLINE} \
    $${GO} build $${GOFLAGS} -o ../../../daemon/libpcnetworkd.so ../../../daemon/pcnetworkd.go $${NEWLINE} \
    -$(MOVE) ../../../daemon/libpcnetworkd.h ../../../daemon/pcnetworkd.h $${NEWLINE} \
    -$(MOVE) ../../../daemon/libpcnetworkd.so ../../../lib $${NEWLINE} \
    $(INSTALL_FILE) ../../../lib/libpcnetworkd.so /usr/lib/plasmacoin
  libpcnetworkd.depends = ../../../daemon/pcnetworkd.go

  libplasmacoin.target = libplasmacoin.so
  libplasmacoin.commands = \
	  $(MKDIR) $${HEADER_DIR} $${NEWLINE} \
	  $(CXX) -shared $${BASE_OBJ} -L/usr/src/cryptopp -L/usr/lib/ -L/usr/lib/qt -L/usr/lib/plasmacoin -o ../../../lib/libplasmacoin.so /usr/src/cryptopp/libcryptopp.a /usr/lib/plasmacoin/libpcnetworkd.so /usr/lib/libboost_system.so $(QTLIBS) $${NEWLINE} \
	  $(INSTALL_FILE) ../../../lib/libplasmacoin.so /usr/lib/plasmacoin $${NEWLINE} \
    $${NEWLINE} \
	  $(eval STANDALONE_HEADERS = ../../merkle-helpers.h ../../cryptopp-sha256-libs.h ../../../daemon/pcnetworkd.h) $${NEWLINE} \
	  $(eval HEADERS := $(filter-out merkle-helpers.o, $${BASE_OBJ})) $${NEWLINE} \
	  $(eval HEADERS := $(HEADERS:%o=../../%hpp)) $${NEWLINE} \
	  $(eval HEADERS += $(STANDALONE_HEADERS)) $${NEWLINE} \
    $${NEWLINE} \
	  $(COPY_FILE) $(HEADERS) $${HEADER_DIR}
  libplasmacoin.depends = $${BASE_OBJ}
}

UI_HEADERS = ui_macos.h ui_linux.h ui_miningdialog.h
QMAKE_EXTRA_TARGETS += daemon pcnetworkd libpcnetworkd libplasmacoin

macx:PRE_TARGETDEPS += libpcnetworkd.dylib libplasmacoin.dylib
macx:POST_TARGETDEPS += pcnetworkd

#unix:!macx:PRE_TARGETDEPS += libpcnetworkd.so libplasmacoin.so
unix:!macx:POST_TARGETDEPS += libpcnetworkd.so libplasmacoin.so pcnetworkd

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
