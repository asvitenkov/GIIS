#ifndef LISTENERROUNDALGORITHM_H
#define LISTENERROUNDALGORITHM_H

#include "abstractlistener.h"
#include "algorithmround.h"
#include "math.h"

class CListenerRoundAlgorithm : public CAbstractListener
{
public:
    CListenerRoundAlgorithm(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor);
    ~CListenerRoundAlgorithm();
    void mousePressEvent(QPoint pos);
    void mouseMoveEvent(QPoint pos);
    void reset();

private:
    void initialize();
    void modeChanged(Mode mode, Mode oldMode);
    void drawRound();
    void drawDebugRound(QPoint center, int radius);
    void drawNormalRound(QPoint center, int radius);
    void drawTemporaryRound(QPoint center, int radius);
    int distance(QPoint start, QPoint end);
    int m_radius;
    QPoint m_centerPoint;
    bool m_bHighlightMainPoints;

    CAlgorithmRound *m_pAlgorithm;

};

#endif // LISTENERROUNDALGORITHM_H
