#ifndef CRIGHTCLICKENABLER_H
#define CRIGHTCLICKENABLER_H

#include <QObject>
#include <QAbstractButton>
#include <QMouseEvent>
#include <QEvent>

class CRightClickEnabler : public QObject {
    Q_OBJECT

public:
    explicit CRightClickEnabler(QAbstractButton* button);  // Constructor

signals:
    void leftClicked();    // Signal for left-click detection
    void rightClicked();   // Signal for right-click detection

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;  // Event filter override

private:
    QAbstractButton* _button;  // Pointer to the button being observed
};

#endif // CRIGHTCLICKENABLER_H
