#include "CRightClickEnabler.h"

CRightClickEnabler::CRightClickEnabler(QAbstractButton* button)
    : QObject(button), _button(button) {
    _button->installEventFilter(this);
}

bool CRightClickEnabler::eventFilter(QObject *watched, QEvent *event) {
    if (watched == _button && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        if (mouseEvent->button() == Qt::LeftButton) {
            emit leftClicked();
            return false;  // Let Qt handle default behavior
        } 
        else if (mouseEvent->button() == Qt::RightButton) {
            emit rightClicked();
            return true;   // Prevent default context menu
        }
    }
    return QObject::eventFilter(watched, event);
}
