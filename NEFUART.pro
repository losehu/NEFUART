QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


include(src/xlsx/qtxlsx.pri)

SOURCES += \
    MDC.cpp \
    NAME.cpp \
    WELCOME.cpp \
    app.cpp \
    comm.cpp \
    main.cpp \
    mainwindow.cpp \
    uart.cpp

HEADERS += \
    mainwindow.h \


FORMS += \
    mainwindow.ui


CONFIG += lrelease\


#DEFINES += QT_NO_DEBUG_OUTPUT
QT       += serialport
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../build-NEFUART-Desktop_Qt_5_14_2_MinGW_32_bit-Release/release/chinese_map.txt \
    RUBO1-tou.ico \
    icon.rc


RC_FILE +=
icon.rc
RC_ICONS = RUBO1-tou.ico
