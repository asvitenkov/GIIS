#include "edge3d.h"

CEdge3D::CEdge3D()
    //QObject(parent)
{
}

CEdge3D::CEdge3D(CVertex3D fPoint, CVertex3D sPoint) :
    m_firstPoint(fPoint), m_secondPoint(sPoint)
{

}



CEdge3D::CEdge3D(const CEdge3D &edge)
{
    this->m_firstPoint = edge.m_firstPoint;
    this->m_secondPoint = edge.m_secondPoint;
    //this->setParent(0);
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


void CEdge3D::setFirstPoint(QVector4D point)
{
    m_firstPoint.setX(point.x());
    m_firstPoint.setY(point.y());
    m_firstPoint.setZ(point.z());
    m_firstPoint.setW(point.w());
}

void CEdge3D::setSecondPoint(QVector4D point)
{
    m_secondPoint.setX(point.x());
    m_secondPoint.setY(point.y());
    m_secondPoint.setZ(point.z());
    m_secondPoint.setW(point.w());
}

