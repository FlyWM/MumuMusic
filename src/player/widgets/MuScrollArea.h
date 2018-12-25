#ifndef MUSCROLLAREA_H
#define MUSCROLLAREA_H

#include <QScrollArea>

class MuScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit MuScrollArea(QWidget *parent = nullptr);

    void setScrollEnabled(bool enabled) { m_scrollEnabled = enabled; }

    bool eventFilter(QObject *o, QEvent *e);

private:
    bool m_scrollEnabled;
};

#endif // MUSCROLLAREA_H
