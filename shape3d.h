#ifndef SHAPE3D_H
#define SHAPE3D_H

//#include <QObject>

#include "edge3d.h"

typedef QList<CEdge3D> CEdgeArray;

class CShape3D : public QObject
{
    Q_OBJECT
public:
    explicit CShape3D(QObject *parent = 0);
    explicit CShape3D(CEdgeArray edges, QObject *parent = 0);
    CEdgeArray getEdges(){ return m_edgeArray; }
    void setEdges(CEdgeArray edges);
    void addEdge(CEdge3D &edge);
private:
    CEdgeArray m_edgeArray;
    
signals:
    
public slots:
    
};

#endif // SHAPE3D_H
