#ifndef SHAPE3D_H
#define SHAPE3D_H

//#include <QObject>

#include <QMatrix4x4>
#include "defines.h"
#include "edge3d.h"
#include <QPen>
//class QMatrix4x4;

typedef QList<CShapeFace*> CShapeFaceArray;

class CShape3D : public QObject
{
    Q_OBJECT
public:
    explicit CShape3D(QObject *parent = 0);
    explicit CShape3D(CEdgeArray edges, QObject *parent = 0);
    CEdgeArray getEdges();
    inline CShapeFaceArray getShapeFaces(){ return m_faceArray; }
    CShapeFaceArray getTransformedShapeFaces();
    QList<CEdge3D> getTransformedEdges();
    void setEdges(CEdgeArray edges);
    void addEdge(CEdge3D *edge);
    void addShapeFace(CShapeFace *face);
    void transform(QMatrix4x4 transform) { m_transform*=transform; }
    void move(int dx, int dy, int dz);
    void rotateZ(int angle);
    void rotateX(int angle);
    void rotateY(int angle);
    void scale(qreal sx, qreal sy, qreal sz);
    QMatrix4x4 getTransformationMatrix(){ return m_transform; }
    void setPen(QPen pen){ m_pen = pen; }
    QPen getPen(){ return m_pen; }
private:
    CEdgeArray m_edgeArray;
    CShapeFaceArray m_faceArray;
    QMatrix4x4 m_transform;
    QPen m_pen;
signals:
    
public slots:
    
};

#endif // SHAPE3D_H
