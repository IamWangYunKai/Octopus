QT += quick
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = $$PWD/../bin
RC_ICONS = octopus.ico

SOURCES += main.cpp \
    imageprovider.cpp

RESOURCES += qml.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    imageprovider.h
