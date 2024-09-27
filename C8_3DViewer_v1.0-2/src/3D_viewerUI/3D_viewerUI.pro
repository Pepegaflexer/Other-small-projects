QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../c_sources/s21_arithmetic.c \
    main.cpp \
    mainwindow.cpp \
    modelviewer.cpp \
    ../c_sources/3d_viewer.c \
    ../c_sources/s21_based.c \
    QtGifImage-master/src/3rdParty/giflib/dgif_lib.c \
    QtGifImage-master/src/3rdParty/giflib/egif_lib.c \
    QtGifImage-master/src/3rdParty/giflib/gif_err.c \
    QtGifImage-master/src/3rdParty/giflib/gif_font.c \
    QtGifImage-master/src/3rdParty/giflib/gif_hash.c \
    QtGifImage-master/src/3rdParty/giflib/gifalloc.c \
    QtGifImage-master/src/3rdParty/giflib/quantize.c \
    QtGifImage-master/src/gifimage/qgifimage.cpp

HEADERS += \
    mainwindow.h \
    modelviewer.h \
    ../c_sources/3d_viewer.h \
    QtGifImage-master/src/3rdParty/giflib/gif_hash.h \
    QtGifImage-master/src/3rdParty/giflib/gif_lib.h \
    QtGifImage-master/src/3rdParty/giflib/gif_lib_private.h \
    QtGifImage-master/src/gifimage/qgifglobal.h \
    QtGifImage-master/src/gifimage/qgifimage.h \
    QtGifImage-master/src/gifimage/qgifimage_p.h

FORMS += \
    mainwindow.ui

#LIBS += -lopengl32 -lGLU32 #-lglut32 -lOpenGL

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
