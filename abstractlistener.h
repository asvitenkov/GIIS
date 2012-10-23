#ifndef ABSTRACTLISTENER_H
#define ABSTRACTLISTENER_H

#include <QPoint>
#include <QColor>

#include "debugmodebox.h"
#include "defines.h"
#include "coordinateview.h"

class CAbstractListener
{
public:
    explicit CAbstractListener(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor);
    virtual ~CAbstractListener();
    void virtual mousePressEvent(QPoint pos) = 0;
    void virtual mouseMoveEvent(QPoint pos) = 0;
    void setMainColor(QColor color);
    void setSecondaryColor(QColor color);
    void setDebugModeEnable();
    void setNormalModeEnable();
    void virtual clearTmpObject() = 0;
    void virtual fixTmpObject() = 0;


protected:
    void initialize();
    void virtual modeChanged(Mode mode, Mode oldMode) = 0;

    MouseClickState m_mouseClickState;
    Mode m_mode;
    QColor m_mainColor;
    QColor m_SecondaryColor;
    CDebugModeBox *m_pDebugModeBox;
    CCoordinateView *m_pCoordinateView;
    QPoint m_currentMousePoint;

    QUndoStack m_tmpUndoStack;

};

#endif // ABSTRACTLISTENER_H
