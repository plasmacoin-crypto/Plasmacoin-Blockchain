QT += core gui network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../transaction.cpp ../../node.cpp ../../block.cpp \
    ../../blockchain.cpp ../../receipt.cpp ../../rsa-fs.cpp \
    ../../dat-fs.cpp ../../transmitter.cpp ../../transmitter.tpp ../../shared-mem.cpp \
    ../../parse-json.cpp ../../validation.cpp ../../hashing.cpp ../../dssize.cpp \
    ../../utility.cpp ../../rsautil.cpp \
    \
    main.cpp mainwindow.cpp \
    transaction-list.cpp  mining-status.cpp \
    recipient-list.cpp firebase-auth.cpp \
    account-pages.cpp mining-dialog.cpp \
    transaction-manager.cpp connections.cpp \
    #\
    #../../../netdial/netdial.go ../../../netlisten/netlisten.go \
    #../../../netutils/compression.go ../../../netutils/netutils.go ../../../netutils/parser.go \
    #../../../handler/handler.go ../../../daemon/pcnetworkd.go ../../../daemon/pcnetworkd.h \
    #../../../daemon/daemon.cpp

HEADERS += \
    ../../transaction.hpp ../../node.hpp ../../block.hpp \
    ../../blockchain.hpp ../../receipt.hpp ../../merkle-helpers.h ../../rsa-fs.hpp \
    ../../dat-fs.hpp ../../transmitter.hpp ../../transmitter.tpp ../../shared-mem.hpp \
    ../../parse-json.hpp ../../validation.hpp ../../hashing.hpp ../../dssize.hpp \
    ../../utility.hpp ../../rsautil.hpp ../../sync-request.hpp ../../user-query.hpp \
    ../../signature.hpp \
    \
    mainwindow.h \
    transaction-list.h  mining-status.h \
    recipient-list.h firebase-auth.h \
    account-pages.h mining-dialog.h \
    transaction-manager.h connections.hpp

FORMS += \
    ui/linux.ui \
    ui/macos.ui \
    ui/miningdialog.ui

GOLIBS = -lpcnetworkd
GOFLAGS = -buildmode c-shared

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

INCLUDEPATH = ../../../daemon /usr/lib /usr/local /usr/local/lib/plasmacoin /opt/homebrew/Cellar/boost/1.78.0_1/include
LIBS += $${GOLIBS} -L/usr/lib/pthread -lpthread -L/usr/local/cryptopp -lcryptopp

# Build the network daemon
daemon.target = daemon.o
daemon.commands = $(CXX) -c $(CXXFLAGS) $(INCPATH) -o daemon.o ../../../daemon/daemon.cpp
daemon.depends = ../../../daemon/daemon.cpp

NEWLINE = $$escape_expand(\n\t)

macx {
  libpcnetworkd.target = libpcnetworkd.dylib
  libpcnetworkd.commands = \
    $(MKDIR) ../../../lib /usr/local/lib/plasmacoin $${NEWLINE} \
    $(GO) build $(GOFLAGS) -o ../../../daemon/libpcnetworkd.dylib ../../../daemon/pcnetworkd.go $${NEWLINE} \
    $(MOVE) ../../../daemon/libpcnetworkd.h ../../../daemon/pcnetworkd.h $${NEWLINE} \
    $(MOVE) ../../../daemon/libpcnetworkd.dylib ../../../lib $${NEWLINE} \
    $(INSTALL_FILE) ../../../lib/libpcnetworkd.dylib /usr/local/lib/plasmacoin
  libpcnetworkd.depends = ../../../daemon/pcnetworkd.go

  libplasmacoin.target = libplasmacoin.dylib
  libplasmacoin.commands = \
    $(MKDIR) $(HEADER_DIR) $${NEWLINE} \
    $(CXX) -shared $(BASE_OBJ) -F/opt/homebrew/lib -L/usr/local/cryptopp -L/usr/local/lib/plasmacoin -o ../../../lib/libplasmacoin.dylib -lcryptopp -lpcnetworkd -framework QtCore $${NEWLINE} \
    $(INSTALL_FILE) ../../../lib/libplasmacoin.dylib /usr/local/lib/plasmacoin $${NEWLINE} \
    $${NEWLINE} \
    $(eval STANDALONE_HEADERS = ../../merkle-helpers.h ../../cryptopp-sha256-libs.h ../../../daemon/pcnetworkd.h) $${NEWLINE} \
    $(eval HEADERS := $(filter-out merkle-helpers.o, $${BASE_OBJ})) \
    $(eval HEADERS := $(HEADERS:%o=../../%hpp)) $${NEWLINE} \
    $(eval HEADERS += $(STANDALONE_HEADERS)) $${NEWLINE} \
    $${NEWLINE} \
    $(COPY_FILE) $(HEADERS) $(HEADER_DIR)
  libplasmacoin.depends = $${BASE_OBJ}
}

unix:!macx {
  libpcnetworkd.target = libpcnetworkd.so
  libpcnetworkd.commands = \
    $(MKDIR) ../../../lib /usr/lib/plasmacoin $${NEWLINE} \
    $(GO) build $(GOFLAGS) -o ../../../daemon/libpcnetworkd.so ../../../daemon/pcnetworkd.go $${NEWLINE} \
    $(MOVE) ../../../daemon/libpcnetworkd.h ../../../daemon/pcnetworkd.h $${NEWLINE} \
    $(MOVE) ../../../daemon/libpcnetworkd.so ../../../lib $${NEWLINE} \
    $(INSTALL_FILE) ../../../lib/libpcnetworkd.so /usr/lib/plasmacoin
  libpcnetworkd.depends = ../../../daemon/pcnetworkd.go
}

QMAKE_EXTRA_TARGETS += daemon libpcnetworkd libplasmacoin

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
