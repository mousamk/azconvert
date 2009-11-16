# -------------------------------------------------
# Project created by QtCreator 2009-09-02T13:27:10
# -------------------------------------------------
TARGET = AzConvert
TEMPLATE = app
TRANSLATIONS = azconvert_en.ts \
    azconvert_fa.ts
SOURCES += main.cpp \
    mainwindow.cpp \
    l2aconversion.cpp \
    mydata.cpp \
    c2lconversion.cpp \
    a2lconversion.cpp \
    addworddialog.cpp \
    calendarconverter.cpp \
    calendarswitchdialog.cpp \
    settings.cpp
HEADERS += mainwindow.h \
    l2aconversion.h \
    mydata.h \
    c2lconversion.h \
    a2lconversion.h \
    addworddialog.h \
    calendarconverter.h \
    calendarswitchdialog.h \
    settings.h
FORMS += mainwindow.ui \
    aboutdialog.ui \
    addworddialog.ui \
    calendarswitchdialog.ui
RESOURCES += azc_res.qrc

# only for unix:
unix {
    # in debug mode...
    CONFIG(debug, debug|release) {
        DESTDIR = debug
    }
    else {
        DESTDIR = release
    }
}
