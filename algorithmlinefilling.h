#ifndef ALGORITHMLINEFILLING_H
#define ALGORITHMLINEFILLING_H


#include "abstractpaintalgorithm.h"
#include <QStack>


class CAlgorithmLineFilling : public CAbstractPaintAlgorithm
{
public:
    CAlgorithmLineFilling();
    StepPoints getDrawPoints();
    bool nextStep();
    StepPoints getStepDrawPoint();
    void reset();
    QString getInfo();
    QString getInitInfo();
    StepPoints getMainPoints();
    void setStartPoint(QPoint pos);
    void setMatrix(bool **matrix);
protected:
    void _init();

private:
    void fillLine(QPoint start, QPoint &leftBorder, QPoint &rigthBorder, QVector<QPoint> &result);
    bool checkLine(int &leftX, int &rightX, int y, int &anchor);

    bool **m_pMatrix;
    QStack<QPoint> m_stack;
    QPoint m_leftBorder;
    QPoint m_rightBorder;
    QPoint m_startPoint;
    QPoint m_curPoint;
    QVector<QPoint> m_resultPoints;
    bool m_bBeginState;


};

#endif // ALGORITHMLINEFILLING_H
