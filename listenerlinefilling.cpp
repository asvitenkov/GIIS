#include "listenerlinefilling.h"

CListenerLineFilling::CListenerLineFilling(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor)
    :CAbstractListener(view, box,mainColor, secondaryColor)
{
    m_sListenerName = "line filling";
    initialize();
}

CListenerLineFilling::~CListenerLineFilling()
{

}


void CListenerLineFilling::mouseMoveEvent(QPoint pos)
{

}

void CListenerLineFilling::mousePressEvent(QPoint pos)
{
    m_clickPos = pos;
    fillingArea();
}


//void CListenerLineFilling::mouseReleaseEvent(QPoint pos)
//{

//}



void CListenerLineFilling::modeChanged(Mode mode, Mode oldMode)
{

}


void CListenerLineFilling::reset()
{

}


void CListenerLineFilling::fillingArea()
{
    switch(m_mode)
    {
    case MODE_NORMAL:
        fillingAreaNormal();
        break;
    case MODE_DEBUG:
        fillingAreaDebug();
        break;
    }
}


void CListenerLineFilling::fillingAreaDebug()
{
    m_pAlgorithm->reset();
    m_pAlgorithm->setStartPoint(m_clickPos+QPoint(130,130));
    updateMatrix();
    m_pAlgorithm->setMatrix(m_pMatrix);

    m_pDebugModeBox->setData(m_pAlgorithm, m_pCoordinateView,m_secondaryColor, m_mainColor);
}

void CListenerLineFilling::fillingAreaNormal()
{
    m_pAlgorithm->reset();
    m_pAlgorithm->setStartPoint(m_clickPos+QPoint(130,130));
    updateMatrix();
    m_pAlgorithm->setMatrix(m_pMatrix);
    StepPoints points = m_pAlgorithm->getDrawPoints();
    while(!points.isEmpty())
    {
        m_pCoordinateView->setCellColor((points.first()),m_secondaryColor);
        points.pop_front();
    }
}

void CListenerLineFilling::initialize()
{
    CAbstractListener::initialize();
    m_pAlgorithm = new CAlgorithmLineFilling();
    m_pMatrix = new bool *[260];
    for(int i=0; i<260; i++)
        m_pMatrix[i] = new bool [260];
}


void CListenerLineFilling::updateMatrix()
{
     m_pCoordinateView->getBoolMatrix(m_pMatrix, m_pCoordinateView->cellColor(m_clickPos.x(), m_clickPos.y()));
//     for(int i=0; i<260; i++)
//         for(int j=0; j<260; j++)
//             if(m_pMatrix[i][j]==true)
//             {
//                 m_pCoordinateView->setCellColor(QPoint(i-130,j-130),QColor(Qt::red));

//                 qDebug() << "ppp "<<QPoint(i,j);
//             }
}
