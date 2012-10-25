#include "listenerdda.h"

CListenerDDA::CListenerDDA(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor)
    :CAbstractListener(view, box, mainColor, secondaryColor)
{
    initialize();
}

void  CListenerDDA::initialize()
{
    CAbstractListener::initialize();
    m_startPos = QPoint(0,0);
    m_endPos = QPoint(0,0);
}

void CListenerDDA::mouseMoveEvent(QPoint pos)
{
    qDebug() << "mouse move to" << pos;
}


void CListenerDDA::mousePressEvent(QPoint pos)
{
    qDebug() << "mouse press at pos" << pos ;
    switch(m_mouseClickState)
    {
    case MCS_UNDEFINED:
        m_mouseClickState = MCS_FIRST_CLICK;
        m_startPos = pos;
        break;
    case MCS_FIRST_CLICK:
        m_endPos = pos;
        m_mouseClickState = MCS_UNDEFINED;
        break;
    default:
        qDebug() << "CListenerDDA::mousePressEvent(QPoint pos) undef value in switch ";
        break;
    }
}


void CListenerDDA::modeChanged(Mode mode, Mode oldMode)
{
    qDebug() << "mode Changed";
}


void CListenerDDA::clearTmpObject()
{
    qDebug() << "clear temporary object";
}

CListenerDDA::~CListenerDDA()
{

}

void CListenerDDA::fixTmpObject()
{

}



void CListenerDDA::reset()
{

}



void CListenerDDA::drawLine()
{

}


void CListenerDDA::drawNormalLine(QPoint start, QPoint end)
{

}


void CListenerDDA::drawDebugLine(QPoint start, QPoint end)
{

}
