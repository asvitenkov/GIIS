#include "listenerparabola.h"

CListenerParabola::CListenerParabola(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor)
    :CAbstractListener(view,box,mainColor,secondaryColor)
{
    m_sListenerName = "Listener parabola algorithm";
    m_pAlgorithm = NULL;
    this->initialize();

}

void CListenerParabola::initialize()
{
    CAbstractListener::initialize();

    m_p = 1;
    m_centerPoint = QPoint(0,0);
    m_bHighlightMainPoints = false;
    m_mode = MODE_NORMAL;
    if(m_pAlgorithm!=NULL) delete m_pAlgorithm;
    m_pAlgorithm = new CAlgorithmParabola(m_centerPoint, m_p);

}


void CListenerParabola::mouseMoveEvent(QPoint pos)
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
        drawTemporaryParabola(m_centerPoint,-m_centerPoint.y() + pos.y());
        break;
    }
}

void CListenerParabola::mousePressEvent(QPoint pos)
{
    switch(m_mouseClickState)
    {
    case MCS_UNDEFINED:
        m_mouseClickState = MCS_FIRST_CLICK;
        m_centerPoint = pos;
        m_p = 1;
        m_pDebugModeBox->fix();
        break;
    case MCS_FIRST_CLICK:
        m_p = - m_centerPoint.y()+pos.y();
        m_mouseClickState = MCS_UNDEFINED;
        clearTmpObject();
        drawParabola();
        break;
    default:
        qCritical() << "void CListenerParabola::mousePressEvent(QPoint pos) undef value in switch ";
    }
}


void CListenerParabola::reset()
{
    m_mouseClickState = MCS_UNDEFINED;
    clearTmpObject();
    if(m_mode == MODE_DEBUG)
    {
        m_pDebugModeBox->fix();
        m_pDebugModeBox->clear();
    }
}

void CListenerParabola::modeChanged(Mode mode, Mode oldMode)
{
    m_mouseClickState = MCS_UNDEFINED;
    clearTmpObject();
    if(m_mode == MODE_DEBUG)
    {
        m_pDebugModeBox->fix();
        m_pDebugModeBox->clear();
    }
}


CListenerParabola::~CListenerParabola()
{

}

void CListenerParabola::drawParabola()
{
    switch(m_mode)
    {
    case MODE_DEBUG:
        drawDebugParabola(m_centerPoint,m_p);
        break;
    case MODE_NORMAL:
        drawNormalParabola(m_centerPoint, m_p);
        break;
    default:
        qCritical() << "void CListenerParabola::drawParabola()undef value in switch ";
        break;
    }
}


void CListenerParabola::drawNormalParabola(QPoint center, int pValue)
{
    m_pAlgorithm->setCenterPoint(center);
    m_pAlgorithm->setPValue(pValue);

    CPainter::drawParabola(m_pCoordinateView,m_pAlgorithm,m_centerPoint,m_mainColor,m_secondaryColor);
}

void CListenerParabola::drawTemporaryParabola(QPoint center, int pValue)
{
    m_pAlgorithm->setCenterPoint(center);
    m_pAlgorithm->setPValue(pValue);

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


void CListenerParabola::drawDebugParabola(QPoint center, int pValue)
{
    clearTmpObject();
    this->m_pAlgorithm->setCenterPoint(center);
    this->m_pAlgorithm->setPValue(pValue);
    m_pDebugModeBox->setData(this->m_pAlgorithm,m_pCoordinateView,m_mainColor);
}
