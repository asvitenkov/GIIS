#ifndef SHAPE3D_H
#define SHAPE3D_H

//#include <QObject>

#include <QMatrix4x4>

#include "edge3d.h"

//class QMatrix4x4;

typedef QList<CEdge3D*> CEdgeArray;

class CShape3D : public QObject
{
    Q_OBJECT
public:
    explicit CShape3D(QObject *parent = 0);
    explicit CShape3D(CEdgeArray edges, QObject *parent = 0);
    CEdgeArray getEdges();
    QList<CEdge3D> getTransformedEdges();
    void setEdges(CEdgeArray edges);
    void addEdge(CEdge3D *edge);
    void transform(QMatrix4x4 transform) { m_transform*=transform; }
    void move(int dx, int dy, int dz);
    void rotateZ(int angle);
    void rotateX(int angle);
    void rotateY(int angle);
    void scale(qreal sx, qreal sy, qreal sz);
    QMatrix4x4 getTransformationMatrix(){ return m_transform; }
private:
    CEdgeArray m_edgeArray;
    QMatrix4x4 m_transform;
signals:
    
public slots:
    
};

#endif // SHAPE3D_H
