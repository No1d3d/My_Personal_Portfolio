QT       += core gui opengl openglwidgets widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += core gui opengl openglwidgets widgets

TEMPLATE = app

CONFIG += c++17 x86
QMAKE_LFLAGS += -F/usr/local/Cellar/qt/6.6.1/lib/QtCore.framework/Versions/A/QtCore
QMAKE_LFLAGS += -F/usr/local/lib/QtCore.framework/Versions/A/QtCore

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    glview.cpp \
    model.cpp \
    MODEL/3rdParty/giflib/dgif_lib.c \
    MODEL/3rdParty/giflib/egif_lib.c \
    MODEL/3rdParty/giflib/gif_err.c \
    MODEL/3rdParty/giflib/gif_font.c \
    MODEL/3rdParty/giflib/gif_hash.c \
    MODEL/3rdParty/giflib/gifalloc.c \
    MODEL/3rdParty/giflib/quantize.c \
    MODEL/gifimage/doc/snippets/doc_src_qtgifimage.cpp \
    MODEL/gifimage/qgifimage.cpp \
    MODEL/gifimage/tests/test.c \
    ubercontroller.cpp

HEADERS += \
    mainwindow.h \
    model.h \
    glview.h \
    MODEL/3rdParty/giflib/gif_hash.h \
    MODEL/3rdParty/giflib/gif_lib.h \
    MODEL/3rdParty/giflib/gif_lib_private.h \
    MODEL/gifimage/qgifglobal.h \
    MODEL/gifimage/qgifimage.h \
    MODEL/gifimage/qgifimage_p.h \
    ubercontroller.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
