#ifndef ALGORITHMVERTEXLINEFILLING_H
#define ALGORITHMVERTEXLINEFILLING_H

#include "abstractpaintalgorithm.h"
#include "algorithmbresenham.h"
//QPolygon m;

class CAlgorithmVertexLineFilling : public CAbstractPaintAlgorithm
{
public:
    CAlgorithmVertexLineFilling();
    StepPoints getDrawPoints();
    bool nextStep();
    StepPoints getStepDrawPoint();
    void reset();
    QString getInfo();
    QString getInitInfo();
    StepPoints getMainPoints();
    void setPoints(QList<QPoint> list);
private:
    void findMinMaxValues();
    void raserLines(QList<QPoint> list);
    void findIntersect();
    StepPoints fillLine(int leftX, int rightX, int y);
    QList<QPoint> m_pointsList;
    QList<StepPoints> m_linesPoints;
    QList<StepPoints> m_intersectPoints;

    StepPoints m_rastedLines;

    int m_height;
    int m_width;
    int m_xMin;
    int m_yMin;
    int m_xMax;
    int m_yMax;
    bool m_matrix[260][260];
    void _init();
    bool m_bBeginState;
    StepPoints m_resultPoints;
    QPoint m_curPoint;
    CAlgorithmBresenham *m_pBresenhamAlg;
};

#endif // ALGORITHMVERTEXLINEFILLING_H
