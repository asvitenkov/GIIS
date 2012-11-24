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
    virtual void mouseReleaseEvent(QPoint pos);
    virtual void setMainColor(QColor color);
    virtual void setSecondaryColor(QColor color);
    virtual QColor mainColor();
    virtual QColor secondaryColor();
    void setMode(Mode mode);
    void virtual clearTmpObject();
    void virtual fixTmpObject();
    virtual void reset() = 0;
    virtual QString name();
    void setHightlightMainPoints(bool enable);
    bool hightlightMainPoints();
    virtual void activate() { m_pCoordinateView->show();}
    virtual void deactivate() {}

protected:
    void initialize();
    void virtual modeChanged(Mode mode, Mode oldMode) = 0;

    bool m_bHighlightMainPoints;

    MouseClickState m_mouseClickState;
    Mode m_mode;

    CDebugModeBox *m_pDebugModeBox;
    QColor m_mainColor;
    QColor m_secondaryColor;
    CCoordinateView *m_pCoordinateView;
    QPoint m_currentMousePoint;

    QUndoStack m_tmpUndoStack;

    QString m_sListenerName;

};

#endif // ABSTRACTLISTENER_H
