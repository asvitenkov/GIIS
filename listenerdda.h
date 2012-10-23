#ifndef LISTENERDDA_H
#define LISTENERDDA_H

#include "abstractlistener.h"

class CListenerDDA : public CAbstractListener
{
public:
    explicit CListenerDDA(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor);
    void mousePressEvent(QPoint pos);
    void mouseMoveEvent(QPoint pos);
    void clearTmpObject();
    void fixTmpObject();
    ~CListenerDDA();

private:
    void initialize();
    void modeChanged(Mode mode, Mode oldMode);
    QPoint m_startPos;
    QPoint m_endPos;
};

#endif // LISTENERDDA_H
