TEMPLATE = app

QT += datavisualization

target.path = $$[QT_INSTALL_EXAMPLES]/datavisualization/$$TARGET
INSTALLS += target

SOURCES += main.cpp scatterdatamodifier.cpp
HEADERS += scatterdatamodifier.h

QT += widgets
requires(qtConfig(combobox))
requires(qtConfig(fontcombobox))
