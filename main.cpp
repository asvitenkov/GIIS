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
#include "qmath.h"

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

    CShape3D shape,s;
//    CVertex3D v1(0,0,0,1);
//    CVertex3D v2(0,40,0,1);
//    CVertex3D v3(40,40,0,1);
//    CVertex3D v4(40,0,0,1);
//    CVertex3D v5(0,0,40,1);
//    CVertex3D v6(0,40,40,1);
//    CVertex3D v7(40,40,40,1);
//    CVertex3D v8(40,0,40,1);

    CVertex3D v1(0,0,0,1);
    CVertex3D v2(0,1,0,1);
    CVertex3D v3(1,1,0,1);
    CVertex3D v4(1,0,0,1);
    CVertex3D v5(0,0,1,1);
    CVertex3D v6(0,1,1,1);
    CVertex3D v7(1,1,1,1);
    CVertex3D v8(1,0,1,1);

    CEdge3D e1( v1,v2 );
    CEdge3D e2( v2,v3 );
    CEdge3D e3( v3,v4 );
    CEdge3D e4( v4,v1 );
    CEdge3D e5( v5,v6 );
    CEdge3D e6( v6,v7 );
    CEdge3D e7( v7,v8 );
    CEdge3D e8( v8,v5 );
    CEdge3D e9( v2,v6 );
    CEdge3D e10( v1,v5 );
    CEdge3D e11( v4,v8 );
    CEdge3D e12( v3,v7 );
    shape.addEdge( &e1 );
    shape.addEdge( &e2 );
    shape.addEdge( &e3 );
    shape.addEdge( &e4 );
    shape.addEdge( &e5 );
    shape.addEdge( &e6 );
    shape.addEdge( &e7 );
    shape.addEdge( &e8 );
    shape.addEdge( &e9 );
    shape.addEdge( &e10 );
    shape.addEdge( &e11 );
    shape.addEdge( &e12 );

    //shape.move(-20,-20,-20);
////    shape.rotateX(30);
////    shape.rotateY(30);
////    shape.rotateZ(30);
    //shape.scale(70,70,70);
//    shape.scale(0.95,0.95,0.95);
//    shape.scale(0.95,0.95,0.95);
//    shape.scale(0.95,0.95,0.95);
//    shape.scale(0.95,0.95,0.95);
//    //shape.scale(0.5,2,2);
//    //shape.scale(2,2,2);
//    //shape.scale(2,2,2);

    view.addShape(&shape);

    shape.scale(100,100,100);
    view.update();

    return a.exec();
}
