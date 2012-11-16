#ifndef _3DVIEW_H
#define _3DVIEW_H

#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QShortcut>

#include "3dscene.h"
#include "shape3d.h"





enum PROJECTION_TYPE
{
    PROJECTION_PERSPECTIVE,
    PROJECTION_DEFAULT
};

typedef QList<CShape3D*> ShapesArray;
typedef PROJECTION_TYPE Projection;
typedef QVector<QGraphicsLineItem*> LineArray;



class C3DView : public QGraphicsView
{
    Q_OBJECT
public:
    C3DView(Projection projection = PROJECTION_DEFAULT, QWidget * parent = 0);
    void addShape(CShape3D *shape);
    //void setProjection(Projection projection){ m_shapesProjection = projection; }
    void clearView(){ m_pScene->clear(); }
    void update(){ updateScene(); }
    void setProjection(Projection projection);
    void setDistance(int distance);
    int getDistance(){ return m_perspectiveDistance; }

private:
    QPoint convertCoord(CVertex3D vertex);
    void init();
    void updateScene();
    void addLine(QPoint p1, QPoint p2, QPen& pen);
    void addLine(qreal x1, qreal y1, qreal x2, qreal y2, QPen& pen);
    QPen m_penLine;
    C3DScene *m_pScene;
    ShapesArray m_shapesArray;
    Projection m_shapesProjection;
    LineArray m_linesArray;
    QShortcut *m_moveXUp, *m_moveXDown;
    QShortcut *m_moveYUp, *m_moveYDown;
    QShortcut *m_moveZUp, *m_moveZDown;

    QShortcut *m_rotateXUp, *m_rotateXDown;
    QShortcut *m_rotateYUp, *m_rotateYDown;
    QShortcut *m_rotateZUp, *m_rotateZDown;

    QShortcut *m_scaleXUp, *m_scaleXDown;
    QShortcut *m_scaleYUp, *m_scaleYDown;
    QShortcut *m_scaleZUp, *m_scaleZDown;

    QShortcut *m_distanceUp, *m_distanceDown;

    int m_move;
    int m_rotate;
    qreal m_scale;
    int m_pDistance;
    int m_perspectiveDistance;

    private slots:
    void moveXUp();
    void moveXDown();
    void moveYUp();
    void moveYDown();
    void moveZUp();
    void moveZDown();

    void rotateXUp();
    void rotateXDown();
    void rotateYUp();
    void rotateYDown();
    void rotateZUp();
    void rotateZDown();

    void scaleXUp();
    void scaleXDown();
    void scaleYUp();
    void scaleYDown();
    void scaleZUp();
    void scaleZDown();

    void distanceUp();
    void distanceDown();


};

#endif // 3DVIEW_H
