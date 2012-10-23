#ifndef ALGORITHMCDA_H
#define ALGORITHMCDA_H


#include <QPoint>

#include "abstractpaintalgorithm.h"

class CAlgorithmDDA: public CAbstractPaintAlgorithm
{
public:
    CAlgorithmDDA(QPoint startPoint, QPoint endPoint);
    StepPoints getDrawPoints();
    bool nextStep();
    StepPoints getStepDrawPoint();
    void reset();
    QString getInfo();

    QString getInitInfo();


private:
    void _init();

    QPoint m_startPoint;
    QPoint m_endPoint;
    QPointF m_curPoint;
    qreal m_fDx;
    qreal m_fDy;
    int m_nStep;
    int m_nLimit;

     bool m_bFirstStep;
};

#endif // ALGORITHMCDA_H
