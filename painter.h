#ifndef PAINTER_H
#define PAINTER_H

#include "coordinateview.h"
#include "abstractpaintalgorithm.h"
#include "command.h"

#include <QUndoStack>
#include <QTextBrowser>

class CPainter
{
public:
    static void drawLine(CCoordinateView *view, CAbstractPaintAlgorithm *algorithm, QPoint startPoint, QPoint endPoint,QColor mainColor, QColor secondaryColor);
    static void drawDebugLine(CCoordinateView *view, CAbstractPaintAlgorithm *algorithm, QTextBrowser *textBrowser, QUndoStack *undoStack, QPoint startPoint, QPoint endPoint,QColor mainColor, QColor secondaryColor);

private:
    CPainter();
};

#endif // PAINTER_H