QT += core quick widgets
android: QT += androidextras
CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = $$PWD/../bin
RC_ICONS = resource/octopus.ico

SOURCES += \
        src/clocsync.cpp \
        src/cmdsender.cpp \
        src/debugger.cpp \
	src/main.cpp \
        src/imageprovider.cpp \
        src/paraminterface.cpp \
        src/parammanager.cpp \
        src/sensorreceiver.cpp \
        src/treeitem.cpp \
        src/udpinterface.cpp \
        src/globaldata.cpp \
        src/interaction.cpp

RESOURCES += qml.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/imageprovider.h \
    include/paraminterface.h \
    include/parammanager.h \
    include/sensorreceiver.h \
    include/singleton.hpp \
    include/treeitem.h \
    include/globaldata.h \
    include/interaction.h \
    include/viewerinterface.hpp \
    include/debugger.h \
    include/clocsync.h \
    include/cmdsender.h \
    include/udpinterface.h

INCLUDEPATH += include

DISTFILES += \
    android-sources/AndroidManifest.xml \

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

android: DEFINES += ANDROID_PLATFORM
