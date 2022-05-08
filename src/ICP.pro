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
    classdialog.cpp \
    classgraphicsobject.cpp \
    environment.cpp \
    eventdialog.cpp \
    lifelinedialog.cpp \
    lifelinegraphicsobject.cpp \
    main.cpp \
    mainwindow.cpp \
    relationdialog.cpp \
    relationgraphicsobject.cpp \
    sequencediagramscene.cpp \
    utils.cpp

HEADERS += \
    classdiagramscene.h \
    classdialog.h \
    classgraphicsobject.h \
    environment.h \
    eventdialog.h \
    graphicsenum.h \
    lifelinedialog.h \
    lifelinegraphicsobject.h \
    mainwindow.h \
    relationdialog.h \
    relationgraphicsobject.h \
    sequencediagramscene.h \
    utils.h

FORMS += \
    classdialog.ui \
    event_activation.ui \
    event_deactivation.ui \
    event_message.ui \
    event_return.ui \
    event_spacer.ui \
    eventdialog.ui \
    lifelinedialog.ui \
    mainwindow.ui \
    relationdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
