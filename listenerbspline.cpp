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
    if(m_pAlgorithm!=NULL) delete m_pAlgorithm;
    m_pAlgorithm = new CAlgorithmBSpline();
    m_bMoveModeEnable = false;
    m_clickPoints.clear();
    m_movePointIndex = 0;
    m_movePointPos = QPoint(-500,-500);
}


CListenerBSpline::~CListenerBSpline()
{

}

void CListenerBSpline::mouseMoveEvent(QPoint pos)
{
    if(m_mouseClickState == MCS_PRESS)
    {
        // смотрим есть ли у нас точка в этой позиции
        if(!m_clickPoints.contains(m_movePointPos))
            return;
        if(m_clickPoints.count(m_movePointPos)==1)
        {
            m_movePointIndex = m_clickPoints.indexOf(m_movePointPos);
        }
        else
        {
            for(int i=0; i<m_clickPoints.size(); i++)
            {
                if (m_clickPoints.at(i) == m_movePointPos)
                    m_movePointIndex = i;
            }
        }

        m_mouseClickState = MCS_MOVE;
        m_clickPoints.replace(m_movePointIndex, pos);

        update();
    }
    if(m_mouseClickState == MCS_MOVE)
    {
        m_clickPoints.replace(m_movePointIndex, pos);
        update();
    }
}


void CListenerBSpline::mousePressEvent(QPoint pos)
{
    m_mouseClickState = MCS_PRESS;
    m_movePointPos = pos;
    qDebug() << pos;
}


void CListenerBSpline::mouseReleaseEvent(QPoint pos)
{

    if(m_mouseClickState == MCS_MOVE)
    {

        m_clickPoints.replace(m_movePointIndex, pos);
        m_mouseClickState = MCS_RELEASE;

        return;
        update();
    }

    m_mouseClickState = MCS_RELEASE;
    qDebug() << pos;
    if(!m_clickPoints.empty())
        if( m_clickPoints.last() == pos )
            return;
    m_clickPoints.push_back(pos);
    drawSpline();
}

void CListenerBSpline::reset()
{
    //initialize();
    m_mouseClickState = MCS_UNDEFINED;
    fixTmpObject();
    clearTmpObject();
    if(m_mode == MODE_DEBUG)
    {
        m_pDebugModeBox->fix();
        m_pDebugModeBox->clear();
    }


    m_bMoveModeEnable = false;
    m_clickPoints.clear();
}


void CListenerBSpline::modeChanged(Mode mode, Mode oldMode)
{

}


void CListenerBSpline::drawDebugSpline(QVector<QPoint> points)
{
    clearTmpObject();
    m_pAlgorithm->reset();
    m_pAlgorithm->clearPoints();
    m_pAlgorithm->addPoints(points);
    if(points.size()<4) return;

    m_pDebugModeBox->setData(this->m_pAlgorithm,m_pCoordinateView,m_mainColor, m_secondaryColor);
}


void CListenerBSpline::drawNormalSpline(QVector<QPoint> points)
{
    m_pAlgorithm->reset();
    m_pAlgorithm->clearPoints();
    m_pAlgorithm->addPoints(points);


    //CPainter::drawBSpline(m_pCoordinateView, m_pAlgorithm, mainColor(), secondaryColor(),hightlightMainPoints());

    drawTempoparySpline(points);

}

void CListenerBSpline::drawSpline()
{
    switch(m_mode)
    {
    case MODE_DEBUG:
        drawDebugSpline(m_clickPoints);
        break;
    case MODE_NORMAL:
        drawNormalSpline(m_clickPoints);
        break;
    default:
        qCritical() << "void CListenerBSpline::drawSpline() undef value in switch ";
        break;
    }

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
        //QColor color = m_mainColor;
        //color.setAlpha(100);
        m_tmpUndoStack.push(new CChangeCellColorCommand(m_pCoordinateView,point.x(),point.y(),mainColor()));
    }


    //if(!hightlightMainPoints())
    //    return;

    StepPoints mainPoints = m_pAlgorithm->getMainPoints();
    QPoint curPoint;
    while(!mainPoints.isEmpty())
    {
        curPoint = mainPoints.at(0);
        mainPoints.pop_front();
        m_tmpUndoStack.push(new CChangeCellColorCommand(m_pCoordinateView,curPoint.x(),curPoint.y(),m_secondaryColor));
    }
}



void CListenerBSpline::update()
{
    clearTmpObject();
    if( m_mode == MODE_DEBUG )
    {
        m_pDebugModeBox->clear();
        drawDebugSpline(m_clickPoints);
        return;
    }
    drawTempoparySpline(m_clickPoints);

}

void CListenerBSpline::setHightlightMainPoints(bool enable)
{
    m_bHighlightMainPoints = true;
}
