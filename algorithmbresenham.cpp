#include "algorithmbresenham.h"

CAlgorithmBresenham::CAlgorithmBresenham(QPoint startPoint, QPoint endPoint)
    : CAbstractLinePaintAlgorithm(startPoint, endPoint)
{
    _init();
}

void CAlgorithmBresenham::_init()
{
    int nTmp;
    m_curPoint = m_startPoint;
    m_nDx = qAbs(m_endPoint.x() - m_startPoint.x());
    m_nDy = qAbs(m_endPoint.y() - m_startPoint.y());
    m_nS1 = _sign(m_endPoint.x() - m_startPoint.x());
    m_nS2 = _sign(m_endPoint.y() - m_startPoint.y());

    if(m_nDx < m_nDy)
    {
        nTmp = m_nDx;
        m_nDx = m_nDy;
        m_nDy = nTmp;
        m_nSwap = 1;
    }
    else
    {
        m_nSwap = 0;
    }
    m_nError = 2*m_nDy - m_nDx;
//    m_nError = 0;
    m_bFirstStep = true;
    m_nCurStep = 0;


    m_sInitInfo.clear();
    m_sInitInfo.append("Algorithm Bresenham. Initialize info\n");
    m_sInitInfo.append(QString("Start point (%1,%2)\n").arg(QString::number(m_startPoint.x())).arg(QString::number(m_startPoint.y())));
    m_sInitInfo.append(QString("End point (%1,%2)\n").arg(QString::number(m_endPoint.x())).arg(QString::number(m_endPoint.y())));
    m_sInitInfo.append(QString("dx = %1\n").arg(QString::number(m_nDx)));
    m_sInitInfo.append(QString("dy = %1\n").arg(QString::number(m_nDy)));
    m_sInitInfo.append(QString("swap = %1\n").arg(QString::number(m_nSwap)));
    m_sInitInfo.append(QString("error = %1").arg(QString::number(m_nError)));


}


int CAlgorithmBresenham::_sign(int n)
{
    if(n>0)
        return 1;
    if(n<0)
        return -1;
    return 0;
}

bool CAlgorithmBresenham::nextStep()
{
    if(m_bFirstStep)
    {
        m_bFirstStep = false;
        return true;
    }

    bool bRes = true;
    if(m_nCurStep < m_nDx)
    {

        while(m_nError >= 0)
        {
            if(m_nSwap == 1)
            {
                m_curPoint+=QPointF(m_nS1,0);
            }
            else
            {
                m_curPoint+=QPointF(0,m_nS2);
            }
            m_nError-=2*m_nDx;
        }
        if(m_nSwap == 1)
        {
            m_curPoint+=QPointF(0,m_nS2);
        }
        else
        {
            m_curPoint+=QPointF(m_nS1,0);
        }
        m_nError+=2*m_nDy;
        m_nCurStep++;
    }
    else{
        bRes = false;
    }
    return bRes;

}


StepPoints CAlgorithmBresenham::getStepDrawPoint()
{
    StepPoints points;
    points.push_back(m_curPoint.toPoint());
    return points;
}


void CAlgorithmBresenham::reset()
{
    _init();
}


QString CAlgorithmBresenham::getInfo()
{
    QString resString;
    resString.append(QString("Step %1:\n").arg(QString::number(m_nCurStep)));
    resString.append(QString("  x = %1\n").arg(QString::number(m_curPoint.x())));
    resString.append(QString("  y = %1\n").arg(QString::number(m_curPoint.y())));
    resString.append(QString("  error = %1").arg(QString::number(m_nError)));
    return resString;
}


QString CAlgorithmBresenham::getInitInfo()
{
    return m_sInitInfo;
}

StepPoints CAlgorithmBresenham::getDrawPoints()
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

