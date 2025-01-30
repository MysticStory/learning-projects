QT       += core gui widgets opengl 
greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets
include(QtGifImage/src/gifimage/qtgifimage.pri)
INCLUDEPATH += View/include/
CONFIG += c++11

DEFINES += GL_SILENCE_DEPRECATION QT_NO_DEBUG_OUTPUT
SOURCES += \
    main.cpp\
    View/src/mainwindow.cpp\
    View/src/GifRecorder.cpp\
    View/src/StyleHelper.cpp\
    View/src/ViewSettings.cpp\
    View/src/QtSceneDrawer.cpp\
    Controller/src/Controller.cpp\
    

HEADERS += \
    View/include/mainwindow.h\
    View/include/GifRecorder.h\
    View/include/StyleHelper.h\
    View/include/QtSceneDrawer.h\
    View/include/SceneDrawerBase.h\
    View/include/ViewSettings.h\
    Controller/include/Controller.h\
    

FORMS += \
    View/include/mainwindow.ui

LIBS += \
    model.a    

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
