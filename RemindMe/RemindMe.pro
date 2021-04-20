QT += core gui \
    multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    sources/eventinfo.cpp \
    sources/eventobject.cpp \
    sources/eventwindow.cpp \
    sources/mainwindow.cpp \
    sources/timeupwindow.cpp

HEADERS += \
    headers/eventinfo.h \
    headers/eventobject.h \
    headers/eventwindow.h \
    headers/mainwindow.h \
    headers/timeupwindow.h

FORMS += \
    forms/eventwindow.ui \
    forms/mainwindow.ui \
    forms/timeupwindow.ui

RESOURCES += \
    resources/resourcefile.qrc \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
