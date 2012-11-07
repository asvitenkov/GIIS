#ifndef DEBUGMODEBOX_H
#define DEBUGMODEBOX_H

#include <QGroupBox>
#include <QUndoStack>
#include <QUndoCommand>
#include <QThread>

#include "painter.h"
#include "abstractpaintalgorithm.h"


class CDebugAnimation;

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
    bool canRedo();
    bool canUndo();
    void undo();
    void redo();



public slots:
    void finishThread();
private:
    void _init();
    void _lastItem();
    void _firstItem();
    void _middleItem();
    int timerInterval();
    CAbstractPaintAlgorithm *m_pAlgorithm;
    QUndoStack m_undoStack;
    QUndoStack m_undoStackMainPoints;
    QColor m_color;
    QColor m_secondaryColor;
    Ui::CDebugModeBox *ui;
    CCoordinateView *m_pView;

    CDebugAnimation *m_pDebugAnimation;
    QThread *m_pAnimationThread;

    bool m_bIsDebugEnable;


private slots:
    void valueChanged(int value);

    void nextStepTh();
    void prevStepTh();
    void startTh();
    void nextStep();
    void previosStep();
    void goToBegin();
    void goToEnd();
    void stackIndexChanged(int index);
signals:
    void startAnimation();
};

#endif // DEBUGMODEBOX_H
