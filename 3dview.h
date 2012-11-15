#ifndef _3DVIEW_H
#define _3DVIEW_H

#include <QGraphicsView>
#include <QGraphicsLineItem>


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
public:
    C3DView(Projection projection = PROJECTION_DEFAULT, QWidget * parent = 0);
    void addShape(CShape3D *shape);
    void setProjection(Projection projection){ m_shapesProjection = projection; }
    void clearView(){ m_pScene->clear(); }
    void update(){ updateScene(); }

private:
    void init();
    void updateScene();
    void addLine(QPoint p1, QPoint p2, QPen& pen);
    QPen m_penLine;
    C3DScene *m_pScene;
    ShapesArray m_shapesArray;
    Projection m_shapesProjection;
    LineArray m_linesArray;

};

#endif // 3DVIEW_H
