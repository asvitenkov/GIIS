#include "abstractlistener.h"

CAbstractListener::CAbstractListener(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor)
    :m_pDebugModeBox(box), m_mainColor(mainColor), m_secondaryColor(secondaryColor), m_pCoordinateView(view)
{

}



void CAbstractListener::initialize()
{
    m_mode = MODE_NORMAL;
    m_mouseClickState = MCS_UNDEFINED;
}


void CAbstractListener::setMode(Mode mode)
{
    Mode oldMode = m_mode;
    m_mode = mode;
    modeChanged(m_mode,oldMode);
}

void CAbstractListener::setMainColor(QColor color)
{
    m_mainColor = color;
}

void CAbstractListener::setSecondaryColor(QColor color)
{
    m_secondaryColor = color;
}


CAbstractListener::~CAbstractListener()
{
    qDebug() << "CAbstractListener::~CAbstractListener()";
}


void CAbstractListener::clearTmpObject()
{
    while(m_tmpUndoStack.canUndo())
        m_tmpUndoStack.undo();
    m_tmpUndoStack.clear();
}


void CAbstractListener::fixTmpObject()
{
    while(m_tmpUndoStack.canRedo())
        m_tmpUndoStack.redo();
    m_tmpUndoStack.clear();
}


QString CAbstractListener::name()
{
    return m_sListenerName;
}


QColor CAbstractListener::mainColor()
{
    return m_mainColor;
}


QColor CAbstractListener::secondaryColor()
{
    if(m_bHighlightMainPoints)
        return m_secondaryColor;
    return m_mainColor;
}



void CAbstractListener::setHightlightMainPoints(bool enable)
{
   m_bHighlightMainPoints = enable;
}


bool CAbstractListener::hightlightMainPoints()
{
    return m_bHighlightMainPoints;
}
