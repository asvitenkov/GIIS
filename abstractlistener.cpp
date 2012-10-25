#include "abstractlistener.h"

CAbstractListener::CAbstractListener(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor)
    :m_pDebugModeBox(box), m_mainColor(mainColor), m_SecondaryColor(secondaryColor), m_pCoordinateView(view)
{

}



void CAbstractListener::initialize()
{
    m_mode = MODE_NORMAL;
    m_mouseClickState = MCS_UNDEFINED;
}


void CAbstractListener::setDebugModeEnable()
{
    Mode oldMode = m_mode;
    m_mode = MODE_DEBUG;
    modeChanged(m_mode,oldMode);
}


void CAbstractListener::setNormalModeEnable()
{
    Mode oldMode = m_mode;
    m_mode = MODE_NORMAL;
    modeChanged(m_mode,oldMode);
}


void CAbstractListener::setMainColor(QColor color)
{
    m_mainColor = color;
}

void CAbstractListener::setSecondaryColor(QColor color)
{
    m_SecondaryColor = color;
}


CAbstractListener::~CAbstractListener()
{

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
