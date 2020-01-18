QT += quick datavisualization widgets
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = $$PWD/../bin
RC_ICONS = resource/octopus.ico

SOURCES += \
	src/main.cpp \
        src/imageprovider.cpp \
        src/paraminterface.cpp \
        src/parammanager.cpp \
        src/treeitem.cpp \
        src/WidgetOSRItem.cpp \
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
    include/singleton.hpp \
    include/treeitem.h \
    include/WidgetOSRItem.h \
    include/globaldata.h \
    include/interaction.h

INCLUDEPATH += include
