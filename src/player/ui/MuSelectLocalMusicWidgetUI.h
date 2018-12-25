#ifndef MUSELECTLOCALMUSICWIDGETUI_H
#define MUSELECTLOCALMUSICWIDGETUI_H

#include <QWidget>

namespace Ui {
class MuSelectLocalMusicWidgetUI;
}

class MuSelectLocalMusicWidgetUI : public QWidget
{
    Q_OBJECT

public:
    explicit MuSelectLocalMusicWidgetUI(QWidget *parent = nullptr);
    ~MuSelectLocalMusicWidgetUI();

    void addItem(const QString &item);

    QStringList getItemsContent() const;

private:
    Ui::MuSelectLocalMusicWidgetUI *ui;
};

#endif // MUSELECTLOCALMUSICWIDGETUI_H
