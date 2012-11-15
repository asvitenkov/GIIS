#include "3dview.h"

C3DView::C3DView(Projection projection, QWidget *parent):
    QGraphicsView(parent), m_shapesProjection(projection)
{
    init();
}


void C3DView::init()
{
    m_pScene = new C3DScene(this);
    this->setScene(m_pScene);
    m_penLine = QPen(QBrush(QColor(Qt::black)),5, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
}


void C3DView::addShape(CShape3D *shape)
{
    if(!m_shapesArray.contains(shape))
    {
        m_shapesArray.push_back(shape);
        updateScene();
    }
}


void C3DView::updateScene()
{
    clearView();
    CShape3D *shape;
    CEdgeArray edges;
    CEdge3D edge;
    CVertex3D fPoint, sPoint;

    for(int i=0; i<m_shapesArray.size(); i++)
    {
        if( !(shape = m_shapesArray.at(i)) )
                continue;

        edges = shape->getEdges();

        for(int i=0; i<edges.size(); i++)
        {
            edge = edges.at(i);
            fPoint = edge.getFirstPoint();
            sPoint = edge.getSecondPoint();
            // TODO получать координаты методом, который учитывает проекцию
            //  addLine(convert(fPoint.toPoint()), convert(sPoint.toPoint()), m_penLine);
            addLine(fPoint.toPoint(), sPoint.toPoint(), m_penLine);
        }
    }
}


void C3DView::addLine(QPoint p1, QPoint p2, QPen &pen)
{
    m_linesArray.push_back(m_pScene->addLine(p1.x(), p1.y(), p2.x(), p2.y(), pen ));
}
