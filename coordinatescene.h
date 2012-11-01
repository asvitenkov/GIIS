#ifndef CCOORDINATESCENE_H
#define CCOORDINATESCENE_H

#include <QGraphicsScene>

class CCoordinateScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CCoordinateScene(QObject* parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    //bool eventFilter(QObject *watched, QEvent *event);

signals:
    void clickOnPos(qreal x, qreal y);
    void releaseOnPos(qreal x, qreal y);
    //void moveOnPos(qreal x, qreal y);
};

#endif // CCOORDINATESCENE_H

