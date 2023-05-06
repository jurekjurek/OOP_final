QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ajout.cpp \
    cavalier.cpp \
    fenetredemarrage.cpp \
    fou.cpp \
    jeuechecwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    piece.cpp \
    pion.cpp \
    plateauechec.cpp \
    reine.cpp \
    roi.cpp \
    tour.cpp

HEADERS += \
    ajout.h \
    cavalier.h \
    fenetredemarrage.h \
    fou.h \
    jeuechecwindow.h \
    mainwindow.h \
    piece.h \
    pion.h \
    plateauechec.h \
    reine.h \
    roi.h \
    tour.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
