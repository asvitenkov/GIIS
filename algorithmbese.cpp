#include "algorithmbese.h"

#include <QVector4D>
#include "math.h"

CAlgorithmBese::CAlgorithmBese()
{
    _init();
}

CAlgorithmBese::~CAlgorithmBese()
{

}


StepPoints CAlgorithmBese::getDrawPoints()
{
    reset();
    StepPoints points;
    StepPoints stepPoints;
    while(nextStep())
    {
        stepPoints = getStepDrawPoint();
        ADD_STEP_POINTS(stepPoints,points);
        //for(int i=0;i<stepPoints.size();i++) points.push_back(stepPoints.at(i));
    }
    return points;
}

bool CAlgorithmBese::nextStep()
{
    if(m_pointsList.size() < 4 )
        return false;

    if(m_newSection)
    {
        m_newSection = false;
        m_currentIndex++;

        while(m_currentIndex < m_pointsList.size()-1 )
        {
            if(m_pointsList.at(m_currentIndex) != m_pointsList.at(m_currentIndex+1))
                break;
            else
                m_currentIndex++;
        }

        if(m_currentIndex > m_pointsList.size()-3 )
            return false;

        m_indexOnSection = 0;
        QPoint distance = m_pointsList.at(m_currentIndex) - m_pointsList.at(m_currentIndex+1);
        m_pointsOnSection = 2000;
        m_deltaT = 1.0/m_pointsOnSection;
        m_currentTValue = 0;
    }
    else
    {
        m_indexOnSection++;
        m_currentTValue=m_deltaT*m_indexOnSection;
        if(m_indexOnSection >= m_pointsOnSection)
        {
            m_newSection = true;
        }
    }



   return true;
}

StepPoints CAlgorithmBese::getStepDrawPoint()
{
    StepPoints points;

    if(m_pointsList.size()<4)
        return points;
    QPoint point = calculatePoint(m_pointsList.at(m_currentIndex-1),m_pointsList.at(m_currentIndex),m_pointsList.at(m_currentIndex+1),m_pointsList.at(m_currentIndex+2),m_currentTValue).toPoint();
    if(point!=m_lastPoint)
    {
        points.push_back(point);
        m_lastPoint = point;
    }

    return points;
}

void CAlgorithmBese::reset()
{
    _init();
}


QString CAlgorithmBese::getInfo()
{
    return "";
}


QString CAlgorithmBese::getInitInfo()
{
    return "";
}

StepPoints CAlgorithmBese::getMainPoints()
{
    return m_pointsList;
}

void CAlgorithmBese::addPoint(QPoint point)
{
    m_pointsList.push_back(point);
}

void CAlgorithmBese::_init()
{

    m_lastPoint = QPoint(-500,-500);
    m_currentIndex = 0;
    m_newSection = true;
    m_indexOnSection = 0;
    m_pointsOnSection = 0;
    m_deltaT = 0.015;
    m_matrix = QMatrix4x4(
                   -1,  3, -3,  1,
                    3, -6,  3,  0,
                   -3,  3,  0,  0,
                    1,  0,  0,  0
                );
}


qreal CAlgorithmBese::multiplication(qreal t, QVector4D vector)
{
    //QVector4D res = ( m_matrix * vector );
    //return ((t*res.x()+res.y())*t+res.z())*t+res.w();
    return pow((1-t),3)*vector.x() +3*t*pow((t-1),2)*vector.y() + 3*t*(1-t)*vector.z() + pow(t,3)*vector.w();
}


QPointF CAlgorithmBese::calculatePoint(QPoint p0, QPoint p1, QPoint p2, QPoint p3, qreal t)
{
    qreal x,y;
    x = multiplication(t, QVector4D(p0.x(),p1.x(),p2.x(),p3.x()));
    y = multiplication(t, QVector4D(p0.y(),p1.y(),p2.y(),p3.y()));
    return QPointF(x,y);
}



//void CAlgorithmBese::getRations(int v0, int v1, int v2, int v3, qreal &a0, qreal &a1, qreal &a2, qreal &a3)
//{
//    a3 = (-v0 + 3*v1 - 3*v2 +   v3)/6.0;
//    a2 = ( v0 - 2*v1 +   v2 + 0*v3)/2.0;
//    a1 = (-v0 + 0*v1 + 1*v2 + 0*v3)/2.0;
//    a0 = ( v0 + 4*v1 + 1*v2 + 0*v3)/6.0;
//}


//QPointF CAlgorithmBese::calculatePointN(QPoint p0, QPoint p1, QPoint p2, QPoint p3, qreal t)
//{
//    qreal a0,a1,a2,a3;
//    qreal b0,b1,b2,b3;
//    getRations(p0.x(), p1.x(), p2.x(), p3.x(), a0,a1,a2,a3);
//    getRations(p0.y(), p1.y(), p2.y(), p3.y(), b0,b1,b2,b3);
//    qreal x;
//    qreal y;
//    x = ((a3*t + a2)*t + a1)*t + a0;
//    y = ((b3*t + b2)*t + b1)*t + b0;

//    return QPointF(x,y);
//}


void CAlgorithmBese::clearPoints()
{
    m_pointsList.clear();
    reset();
}


void CAlgorithmBese::addPoints(QVector<QPoint> points)
{
    m_pointsList << points;
//    QPoint point;
//    for(int i=0; i<points.size(); i++)
//    {
//        point = points.at(i);
//        if(m_pointsList.isEmpty())
//            m_pointsList << point;
//        else if(m_pointsList.last()!= point)
//            m_pointsList << point;
//    }
}
