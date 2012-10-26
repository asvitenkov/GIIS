#include "coordinateview.h"

#include <QDebug>
#include <QMouseEvent>
CCoordinateView::CCoordinateView(QWidget *parent)
    :QGraphicsView(parent)
{
    _init();
}
CCoordinateView::~CCoordinateView()
{

}



//int CCoordinateView::heightForWidth(int width) const
//{
//    return width;
//}



void CCoordinateView::_init()
{
    //m_nWidgetSize = 603;

    m_nCellSize = 40;

    this->setMouseTracking(true);

    m_pScene = new CCoordinateScene(this);
    //m_pScene->setSceneRect(-m_nWidgetSize/2.0,-m_nWidgetSize/2.0,m_nWidgetSize-2,m_nWidgetSize-2);
    m_pScene->setSceneRect(-50,-50,100,100);
    setScene(m_pScene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //setMaximumSize(m_nWidgetSize,m_nWidgetSize);
    //setMinimumSize(m_nWidgetSize,m_nWidgetSize);

    connect(m_pScene,SIGNAL(clickOnPos(qreal,qreal)),this,SLOT(clickOnScenePos(qreal,qreal)));
    //connect(m_pScene,SIGNAL(moveOnPos(qreal,qreal)),this,SLOT(moveOnScenePos(qreal,qreal)));

    m_pVerCoordLine = NULL;
    m_pHorCoordLine = NULL;

    //m_nCellOldPosX = m_nCellOldPosY = - 65000;

    // delete
    m_coordLinePen = QPen(QBrush(Qt::red),5,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin);
    m_rectItemPen = QPen(QBrush(Qt::red),1,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin);
    m_gridPen.setColor(Qt::black);
    m_gridPen.setWidth(1);

//    *m_pArray=new QGraphicsRectItem*[10000];
//    for(int i=0; i<=10000;i++)
//    {
//        *m_pArray[i]=new QGraphicsRectItem[10000];
//    }


    memset(&m_pArray,NULL,260*260*sizeof(QGraphicsRectItem*));

    _drawGrid();


    scale(0.3,0.3);

}





void CCoordinateView::_drawGrid()
{
    int i;

    QGraphicsLineItem *item;
    m_horLines << (item = m_pScene->addLine(-5000,0,5000,0,m_gridPen));
    item->setZValue(0.9);
    m_vertLines << (item =  m_pScene->addLine(0,-5000,0,5000,m_gridPen));
    item->setZValue(0.9);
    for(i=m_nCellSize; i<= 5000; i+=m_nCellSize)
    {
        m_horLines << (item = m_pScene->addLine(-5000,i,5000,i,m_gridPen));
        item->setZValue(0.9);
        m_horLines << (item = m_pScene->addLine(-5000,-i,5000,-i,m_gridPen));
        item->setZValue(0.9);
        m_vertLines << (item = m_pScene->addLine(i,-5000,i,5000,m_gridPen));
        item->setZValue(0.9);
        m_vertLines << (item = m_pScene->addLine(-i,-5000,-i,5000,m_gridPen));
        item->setZValue(0.9);
    }

}


void CCoordinateView::scale(qreal sx, qreal sy)
{
    QGraphicsView::scale(sx,sy);
}



void CCoordinateView::_drawCoordDirection()
{

    return;


    int x0,x1,x2,y0,y1,y2;

    x0 = y0 = 0;
    x1 = ( m_pScene->sceneRect().width()/2.0 - 3 * m_nCellSize );
    y1 = 0;
    x2 = 0;
    y2 = -( m_pScene->sceneRect().height()/2.0 - 3 * m_nCellSize );

    QPolygonF polygonHor;
    polygonHor << QPointF(x0,y0) << QPointF(x1,y1) << QPointF(x1+m_nCellSize,y1-m_nCellSize/2.0) << QPointF(x1, y1-m_nCellSize) << QPointF(x0,y0-m_nCellSize);
               //<< QPointF(x1-15,y1+10) << QPointF(x1,y1);
    if(!m_pHorCoordLine)
        m_pHorCoordLine = m_pScene->addPolygon(polygonHor,m_coordLinePen);
    else
        m_pHorCoordLine->setPolygon(polygonHor);

    m_pHorCoordLine->setPos(0,0);
    m_pHorCoordLine->setZValue(0.9);


    QPolygonF polygonVert;
    polygonVert << QPointF(x0,y0) << QPointF(x2,y2) << QPointF(x2+m_nCellSize/2.0, y2-m_nCellSize) << QPointF(x2+m_nCellSize,y2) << QPointF(x0+m_nCellSize,y0);
                //<< QPointF(x2+10,y2-15) << QPointF(x2,y2);
    if(!m_pVerCoordLine)
        m_pVerCoordLine = m_pScene->addPolygon(polygonVert,m_coordLinePen);
    else
        m_pVerCoordLine->setPolygon(polygonVert);
    m_pVerCoordLine->setPos(0,0);
    m_pVerCoordLine->setZValue(0.9);

}



void CCoordinateView::zoomIn()
{
    //qDebug() << transform().m11();
    if(transform().m11() >= 1) return;
    scale(1.05,1.05);
}


void CCoordinateView::zoomOut()
{
    if(transform().m11() <= 0.16) return;
    scale(0.95,0.95);
}



void CCoordinateView::clickOnScenePos(qreal x, qreal y)
{
    int nX, nY;
    QPoint point = posToCell(x,y);
    nX = point.x();
    nY = point.y();
//    qDebug() << nX << " " << nY;
    emit clickOnCell(nX, nY);
    //setCellColor(nX,nY,QColor(Qt::green));
}

void CCoordinateView::setCellColor(int x, int y, QColor color)
{
    int nX,nY;


    nY = (y+1) * m_nCellSize;
    nX = x * m_nCellSize;

    QGraphicsRectItem *item;
    item = m_pArray[x+130][y+130];

    QPen cellPen;

    if(item != NULL)
    {
        QBrush brush = item->brush();
        brush.setColor(color);
        cellPen = item->pen();
        cellPen.setColor(color);
        item->setBrush(brush);
        item->setPen(cellPen);
        item->setZValue(0.3);
    }
    else
    {
        m_rectItemPen.setColor(color);
        item = m_pScene->addRect(0,0,m_nCellSize-0,m_nCellSize-0,m_rectItemPen,QBrush(color));
        item->setData(0,QVariant(x));
        item->setData(1,QVariant(y));
        item->setPos(nX,-nY);
        m_pArray[x+130][y+130] = item;

//        qDebug() << "add item at pos:" <<item->pos();
    }
}



void CCoordinateView::moveOnScenePos(int x, int y)
{
    QPointF curPointF = mapToScene(QPoint(x,y));
    QPoint curPoint = posToCell((int)curPointF.x(),(int)-curPointF.y());
    if(curPoint != m_lastCellPos){
        m_lastCellPos = curPoint;
        emit moveOnCell(curPoint.x(), curPoint.y());

    }
}

void CCoordinateView::mouseMoveEvent(QMouseEvent *event)
{
    moveOnScenePos((event->pos().x()), event->pos().y());
}


QPoint CCoordinateView::posToCell(qreal x, qreal y)
{
    int nX, nY;
    nX = ((int) (x/m_nCellSize)) ;
    nY = ((int) (y/m_nCellSize)) ;
    if(x<0) nX-=1;
    if(y<0) nY-=1;
    return QPoint(nX,nY);
}


QColor CCoordinateView::cellColor(int x, int y)//, bool isEmpty)
{

    QGraphicsRectItem *item = m_pArray[x+130][y+130];
    if(item != NULL)
    {
        return (item->brush().color());
    }
    else return QColor(Qt::white);
}


QPoint CCoordinateView::cellToPos(int x, int y)
{
    int nX,nY;
    nY = (y+1) * m_nCellSize;
    nX = x * m_nCellSize;
    return QPoint(nX, -nY);
}

void CCoordinateView::setCellColor(QPoint cellPos, QColor color)
{
    setCellColor(cellPos.x(), cellPos.y(),color);
}


void CCoordinateView::clear(){

    QList<QGraphicsItem*> items = m_pScene->items();
    QList<QGraphicsItem*>::iterator it;
    QGraphicsRectItem *rItem;
    for(it = items.begin(); it!=items.end(); it++)
    {
        rItem = dynamic_cast<QGraphicsRectItem*>(*it);
        if(rItem != NULL)
        {
            bool ok = false;
            int x = rItem->data(0).toInt(&ok);
            int y = rItem->data(1).toInt(&ok);
            m_pArray[x+130][y+130] = NULL;
            m_pScene->removeItem(rItem);
            delete rItem;
        }
    }
    memset(m_pArray,NULL,260*260*sizeof(QGraphicsRectItem*));
   //m_pScene->clear();
   //_drawGrid();
}
