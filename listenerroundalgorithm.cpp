#include "listenerroundalgorithm.h"

CListenerRoundAlgorithm::CListenerRoundAlgorithm(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor)
    :CAbstractListener(view,box,mainColor,secondaryColor)
{
    m_sListenerName = "Listener round algorithm";
    m_pAlgorithm = NULL;
    this->initialize();
}

void CListenerRoundAlgorithm::initialize()
{
    CAbstractListener::initialize();

    m_radius = 0;
    m_centerPoint = QPoint(0,0);
    m_bHighlightMainPoints = false;
    m_mode = MODE_NORMAL;
    if(m_pAlgorithm!=NULL) delete m_pAlgorithm;
    m_pAlgorithm = new CAlgorithmRound(m_centerPoint,m_radius);

}


void CListenerRoundAlgorithm::mouseMoveEvent(QPoint pos)
{
    //m_radius = distance(m_centerPoint,pos);

    switch (m_mouseClickState)
    {
    case MCS_UNDEFINED:
        return;

        break;
    case MCS_FIRST_CLICK:
        // удаляем старый временный объект
        clearTmpObject();
        // рисуется новый временный объект
        drawTemporaryRound(m_centerPoint, distance(m_centerPoint,pos));
        break;
    }
}

void CListenerRoundAlgorithm::mousePressEvent(QPoint pos)
{
    switch(m_mouseClickState)
    {
    case MCS_UNDEFINED:
        m_mouseClickState = MCS_FIRST_CLICK;
        m_centerPoint = pos;
        m_radius = 0;
        m_pDebugModeBox->fix();
        break;
    case MCS_FIRST_CLICK:
        m_radius = distance(m_centerPoint,pos);
        m_mouseClickState = MCS_UNDEFINED;
        clearTmpObject();
        drawRound();
        break;
    default:
        qCritical() << "void CListenerRoundAlgorithm::mousePressEvent(QPoint pos) undef value in switch ";
    }
}


void CListenerRoundAlgorithm::reset()
{
    m_mouseClickState = MCS_UNDEFINED;
    clearTmpObject();
    if(m_mode == MODE_DEBUG)
    {
        m_pDebugModeBox->fix();
        m_pDebugModeBox->clear();
    }
}

void CListenerRoundAlgorithm::modeChanged(Mode mode, Mode oldMode)
{
    m_mouseClickState = MCS_UNDEFINED;
    clearTmpObject();
    if(m_mode == MODE_DEBUG)
    {
        m_pDebugModeBox->fix();
        m_pDebugModeBox->clear();
    }
}


CListenerRoundAlgorithm::~CListenerRoundAlgorithm()
{

}

void CListenerRoundAlgorithm::drawRound()
{
    switch(m_mode)
    {
    case MODE_DEBUG:
        drawDebugRound(m_centerPoint,m_radius);
        break;
    case MODE_NORMAL:
        drawNormalRound(m_centerPoint, m_radius);
        break;
    default:
        qCritical() << "CListenerRoundAlgorithm::drawRound() undef value in switch ";
        break;
    }
}


void CListenerRoundAlgorithm::drawNormalRound(QPoint center, int radius)
{
    m_pAlgorithm->setCenterPoint(center);
    m_pAlgorithm->setRadius(radius);

    CPainter::drawRound(m_pCoordinateView,m_pAlgorithm,m_centerPoint,mainColor(),secondaryColor(),hightlightMainPoints());
}

void CListenerRoundAlgorithm::drawTemporaryRound(QPoint center, int radius)
{
    m_pAlgorithm->setRadius(radius);
    m_pAlgorithm->setCenterPoint(center);

    StepPoints points = m_pAlgorithm->getDrawPoints();
    StepPoints::iterator it;
    QPoint point;
    for(it = points.begin(); it!= points.end(); it++)
    {
        point = *it;
        QColor color = m_mainColor;
        color.setAlpha(100);
        m_tmpUndoStack.push(new CChangeCellColorCommand(m_pCoordinateView,point.x(),point.y(),color));
    }
}


void CListenerRoundAlgorithm::drawDebugRound(QPoint center, int radius)
{
    clearTmpObject();
    m_pAlgorithm->setCenterPoint(center);
    m_pAlgorithm->setRadius(radius);
    m_pDebugModeBox->setData(m_pAlgorithm,m_pCoordinateView,mainColor(), m_secondaryColor);
}


int CListenerRoundAlgorithm::distance(QPoint start, QPoint end)
{
    QPoint r = start - end;
    return sqrt(pow(r.x(),2)+pow(r.y(),2));
}
