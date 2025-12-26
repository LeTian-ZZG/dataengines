QT       += core gui
TEMPLATE = lib
CONFIG   += plugin

# 输出文件的名字 (编译出来就是 JustInt16.dll)
TARGET = JustInt16

# 包含刚才写的代码
HEADERS += \
    justint16.h \
    ../shared/dataengineinterface.h

SOURCES += \
    justint16.cpp

# 输出目录设置 (保持原样即可)
DESTDIR = ../bin
