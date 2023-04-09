#-------------------------------------------------
#
# Project created by QtCreator 2023-03-25T15:17:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

INCLUDEPATH += \
    include

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/polynoms/Monom.cpp \
    src/polynoms/Polynom.cpp \
    src/tables/hasher.cpp

HEADERS += \
    include/mainwindow.h \
    include/tables/unsorted_array.h \
    include/tables/unsorted_list.h \
    include/tables/sorted_array.h \
    include/polynoms/Monom.h \
    include/polynoms/Polynom.h \
    include/polynoms/Polynom.h \
    include/tables/connector.h \
    include/tables/hasher.h \
    include/tables/hashmap_chains.h \
    include/tables/hashmap_openadressing.h \
    include/tables/tree_avl.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
