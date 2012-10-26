#ifndef ALGORITHMCDA_H
#define ALGORITHMCDA_H




#include "abstractlinepaintalgorithm.h"

class CAlgorithmDDA: public CAbstractLinePaintAlgorithm
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


    qreal m_fDx;
    qreal m_fDy;
    int m_nStep;
    int m_nLimit;


};

#endif // ALGORITHMCDA_H
