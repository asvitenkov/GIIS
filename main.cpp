#include <QtGui/QApplication>
#include<QTextCodec>

#include "mainwindow.h"
#include "coordinateview.h"

#include "algorithmbspline.h"

#include <QDebug>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QApplication::setStyle("Cleanlooks");
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    MainWindow w;
    w.setWindowTitle("ГИИС. ЛАБОРАТОРНАЯ 1. ГЕНЕРАЦИЯ ОТРЕЗКОВ");
    w.show();

    return a.exec();
}
