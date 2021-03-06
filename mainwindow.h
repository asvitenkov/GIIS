#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUndoStack>
#include <QColor>

#include "coordinateview.h"
#include "algorithmdda.h"
#include "algorithmbresenham.h"
#include "defines.h"
#include "painter.h"
#include "debugmodebox.h"
#include "listenerlinedda.h"
#include "listenerlinebresenham.h"
#include "algorithmround.h"
#include "listenerroundalgorithm.h"

#include "algorithmparabola.h"
#include "listenerparabola.h"
#include "algorithmbspline.h"
#include "listenerbspline.h"
#include "listenerbese.h"
#include "listenerlinefilling.h"
#include "algorithmvertexlinefilling.h"
#include "listenervertexlinefilling.h"

#include "3dview.h"
#include "transformationlistener.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    

public slots:


private:
    void _init();
    void _setMainColor(QColor color);
    void _setSecondaryColor(QColor color);
    QColor _mainColor();
    QColor _secondaryColor();
    void createListeners();

    QPoint m_firstPoint;
    QPoint m_secondPoint;

    bool m_bDebugModeEnable;
    bool m_bHighlightInitPoints;
    bool m_bHideFaces;

    MouseClickState m_btnClickState;

    DrawShapeTypes m_drawShapeType;

    Ui::MainWindow *ui;

    QUndoStack m_pUndoStack;
    QUndoStack m_pTmpUndoStack;
    CCoordinateView *m_pView;
    C3DView *m_pView3D;

    bool m_bPerspectiveProjection;

    QColor m_mainColor;
    QColor m_secondaryColor;

    CDebugModeBox *m_pDebugBox;
    QMap<QObject*, CAbstractListener*> m_listenersMap;

    CAbstractListener *m_pCurrentListener;

    //delete
    //CAbstractListener *m_pListener;

    Mode m_mode;
    int m_lastZoomValue;

private slots:
    void mouseClickOnCell(int x, int y);
    void mouseMoveOnCell(int x, int y);
    void mouseReleaseOnCell(int x, int y);
    void setMainColor();
    void setSecondaryColor();
    void debugModeEnable();
    void defaultModeEnable();
    void clearView();
    void zoomOut();
    void zoomIn();
    void highlightEndPoints();
    void drawAlgorithmChanged();
    void algorithmTabIndexChanged(int index);
    void zoomChanged(int newValue);
    void perspectiveProjection();
    void hideFaces();
};

#endif // MAINWINDOW_H
