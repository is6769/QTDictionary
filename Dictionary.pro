QT += core gui widgets

TARGET = Dictionary
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    Dictionary.cpp \
    WordDefinition.cpp \
    AddEditDialog.cpp \
    JsonHandler.cpp \
    Settings.cpp \
    SettingsDialog.cpp

HEADERS += \
    MainWindow.h \
    Dictionary.h \
    WordDefinition.h \
    AddEditDialog.h \
    JsonHandler.h \
    Settings.h \
    SettingsDialog.h

FORMS += \
    MainWindow.ui \
    AddEditDialog.ui \
    SettingsDialog.ui

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
