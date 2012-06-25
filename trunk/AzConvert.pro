# -------------------------------------------------
# Project created by QtCreator 2009-09-02T13:27:10
# -------------------------------------------------
QT += core gui network sql

TARGET = AzConvert

TEMPLATE = app

TRANSLATIONS = azconvert_en.ts \
    azconvert_fa.ts

SOURCES += main.cpp \
    mainwindow.cpp \
    l2aconversion.cpp \
    c2lconversion.cpp \
    a2lconversion.cpp \
    addworddialog.cpp \
    calendarconverter.cpp \
    calendarswitchdialog.cpp \
    settings.cpp \
    update.cpp \
    dbservice.cpp \
    convertor.cpp

HEADERS += mainwindow.h \
    l2aconversion.h \
    c2lconversion.h \
    a2lconversion.h \
    addworddialog.h \
    calendarconverter.h \
    calendarswitchdialog.h \
    settings.h \
    update.h \
    util.h \
    dbservice.h \
    convertor.h

FORMS += mainwindow.ui \
    aboutdialog.ui \
    addworddialog.ui \
    calendarswitchdialog.ui

RESOURCES += azc_res.qrc

RC_FILE = AzConvert.rc

# only for unix:
#unix {
    # in debug mode...
#    CONFIG(debug, debug|release) {
#        DESTDIR = debug
#    }
#    else {
#        DESTDIR = release
#    }
#}
