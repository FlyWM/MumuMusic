TEMPLATE = app

TARGET = MumuMusic

QT += widgets
QT += concurrent sql

QMAKE_CXXFLAGS += -gstabs+

include(../libFramelessWindow/libFramelessWindow.pri)

DESTDIR = $$PROJECT_BINDIR

INCLUDEPATH += widgets \
            ui \
            utils \
            test \
            core

SOURCES += \
    main.cpp \
    widgets/MuScrollArea.cpp \
    widgets/MuToolbox.cpp \
    test/MuTestMainWidget.cpp \
    widgets/MuBaseWidget.cpp \
    widgets/MuCentralWidget.cpp \
    widgets/MuMainWindow.cpp \
    widgets/MuMusicMangeWidget.cpp \
    widgets/MuPlayStatusBar.cpp \
    widgets/MuPopupWidgetButton.cpp \
    widgets/MuShadowWidget.cpp \
    widgets/MuSmallControls.cpp \
    widgets/MuTableView.cpp \
    widgets/MuTableViewHelper.cpp \
    widgets/MuListWidgetItem.cpp \
    utils/MuImageHandler.cpp \
    utils/MuStyleHelper.cpp \
    ui/MuCreatePlayListDlgUI.cpp \
    ui/MuPlayListMainWidgetUI.cpp \
    ui/MuPlayStatusBarUI.cpp \
    widgets/MuListViewItemDelegate.cpp \
    widgets/MuListView.cpp \
    utils/MuConversionTool.cpp \
    ui/MuLocalMusicWidgetUI.cpp \
    ui/MuLocalMusicDetailUI.cpp \
    ui/MuSelectLocalMusicWidgetUI.cpp \
    ui/MuDialogUI.cpp \
    ui/MuLocalMusicTableAreaUI.cpp \
    core/MuDBManager.cpp \
    widgets/MuTableManageMenu.cpp \
    core/MuLocalMusicManager.cpp

HEADERS += \
    widgets/MuScrollArea.h \
    widgets/MuToolbox.h \
    test/MuTestMainWidget.h \
    widgets/MuBaseWidget.h \
    widgets/MuCentralWidget.h \
    widgets/MuMainWindow.h \
    widgets/MuMusicMangeWidget.h \
    widgets/MuPlayStatusBar.h \
    widgets/MuPopupWidgetButton.h \
    widgets/MuShadowWidget.h \
    widgets/MuSmallControls.h \
    widgets/MuTableView.h \
    widgets/MuTableViewHelper.h \
    widgets/MuListWidgetItem.h \
    utils/MuImageHandler.h \
    utils/MuStyleHelper.h \
    ui/MuCreatePlayListDlgUI.h \
    ui/MuPlayListMainWidgetUI.h \
    ui/MuPlayStatusBarUI.h \
    widgets/MuListViewItemDelegate.h \
    widgets/MuListView.h \
    utils/MuConversionTool.h \
    ui/MuLocalMusicWidgetUI.h \
    ui/MuLocalMusicDetailUI.h \
    ui/MuSelectLocalMusicWidgetUI.h \
    ui/MuDialogUI.h \
    MuGlobal.h \
    ui/MuLocalMusicTableAreaUI.h \
    core/MuDBManager.h \
    widgets/MuTableManageMenu.h \
    core/MuLocalMusicManager.h \
    core/MuLocalMusicManager_p.h

RESOURCES += \
    resources/images.qrc \
    resources/styles.qrc \
    resources/gif.qrc \
    resources/testImgs.qrc \
    resources/i18n.qrc

FORMS += \
    ui/MuCreatePlayListDlgUI.ui \
    ui/MuPlayListMainWidgetUI.ui \
    ui/MuPlayStatusBarUI.ui \
    ui/MuLocalMusicWidgetUI.ui \
    ui/MuLocalMusicDetailUI.ui \
    ui/MuSelectLocalMusicWidgetUI.ui \
    ui/MuDialogUI.ui \
    ui/MuLocalMusicTableAreaUI.ui


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libMuMediaHandler/release/ -lMuMediaHandler
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libMuMediaHandler/debug/ -lMuMediaHandler
else:unix:!macx: LIBS += -L$$OUT_PWD/../libMuMediaHandler/ -lMuMediaHandler

INCLUDEPATH += $$PWD/../libMuMediaHandler/src
DEPENDPATH += $$PWD/../libMuMediaHandler/src

TRANSLATIONS += $$PWD/resources/i18n/zh_cn.ts
