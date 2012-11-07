#ifndef DEBUGANIMATION_H
#define DEBUGANIMATION_H

#include <QObject>

#include <QTimer>

#include "debugmodebox.h"
#include "coordinateview.h"

class CDebugAnimation : public QObject
{
    Q_OBJECT
public:
    explicit CDebugAnimation(CCoordinateView *view, CDebugModeBox *debugBox, int interval, QObject *parent = 0);
    
signals:
    void finished();
public slots:
    void process();
    void start();
    void stop();
    void pause();
    void setInterval(int interval);

private slots:
    void timerSlot();

private:
    QTimer m_timer;
    CCoordinateView *m_pView;
    CDebugModeBox *m_pDebugBox;
    int m_interval;
};

#endif // DEBUGANIMATION_H
