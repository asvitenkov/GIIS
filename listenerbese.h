#ifndef LISTENERBESE_H
#define LISTENERBESE_H

#include "abstractlistener.h"
#include "algorithmbese.h"

class CListenerBese : public CAbstractListener
{
public:
    explicit CListenerBese(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor);
    ~CListenerBese();
    void mousePressEvent(QPoint pos);
    void mouseMoveEvent(QPoint pos);
    void mouseReleaseEvent(QPoint pos);
    void reset();
    void setHightlightMainPoints(bool enable);
private:
    void fixSpline();
    void initialize();
    void modeChanged(Mode mode, Mode oldMode);
    void drawSpline();
    void drawNormalSpline(QVector<QPoint> points);
    void drawDebugSpline(QVector<QPoint> points);
    void drawTempoparySpline(QVector<QPoint> pointsSpline);

    void update(QVector<QPoint> points);
    void updateMainPoints(QVector<QPoint> points);

    void clearMainPoints();
    QVector<QPoint> m_clickPoints;

    bool m_bMoveModeEnable;
    //CAlgorithmBSpline *m_pAlgorithm;
    CAlgorithmBese *m_pAlgorithm;
    int m_movePointIndex;
    QPoint m_movePointPos;
    QPoint m_mousePressPos;
    QUndoStack m_mainPointsUndoStack;
};

#endif // LISTENERBESE_H
