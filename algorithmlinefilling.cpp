#include "algorithmlinefilling.h"



CAlgorithmLineFilling::CAlgorithmLineFilling()
{
    m_pMatrix = NULL;
    _init();
}



void CAlgorithmLineFilling::_init()
{
    m_sInitInfo = "Algorithm Filling line";
    m_bBeginState = true;
}



StepPoints CAlgorithmLineFilling::getDrawPoints()
{

    //reset();

//    StepPoints poitns;
//    m_stack.push_back(m_startPoint);
//    QPoint curPoint;
//    QPoint left, right;
//    int anchor;
//    while(!m_stack.isEmpty())
//    {
//        curPoint = m_stack.at(0);
//        m_stack.pop_front();
//        fillLine(curPoint,left, right, poitns);
//        int leftX,rightX;
//        leftX = left.x();
//        rightX = right.x();
//        checkLine(leftX, rightX, curPoint.y()-1, anchor);
//        leftX = left.x();
//        rightX = right.x();
//        checkLine(leftX, rightX, curPoint.y()+1, anchor);

//    }

//    return poitns;



    StepPoints poitns;
    m_stack.push_back(m_startPoint);
    QPoint curPoint;
    QPoint left, right;
    int anchor;
    while(!m_stack.isEmpty())
    {
        curPoint = m_stack.at(0);

        m_stack.pop_front();
        poitns.push_back(curPoint-QPoint(130,130));
        int x = curPoint.x();
        int y = curPoint.y();
        m_pMatrix[x][y] = true;
        if(!m_pMatrix[x-1][y] && !m_stack.contains(QPoint(x-1,y))) m_stack.push_back(QPoint(x-1,y));
        if(!m_pMatrix[x+1][y] && !m_stack.contains(QPoint(x+1,y))) m_stack.push_back(QPoint(x+1,y));
        if(!m_pMatrix[x][y-1] && !m_stack.contains(QPoint(x,y-1))) m_stack.push_back(QPoint(x,y-1));
        if(!m_pMatrix[x][y+1] && !m_stack.contains(QPoint(x,y+1))) m_stack.push_back(QPoint(x,y+1));

    }

    return poitns;

}

bool CAlgorithmLineFilling::nextStep()
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

StepPoints CAlgorithmLineFilling::getStepDrawPoint()
{
    StepPoints points;
    //points <<m_resultPoints.first();
    m_curPoint = m_resultPoints.at(0);
    points.push_back(m_curPoint);
    m_resultPoints.pop_front();
    return points;
}

void CAlgorithmLineFilling::reset()
{
    m_bBeginState = true;
}

QString CAlgorithmLineFilling::getInfo()
{
    return QString("(%1,%2)").arg(m_curPoint.x()).arg(m_curPoint.y());
}



QString CAlgorithmLineFilling::getInitInfo()
{
    return m_sInitInfo;
}

StepPoints CAlgorithmLineFilling::getMainPoints()
{
    StepPoints points;
    return points;
}

void CAlgorithmLineFilling::setMatrix(bool **matrix)
{
    if(matrix!=NULL)
        m_pMatrix = matrix;
}


void CAlgorithmLineFilling::setStartPoint(QPoint pos)
{
    m_startPoint = pos;
}



void CAlgorithmLineFilling::fillLine(QPoint start, QPoint &leftBorder, QPoint &rigthBorder, QVector<QPoint> &result)
{
    int y = start.y();
    int x = start.x();
    result.push_back(start-QPoint(130,130));
    m_pMatrix[x][y] = true;
    while(!m_pMatrix[x-1][y] && x>20)
    {
        x--;
        result.push_back(QPoint(x,y)-QPoint(130,130));
        m_pMatrix[x][y] = true;
    }

    leftBorder = QPoint(x,y);
    x = start.x();
    while(!m_pMatrix[x+1][y] && x<220)
    {
        x++;
        result.push_back(QPoint(x,y)-QPoint(130,130));
        m_pMatrix[x][y] = true;
    }
    rigthBorder = QPoint(x,y);
}


bool CAlgorithmLineFilling::checkLine(int &leftX, int &rightX, int y, int &anchor)
{
    bool newPart = true;
    for(int i=leftX; i<=rightX; i++)
    {
        if(m_pMatrix[i][y])
        {
            newPart = true;
        }
        else
        {
            if(newPart)
            {
                newPart = false;
                m_stack.push_back(QPoint(i,y));
            }
        }
    }
    return false;
}
