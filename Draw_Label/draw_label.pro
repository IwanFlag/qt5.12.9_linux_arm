#-------------------------------------------------
#
# Project created by QtCreator 2021-03-29T11:12:33
#
#-------------------------------------------------

QT       += core gui serialport xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = draw_label
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#Msvc wasn't finding the "config.h" file in the project dir
#and this includepath takes care of that.

INCLUDEPATH += $$PWD

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    drawscene.cpp \
    drawview.cpp \
    drawlineitem.cpp \
    drawrectitem.cpp \
    drawrectitemex.cpp \
    drawtextitem.cpp \
    drawtwocodeitem.cpp \
    third_party/qrencode/source/bitstream.c \
    third_party/qrencode/source/mask.c \
    third_party/qrencode/source/mmask.c \
    third_party/qrencode/source/mqrspec.c \
    third_party/qrencode/source/qrencode.c \
    third_party/qrencode/source/qrinput.c \
    third_party/qrencode/source/qrspec.c \
    third_party/qrencode/source/rscode.c \
    third_party/qrencode/source/split.c \
    third_party/barcode/source/2of5.c \
    third_party/barcode/source/auspost.c \
    third_party/barcode/source/aztec.c \
    third_party/barcode/source/code.c \
    third_party/barcode/source/code1.c \
    third_party/barcode/source/code128.c \
    third_party/barcode/source/code16k.c \
    third_party/barcode/source/code49.c \
    third_party/barcode/source/common.c \
    third_party/barcode/source/composite.c \
    third_party/barcode/source/dllversion.c \
    third_party/barcode/source/dmatrix.c \
    third_party/barcode/source/gridmtx.c \
    third_party/barcode/source/gs1.c \
    third_party/barcode/source/imail.c \
    third_party/barcode/source/large.c \
    third_party/barcode/source/library.c \
    third_party/barcode/source/maxicode.c \
    third_party/barcode/source/medical.c \
    third_party/barcode/source/pdf417.c \
    third_party/barcode/source/plessey.c \
    third_party/barcode/source/png.c \
    third_party/barcode/source/postal.c \
    third_party/barcode/source/ps.c \
    third_party/barcode/source/qr.c \
    third_party/barcode/source/reedsol.c \
    third_party/barcode/source/render.c \
    third_party/barcode/source/rss.c \
    third_party/barcode/source/svg.c \
    third_party/barcode/source/telepen.c \
    third_party/barcode/source/upcean.c \
    third_party/barcode/cppClass/Barcode.cpp \
    third_party/barcode/cppClass/qzint.cpp \
    drawonecodeitem.cpp \
    common_fun.cpp \
    common_def.cpp \
    uarttabwidget.cpp \
    attrtexttabwidget.cpp \
    attrrecttabwidget.cpp \
    attronecodetabwidget.cpp \
    attrtwocodetabwidget.cpp \
    attrlinetabwidget.cpp \
    attrlabeltabwidget.cpp \
    printeruartthread.cpp \
    drawlabel.cpp

HEADERS += \
        mainwindow.h \
    common_res.h \
    main.h \
    drawscene.h \
    drawview.h \
    drawlineitem.h \
    drawrectitem.h \
    drawrectitemex.h \
    drawtextitem.h \
    drawtwocodeitem.h \
    third_party/qrencode/include/bitstream.h \
    third_party/qrencode/include/config.h \
    third_party/qrencode/include/mask.h \
    third_party/qrencode/include/mmask.h \
    third_party/qrencode/include/mqrspec.h \
    third_party/qrencode/include/qrencode.h \
    third_party/qrencode/include/qrencode_inner.h \
    third_party/qrencode/include/qrinput.h \
    third_party/qrencode/include/qrspec.h \
    third_party/qrencode/include/rscode.h \
    third_party/qrencode/include/split.h \
    third_party/barcode/include/aztec.h \
    third_party/barcode/include/code1.h \
    third_party/barcode/include/code49.h \
    third_party/barcode/include/common.h \
    third_party/barcode/include/composite.h \
    third_party/barcode/include/dmatrix.h \
    third_party/barcode/include/font.h \
    third_party/barcode/include/gb2312.h \
    third_party/barcode/include/gridmtx.h \
    third_party/barcode/include/gs1.h \
    third_party/barcode/include/large.h \
    third_party/barcode/include/maxicode.h \
    third_party/barcode/include/maxipng.h \
    third_party/barcode/include/ms_stdint.h \
    third_party/barcode/include/pdf417.h \
    third_party/barcode/include/qr.h \
    third_party/barcode/include/reedsol.h \
    third_party/barcode/include/rss.h \
    third_party/barcode/include/sjis.h \
    third_party/barcode/include/zint.h \
    third_party/barcode/source/libzint.rc \
    third_party/barcode/source/libzint.rc \
    third_party/barcode/cppClass/Barcode.h \
    third_party/barcode/cppClass/qzint.h \
    drawonecodeitem.h \
    common_def.h \
    common_fun.h \
    uarttabwidget.h \
    attrtexttabwidget.h \
    attrrecttabwidget.h \
    attronecodetabwidget.h \
    attrtwocodetabwidget.h \
    attrlinetabwidget.h \
    attrlabeltabwidget.h \
    printeruartthread.h \
    drawlabel.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    icon/images.qrc \
    language.qrc

DISTFILES += \
    third_party/barcode/include/CMakeLists.txt \
    third_party/barcode/source/DEVELOPER \
    third_party/barcode/source/DEVELOPER \
    language/draw_label_zh.qm


#--------移植代码添加如下
#这两句必须得要，否在要一个一个去.cpp改头文件路径,麻烦得很
INCLUDEPATH += $$PWD/third_party/barcode/include\
                $$PWD/third_party/barcode/cppClass

#DEPENDPATH += $$PWD/third_party/barcode/include

DEFINES += ZINT_VERSION=\\\"2.4.4\\\"
DEFINES += NO_PNG
DEFINES += _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS


#language files
TRANSLATIONS += language/draw_label_en.ts\
                language/draw_label_zh.ts
