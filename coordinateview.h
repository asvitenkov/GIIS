#ifndef CCOORDINATEVIEW_H
#define CCOORDINATEVIEW_H

#include <QGraphicsView>
#include <QVector>
#include <QGraphicsLineItem>
#include <QPen>
#include <QGraphicsPolygonItem>

#include "coordinatescene.h"

class CCoordinateView : public QGraphicsView
{
    Q_OBJECT
public:
    CCoordinateView(QWidget* parent = 0);
    ~CCoordinateView();
//    int heightForWidth(int width) const;
    void scale(qreal sx, qreal sy);
    void setCellColor(int x, int y, QColor color);
    void setCellColor(QPoint cellPos, QColor color);
    QColor cellColor(int x, int y);

private:
    QPoint m_lastCellPos;
    void _init();
    void _drawGrid();
    void _drawCoordDirection();
    void mouseMoveEvent(QMouseEvent *event);
    QPoint posToCell(qreal x, qreal y);
    QPoint cellToPos(int x, int y);

     CCoordinateScene* m_pScene;
     int m_nWidgetSize;
     int m_nCellSize;
     QVector<QGraphicsLineItem*> m_horLines;
     QVector<QGraphicsLineItem*> m_vertLines;
     QPen m_coordLinePen;
     QPen m_gridPen;
     QPen m_rectItemPen;
     QGraphicsPolygonItem* m_pVerCoordLine;
     QGraphicsPolygonItem* m_pHorCoordLine;

     QGraphicsRectItem* m_pArray[260][260];
public slots:
     void zoomIn();
     void zoomOut();
     void clear();


private slots:
     void clickOnScenePos(qreal x, qreal y);
     void releaseOnScenePos(qreal x, qreal y);
     void moveOnScenePos(int x, int y);

signals:
     void clickOnCell(int x, int y);
     void moveOnCell(int x, int y);
     void releaseOnScene(int x, int y);

};

#endif // CCOORDINATEVIEW_H
