QT       += core gui
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    table.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-qcustomplot-Desktop_Qt_6_4_1_MinGW_64_bit-Debug/release/ -lqcustomplot
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-qcustomplot-Desktop_Qt_6_4_1_MinGW_64_bit-Debug/debug/ -lqcustomplot
else:unix: LIBS += -L$$PWD/../build-qcustomplot-Desktop_Qt_6_4_1_MinGW_64_bit-Debug/ -lqcustomplot

INCLUDEPATH += $$PWD/../qcustomplot
DEPENDPATH += $$PWD/../qcustomplot

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-qcustomplot-Desktop_Qt_6_4_1_MinGW_64_bit-Debug/release/libqcustomplot.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-qcustomplot-Desktop_Qt_6_4_1_MinGW_64_bit-Debug/debug/libqcustomplot.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-qcustomplot-Desktop_Qt_6_4_1_MinGW_64_bit-Debug/release/qcustomplot.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-qcustomplot-Desktop_Qt_6_4_1_MinGW_64_bit-Debug/debug/qcustomplot.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-qcustomplot-Desktop_Qt_6_4_1_MinGW_64_bit-Debug/libqcustomplot.a
