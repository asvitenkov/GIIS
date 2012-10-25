#include "algorithmdda.h"





CAlgorithmDDA::CAlgorithmDDA(QPoint startPoint, QPoint endPoint)
    : m_startPoint(startPoint), m_endPoint(endPoint)
{
    _init();
}



void CAlgorithmDDA::_init()
{
    qreal dx = (m_endPoint.x() - m_startPoint.x());
    qreal dy = (m_endPoint.y() - m_startPoint.y());
    m_nLimit = qMax(qAbs(dx),qAbs(dy));
    m_fDx = dx/m_nLimit;
    m_fDy = dy/m_nLimit;
    m_curPoint = m_startPoint;
    m_nStep = 0;

    m_bFirstStep = true;

    m_sInitInfo.clear();
    m_sInitInfo.append("Algorithm DDA. Initialize info\n");
    m_sInitInfo.append(QString("Start point (%1,%2)\n").arg(QString::number(m_startPoint.x())).arg(QString::number(m_startPoint.y())));
    m_sInitInfo.append(QString("End point (%1,%2)\n").arg(QString::number(m_endPoint.x())).arg(QString::number(m_endPoint.y())));
    m_sInitInfo.append(QString("length = %1\n").arg(QString::number(m_nLimit)));
    m_sInitInfo.append(QString("dx = %1\n").arg(QString::number(m_fDx,'f',4)));
    m_sInitInfo.append(QString("dy = %1").arg(QString::number(m_fDy,'f',4)));

}

StepPoints CAlgorithmDDA::getDrawPoints()
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

void CAlgorithmDDA::reset()
{
    _init();
}

bool CAlgorithmDDA::nextStep()
{

    if(m_bFirstStep)
    {
        m_bFirstStep = false;
        return true;
    }
    bool bRes = true;
    if(m_nStep<m_nLimit)
    {
        m_curPoint = QPointF(m_curPoint.x()+m_fDx, m_curPoint.y()+m_fDy);
        m_nStep++;
    }
    else
    {
        bRes = false;
    }
    return bRes;
}

StepPoints CAlgorithmDDA::getStepDrawPoint()
{
    StepPoints points;
    points.push_back(m_curPoint.toPoint());
    return points;
}

QString CAlgorithmDDA::getInfo()
{
    QString resString;
    resString.append(QString("Step %1:\n").arg(QString::number(m_nStep)));
    resString.append(QString("  x = %1\n").arg(QString::number(m_curPoint.x(),'f',4)));
    resString.append(QString("  y = %1\n").arg(QString::number(m_curPoint.y(),'f',4)));
    resString.append(QString("  draw (%1,%2)").arg(QString::number(m_curPoint.toPoint().x())).arg(QString::number(m_curPoint.toPoint().y())));
    return resString;
}


QString CAlgorithmDDA::getInitInfo()
{
    return m_sInitInfo;
}


void CAlgorithmDDA::setEndPos(QPoint pos)
{
    m_endPoint = pos;
}


void CAlgorithmDDA::setStartPos(QPoint pos)
{
    m_startPoint = pos;
}
