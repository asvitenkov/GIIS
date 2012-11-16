#include "shape3d.h"

#include "qmath.h"

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


void CShape3D::addEdge(CEdge3D *edge)
{
    m_edgeArray.push_back(edge);
}


CEdgeArray CShape3D::getEdges()
{
    return m_edgeArray;
}



QList<CEdge3D> CShape3D::getTransformedEdges()
{
    QList<CEdge3D> list;

    CEdge3D *edge;
    CEdge3D transformedEdge;
    CVertex3D p1,p2;

    for(int i=0; i< m_edgeArray.size(); i++)
    {
        edge = m_edgeArray.at(i);
        p1 = edge->getFirstPoint();
        p2 = edge->getSecondPoint();

        transformedEdge.setFirstPoint( p1 * m_transform );
        transformedEdge.setSecondPoint( p2 * m_transform );

        list.push_back(transformedEdge);


    }

    return list;
}


void CShape3D::move(int dx, int dy, int dz)
{
    QMatrix4x4 moveMatrix(  1,0,0,0,
                            0,1,0,0,
                            0,0,1,0,
                            dx,dy,dz,1);

    m_transform*=moveMatrix;
}

void CShape3D::rotateZ(int angle)
{
    qreal c, s;
    c = qCos(angle * M_PI / 180 );
    s = qSin(angle * M_PI / 180 );
    QMatrix4x4 rotate( c, s, 0, 0,
                      -s, c, 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1);
    m_transform*=rotate;
}

void CShape3D::rotateX(int angle)
{
    qreal c, s;
    c = qCos(angle * M_PI / 180 );
    s = qSin(angle * M_PI / 180 );
    QMatrix4x4 rotate( 1, 0, 0, 0,
                       0, c, s, 0,
                       0,-s, c, 0,
                       0, 0, 0, 1);
    m_transform*=rotate;
}

void CShape3D::rotateY(int angle)
{
    qreal c, s;
    c = qCos(angle * M_PI / 180 );
    s = qSin(angle * M_PI / 180 );
    QMatrix4x4 rotate( c, 0,-s, 0,
                       0, 1, 0, 0,
                       s, 0, c, 0,
                       0, 0, 0, 1);
    m_transform*=rotate;
}


void CShape3D::scale(qreal sx, qreal sy, qreal sz)
{
    //qDebug() << m_transform;
    //sx=m_transform.row(0).x()+sx;
    //sy=m_transform.row(1).y()+sy;
    //sz=m_transform.row(2).z()+sz;

    QMatrix4x4 scale(  sx,0,0,0,
                       0,sy,0,0,
                       0,0,sz,0,
                       0,0,0,1);

    m_transform*=scale;
    //qDebug() << m_transform;
}
