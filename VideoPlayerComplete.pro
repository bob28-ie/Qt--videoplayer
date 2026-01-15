QT += core gui multimedia multimediawidgets widgets network sql

CONFIG += c++17

TARGET = VideoPlayerComplete
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    database.cpp \
    loginwindow.cpp \
    registerwindow.cpp \
    mainwindow.cpp

HEADERS += \
    database.h \
    loginwindow.h \
    registerwindow.h \
    mainwindow.h

FORMS += \
    loginwindow.ui \
    registerwindow.ui \
    mainwindow.ui

# 部署设置
win32 {
    target.path = $$OUT_PWD
    !isEmpty(target.path): INSTALLS += target
}
