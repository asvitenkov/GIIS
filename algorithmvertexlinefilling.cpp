#include "algorithmvertexlinefilling.h"

bool caseLessThan(const QPoint &s1, const QPoint &s2)
 {
     return s1.x()<s2.x();
 }

bool sortVectorPoints(const StepPoints &s1, const StepPoints &s2)
 {
    QPoint p1 = s1.at(0);
    QPoint p2 = s2.at(0);
    return ( (p1.y()<p2.y()) || (p1.y()==p2.y() && p1.x()<p2.x()));
 }




CAlgorithmVertexLineFilling::CAlgorithmVertexLineFilling()
{

    m_pBresenhamAlg = NULL;
    m_pBresenhamAlg = new CAlgorithmBresenham(QPoint(0,0), QPoint(0,0));
    m_bBeginState = true;
    _init();
}


void CAlgorithmVertexLineFilling::_init()
{
    m_xMin = 99999;
    m_yMin = 99999;
    m_xMax = -99999;
    m_yMax = -99999;
    m_resultPoints.clear();
    m_intersectPoints.clear();
    m_linesPoints.clear();
    m_rastedLines.clear();
    //m_pointsList.clear();
    memset(&m_matrix,0,260*260*sizeof(bool));
    m_linesPoints.clear();
}

StepPoints CAlgorithmVertexLineFilling::getDrawPoints()
{
    StepPoints points;
    //reset();
    findMinMaxValues();
    raserLines(m_pointsList);
    findIntersect();
    qSort(m_intersectPoints.begin(),m_intersectPoints.end(),sortVectorPoints);

    StepPoints p1,p2,p3;



    while(!m_intersectPoints.isEmpty())
    {
        p1=m_intersectPoints.takeFirst();
        if(m_intersectPoints.isEmpty())
            continue;
        p2=m_intersectPoints.takeFirst();

        if(p1.first().y()!=p2.first().y())
        {
            m_intersectPoints.push_front(p2);
            continue;
        }

        if(!m_intersectPoints.isEmpty())
        {
            p3 = m_intersectPoints.takeFirst();
            // проверяем на горизонтальную линию
            if(p1.last().x()==p2.first().x() && p2.last()==p3.first() && p1.last().y() == p2.last().y() && p3.last().y()==p2.last().y())
            {
                // горизонтальная линия ничего не делаем
            }
            else
            {
                m_intersectPoints.push_front(p3);
                int y = p1.first().y();
                for(int i=p1.last().x()+1; i<p2.first().x();i++)
                {
                    points.push_back(QPoint(i,y));
                }
            }
        }
    }
    StepPoints res;
    QPoint point;
    for(int i=0; i<points.size(); i++)
    {
        point = points.at(i);
        if(!m_rastedLines.contains(point))
            res.push_back(point);
    }

    return res;
}


bool CAlgorithmVertexLineFilling::nextStep()
{
    if(m_bBeginState)
    {
        m_bBeginState = false;
        m_resultPoints = getDrawPoints();
        return true;
    }
    if(!m_resultPoints.isEmpty())
        return true;
    return false;
}


StepPoints CAlgorithmVertexLineFilling::getStepDrawPoint()
{

    StepPoints points;
    if(m_resultPoints.isEmpty())
        return points;
    m_curPoint = m_resultPoints.at(0);
    points.push_back(m_curPoint);
    m_resultPoints.pop_front();
    return points;
}

void CAlgorithmVertexLineFilling::reset()
{
    m_bBeginState = true;

    _init();
}


QString CAlgorithmVertexLineFilling::getInitInfo()
{
    return "";
}

QString CAlgorithmVertexLineFilling::getInfo()
{
    return "";
}

StepPoints CAlgorithmVertexLineFilling::getMainPoints()
{
    StepPoints points;
    return points;
}

void CAlgorithmVertexLineFilling::findMinMaxValues()
{
    for(int i=0; i<m_pointsList.size(); i++)
    {
        QPoint point = m_pointsList.at(i);

        if(point.x()>m_xMax) m_xMax = point.x();
        if(point.x()<m_xMin) m_xMin = point.x();

        if(point.y()>m_yMax) m_yMax = point.y();
        if(point.y()<m_yMin) m_yMin = point.y();

    }
}


void CAlgorithmVertexLineFilling::raserLines(QList<QPoint> list)
{
    if(list.size()<3) return;
    list.push_back(list.at(0));
    StepPoints points, line;
    QPoint start,end, next;

    int listSize = list.size();
    list.push_back(list.at(1));
    for(int i=0; i<listSize-1; i++)
    {
        start = list.at(i);
        end = list.at(i+1);
        next = list.at(i+2);



        if((start.y()-end.y())*(end.y()-next.y())<=0)
        {
            // local max or min
            m_pBresenhamAlg->setStartPos(start);
            m_pBresenhamAlg->setEndPos(end);
            points = m_pBresenhamAlg->getDrawPoints();
            m_linesPoints.push_back(points);

            m_rastedLines << points;
        }
        else
        {
            m_pBresenhamAlg->setStartPos(start);
            m_pBresenhamAlg->setEndPos(end);
            points = m_pBresenhamAlg->getDrawPoints();

            m_rastedLines << points;

            StepPoints res;
            for(int i=0; i<points.size(); i++)
            {
                if(points.at(i).y()!=end.y())
                    res.push_back(points.at(i));
            }
            if(!res.isEmpty())
                m_linesPoints.push_back(res);

        }
    }
    list.pop_back();
    list.pop_back();
}


void CAlgorithmVertexLineFilling::setPoints(QList<QPoint> list)
{
    m_pointsList = list;
}



StepPoints CAlgorithmVertexLineFilling::fillLine(int leftX, int rightX, int y)
{
    StepPoints points;

    return points;
}


void CAlgorithmVertexLineFilling::findIntersect()
{
    for(int i=0; i<m_linesPoints.size(); i++)
    {
        StepPoints line = m_linesPoints.at(i);
        StepPoints intersect;
        bool newPart = true;
        for(int i=0; i<line.size();i++)
        {
            if(newPart)
            {
                intersect.clear();
                newPart = false;
                intersect.push_back(line.at(i));
            }
            else
            {
                if(line.at(i).y()==line.at(i-1).y())
                {
                    intersect.push_back(line.at(i));
                }
                else
                {
                    qSort(intersect.begin(), intersect.end(),caseLessThan);
                    m_intersectPoints.push_back(intersect);
                    intersect.clear();
                    intersect.push_back(line.at(i));
                }
            }
        }
        if(!intersect.isEmpty())
        {
            qSort(intersect.begin(), intersect.end(),caseLessThan);
            m_intersectPoints.push_back(intersect);
            intersect.clear();
        }

    }
}
