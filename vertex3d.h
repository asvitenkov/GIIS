#ifndef VERTEX3D_H
#define VERTEX3D_H

#include <QVector4D>

#include <QDebug>

class CVertex3D : public QVector4D
{
public:
    explicit CVertex3D();
    explicit CVertex3D(qreal x,qreal y, qreal z, qreal w=1);
    qreal x() const { /*qDebug() << "x =" << m_x/m_w;*/ return m_x/m_w; }
    qreal y() const { /*qDebug() << "y =" << m_y/m_w;*/ return m_y/m_w; }
    qreal z() const { /*qDebug() << "z =" << m_z/m_w;*/ return m_z/m_w; }
    qreal w() const { return m_w; }

    qreal xx() const { /*qDebug() << "x =" << m_x/m_w;*/ return m_x; }
    qreal yy() const { /*qDebug() << "y =" << m_y/m_w;*/ return m_y; }
    qreal zz() const { /*qDebug() << "z =" << m_z/m_w;*/ return m_z; }
    qreal ww() const { return m_w; }


    QPoint toPoint() { /*qDebug() << m_w;*/  return QPoint(x(),y()); }
    void setX(qreal x) { m_x = x; }
    void setY(qreal y) { m_y = y; }
    void setZ(qreal z) { m_z = z; }
    void setW(qreal w) { m_w = w; }

private:
    qreal m_x;
    qreal m_y;
    qreal m_z;
    qreal m_w;
};

#endif // VERTEX3D_H
