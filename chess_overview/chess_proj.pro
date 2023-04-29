TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        board.cpp \
        boardclass.cpp \
        main.cpp \
        piece.cpp \
        player.cpp \
        position.cpp

HEADERS += \
    board.h \
    boardclass.h \
    piece.h \
    player.h \
    position.h \
    test.h
