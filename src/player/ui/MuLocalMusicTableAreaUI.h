/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MULOCALMUSICTABLEAREAUI_H
#define MULOCALMUSICTABLEAREAUI_H

#include <QWidget>
#include "MuBaseWidget.h"

namespace Ui {
class MuLocalMusicTableAreaUI;
}

class MuTableView;
class QPushButton;
class QLineEdit;
class MuLocalMusicTableAreaUI : public MuBaseWidget
{
    Q_OBJECT

public:
    explicit MuLocalMusicTableAreaUI(QWidget *parent = nullptr);
    ~MuLocalMusicTableAreaUI();

    MuTableView *tableView() const;
    QPushButton *matchButton() const;
    QLineEdit *searchLocalMusicBox() const;

signals:
    void TableRowCount(int count);

private:
    Ui::MuLocalMusicTableAreaUI *ui;
};

#endif // MULOCALMUSICTABLEAREAUI_H
