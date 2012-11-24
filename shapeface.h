#ifndef SHAPEFACE_H
#define SHAPEFACE_H

#include <QObject>
#include "defines.h"
//#include "edge3d.h"


typedef QList<CEdge3D*> CEdgeArray;


class CShapeFace : public QObject
{
    Q_OBJECT
public:
    explicit CShapeFace(QObject *parent = 0);
    explicit CShapeFace(CEdgeArray  edgeArray, QObject *parent = 0);
    explicit CShapeFace(const CShapeFace& copy);
    CShapeFace& operator=(const CShapeFace& copy);
    void addEdge(CEdge3D *edge);
    inline CEdgeArray getEdges() { return m_edgeArray; }
private:
    CEdgeArray m_edgeArray;

signals:
    
public slots:
    
};

#endif // SHAPEFACE_H
