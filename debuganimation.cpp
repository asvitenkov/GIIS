#include "debuganimation.h"

CDebugAnimation::CDebugAnimation(CCoordinateView *view, CDebugModeBox *debugBox, int interval, QObject *parent):
    QObject(parent), m_pView(view), m_pDebugBox(debugBox), m_interval(interval)
{
    qDebug() << m_timer.thread();
    qDebug() << this->thread();
}


void CDebugAnimation::start()
{
        m_timer.start(m_interval);
        qDebug() << m_timer.thread();
        qDebug() << this->thread();
}

void CDebugAnimation::stop()
{

        m_timer.stop();
        emit finished();

}

void CDebugAnimation::pause()
{

        m_timer.stop();

}

void CDebugAnimation::setInterval(int interval)
{
    if(interval<1)
        return;
    m_interval = interval;
    qDebug() << "interval =" << m_interval;
        if(m_timer.isActive())
        {
            m_timer.stop();
            m_timer.setInterval(interval);
            m_timer.start();
        }
        else
            m_timer.setInterval(interval);
}

void CDebugAnimation::timerSlot()
{
    if(m_pDebugBox->canRedo())
        m_pDebugBox->redo();
    else
        stop();
}


void CDebugAnimation::process()
{
    m_timer.setInterval(m_interval);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(timerSlot()));
}
