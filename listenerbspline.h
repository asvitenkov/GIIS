#ifndef LISTENERBSPLINE_H
#define LISTENERBSPLINE_H

#include "algorithmbspline.h"
#include "abstractlistener.h"

class CListenerBSpline : public CAbstractListener
{
public:
    explicit CListenerBSpline(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor);
    ~CListenerBSpline();
    void mousePressEvent(QPoint pos);
    void mouseMoveEvent(QPoint pos);
    void mouseReleaseEvent(QPoint pos);
    void reset();

private:
    void initialize();
    void modeChanged(Mode mode, Mode oldMode);
    void drawSpline();
    void drawNormalSpline(QVector<QPoint> points);
    void drawDebugSpline(QVector<QPoint> points);
    void drawTempoparySpline(QVector<QPoint> pointsSpline);

    void update();

    QVector<QPoint> m_clickPoints;

    bool m_bMoveModeEnable;
    CAlgorithmBSpline *m_pAlgorithm;
    int m_movePointIndex;
    QPoint m_movePointPos;

};

#endif // LISTENERBSPLINE_H
