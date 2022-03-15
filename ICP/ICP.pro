QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aggregation.cpp \
    association.cpp \
    environment.cpp \
    generalization.cpp \
    main.cpp \
    mainwindow.cpp \
    metaclass.cpp \
    metaclassattribute.cpp \
    metaclassmethod.cpp \
    metaclassobject.cpp \
    relation.cpp

HEADERS += \
    aggregation.h \
    association.h \
    environment.h \
    generalization.h \
    mainwindow.h \
    metaclass.h \
    metaclassattribute.h \
    metaclassmethod.h \
    metaclassobject.h \
    relation.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
