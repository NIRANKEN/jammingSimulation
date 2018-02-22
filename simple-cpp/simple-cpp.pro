#!include( ../examples.pri ) {
#    error( "Couldn't find the examples.pri file!" )
#}

QT += 3dcore 3dinput gui core widgets 3dextras
INCLUDEPATH += . /home/y-kimura/lib
CONFIG += c++11

# Input
SOURCES += \
    main.cpp \
    FIREVV3D.cpp \
    scenemodifier.cpp \
    mainwindow.cpp

HEADERS += \
    FIREVV3D.h \
    scenemodifier.h \
    mainwindow.h

FORMS += \
    mainwindow.ui


