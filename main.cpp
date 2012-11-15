#include <QtGui/QApplication>
#include<QTextCodec>

#include "mainwindow.h"
#include "coordinateview.h"

#include "algorithmbspline.h"

#include <QDebug>



// DELETE
#include <QMatrix4x4>
#include <QVector4D>
#include "3dview.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QApplication::setStyle("Cleanlooks");
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    //MainWindow w;
    //w.setWindowTitle("ГИИС. ЛАБОРАТОРНАЯ 1. ГЕНЕРАЦИЯ ОТРЕЗКОВ");
    //w.show();

    C3DView view;
    view.show();

    CShape3D shape;
    CVertex3D v1(0,0,0);
    CVertex3D v2(0,100,100);
    CVertex3D v3(100,100,100);
    CVertex3D v4(100,0,100);
    CEdge3D e1( v1,v2 );
    CEdge3D e2( v2,v3 );
    CEdge3D e3( v3,v4 );
    CEdge3D e4( v4,v1 );
    shape.addEdge( e1 );
    shape.addEdge( e2 );
    shape.addEdge( e3 );
    shape.addEdge( e4 );

    view.addShape(&shape);


    QMatrix4x4 matrix(
                3,0,0,0,
                0,15,0,0,
                0,0,3,0,
                10,-5,100,1);

    QVector4D vector4d(1,1,1,1);
    QVector3D vector3D(0,0,0);

    qDebug() << vector4d * matrix;

    return a.exec();
}
