#ifndef LISTENERPARABOLA_H
#define LISTENERPARABOLA_H

#include "abstractlistener.h"
#include "algorithmparabola.h"

class CListenerParabola : public CAbstractListener
{
public:
    CListenerParabola(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor);
    ~CListenerParabola();
    void mousePressEvent(QPoint pos);
    void mouseMoveEvent(QPoint pos);
    void reset();
    void setPValue(int pValue);
    void setCenter(QPoint center);
private:
    void initialize();
    void modeChanged(Mode mode, Mode oldMode);
    void drawParabola();
    void drawDebugParabola(QPoint center, int pValue);
    void drawNormalParabola(QPoint center, int pValue);
    void drawTemporaryParabola(QPoint center, int pValue);
    int m_p;
    QPoint m_centerPoint;
    bool m_bHighlightMainPoints;

    CAlgorithmParabola *m_pAlgorithm;
};

#endif // LISTENERPARABOLA_H
