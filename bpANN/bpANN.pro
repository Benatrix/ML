#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T15:46:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT +=multimedia
QT+=multimediawidgets
QT           += network

TARGET = bpANN
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bp.cpp

HEADERS  += mainwindow.h \
    bp.h


INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2\
INCLUDEPATH += /home/luzj/Code/TCPIP/omd
INCLUDEPATH+=/home/luzj/Code_Exer2/Force_Control/Force_Control/omd
INCLUDEPATH+=/usr/include/eigen3/Eigen

LIBS += /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so    \
       /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_video.so\
    /usr/local/lib/libopencv_shape.so \
/usr/local/lib/libopencv_videoio.so.3.2\
/usr/local/lib/libopencv_calib3d.so\
/usr/local/lib/libopencv_ml.so\
        /usr/local/lib/libopencv_imgproc.so

LIBS += -lARToolKitPlus


FORMS    += mainwindow.ui
