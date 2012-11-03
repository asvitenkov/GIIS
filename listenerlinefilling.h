#ifndef LISTENERLINEFILLING_H
#define LISTENERLINEFILLING_H

#include "abstractlistener.h"
#include "algorithmlinefilling.h"

class CListenerLineFilling : public CAbstractListener
{
public:
    CListenerLineFilling(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor);
    ~CListenerLineFilling();
    void  mousePressEvent(QPoint pos);
    void  mouseMoveEvent(QPoint pos);
    //void  mouseReleaseEvent(QPoint pos);
     void reset();

private:
    void initialize();
    void virtual modeChanged(Mode mode, Mode oldMode);
    void fillingArea();
    void fillingAreaNormal();
    void fillingAreaDebug();
    void updateMatrix();
    bool **m_pMatrix;
    QPoint m_clickPos;
    CAlgorithmLineFilling *m_pAlgorithm;
};

#endif // LISTENERLINEFILLING_H
