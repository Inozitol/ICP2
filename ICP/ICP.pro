TOPDIR = $$PWD

INCLUDEPATH += . \
               $$TOPDIR

INCLUDEPATH += \
        $$TOPDIR/ClassDiagram \
        $$TOPDIR/SequenceDiagram


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(ClassDiagram/classdiagram.pri)
include(SequenceDiagram/sequencediagram.pri)

SOURCES += \
    classdiagramscene.cpp \
    classgraphicsobject.cpp \
    environment.cpp \
    eventdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    newclassform.cpp \

HEADERS += \
    classdiagramscene.h \
    classgraphicsobject.h \
    environment.h \
    eventdialog.h \
    mainwindow.h \
    newclassform.h \

FORMS += \
    eventdialog.ui \
    mainwindow.ui \
    newclassform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
