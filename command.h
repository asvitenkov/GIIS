#ifndef COMMAND_H
#define COMMAND_H

#include <QUndoCommand>
#include <QBrush>
#include "coordinateview.h"

#include <QTextBrowser>


class CChangeCellColorCommand: public QUndoCommand
{
public:
    CChangeCellColorCommand(CCoordinateView *view, int x, int y, QColor color);
    void undo();
    void redo();

private:
    CCoordinateView* m_pView;
    int m_nPosX;
    int m_nPosY;
    QColor m_oldColor;
    QColor m_newColor;
};




class CCommandGroup: public QUndoCommand
{
public:
    CCommandGroup(std::vector<QUndoCommand *> vCommand);
    void undo();
    void redo();

private:
    std::vector<QUndoCommand*> m_vCommands;
};



class CChangeBrowserTextCommand: public QUndoCommand
{
public:
    CChangeBrowserTextCommand(QTextBrowser *textBrowser,QString sText);
    void undo();
    void redo();
private:
    QString m_sOldText;
    QTextBrowser *m_pTextBrowser;
    QString m_sText;

};

#endif // COMMAND_H
