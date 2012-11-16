#include "transformationlistener.h"



#include <QFileDialog>

CTransformationListener::CTransformationListener(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor, C3DView* view3d)
    :QObject(0),CAbstractListener(view, box, mainColor, secondaryColor), m_p3dView(view3d)
{
    m_sListenerName = "Listener transformation";
}


void CTransformationListener::reset()
{
//    m_pCoordinateView->hide();
//    m_p3dView->show();
}


void CTransformationListener::activate()
{
    m_pCoordinateView->hide();
    m_p3dView->show();
}

void CTransformationListener::deactivate()
{
    m_pCoordinateView->show();
    m_p3dView->hide();
}

void CTransformationListener::mousePressEvent(QPoint pos)
{

}


void CTransformationListener::mouseMoveEvent(QPoint pos)
{

}


void CTransformationListener::modeChanged(Mode mode, Mode oldMode)
{

}


void CTransformationListener::load3DShape()
{
    qDebug() << "load";
    QString fileName = QFileDialog::getOpenFileName();
    if(fileName.isEmpty())
        return;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        return;

    QTextStream stream(&file);
    QString line;
    QRegExp expr("\\((\\d+),(\\d+),(\\d+)\\)->\\((\\d+),(\\d+),(\\d+)\\)");

    bool ok;
    CShape3D *shape = new CShape3D(0);
    while(!stream.atEnd())
    {
        stream >> line;
        qDebug() << line;
        if(expr.indexIn(line)!=-1)
        {

            CVertex3D v1,v2;
            v1.setX(expr.cap(1).toInt(&ok));
            v1.setY(expr.cap(2).toInt(&ok));
            v1.setZ(expr.cap(3).toInt(&ok));

            v2.setX(expr.cap(4).toInt(&ok));
            v2.setY(expr.cap(5).toInt(&ok));
            v2.setZ(expr.cap(6).toInt(&ok));


            shape->addEdge(new CEdge3D(v1,v2));
        }
    }
    m_p3dView->addShape(shape);
}
