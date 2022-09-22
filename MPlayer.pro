QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QMAKE_CXXFLAGS += -lid3v2

QMAKE_CFLAGS += -lid3v2

LIBS += -lid3v2 -ltag

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog.cpp \
    exceptions.cpp \
    main.cpp \
    mainwindow.cpp \
    player.cpp \
    song.cpp

HEADERS += \
    dialog.h \
    exceptions.h \
    mainwindow.h \
    player.h \
    song.h

FORMS += \
    dialog.ui \
    mainwindow.ui

DEFINES += TAGLIB_STATIC
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
