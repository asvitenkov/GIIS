#include "painter.h"

#include <QDebug>


CPainter::CPainter()
{
}


void CPainter::drawLine(CCoordinateView *view, CAbstractPaintAlgorithm *algorithm, QPoint startPoint, QPoint endPoint, QColor mainColor, QColor secondaryColor)
{
    StepPoints points = algorithm->getDrawPoints();
    QColor curColor;
    for( int i=0; i<points.size(); i++)
    {
        if( i==0 || i == points.size() - 1 )
            curColor = secondaryColor;
        else curColor = mainColor;
        QPoint curPoint = points.at(i);
        view->setCellColor(curPoint,curColor);
    }
}

void CPainter::drawRound(CCoordinateView *view, CAbstractPaintAlgorithm *algorithm, QPoint startPoint, QColor mainColor, QColor secondaryColor, bool highlight)
{
    StepPoints points = algorithm->getDrawPoints();
    QColor curColor = mainColor;
    for(int i=0; i<points.size(); i++)
    {
        QPoint curPoint = points.at(i);
//        if( i==0 || i == points.size() - 1 )
//            curColor = secondaryColor;
//        else curColor = mainColor;

        view->setCellColor(curPoint,curColor);
    }

    if(!highlight)
        return;

    StepPoints mainPoints = algorithm->getMainPoints();
    QPoint curPoint;
    while(!mainPoints.isEmpty())
    {
        curPoint = mainPoints.at(0);
        mainPoints.pop_front();
        view->setCellColor(curPoint,secondaryColor);
    }
}

void CPainter::drawParabola(CCoordinateView *view, CAbstractPaintAlgorithm *algorithm, QPoint startPoint, QColor mainColor, QColor secondaryColor, bool highlight)
{
    StepPoints points = algorithm->getDrawPoints();
    QColor curColor = mainColor;
    for( int i=0; i<points.size(); i++)
    {
        QPoint curPoint = points.at(i);
//        if( i==0 || i == points.size() - 1 )
//            curColor = secondaryColor;
//        else curColor = mainColor;

        view->setCellColor(curPoint,curColor);
    }
    if(!highlight)
        return;

    StepPoints mainPoints = algorithm->getMainPoints();
    QPoint curPoint;
    while(!mainPoints.isEmpty())
    {
        curPoint = mainPoints.at(0);
        mainPoints.pop_front();
        view->setCellColor(curPoint,secondaryColor);
    }

}


void CPainter::drawBSpline(CCoordinateView *view, CAbstractPaintAlgorithm *algorithm, QColor mainColor, QColor secondaryColor, bool highlight)
{
    StepPoints points = algorithm->getDrawPoints();
    QColor curColor = mainColor;
    for( int i=0; i<points.size(); i++)
    {
        QPoint curPoint = points.at(i);
//        if( i==0 || i == points.size() - 1 )
//            curColor = secondaryColor;
//        else curColor = mainColor;

        view->setCellColor(curPoint,curColor);
    }
    if(!highlight)
        return;

    StepPoints mainPoints = algorithm->getMainPoints();
    QPoint curPoint;
    while(!mainPoints.isEmpty())
    {
        curPoint = mainPoints.at(0);
        mainPoints.pop_front();
        view->setCellColor(curPoint,secondaryColor);
    }

}



void CPainter::drawDebugLine(CCoordinateView *view, CAbstractPaintAlgorithm *algorithm, QTextBrowser *textBrowser, QUndoStack *undoStack, QPoint startPoint, QPoint endPoint, QColor mainColor, QColor secondaryColor)
{
    QColor curColor = mainColor;
    std::vector<QUndoCommand *> commands;
    undoStack->push(new CChangeBrowserTextCommand(textBrowser,algorithm->getInitInfo()));
    algorithm->reset();
    QPoint curPoint;
    while(algorithm->nextStep())
    {
        curPoint = algorithm->getStepDrawPoint().at(0);
        if(curPoint == startPoint || curPoint == endPoint)
        {
            curColor = secondaryColor;
        }
        else
        {
            curColor = mainColor;
        }
        commands.push_back(new CChangeCellColorCommand(view,curPoint.x(),curPoint.y(),curColor));
        commands.push_back(new CChangeBrowserTextCommand(textBrowser,algorithm->getInfo()));
        undoStack->push(new CCommandGroup(commands));
        commands.clear();
    }
    while(undoStack->canUndo())
        undoStack->undo();
}
