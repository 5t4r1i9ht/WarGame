QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# 2205768945665
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Chessman.cpp \
    Coordinate.cpp \
    Main.cpp \
    MyButton.cpp \
    Square.cpp \
    WarGameWidget.cpp \
    widget.cpp

HEADERS += \
    Chessman.h \
    Coordinate.h \
    MyButton.h \
    Square.h \
    WarGameWidget.h \
    widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
