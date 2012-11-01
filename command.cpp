#include "command.h"


CChangeCellColorCommand::CChangeCellColorCommand(CCoordinateView *view, int x, int y, QColor color)
    :m_pView(view), m_nPosX(x), m_nPosY(y), m_newColor(color)
{
    m_oldColor = view->cellColor(x,y);
}



CChangeCellColorCommand::CChangeCellColorCommand(CCoordinateView *view, QPoint pos, QColor color)
    : m_pView(view), m_nPosX(pos.x()), m_nPosY(pos.y()), m_newColor(color)
{
    m_oldColor = view->cellColor(m_nPosX,m_nPosY);
}

void CChangeCellColorCommand::redo()
{
    m_pView->setCellColor(m_nPosX, m_nPosY, m_newColor);
}


void CChangeCellColorCommand::undo()
{
    m_pView->setCellColor(m_nPosX, m_nPosY, m_oldColor);
}



CCommandGroup::CCommandGroup(std::vector<QUndoCommand*> vCommand)
    :m_vCommands(vCommand)
{

}


void CCommandGroup::undo()
{
    std::vector<QUndoCommand*>::iterator it;
    QUndoCommand* command;
    for(it = m_vCommands.begin(); it!=m_vCommands.end(); it++)
    {
        command = *it;
        command->undo();
    }
}


void CCommandGroup::redo()
{
    std::vector<QUndoCommand*>::iterator it;
    QUndoCommand* command;
    for(it = m_vCommands.begin(); it!=m_vCommands.end(); it++)
    {
        command = *it;
        command->redo();
    }
}


CChangeBrowserTextCommand::CChangeBrowserTextCommand(QTextBrowser *textBrowser, QString sText)
     : m_pTextBrowser(textBrowser), m_sText(sText)
{
    m_sOldText = m_pTextBrowser->toPlainText();
}


void CChangeBrowserTextCommand::undo()
{
    m_pTextBrowser->clear();
    m_pTextBrowser->setText(m_sOldText);
}


void CChangeBrowserTextCommand::redo()
{
    m_pTextBrowser->clear();
    m_pTextBrowser->setText(m_sText);
}
