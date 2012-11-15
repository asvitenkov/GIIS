#include "edge3d.h"

CEdge3D::CEdge3D(QObject *parent) :
    QObject(parent)
{
}

CEdge3D::CEdge3D(CVertex3D fPoint, CVertex3D sPoint, QObject *parent) :
    QObject(parent), m_firstPoint(fPoint), m_secondPoint(sPoint)
{

}



CEdge3D::CEdge3D(const CEdge3D &edge)
{
    this->m_firstPoint = edge.m_firstPoint;
    this->m_secondPoint = edge.m_secondPoint;
    this->setParent(0);
}

CEdge3D& CEdge3D::operator =(const CEdge3D& edge)
{
    this->m_firstPoint = edge.m_firstPoint;
    this->m_secondPoint = edge.m_secondPoint;
    return *this;
}

void CEdge3D::setFirstPoint(CVertex3D point)
{
    m_firstPoint = point;
}

void CEdge3D::setSecondPoint(CVertex3D point)
{
    m_secondPoint = point;
}

