#ifndef ALGORITHMPARABOLA_H
#define ALGORITHMPARABOLA_H

#include "abstractpaintalgorithm.h"

class CAlgorithmParabola : public CAbstractPaintAlgorithm
{
public:
    CAlgorithmParabola(QPoint center, int pValue);
    ~CAlgorithmParabola();
    StepPoints getDrawPoints();
    bool nextStep();
    StepPoints getStepDrawPoint();
    void reset();
    QString getInfo();
    QString getInitInfo();
    void setCenterPoint(QPoint pos);
    void setPValue(int pVal);
    StepPoints getMainPoints();


private:
    void caseA();
    void caseB();
    void caseV();
    void _init();
    int deltaH(QPoint point);
    int deltaV(QPoint point);
    int deltaD(QPoint point);
    QPoint m_center;
    int m_p;
    int m_delta;
    int m_sigma;
    int m_x;
    int m_y;
    int m_limit;
    int m_currentStep;
    bool m_bFirstStep;
    bool m_bIsRevert;
    QPoint m_currentPoint;
};

#endif // ALGORITHMPARABOLA_H
