#ifndef DEBUGMODEBOX_H
#define DEBUGMODEBOX_H

#include <QGroupBox>
#include <QUndoStack>
#include <QUndoCommand>


#include "painter.h"
#include "abstractpaintalgorithm.h"

namespace Ui {
class CDebugModeBox;
}

class CDebugModeBox : public QGroupBox
{
    Q_OBJECT
    
public:
    void setData(CAbstractPaintAlgorithm *algorithm, CCoordinateView *view, QColor color, QColor secondaryColor);
    void clear();
    explicit CDebugModeBox(QWidget *parent = 0);
    void fix();
    ~CDebugModeBox();
    void hideMainPoints();
    void showMainPoints();

private:
    void _init();
    void _lastItem();
    void _firstItem();
    void _middleItem();
    CAbstractPaintAlgorithm *m_pAlgorithm;
    QUndoStack m_undoStack;
    QUndoStack m_undoStackMainPoints;
    QColor m_color;
    QColor m_secondaryColor;
    Ui::CDebugModeBox *ui;
    CCoordinateView *m_pView;


private slots:
    void nextStep();
    void previosStep();
    void goToBegin();
    void goToEnd();
    void stackIndexChanged(int index);
};

#endif // DEBUGMODEBOX_H
