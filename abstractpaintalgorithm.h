#ifndef ABSTRACTPAINTALGORITHM_H
#define ABSTRACTPAINTALGORITHM_H

#include <QPoint>
#include "coordinateview.h"

#include <QDebug>


#define ADD_STEP_POINTS(from, to) for(int i=0;i<from.size();i++) to.push_back(from.at(i));
typedef QVector<QPoint> StepPoints;

class CAbstractPaintAlgorithm

{

public:
    CAbstractPaintAlgorithm();
    virtual StepPoints getDrawPoints() = 0;
    virtual bool nextStep() = 0;
    virtual StepPoints getStepDrawPoint() = 0;
    virtual void reset() = 0;
    virtual QString getInfo() = 0;
    virtual QString getInitInfo() = 0;
    virtual StepPoints getMainPoints() = 0;
protected:
    QString m_sInitInfo;
    virtual void _init() = 0;
};

#endif // ABSTRACTPAINTALGORITHM_H
