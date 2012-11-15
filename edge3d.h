#ifndef EDGE3D_H
#define EDGE3D_H

#include <QObject>
#include <QVector3D>

typedef QVector3D CVertex3D;

class CEdge3D : public QObject
{
    Q_OBJECT
public:
    explicit CEdge3D(QObject *parent = 0);
    explicit CEdge3D(CVertex3D fPoint, CVertex3D sPoint, QObject *parent=0);
    explicit CEdge3D(const CEdge3D& edge);
    CEdge3D& operator=(const CEdge3D& edge);
    void setFirstPoint(CVertex3D point);
    void setSecondPoint(CVertex3D point);
    CVertex3D getFirstPoint(){ return m_firstPoint; }
    CVertex3D getSecondPoint(){ return m_secondPoint; }
//    ~CEdge3D();
private:
    CVertex3D m_firstPoint;
    CVertex3D m_secondPoint;
signals:
    
public slots:
    
};

#endif // EDGE3D_H
