#ifndef ALGORITHMROUND_H
#define ALGORITHMROUND_H

#include <QPoint>
#include <QDebug>

#include "abstractpaintalgorithm.h"

class CAlgorithmRound : public CAbstractPaintAlgorithm
{
public:
    CAlgorithmRound(QPoint center, int radius);
    ~CAlgorithmRound();
    StepPoints getDrawPoints();
    bool nextStep();
    StepPoints getStepDrawPoint();
    void reset();
    QString getInfo();
    QString getInitInfo();
    void setCenterPoint(QPoint pos);
    void setRadius(int radius);
private:
    void caseA();
    void caseB();
    void caseV();
    void _init();
    QPoint m_center;
    int m_radius;
    int m_delta;
    int m_sigma;
    int m_limit;
    int m_x;
    int m_y;
    int m_currentStep;
    bool m_bFirstStep;
    QPoint m_currentPoint;
};

#endif // ALGORITHMROUND_H
