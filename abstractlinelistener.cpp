#include "abstractlinelistener.h"

CAbstractLineListener::CAbstractLineListener(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor)
    :CAbstractListener(view, box, mainColor, secondaryColor)
{m_sListenerName = "Listener DDA";
    initialize();
}

void  CAbstractLineListener::initialize()
{
    CAbstractListener::initialize();
    m_startPos = QPoint(0,0);
    m_endPos = QPoint(0,0);
    m_mode = MODE_NORMAL;
    this->m_pAlgorithm = new CAlgorithmDDA(m_startPos, m_endPos);
}

void CAbstractLineListener::mouseMoveEvent(QPoint pos)
{
    //qDebug() << "mouse move to" << pos;

    switch (m_mouseClickState)
    {
    case MCS_UNDEFINED:
        return;

        break;
    case MCS_FIRST_CLICK:
        // удаляем старый временный объект
        clearTmpObject();
        // рисуется новый временный объект
        drawTemporaryLine(m_startPos, pos);
        break;
    }
}


void CAbstractLineListener::mousePressEvent(QPoint pos)
{
    qDebug() << "mouse press at pos" << pos ;
    switch(m_mouseClickState)
    {
    case MCS_UNDEFINED:
        m_mouseClickState = MCS_FIRST_CLICK;
        m_startPos = pos;
        m_endPos = pos;
        m_pDebugModeBox->fix();
        break;
    case MCS_FIRST_CLICK:
        m_endPos = pos;
        m_mouseClickState = MCS_UNDEFINED;
        clearTmpObject();
        drawLine();
        break;
    default:
        qCritical() << "CAbstractLineListener::mousePressEvent(QPoint pos) undef value in switch ";
        break;
    }
}


void CAbstractLineListener::modeChanged(Mode mode, Mode oldMode)
{
    qDebug() << "mode Changed";
    m_mouseClickState = MCS_UNDEFINED;
    clearTmpObject();
    if(oldMode == MODE_DEBUG)
    {
        m_pDebugModeBox->fix();
        m_pDebugModeBox->clear();
    }
}

CAbstractLineListener::~CAbstractLineListener()
{
    qDebug() << "CAbstractLineListener::~CAbstractLineListener()";
}


void CAbstractLineListener::reset()
{
    m_mouseClickState = MCS_UNDEFINED;
    clearTmpObject();
    if(m_mode == MODE_DEBUG)
    {
        m_pDebugModeBox->fix();
        m_pDebugModeBox->clear();
    }
}



void CAbstractLineListener::drawLine()
{
    switch(m_mode)
    {
    case MODE_DEBUG:
        drawDebugLine(m_startPos,m_endPos);
        break;
    case MODE_NORMAL:
        drawNormalLine(m_startPos, m_endPos);
        break;
    default:
        qCritical() << "ListenerDDA::drawLine() undef value in switch ";
        break;
    }
}


void CAbstractLineListener::drawNormalLine(QPoint start, QPoint end)
{
    this->m_pAlgorithm->setStartPos(start);
    this->m_pAlgorithm->setEndPos(end);
    CPainter::drawLine(m_pCoordinateView,this->m_pAlgorithm,start,end,m_mainColor,m_SecondaryColor);
}


void CAbstractLineListener::drawDebugLine(QPoint start, QPoint end)
{
    clearTmpObject();
    this->m_pAlgorithm->setStartPos(start);
    this->m_pAlgorithm->setEndPos(end);
    m_pDebugModeBox->setData(this->m_pAlgorithm,m_pCoordinateView,m_mainColor);
}

void CAbstractLineListener::drawTemporaryLine(QPoint start, QPoint end)
{
    this->m_pAlgorithm->setStartPos(start);
    this->m_pAlgorithm->setEndPos(end);

    StepPoints points = this->m_pAlgorithm->getDrawPoints();
    StepPoints::iterator it;
    QPoint point;
    for(it = points.begin(); it!=points.end(); it++)
    {
        point = *it;
        QColor color = m_mainColor;
        color.setAlpha(100);
        m_tmpUndoStack.push(new CChangeCellColorCommand(m_pCoordinateView,point.x(),point.y(),color));
    }
}
