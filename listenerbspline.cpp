#include "listenerbspline.h"

CListenerBSpline::CListenerBSpline(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor)
    : CAbstractListener(view, box, mainColor, secondaryColor)
{
    m_sListenerName = "Listener BSpline";
    m_pAlgorithm = NULL;
    initialize();
}



void CListenerBSpline::initialize()
{
    CAbstractListener::initialize();
    m_mouseClickState = MCS_RELEASE;
    m_bHighlightMainPoints = true;
    m_mode = MODE_NORMAL;

    m_bMoveModeEnable = false;
    m_clickPoints.clear();
    m_movePointIndex = 0;
    m_movePointPos = QPoint(-500,-500);
    m_mousePressPos = QPoint(-500,-500);



    if(m_pAlgorithm!=NULL) delete m_pAlgorithm;
    m_pAlgorithm = new CAlgorithmBSpline();
}


CListenerBSpline::~CListenerBSpline()
{
    if(m_pAlgorithm!=NULL) delete m_pAlgorithm;
}

void CListenerBSpline::mouseMoveEvent(QPoint pos)
{

    if(m_mouseClickState == MCS_RELEASE)
    {
        // попытаться словить точку и достроить сплайн
    }

    if(m_mouseClickState == MCS_PRESS)
    {

        // смотрим, было ли нажатие на какую то главную точку
            if(m_clickPoints.contains(m_mousePressPos))
            {
                int index = 0;
                for(int i=0; i<m_clickPoints.size(); i++)
                    if(m_clickPoints.at(i)==m_mousePressPos)
                        index = i;
                m_mouseClickState = MCS_MOVE;
                m_movePointIndex = index;
                m_movePointPos = pos;

                m_clickPoints.replace(m_movePointIndex, pos);
                update(m_clickPoints);
            }
    }
    if(m_mouseClickState== MCS_MOVE)
    {
        m_clickPoints.replace(m_movePointIndex, pos);
        update(m_clickPoints);
    }
}


void CListenerBSpline::mousePressEvent(QPoint pos)
{
    m_mouseClickState = MCS_PRESS;
    m_mousePressPos = pos;

}


void CListenerBSpline::mouseReleaseEvent(QPoint pos)
{
    if(m_mouseClickState == MCS_MOVE)
    {

    }
    if(m_mouseClickState == MCS_PRESS)
    {
        m_clickPoints.push_back(pos);
    }

    update(m_clickPoints);
    m_mouseClickState = MCS_RELEASE;
}

void CListenerBSpline::reset()
{
    m_pDebugModeBox->fix();
    clearMainPoints();
    m_tmpUndoStack.clear();
    m_clickPoints.clear();

    initialize();
}


void CListenerBSpline::modeChanged(Mode mode, Mode oldMode)
{

}


void CListenerBSpline::drawDebugSpline(QVector<QPoint> points)
{

}


void CListenerBSpline::drawNormalSpline(QVector<QPoint> points)
{


}

void CListenerBSpline::drawSpline()
{



}

void CListenerBSpline::drawTempoparySpline(QVector<QPoint> pointsSpline)
{
    clearTmpObject();
    m_pAlgorithm->reset();
    m_pAlgorithm->clearPoints();
    m_pAlgorithm->addPoints(pointsSpline);

    StepPoints points = m_pAlgorithm->getDrawPoints();
    StepPoints::iterator it;
    QPoint point;
    for(it = points.begin(); it!= points.end(); it++)
    {
        point = *it;
        m_tmpUndoStack.push(new CChangeCellColorCommand(m_pCoordinateView,point.x(),point.y(),m_mainColor));
    }
}



void CListenerBSpline::update(QVector<QPoint> points)
{

    clearMainPoints();
    clearTmpObject();
    if(m_mode == MODE_DEBUG)
    {
        if(points.size()>=4)
        {
            m_pAlgorithm->reset();
            m_pAlgorithm->clearPoints();
            m_pAlgorithm->addPoints(points);
            m_pDebugModeBox->setData(m_pAlgorithm, m_pCoordinateView, m_mainColor, m_secondaryColor);
            updateMainPoints(points);
        }
    }

    if(m_mode == MODE_NORMAL)
    {
        drawTempoparySpline(points);

    }

    m_pDebugModeBox->hideMainPoints();
    updateMainPoints(points);
    m_pDebugModeBox->showMainPoints();

}

void CListenerBSpline::updateMainPoints(QVector<QPoint> points)
{

    for(int i=0; i<points.size(); i++)
    {
        m_tmpUndoStack.push(new CChangeCellColorCommand(m_pCoordinateView,points.at(i), m_secondaryColor));
    }
}

void CListenerBSpline::clearMainPoints()
{
    for(int i=0; i<m_clickPoints.size(); i++)
    {
        m_tmpUndoStack.undo();
    }
}

void CListenerBSpline::setHightlightMainPoints(bool enable)
{
    m_bHighlightMainPoints = true;
}

