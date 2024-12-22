QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Enable MOC (Meta-Object Compiler) for custom signals/slots
CONFIG += moc

# You can make your code fail to compile if it uses deprecated APIs.
# Uncomment the following line to disable APIs deprecated before Qt 6.0.0
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Source files
SOURCES += \
    main.cpp \
    mainwindow.cpp

# Header files
HEADERS += \
    mainwindow.h

# UI forms
FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
