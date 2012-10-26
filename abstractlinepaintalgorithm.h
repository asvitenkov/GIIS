#ifndef ABSTRACTLINEPAINTALGORITHM_H
#define ABSTRACTLINEPAINTALGORITHM_H

#include <QPoint>

#include "abstractpaintalgorithm.h"

class CAbstractLinePaintAlgorithm : public CAbstractPaintAlgorithm
{
public:
    CAbstractLinePaintAlgorithm(QPoint startPoint, QPoint endPoint);
    virtual ~CAbstractLinePaintAlgorithm();

    virtual StepPoints getDrawPoints() = 0;
    virtual bool nextStep() = 0;
    virtual StepPoints getStepDrawPoint() = 0;
    virtual void reset() = 0;
    virtual QString getInfo() = 0;
    virtual QString getInitInfo() = 0;

    virtual void setStartPos(QPoint pos);
    virtual void setEndPos(QPoint pos);

protected:
    QPoint m_startPoint;
    QPoint m_endPoint;
    QPointF m_curPoint;
    bool m_bFirstStep;
    virtual void _init() = 0;
};

#endif // ABSTRACTLINEPAINTALGORITHM_H
