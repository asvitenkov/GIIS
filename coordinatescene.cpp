#include "coordinatescene.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

CCoordinateScene::CCoordinateScene(QObject *parent)
    :QGraphicsScene(parent)
{

}


void CCoordinateScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() != Qt::LeftButton) return;
    emit clickOnPos(event->scenePos().x(),-event->scenePos().y());
}


void CCoordinateScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
   if(event->button() != Qt::LeftButton) return;
   emit clickOnPos(event->scenePos().x(),-event->scenePos().y());
}



void CCoordinateScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "mouse release event";
    if(event->button() != Qt::LeftButton) return;
    emit releaseOnPos(event->scenePos().x(), -event->scenePos().y());
}
