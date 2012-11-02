#ifndef ALGORITHMBESE_H
#define ALGORITHMBESE_H

#include "abstractpaintalgorithm.h"

#include <QMatrix4x4>

class CAlgorithmBese : public CAbstractPaintAlgorithm
{
public:
    CAlgorithmBese();
    ~CAlgorithmBese();
    StepPoints getDrawPoints();
    bool nextStep();
    StepPoints getStepDrawPoint();
    void reset();
    QString getInfo();
    QString getInitInfo();
    StepPoints getMainPoints();
    void addPoint(QPoint point);
    void addPoints(QVector<QPoint> points);
    void clearPoints();

private:
    void _init();
    qreal multiplication(qreal t, QVector4D vector);
    QPointF calculatePoint(QPoint p0, QPoint p1, QPoint p2, QPoint p3, qreal t);
    //QPointF calculatePointN(QPoint p0, QPoint p1, QPoint p2, QPoint p3, qreal t);
    qreal m_deltaT;
    qreal m_currentTValue;
    int m_pointsOnSection;
    int m_indexOnSection;
    QMatrix4x4 m_matrix;
    QVector<QPoint> m_pointsList;
    int m_currentIndex;
    bool m_newSection;
    QPoint m_lastPoint;
    //void getRations(int v0, int v1, int v2, int v3, qreal &a0, qreal &a1, qreal &a2, qreal &a3);
};
#endif // ALGORITHMBESE_H
