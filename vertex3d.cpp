#include "vertex3d.h"

CVertex3D::CVertex3D():
    QVector4D(0,0,0,1), m_x(0), m_y(0), m_z(0), m_w(1)
{

}

CVertex3D::CVertex3D(qreal x, qreal y, qreal z, qreal w):
    QVector4D(x,y,z,w), m_x(x), m_y(y), m_z(z), m_w(w)
{
    if(m_w==0)
        m_w = 1;
}
