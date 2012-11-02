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

    reset();

    StepPoints poitns;
    m_stack.push_back(m_startPoint);
    QPoint curPoint;
    QPoint left, right;
    int anchor;
    while(!m_stack.isEmpty())
    {
        curPoint = m_stack.pop();
        fillLine(curPoint,left, right, poitns);
        int leftX,rightX;
        leftX = left.x();
        rightX = right.x();
        if(checkLine(leftX, rightX, curPoint.y()-1, anchor))
        {
            m_stack.push_back(QPoint(anchor, curPoint.y()-1));
        }
        leftX = left.x();
        rightX = right.x();
        if(checkLine(leftX, rightX, curPoint.y()+1, anchor))
        {
            m_stack.push_back(QPoint(anchor, curPoint.y()+1));
        }

    }

    return poitns;
}

bool CAlgorithmLineFilling::nextStep()
{

}

StepPoints CAlgorithmLineFilling::getStepDrawPoint()
{

}

void CAlgorithmLineFilling::reset()
{

}

QString CAlgorithmLineFilling::getInfo()
{
    return "";
}



QString CAlgorithmLineFilling::getInitInfo()
{
    return m_sInitInfo;
}

StepPoints CAlgorithmLineFilling::getMainPoints()
{

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
    result.push_back(start);
    m_pMatrix[x][y] = true;
    while(!m_pMatrix[x-1][y] && x>0)
    {
        x--;
        result.push_back(QPoint(x,y));
        m_pMatrix[x][y] = true;
    }

    leftBorder = QPoint(x,y);
    x = start.x();
    while(!m_pMatrix[x+1][y] && x<260)
    {
        x++;
        result.push_back(QPoint(x,y));
        m_pMatrix[x][y] = true;
    }
    rigthBorder = QPoint(x,y);
}


bool CAlgorithmLineFilling::checkLine(int &leftX, int &rightX, int y, int &anchor)
{
    for(int i=leftX; i<=rightX; i++)
    {
        if(m_pMatrix[i][y]==false)
        {
            anchor = i;
            return true;

        }
    }
    return false;
}
