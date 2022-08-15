QT += core gui network concurrent
QT_MAJOR_VERSION = 6
RESOURCES = ../resources.qrc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
PKGCONFIG += libnotify

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	../../transaction.cpp ../../node.cpp ../../block.cpp ../../blockchain.cpp \
	../../receipt.cpp ../../rsa-fs.cpp ../../dat-fs.cpp ../../transmitter.cpp \
	../../shared-mem.cpp ../../parse-json.cpp ../../validation.cpp ../../hashing.cpp \
	../../dssize.cpp ../../utility.cpp ../../utility.tpp ../../rsautil.cpp \
	../../merkle-helpers.cpp ../../mining.cpp ../../notification.cpp ../../upnp.cpp \
	\
	main.cpp mainwindow.cpp transaction-list.cpp  mining-status.cpp recipient-list.cpp \
	firebase-auth.cpp account-pages.cpp mining-dialog.cpp transaction-manager.cpp \
	connections.cpp address-book.cpp contact.cpp transaction-view.cpp block-view.cpp \
	blockchain-viewer.cpp wallet-page.cpp wallet.cpp settings-manager.cpp pc-splash-screen.cpp
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
	../../removal-request.hpp ../../notification.hpp ../../upnp.hpp ../../net-constants.hpp \
	\
	mainwindow.h transaction-list.h  mining-status.h recipient-list.h \
	firebase-auth.h account-pages.h mining-dialog.h transaction-manager.h \
	connections.hpp address-book.h contact.h transaction-view.h block-view.h \
	blockchain-viewer.h wallet-page.h wallet.h ui.h settings-manager.h pc-splash-screen.h

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
	rsautil.o \
  mining.o \
  upnp.o

#
# Compiler flags
#
GOFLAGS = -buildmode c-shared
QMAKE_CXXFLAGS += -g -O0

#
# Include paths
#

unix:!macx:LIBNOTIFY_INCLUDE =	/usr/include/gdk-pixbuf-2.0 /usr/include/glib-2.0 \
								                /usr/lib/glib-2.0/include /usr/include/sysprof-4 \
								                /usr/include/libpng16 /usr/include/libmount /usr/include/blkid
unix:!macx:LIBNOTIFY_LIBS = $$system(pkg-config --libs libnotify)

INCLUDEPATH =	../../ ../../../daemon ../plasmacoin-client \
				/usr/lib /usr/local /usr/local/plasmacoin /usr/src \
				/opt/homebrew/Cellar/boost/1.79.0_1/include \
				$${LIBNOTIFY_INCLUDE}

macx:LIBPLASMACOIN = -L/usr/local/lib/
unix:!macx:LIBPLASMACOIN = -L/usr/lib/plasmacoin

unix:!macx:QTLIBS = /usr/lib/libQt5Widgets.so /usr/lib/libQt5Gui.so /usr/lib/libQt5Network.so /usr/lib/libQt5Concurrent.so /usr/lib/libQt5Core.so

macx:GOLIBS = /usr/local/lib/libplasmacoin.a /usr/local/lib/libpcnetworkd.dylib
unix:!macx:GOLIBS = $${LIBPLASMACOIN} /usr/lib/libplasmacoin.a -lpcnetworkd

macx:DAEMON_LIBS = $${GOLIBS} -pthread
unix:!macx:DAEMON_LIBS = $${GOLIBS} -lplasmacoin -lpthread -L/usr/lib/ -lboost_system $${QTLIBS}

macx:LIBS += -pthread /usr/local/lib/libplasmacoin.a /usr/local/cryptopp/libcryptopp.a /usr/local/lib/libpcnetworkd.dylib
unix:!macx:LIBS += $${GOLIBS} -L/usr/lib -lpthread -L/usr/src/cryptopp -lcryptopp $${LIBNOTIFY_LIBS}

# Build the network daemon object
daemon.target = daemon.o
daemon.commands = $(CXX) -c $(CXXFLAGS) $(INCPATH) -o daemon.o ../../../daemon/daemon.cpp
daemon.depends = ../../../daemon/daemon.cpp

# Build the network daemon executable
pcnetworkd.target = pcnetworkd
pcnetworkd.commands = $(LINK) $(LFLAGS) -o pcnetworkd daemon.o $(OBJCOMP) $${DAEMON_LIBS} $${QTLIBS}
pcnetworkd.depends = daemon.o

NEWLINE = $$escape_expand(\n\t)

# macOS-specific extra targets
macx {
	GO = /opt/homebrew/bin/go
	HEADER_DIR = /usr/local/plasmacoin

	libpcnetworkd.target = libpcnetworkd.dylib
	libpcnetworkd.commands = \
	$(MKDIR) ../../../lib /usr/local/lib/plasmacoin $${NEWLINE} \
	$${GO} build $${GOFLAGS} -o ../../../daemon/libpcnetworkd.dylib ../../../daemon/pcnetworkd.go $${NEWLINE} \
	$(MOVE) ../../../daemon/libpcnetworkd.h ../../../daemon/pcnetworkd.h $${NEWLINE} \
	$(MOVE) ../../../daemon/libpcnetworkd.dylib ../../../lib $${NEWLINE} \
	$(INSTALL_FILE) ../../../lib/libpcnetworkd.dylib /usr/local/lib/
	libpcnetworkd.depends = ../../../daemon/pcnetworkd.go

	libplasmacoin.target = libplasmacoin.a
	libplasmacoin.commands = \
	$(MKDIR) $${HEADER_DIR} $${NEWLINE} \
	$(AR) ../../../lib/libplasmacoin.a $${BASE_OBJ} /usr/local/cryptopp/*.o $${NEWLINE} \
	$(INSTALL_FILE) ../../../lib/libplasmacoin.a /usr/local/lib $${NEWLINE} \
	$${NEWLINE} \
	$(eval STANDALONE_HEADERS = ../../merkle-helpers.h ../../cryptopp-sha256-libs.h ../../../daemon/pcnetworkd.h) $${NEWLINE} \
	$(eval HEADERS := $(filter-out merkle-helpers.o, $${BASE_OBJ})) $${NEWLINE} \
	$(eval HEADERS := $(HEADERS:%o=../../%hpp)) $${NEWLINE} \
	$(eval HEADERS += $(STANDALONE_HEADERS)) $${NEWLINE} \
	$${NEWLINE} \
	$(COPY_FILE) $(HEADERS) $${HEADER_DIR}
	libplasmacoin.depends = $${BASE_OBJ}
}

# Linux-specific extra targets
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

	libplasmacoin.target = libplasmacoin.a
	libplasmacoin.commands = \
		$(MKDIR) $${HEADER_DIR} $${NEWLINE} \
	$(AR) ../../../lib/libplasmacoin.a $${BASE_OBJ} /usr/src/cryptopp/*.o $${NEWLINE} \
	$(INSTALL_FILE) ../../../lib/libplasmacoin.a /usr/lib $${NEWLINE} \
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

macx:PRE_TARGETDEPS += libpcnetworkd.dylib libplasmacoin.a
macx:POST_TARGETDEPS += pcnetworkd

#unix:!macx:PRE_TARGETDEPS += libpcnetworkd.so libplasmacoin.so
unix:!macx:POST_TARGETDEPS += libpcnetworkd.so libplasmacoin.a pcnetworkd

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
