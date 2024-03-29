QT += core
QT -= gui

CONFIG += c++11

TARGET = Proyecto1_201313722
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    scanner.cpp \
    parser.cpp \
    comando_mkdisk.cpp \
    estructuras.cpp \
    comando_rmdisk.cpp \
    libreria.cpp \
    comando_fdisk.cpp \
    comando_exec.cpp \
    comando_mount.cpp \
    comando_unmount.cpp \
    comando_mkfs.cpp \
    comando_login.cpp \
    comando_logout.cpp \
    comando_rep.cpp \
    comando_pause.cpp \
    comando_mkdir.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DISTFILES += \
    lexico.l \
    parser.y

HEADERS += \
    scanner.h \
    parser.h \
    comando_mkdisk.h \
    estructuras.h \
    comando_rmdisk.h \
    libreria.h \
    comando_fdisk.h \
    comando_exec.h \
    comando_mount.h \
    comando_unmount.h \
    comando_mkfs.h \
    comando_login.h \
    comando_logout.h \
    comando_rep.h \
    comando_pause.h \
    comando_mkdir.h
