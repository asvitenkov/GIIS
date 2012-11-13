#include "listenervertexlinefilling.h"

CListenerVertexLineFilling::CListenerVertexLineFilling(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor)
    :CAbstractListener(view, box,mainColor, secondaryColor)
{
    m_sListenerName = "line vertex filling";
    m_pAlgorithm = new CAlgorithmVertexLineFilling();
    m_pBresenhamAlg = new CAlgorithmBresenham(QPoint(),QPoint());

    initialize();
}

CListenerVertexLineFilling::~CListenerVertexLineFilling()
{
    if(m_pAlgorithm!=NULL) delete  m_pAlgorithm;
    if(m_pBresenhamAlg!=NULL) delete  m_pBresenhamAlg;
}


void CListenerVertexLineFilling::mouseMoveEvent(QPoint pos)
{
    if(m_mouseClickState == MCS_RELEASE)
    {
        // попытаться словить точку и достроить сплайн
        StepPoints points = m_clickPoints;
        points << pos;
    }

    if(m_mouseClickState == MCS_PRESS)
    {

        // смотрим, было ли нажатие на какую то главную точку
            if(m_clickPoints.contains(m_mousePressPos))
            {
                int index = 0;
                for(int i=0; i<m_clickPoints.size(); i++)
                    if(m_clickPoints.at(i)==m_mousePressPos)
                        index = i;
                m_mouseClickState = MCS_MOVE;
                m_movePointIndex = index;
                m_movePointPos = pos;

                m_clickPoints.replace(m_movePointIndex, pos);
                update(m_clickPoints);
            }
    }
    if(m_mouseClickState== MCS_MOVE)
    {
        m_clickPoints.replace(m_movePointIndex, pos);
        update(m_clickPoints);
    }
}

void CListenerVertexLineFilling::mousePressEvent(QPoint pos)
{
    m_clickPos = pos;

    m_mouseClickState = MCS_PRESS;

    m_mousePressPos = pos;

}


void CListenerVertexLineFilling::mouseReleaseEvent(QPoint pos)
{
    if(m_mouseClickState == MCS_MOVE)
    {

    }
    if(m_mouseClickState == MCS_PRESS)
    {
        if( !m_clickPoints.isEmpty() && m_clickPoints.contains(pos) && m_mousePressPos == m_clickPoints.last() )
            fillingArea();
        else
        {
            //if(m_mode = MODE_DEBUG)
            //clearMainPoints();
            //fixTmpObject();
            m_pDebugModeBox->fix();
            m_clickPoints.push_back(pos);
            update(m_clickPoints);
        }
    }


    m_mouseClickState = MCS_RELEASE;
}



void CListenerVertexLineFilling::modeChanged(Mode mode, Mode oldMode)
{

}


void CListenerVertexLineFilling::reset()
{


    clearMainPoints();
    if(m_mode == MODE_DEBUG)
        fixTmpObject();
    else
        clearTmpObject();
    if(m_mode == MODE_DEBUG)
        m_pDebugModeBox->fix();


    m_mouseClickState = MCS_UNDEFINED;

    m_bMoveModeEnable = false;
    m_clickPoints.clear();
    m_movePointIndex = 0;
    m_movePointPos = QPoint(-500,-500);
    m_mousePressPos = QPoint(-500,-500);


    m_tmpUndoStack.clear();
    m_clickPoints.clear();

    //initialize();
}


void CListenerVertexLineFilling::fillingArea()
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


void CListenerVertexLineFilling::fillingAreaDebug()
{
    m_pAlgorithm->reset();
    m_pAlgorithm->setPoints(m_clickPoints.toList());
    m_pDebugModeBox->setData(m_pAlgorithm, m_pCoordinateView,m_secondaryColor, m_mainColor);

    m_clickPoints.clear();
    m_mouseClickState = MCS_UNDEFINED;
    m_tmpUndoStack.clear();
}

void CListenerVertexLineFilling::fillingAreaNormal()
{

    m_pAlgorithm->reset();
    m_pAlgorithm->setPoints(m_clickPoints.toList());
    StepPoints points = m_pAlgorithm->getDrawPoints();
    while(!points.isEmpty())
    {
        m_pCoordinateView->setCellColor((points.first()),m_secondaryColor);
        points.pop_front();
    }
    //reset();

    clearMainPoints();

    fixTmpObject();

    reset();
    //clearTmpObject();
    //reset();
}

void CListenerVertexLineFilling::initialize()
{
    CAbstractListener::initialize();

    m_mouseClickState = MCS_RELEASE;
    m_bHighlightMainPoints = true;


    m_bMoveModeEnable = false;
    m_clickPoints.clear();
    m_movePointIndex = 0;
    m_movePointPos = QPoint(-500,-500);
    m_mousePressPos = QPoint(-500,-500);
}





void CListenerVertexLineFilling::update(QVector<QPoint> points)
{
    clearMainPoints();
    clearTmpObject();
//    if(m_mode == MODE_DEBUG)
//    {
//        if(points.size()>2)
//        {
//            m_pAlgorithm->reset();
//            m_pAlgorithm->setPoints(m_clickPoints.toList());
//            m_pDebugModeBox->setData(m_pAlgorithm, m_pCoordinateView, m_mainColor, m_secondaryColor);
//            updateMainPoints(points);
//        }
//    }

//    if(m_mode == MODE_NORMAL)
//    {

//        drawTempopary(points);
//    }

    drawTempopary(points);

    m_pDebugModeBox->hideMainPoints();
    updateMainPoints(points);
    m_pDebugModeBox->showMainPoints();

}

void CListenerVertexLineFilling::updateMainPoints(QVector<QPoint> points)
{
    //return;
    QColor color = m_secondaryColor;
    color.setAlpha(150);

    for(int i=0; i<points.size(); i++)
    {
        m_mainPointsUndoStack.push(new CChangeCellColorCommand(m_pCoordinateView,points.at(i), color));
    }
}


void CListenerVertexLineFilling::clearMainPoints()
{
    while(m_mainPointsUndoStack.canUndo())
        m_mainPointsUndoStack.undo();
    m_mainPointsUndoStack.clear();
}


void CListenerVertexLineFilling::drawTempopary(QVector<QPoint> points)
{
    clearTmpObject();
    if(points.size()<3)
        return;
    points.push_back(points.at(0));
    StepPoints line;
    QPoint start;
    QPoint end;
    for(int i=0; i< points.size()-1; i++)
    {
        start = points.at(i);
        end = points.at(i+1);
        m_pBresenhamAlg->setStartPos(start);
        m_pBresenhamAlg->setEndPos(end);
        line = m_pBresenhamAlg->getDrawPoints();
        StepPoints::iterator it;
        QPoint point;
        for(it = line.begin(); it!= line.end(); it++)
        {
            point = *it;
            m_tmpUndoStack.push(new CChangeCellColorCommand(m_pCoordinateView,point.x(),point.y(),m_mainColor));
        }
    }
}
