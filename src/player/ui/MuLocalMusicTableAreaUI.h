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
