#ifndef TRANSFORMATIONLISTENER_H
#define TRANSFORMATIONLISTENER_H

#include <QObject>

#include "abstractlistener.h"

#include "3dview.h"

class CTransformationListener : public QObject, public CAbstractListener
{

    Q_OBJECT
public:
    CTransformationListener(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor, C3DView *view3d);
    void reset();
    void mouseMoveEvent(QPoint pos);
    void mousePressEvent(QPoint pos);
    void activate();
    void deactivate();
    void setMainColor(QColor color);

public slots:
    void load3DShape();


private:
    C3DView *m_p3dView;
    void modeChanged(Mode mode, Mode oldMode);
};

#endif // TRANSFORMATIONLISTENER_H
