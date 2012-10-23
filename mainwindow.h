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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    void _init();
    void _mouseFirstClick(QPoint cellPos);
    void _mouseSecondClick(QPoint cellPos);
    void _drawCommonLine(QPoint startPoint, QPoint endPoint);
    void _drawDefaultLine(QPoint startPoint, QPoint endPoint);
    void _drawDebugLine(QPoint startPoint, QPoint endPoint);
    void _setMainColor(QColor color);
    void _setSecondaryColor(QColor color);
    void _switchMode();
    void _drawTempararyObjectAfterFirstClick(QPoint curentPos);
    void _fixTemporaryObject();
    QColor _mainColor();
    void _removeTemporaryObject();
    void _drawTemporaryLine(QPoint startPoint, QPoint endPoint);
    QColor _secondaryColor();
    CAbstractPaintAlgorithm *_getCurrentPaintAlgorithm();
//    void _redoStack();
//    void _drawLineAtDebugMode();
//    void _clearLastDraw();


    QPoint m_firstPoint;
    QPoint m_secondPoint;

    bool m_bDebugModeEnable;
    bool m_bHighlightInitPoints;

    MouseClickState m_btnClickState;

    DrawShapeTypes m_drawShapeType;

    Ui::MainWindow *ui;
    QUndoStack *m_pUndoStack;
    CCoordinateView *m_pView;

    QUndoStack m_pTmpUndoStack;

    QColor m_mainColor;
    QColor m_secondaryColor;

    CDebugModeBox *m_pDebugBox;

private slots:
    void mouseClickOnCell(int x, int y);
    void mouseMoveOnCell(int x, int y);
    void setMainColor();
    void setSecondaryColor();
    void debugModeEnable();
    void defaultModeEnable();
//    void debugModeNextStep();
//    void debugModePreviosStep();
    void clearView();
    void zoomOut();
    void zoomIn();
//    void stepToSrart();
//    void stepToEnd();
    void highlightEndPoints();
    void drawAlgorithmChanged();
};

#endif // MAINWINDOW_H
