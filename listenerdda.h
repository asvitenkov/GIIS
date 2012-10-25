#ifndef LISTENERDDA_H
#define LISTENERDDA_H

#include "abstractlistener.h"
#include "algorithmdda.h"
#include "painter.h"

class CListenerDDA : public CAbstractListener
{
public:
    explicit CListenerDDA(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor);
    void mousePressEvent(QPoint pos);
    void mouseMoveEvent(QPoint pos);
    ~CListenerDDA();
    void reset();

private:
    void initialize();
    void drawLine();
    void drawDebugLine(QPoint start, QPoint end);
    void drawNormalLine(QPoint start, QPoint end);
    void drawTemporaryLine(QPoint start, QPoint end);
    void modeChanged(Mode mode, Mode oldMode);


    CAlgorithmDDA *m_pAlgorithm;
    QPoint m_startPos;
    QPoint m_endPos;
};

#endif // LISTENERDDA_H
