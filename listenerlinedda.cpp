#include "listenerlinedda.h"

CListenerLineDDA::CListenerLineDDA(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor)
    :CAbstractLineListener(view, box, mainColor, secondaryColor)
{
    m_sListenerName = "Listener DDA";
    initialize();
}



void CListenerLineDDA::initialize()
{
    CAbstractLineListener::initialize();
    m_pAlgorithm = new CAlgorithmDDA(m_startPos, m_endPos);
}
