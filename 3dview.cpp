#include "3dview.h"

#include <QDebug>
#include <QVector4D>
#include <QLineF>


C3DView::C3DView(Projection projection, QWidget *parent):
    QGraphicsView(parent), m_shapesProjection(projection)
{
    init();
}


void C3DView::init()
{

    m_viewPoint = QVector3D(0,0,-1000);
    m_move = 5;
    m_rotate = 5;
    m_scale = 0.2;
    m_perspectiveDistance = 200;
    m_pDistance = 10;
    setShortcutEnabled(true);

    m_bShowHiddenFaces = true;
    //m_shapesProjection = PROJECTION_PERSPECTIVE;
    m_moveXUp = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z),this);
    m_moveXDown = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_X),this);
    m_moveYUp = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_A),this);
    m_moveYDown = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S),this);
    m_moveZUp = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q),this);
    m_moveZDown = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W),this);
    connect(m_moveXUp,SIGNAL(activated()),this,SLOT(moveXUp()));
    connect(m_moveXDown,SIGNAL(activated()),this,SLOT(moveXDown()));
    connect(m_moveYUp,SIGNAL(activated()),this,SLOT(moveYUp()));
    connect(m_moveYDown,SIGNAL(activated()),this,SLOT(moveYDown()));
    connect(m_moveZUp,SIGNAL(activated()),this,SLOT(moveZUp()));
    connect(m_moveZDown,SIGNAL(activated()),this,SLOT(moveZDown()));


    m_rotateXUp = new QShortcut(QKeySequence(Qt::SHIFT + Qt::Key_Z),this);
    m_rotateXDown = new QShortcut(QKeySequence(Qt::SHIFT + Qt::Key_X),this);
    m_rotateYUp = new QShortcut(QKeySequence(Qt::SHIFT + Qt::Key_A),this);
    m_rotateYDown = new QShortcut(QKeySequence(Qt::SHIFT + Qt::Key_S),this);
    m_rotateZUp = new QShortcut(QKeySequence(Qt::SHIFT + Qt::Key_Q),this);
    m_rotateZDown = new QShortcut(QKeySequence(Qt::SHIFT + Qt::Key_W),this);
    connect(m_rotateXUp,SIGNAL(activated()),this,SLOT(rotateXUp()));
    connect(m_rotateXDown,SIGNAL(activated()),this,SLOT(rotateXDown()));
    connect(m_rotateYUp,SIGNAL(activated()),this,SLOT(rotateYUp()));
    connect(m_rotateYDown,SIGNAL(activated()),this,SLOT(rotateYDown()));
    connect(m_rotateZUp,SIGNAL(activated()),this,SLOT(rotateZUp()));
    connect(m_rotateZDown,SIGNAL(activated()),this,SLOT(rotateZDown()));



    m_scaleXUp = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_Z),this);
    m_scaleXDown = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_X),this);
    m_scaleYUp = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_A),this);
    m_scaleYDown = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_S),this);
    m_scaleZUp = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_Q),this);
    m_scaleZDown = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_W),this);
    connect(m_scaleXUp,SIGNAL(activated()),this,SLOT(scaleXUp()));
    connect(m_scaleXDown,SIGNAL(activated()),this,SLOT(scaleXDown()));
    connect(m_scaleYUp,SIGNAL(activated()),this,SLOT(scaleYUp()));
    connect(m_scaleYDown,SIGNAL(activated()),this,SLOT(scaleYDown()));
    connect(m_scaleZUp,SIGNAL(activated()),this,SLOT(scaleZUp()));
    connect(m_scaleZDown,SIGNAL(activated()),this,SLOT(scaleZDown()));

    m_distanceUp = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Equal),this);
    m_distanceDown = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus),this);
    connect(m_distanceUp,SIGNAL(activated()),this,SLOT(distanceUp()));
    connect(m_distanceDown,SIGNAL(activated()),this,SLOT(distanceDown()));

    m_pScene = new C3DScene(this);
    this->setScene(m_pScene);
    setSceneRect(-100,-100,200,200);
    m_penLine = QPen(QBrush(QColor(Qt::blue)),5, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
}


void C3DView::addShape(CShape3D *shape)
{
    if(!m_shapesArray.contains(shape))
    {
        m_shapesArray.push_back(shape);
        shape->setPen(m_penLine);
        updateScene();
    }
    else
    {
        qDebug() << "shape alredy at scene";
    }
}


void C3DView::updateScene()
{

    m_pScene->clear();
    //m_shapesArray.clear();
    m_linesArray.clear();

    //clearView();

    CShape3D *shape;
    CVertex3D fPoint, sPoint;

    for(int i=0; i<m_shapesArray.size(); i++)
    {
        shape = m_shapesArray.at(i);
        CShapeFaceArray fases = shape->getTransformedShapeFaces();
        CShapeFace *face;
        QPen pen = shape->getPen();
        for(int i=0; i<fases.size(); i++)
        {
            face = fases.at(i);

            if(!isHideFace(face,m_viewPoint))
            {
                CEdgeArray edges = face->getEdges();
                CEdge3D *edge;

                for(int i=0; i<edges.size(); i++)
                {
                    edge = edges.at(i);
                    fPoint = edge->getFirstPoint();
                    sPoint = edge->getSecondPoint();
                    // TODO получать координаты методом, который учитывает проекцию
                    //  addLine(convert(fPoint.toPoint()), convert(sPoint.toPoint()), m_penLine);

                    addLine(convertCoord(fPoint).toPoint(), convertCoord(sPoint).toPoint(), pen);
                }
            }
        }

    }

    //    clearView();
    //    CShape3D *shape;
    //    QList<CEdge3D> edges;
    //    CEdge3D edge;
    //    CVertex3D fPoint, sPoint;

    //    for(int i=0; i<m_shapesArray.size(); i++)
    //    {
    //        if( !(shape = m_shapesArray.at(i)) )
    //                continue;

    //        edges = shape->getTransformedEdges();

    //        for(int i=0; i<edges.size(); i++)
    //        {
    //            edge = edges.at(i);
    //            fPoint = edge.getFirstPoint();
    //            sPoint = edge.getSecondPoint();
    //            // TODO получать координаты методом, который учитывает проекцию
    //            //  addLine(convert(fPoint.toPoint()), convert(sPoint.toPoint()), m_penLine);
    //            addLine(convertCoord(fPoint), convertCoord(sPoint), m_penLine);
    //        }
    //    }
}


void C3DView::addLine(QPoint p1, QPoint p2, QPen &pen)
{
    //qDebug() << QLine(p1,p2);


    LineArray::iterator it;

    QLineF line;
    //    for(it = m_linesArray.begin(); it!=m_linesArray.end(); it++)
    //    {
    //        line = (*it)->line();
    //        if(line.x1() == p1.x() && line.x2() == p2.x() && line.y1() == p1.y() && line.y2() == p2.y())
    //            return;
    //    }
    m_linesArray.push_back(m_pScene->addLine(p1.x(), p1.y(), p2.x(), p2.y(), pen ));
}



void C3DView::addLine(qreal x1, qreal y1, qreal x2, qreal y2, QPen &pen)
{
    m_linesArray.push_back(m_pScene->addLine(x1,y1,x2,y2,pen));
}

void C3DView::moveXUp()
{
    if(m_shapesArray.isEmpty()) return;
    for(int i=0;i<m_shapesArray.size();i++)
        m_shapesArray.at(i)->move(m_move,0,0);
    update();
}

void C3DView::moveXDown()
{
    if(m_shapesArray.isEmpty()) return;

    for(int i=0;i<m_shapesArray.size();i++)
    m_shapesArray.at(i)->move(-m_move,0,0);
    update();
}

void C3DView::moveYUp()
{
    if(m_shapesArray.isEmpty()) return;

    for(int i=0;i<m_shapesArray.size();i++)
    m_shapesArray.at(i)->move(0,m_move,0);
    update();
}

void C3DView::moveYDown()
{
    if(m_shapesArray.isEmpty()) return;

    for(int i=0;i<m_shapesArray.size();i++)
    m_shapesArray.at(i)->move(0,-m_move,0);
    update();
}

void C3DView::moveZUp()
{
    if(m_shapesArray.isEmpty()) return;

    for(int i=0;i<m_shapesArray.size();i++)
    m_shapesArray.at(i)->move(0,0,m_move);
    update();
}

void C3DView::moveZDown()
{
    if(m_shapesArray.isEmpty()) return;

    for(int i=0;i<m_shapesArray.size();i++)
    m_shapesArray.at(i)->move(0,0,-m_move);
    update();
}

void C3DView::rotateXUp()
{
    if(m_shapesArray.isEmpty()) return;

    for(int i=0;i<m_shapesArray.size();i++)
    m_shapesArray.at(i)->rotateX(m_rotate);
    update();
}

void C3DView::rotateXDown()
{
    if(m_shapesArray.isEmpty()) return;

    for(int i=0;i<m_shapesArray.size();i++)
    m_shapesArray.at(i)->rotateX(-m_rotate);
    update();
}

void C3DView::rotateYUp()
{
    if(m_shapesArray.isEmpty()) return;

    for(int i=0;i<m_shapesArray.size();i++)
    m_shapesArray.at(i)->rotateY(m_rotate);
    update();
}

void C3DView::rotateYDown()
{
    if(m_shapesArray.isEmpty()) return;

    for(int i=0;i<m_shapesArray.size();i++)
    m_shapesArray.at(i)->rotateY(-m_rotate);
    update();
}
void C3DView::rotateZUp()
{
    if(m_shapesArray.isEmpty()) return;

    for(int i=0;i<m_shapesArray.size();i++)
    m_shapesArray.at(i)->rotateZ(m_rotate);
    update();
}

void C3DView::rotateZDown()
{
    if(m_shapesArray.isEmpty()) return;

    for(int i=0;i<m_shapesArray.size();i++)
    m_shapesArray.at(i)->rotateZ(-m_rotate);
    update();
}



void C3DView::scaleXUp()
{
    if(m_shapesArray.isEmpty()) return;

    for(int i=0;i<m_shapesArray.size();i++)
    m_shapesArray.at(i)->scale(1+m_scale,1,1);
    update();
}

void C3DView::scaleXDown()
{
    if(m_shapesArray.isEmpty()) return;

    for(int i=0;i<m_shapesArray.size();i++)
    m_shapesArray.at(i)->scale(1-m_scale,1,1);
    update();
}


void C3DView::scaleYUp()
{
    if(m_shapesArray.isEmpty()) return;

    for(int i=0;i<m_shapesArray.size();i++)
    m_shapesArray.at(i)->scale(1,1+m_scale,1);
    update();
}

void C3DView::scaleYDown()
{
    if(m_shapesArray.isEmpty()) return;

    for(int i=0;i<m_shapesArray.size();i++)
    m_shapesArray.at(i)->scale(1,1-m_scale,1);
    update();
}

void C3DView::scaleZUp()
{
    if(m_shapesArray.isEmpty()) return;

    for(int i=0;i<m_shapesArray.size();i++)
    m_shapesArray.at(i)->scale(1,1,1+m_scale);
    update();
}

void C3DView::scaleZDown()
{
    if(m_shapesArray.isEmpty()) return;

    for(int i=0;i<m_shapesArray.size();i++)
    m_shapesArray.at(i)->scale(1,1,1-m_scale);
    update();
}


CVertex3D C3DView::convertCoord(CVertex3D vertex)
{

    CVertex3D point = vertex;

    //    if(vertex.z()>m_perspectiveDistance)
    //        //vertex.setZ(m_perspectiveDistance);
    //        return point;

    //    if(vertex.z()<0 && -vertex.z() > m_perspectiveDistance )
    //        return point;


    int k = m_perspectiveDistance;

    //    if(vertex.z()>m_perspectiveDistance || -vertex.z() >m_perspectiveDistance)
    //    {
    //        qDebug() << "work";
    //        k*=-1;
    //    }

    switch (m_shapesProjection)
    {
    case PROJECTION_PERSPECTIVE :
        QMatrix4x4 pos(1,0,0,0,
                       0,1,0,0,
                       0,0,0,1.0/m_perspectiveDistance,
                       0,0,0,1);
        QVector4D coord(vertex.x(), vertex.y(), vertex.z(), vertex.w()) ;
        coord = coord * pos;
        CVertex3D v3d(coord.x(),coord.y(),coord.z(),coord.w());
        point = v3d;

        //        if(vertex.z()>m_perspectiveDistance || -vertex.z() >m_perspectiveDistance)
        //        {
        //            qDebug() << "work";
        //            point.setX(-point.x());
        //        }
    }


    return point;

}


void C3DView::setProjection(Projection projection)
{
    if(m_shapesProjection != projection)
    {
        m_shapesProjection = projection;
        updateScene();
    }
}


void C3DView::distanceUp()
{
    setDistance(getDistance()+m_pDistance);
}


void C3DView::distanceDown()
{
    setDistance(getDistance()-m_pDistance);
}


void C3DView::setDistance(int distance)
{
    if(distance<=10)
        return;
    m_perspectiveDistance = distance;

    qDebug() << m_perspectiveDistance;
    updateScene();
}


bool C3DView::isHideFace(CShapeFace *face, QVector3D P)
{

    if(m_bShowHiddenFaces)
        return false;

    CEdgeArray edges = face->getEdges();
    if(edges.size()<3)
        return true;
    CVertex3D p1 = convertCoord(edges.at(0)->getFirstPoint());
    CVertex3D p2 = convertCoord(edges.at(1)->getFirstPoint());
    CVertex3D p3 = convertCoord(edges.at(2)->getFirstPoint());



    QVector3D vector1(p1.x()-p2.x(),p1.y()-p2.y(), p1.z()-p2.z() );
    QVector3D vector2(p3.x()-p2.x(),p3.y()-p2.y(), p3.z()-p2.z() );

    qreal a,b,c,d;
    a = vector1.y() * vector2.z() - vector2.y() * vector1.z();
    b = vector1.z() * vector2.x() - vector2.z() * vector1.x();
    c = vector1.x() * vector2.y() - vector2.x() * vector1.y();
    d = -1 * ( a * vector1.x() + b * vector1.y() + c * vector1.z() );

    int val = (a * P.x() + b * P.y() + c*P.z() + d);
    if( (val) > 0 ){
        return true;
    } else {
        return false;
    }

}
