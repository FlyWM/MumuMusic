#ifndef MUMUSICMANGEWIDGET_H
#define MUMUSICMANGEWIDGET_H

#include <QWidget>

/**
 * @brief The MuMusicMangeWidget class
 *  the left widget that manages the songs
 */
class MuMusicMangeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MuMusicMangeWidget(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    QWidget *createMangeScrollArea();

signals:
    void ListItemPressed(const int index);

public slots:
};

#endif // MUMUSICMANGEWIDGET_H
