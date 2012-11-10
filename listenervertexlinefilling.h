#ifndef LISTENERVERTEXLINEFILLING_H
#define LISTENERVERTEXLINEFILLING_H


#include "abstractlistener.h"
#include "algorithmlinefilling.h"
#include "algorithmvertexlinefilling.h"
#include "algorithmbresenham.h"

class CListenerVertexLineFilling : public CAbstractListener
{
public:
    CListenerVertexLineFilling(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor);
    ~CListenerVertexLineFilling();
    void  mousePressEvent(QPoint pos);
    void  mouseMoveEvent(QPoint pos);
    void  mouseReleaseEvent(QPoint pos);
    void reset();

private:
    void initialize();
    void clearMainPoints();
    void modeChanged(Mode mode, Mode oldMode);
    void update(QVector<QPoint> points);
    void updateMainPoints(QVector<QPoint> points);
    void drawTempopary(QVector<QPoint> points);
    void fillingArea();
    void fillingAreaNormal();
    void fillingAreaDebug();
//    void updateMatrix();
    bool m_bMoveModeEnable;
    QPoint m_clickPos;
    CAlgorithmVertexLineFilling *m_pAlgorithm;
    CAlgorithmBresenham *m_pBresenhamAlg;
    QVector<QPoint> m_clickPoints;
    int m_movePointIndex;
    QPoint m_movePointPos;
    QPoint m_mousePressPos;
    QUndoStack m_mainPointsUndoStack;

};

#endif // LISTENERVERTEXLINEFILLING_H
