#include "algorithmround.h"

CAlgorithmRound::CAlgorithmRound(QPoint center, int radius)
    : m_center(center), m_radius(radius)
{
    _init();
}


void CAlgorithmRound::_init()
{
    m_x = 0;
    m_y = m_radius;
    m_limit = 0;
    m_delta = 2 - 2 * m_radius;
    m_currentStep = 0;
    m_bFirstStep = true;
}



void CAlgorithmRound::reset()
{
    _init();
}


QString CAlgorithmRound::getInfo()
{
    return "";
}


QString CAlgorithmRound::getInitInfo()
{
    return m_sInitInfo;
}


void CAlgorithmRound::caseA()
{
    m_sigma = 2 * m_delta + 2 * m_y - 1;
    if(m_sigma<=0)
    {
        m_x++;
        m_delta+=(2*m_x+1);
    }
    else{
        caseV();
    }
}

void CAlgorithmRound::caseB()
{
    m_sigma = 2 * m_delta - 2 * m_x - 1;
    if(m_sigma<=0)
    {
        caseV();
    }
    else{
        m_y--;
        m_delta += (-2 * m_y + 1);
    }
}

void CAlgorithmRound::caseV()
{
    m_x++;
    m_y--;
    m_delta +=( - 2 * m_y + 2* m_x + 2);
}

StepPoints CAlgorithmRound::getStepDrawPoint()
{
    StepPoints array;

    if(m_bFirstStep)
    {
        m_bFirstStep = false;
        array.push_back(m_center+QPoint(0,m_radius));
        array.push_back(m_center+QPoint(0,-m_radius));
        //array.push_back(m_center+QPoint(0,-m_radius));
        //array.push_back(m_center+QPoint(-m_radius,0));
    }
    else
    {
        array.push_back(m_center+QPoint( m_x,  m_y));
        array.push_back(m_center+QPoint(-m_x,  m_y));
        array.push_back(m_center+QPoint( m_x, -m_y));
        array.push_back(m_center+QPoint(-m_x, -m_y));

    }



    return array;
}

StepPoints CAlgorithmRound::getDrawPoints()
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



CAlgorithmRound::~CAlgorithmRound()
{

}


bool CAlgorithmRound::nextStep()
{
    if(m_bFirstStep)
    {
        //m_bFirstStep = false;
        m_currentPoint = QPoint(m_x, m_y);
        return true;
    }

    if(m_y<=m_limit)
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



void CAlgorithmRound::setRadius(int radius)
{
    if(radius<0) return;
    m_radius = radius;
    reset();
}


void CAlgorithmRound::setCenterPoint(QPoint pos)
{
    m_center = pos;
    reset();
}


StepPoints CAlgorithmRound::getMainPoints()
{
    StepPoints points;
    points << m_center << QPoint(m_center+QPoint(0,m_radius));
    return points;
}
