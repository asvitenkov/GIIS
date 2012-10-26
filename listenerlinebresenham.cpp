#include "listenerlinebresenham.h"

CListenerLineBresenham::CListenerLineBresenham(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor)
    :CAbstractLineListener(view, box, mainColor, secondaryColor)
{
    m_sListenerName = "Listener Bresenham";
    initialize();
}

void CListenerLineBresenham::initialize()
{
    CAbstractLineListener::initialize();
    m_pAlgorithm = new CAlgorithmDDA(m_startPos, m_endPos);
}
