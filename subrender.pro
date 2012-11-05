#-------------------------------------------------
#
# Project created by QtCreator 2012-07-13T19:34:49
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = subrender
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sample.cpp \
    dive.cpp \
    divemanager.cpp \
    divewidget.cpp \
    diverenderworker.cpp \
    diverenderer.cpp \
    settings.cpp \
    positiondialog.cpp \
    diveselectiondialog.cpp \
    rendersettingsdialog.cpp \
    renderprogressdialog.cpp

HEADERS  += mainwindow.h \
    sample.h \
    dive.h \
    divemanager.h \
    divewidget.h \
    diverenderworker.h \
    diverenderer.h \
    settings.h \
    positiondialog.h \
    diveselectiondialog.h \
    rendersettingsdialog.h \
    renderprogressdialog.h

FORMS    += mainwindow.ui \
    positiondialog.ui \
    diveselectiondialog.ui \
    rendersettingsdialog.ui \
    renderprogressdialog.ui

TRANSLATIONS = language/subrender_de_DE.ts \
               language/subrender_en_US.ts

CODECFORTR = UTF-8

unix {
    target.path = /usr/bin
    INSTALLS += target
}

win32 {
    RC_FILE = packaging/windows/subrender.rc
}

RESOURCES += \
    subrender.qrc
