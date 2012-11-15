#include "shape3d.h"

CShape3D::CShape3D(QObject *parent) :
    QObject(parent)
{

}


CShape3D::CShape3D(CEdgeArray edges, QObject *parent):
    QObject(parent), m_edgeArray(edges)
{

}



void CShape3D::setEdges(CEdgeArray edges)
{
    m_edgeArray = edges;
}


void CShape3D::addEdge(CEdge3D& edge)
{
    m_edgeArray.push_back(edge);
}
