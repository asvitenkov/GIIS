#ifndef ALGORITHMBRESENHAM_H
#define ALGORITHMBRESENHAM_H

#include "abstractlinepaintalgorithm.h"


#include <QPoint>

class CAlgorithmBresenham : public CAbstractLinePaintAlgorithm
{
public:
    CAlgorithmBresenham(QPoint startPoint, QPoint endPoint);
    StepPoints getDrawPoints();
    bool nextStep();
    StepPoints getStepDrawPoint();
    void reset();
    QString getInfo();
    QString getInitInfo();

private:
    void _init();
    inline int _sign(int n);
    //QPoint m_startPoint;
    //QPoint m_endPoint;
    //QPointF m_curPoint;
    bool m_bFirstStep;
    int m_nError;
    int m_nLength;
    int m_nCurStep;
    int m_nSwap;
    int m_nDx;
    int m_nDy;
    int m_nS1;
    int m_nS2;

};

#endif // ALGORITHMBRESENHAM_H
