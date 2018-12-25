#ifndef MUPOPUPWIDGETBUTTON_H
#define MUPOPUPWIDGETBUTTON_H

#include <QWidget>
#include <QPushButton>

namespace PWB {
enum WidgetOrientation {
    Horizontal,
    Vertical,
};
}

class QPushButton;
class PopupWidget;
class MuPopupWidgetButton : public QWidget
{
    Q_OBJECT
public:
    explicit MuPopupWidgetButton(PWB::WidgetOrientation orien, QWidget *parent = nullptr);
    ~MuPopupWidgetButton();

    /**
     * @brief setMainWidget 设置弹出的widget
     * @param widget
     */
    void setMainWidget(QWidget *widget);
    /**
     * @brief setButtonObjectName 设置按钮 objectname，方便设置样式表
     * @param name
     */
    void setButtonObjectName(const QString &name);

    /**
     * @brief button 方便设置按钮的一些属性
     * @return
     */
    QPushButton *button() { return m_pButton; }



protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);

signals:
    void ButtonClicked();
    void OthersClicked();

public slots:
    void hideWidget();

private:
    QPushButton *m_pButton;
    PWB::WidgetOrientation m_orien;
    PopupWidget *m_pMainWidget;
    bool m_mainWidgetClicked;
    static QList<PopupWidget *> m_pWidgets;
};

#endif // MUPOPUPWIDGETBUTTON_H
