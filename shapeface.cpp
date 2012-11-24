#include "shapeface.h"

CShapeFace::CShapeFace(QObject *parent) :
    QObject(parent)
{
}


CShapeFace::CShapeFace(CEdgeArray edgeArray, QObject *parent):
    QObject(parent), m_edgeArray(edgeArray)
{

}


void CShapeFace::addEdge(CEdge3D *edge)
{
    if(edge!=NULL)
        m_edgeArray.push_back(edge);
}

CShapeFace::CShapeFace(const CShapeFace &copy)
{
    m_edgeArray = copy.m_edgeArray;
}

CShapeFace& CShapeFace::operator=(const CShapeFace& copy)
{
    m_edgeArray = copy.m_edgeArray;
    return *this;
}
