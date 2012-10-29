#include "algorithmparabola.h"


CAlgorithmParabola::CAlgorithmParabola(QPoint center, int pValue)
    : m_center(center), m_p(pValue)
{
    _init();
    m_bIsRevert = false;
}


void CAlgorithmParabola::_init()
{
    m_x = 0;
    m_y = 0;
    m_limit = 30;
    m_delta =(qAbs(m_p)-1);
    m_currentStep = 0;
    m_bFirstStep = true;


    m_sInitInfo.clear();
    m_sInitInfo+=QString("center = (%1,%2)\n").arg(m_center.x()).arg(m_center.y());
    m_sInitInfo+=QString("p = %1").arg(qAbs(m_p));
}



void CAlgorithmParabola::reset()
{
    _init();
}


QString CAlgorithmParabola::getInfo()
{
    QString res;
    res+=QString("delta = %1\n").arg(m_delta);
    return res;
}


QString CAlgorithmParabola::getInitInfo()
{
    return m_sInitInfo;
}


void CAlgorithmParabola::caseA()
{
    m_sigma = qAbs(deltaH(QPoint(m_x,m_y)))-qAbs(deltaD(QPoint(m_x,m_y)));
    if(m_sigma<=0)
    {
        m_x++;
        m_delta+= 2* qAbs(m_p);
    }
    else{
        caseV();
    }
}

void CAlgorithmParabola::caseB()
{
    m_sigma = 2 * m_delta - 2 * m_x - 1;
    if(m_sigma<=0)
    {
        caseV();
    }
    else{
        m_y++;
        m_delta -=(2*m_y +1);
    }
}

void CAlgorithmParabola::caseV()
{
    m_x++;
    m_y++;

    m_delta+=( 2*(qAbs(m_p) - m_y) -1);
}

StepPoints CAlgorithmParabola::getStepDrawPoint()
{
    StepPoints array;

    if(m_bFirstStep)
    {
        m_bFirstStep = false;
        array.push_back(m_center+QPoint(0,0));
    }
    else
    {

    }
    if(!m_bIsRevert)
    {
        array.push_back(m_center+QPoint( m_y,  m_x));
        array.push_back(m_center+QPoint( -m_y,  m_x));
    }
    else
    {
        array.push_back(m_center+QPoint( m_y,  -m_x));
        array.push_back(m_center+QPoint( -m_y,  -m_x));
    }
    return array;
}

StepPoints CAlgorithmParabola::getDrawPoints()
{
    reset();
    StepPoints points;
    StepPoints stepPoints;
    while(nextStep())
    {
        stepPoints = getStepDrawPoint();
        ADD_STEP_POINTS(stepPoints,points);
    }
    return points;
}



CAlgorithmParabola::~CAlgorithmParabola()
{

}


bool CAlgorithmParabola::nextStep()
{
    if(m_bFirstStep)
    {
        m_currentPoint = QPoint(m_x, m_y);
        return true;
    }

    if(m_x>=m_limit)
        return false;

    if(m_delta<0)
    {
        caseA();
    }
    else
    {
        if(m_delta>0)
        {
            caseB();
        }
        else{
            caseV();
        }
    }


    return true;


}



void CAlgorithmParabola::setPValue(int pVal)
{
    if(pVal<0)
    {
        m_bIsRevert = true;
    }
    else
    {
        m_bIsRevert = false;
    }
    m_p = pVal;
    qDebug() << "pVel= "<<pVal;
    //reset();
}


void CAlgorithmParabola::setCenterPoint(QPoint pos)
{
    m_center = pos;
    //reset();
}


int CAlgorithmParabola::deltaD(QPoint point)
{
    return (2*qAbs(m_p)*(point.x()+1)-(point.y()+1)*(point.y()+1));
}

int CAlgorithmParabola::deltaV(QPoint point)
{
    return (2*qAbs(m_p)*(point.x())-(point.y()+1)*(point.y()+1));
}

int CAlgorithmParabola::deltaH(QPoint point)
{
    return (2*qAbs(m_p)*(point.x()+1)-(point.y())*(point.y()));
}



StepPoints CAlgorithmParabola::getMainPoints()
{
    StepPoints points;
    points << m_center << QPoint(m_center + QPoint(0,m_p));
    return points;
}
