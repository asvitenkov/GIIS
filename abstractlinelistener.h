#ifndef LISTENERDDA_H
#define LISTENERDDA_H

#include "abstractlistener.h"
#include "algorithmdda.h"
#include "painter.h"

class CAbstractLineListener : public CAbstractListener
{
public:
    explicit CAbstractLineListener(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor);
    void mousePressEvent(QPoint pos);
    void mouseMoveEvent(QPoint pos);
    ~CAbstractLineListener();
    void reset();

private:

    void drawLine();
    void drawDebugLine(QPoint start, QPoint end);
    void drawNormalLine(QPoint start, QPoint end);
    void drawTemporaryLine(QPoint start, QPoint end);
    void modeChanged(Mode mode, Mode oldMode);


protected:
    void initialize();
    CAbstractLinePaintAlgorithm *m_pAlgorithm;
    QPoint m_startPos;
    QPoint m_endPos;
};

#endif // LISTENERDDA_H
