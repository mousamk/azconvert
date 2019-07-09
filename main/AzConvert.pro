# -------------------------------------------------
# Project created by QtCreator 2009-09-02T13:27:10
# -------------------------------------------------
QT += core gui widgets network sql
TARGET = AzConvert
TEMPLATE = app


TRANSLATIONS = azconvert_fa_IR.ts \
    azconvert_tr_TR.ts \
    azconvert_az_AZ.ts \
    azconvert_az_IR.ts

CODECFORTR = UTF-8


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
    convertor.cpp \
    regex.cpp \
    regexurl.cpp \
    regexemail.cpp \
    regexwikitemplate.cpp \
    regexwikiinterwiki.cpp \
    regexwikipicture.cpp \
    regexhtmltag.cpp \
    regexwikilink.cpp \
    regexwikinoconvert.cpp \
    regexwikiforceconvert.cpp \
    regexwikinowiki.cpp \
    regexruminumbers.cpp \
    aboutdialog.cpp \
    l2cconversion.cpp \
    settingsdialog.cpp


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
    convertor.h \
    specialcharacterrecord.h \
    config.h \
    regex.h \
    regexurl.h \
    regexemail.h \
    regexwikitemplate.h \
    regexwikiinterwiki.h \
    regexwikipicture.h \
    regexhtmltag.h \
    regexwikilink.h \
    regexwikinoconvert.h \
    regexwikiforceconvert.h \
    regexwikinowiki.h \
    regexruminumbers.h \
    aboutdialog.h \
    l2cconversion.h \
    settingsdialog.h \
    charreplacerecord.h


FORMS += mainwindow.ui \
    aboutdialog.ui \
    addworddialog.ui \
    calendarswitchdialog.ui \
    settingsdialog.ui


RESOURCES += azc_res.qrc

RC_FILE = AzConvert.rc


DEFINES += DEBUG_BUILD


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
