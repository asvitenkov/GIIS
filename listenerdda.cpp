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
