INCLUDEPATH += $$PWD

DEPENDPATH += $$PWD

TEMPLATE += fakelib

# qtLibraryTarget确保windows下debug模式生成的动态库可以自动加个d
# 用来区分 release 和 debug 模式下的库, 这里只是为了设置LIBFRAMELESSWINDOW_NAME的值，
# 所以 TEMPLATE -= fakelib，不然 qtLibraryTarget 获取不到值
LIBMUMEDIAHANDLER_NAME = $$qtLibraryTarget(MuMediaHandler)

TEMPLATE -= fakelib

include(../../common.pri)

# MuMediaHandler-buildlib 标志用来区分是 libFramelessWindow调用
# 还是 libTest调用, 所以需要在 libFramelessWindow.pro中
# 设置 CONFIG += FramelessWindow-buidlib
MuMediaHandler-buildlib{
    HEADERS += libMuMediaHandler_Global.h \
        MuMedia.h \
        MuMedia_p.h

    SOURCES += \
        MuMedia.cpp

}else{
    LIBS += -L$$PROJECT_LIBDIR -l$$LIBMUMEDIAHANDLER_NAME
}

