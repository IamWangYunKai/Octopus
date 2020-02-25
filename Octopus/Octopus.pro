QT += core quick widgets opengl datavisualization
CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = $$PWD/../bin
RC_ICONS = resource/octopus.ico

SOURCES += \
        src/clocsync.cpp \
        src/cmdreceiver.cpp \
        src/debugger.cpp \
	src/main.cpp \
        src/imageprovider.cpp \
        src/paraminterface.cpp \
        src/parammanager.cpp \
        src/treeitem.cpp \
        src/udpreceiver.cpp \
        src/widgetosritem.cpp \
        src/globaldata.cpp \
        src/interaction.cpp \
        src/glitem.cpp \
        src/squircle.cpp

RESOURCES += qml.qrc \
             shader.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/imageprovider.h \
    include/paraminterface.h \
    include/parammanager.h \
    include/singleton.hpp \
    include/treeitem.h \
    include/widgetosritem.h \
    include/globaldata.h \
    include/interaction.h \
    include/viewerinterface.hpp \
    include/glitem.h \
    include/udpreceiver.h \
    include/cmdreceiver.h \
    include/debugger.h \
    include/clocsync.h \
    include/squircle.h

INCLUDEPATH += include

DISTFILES += \
    android-sources/AndroidManifest.xml \

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources
