#include "debugmodebox.h"
#include "ui_debugmodebox.h"
#include "debuganimation.h"

void CDebugModeBox::setData(CAbstractPaintAlgorithm *algorithm, CCoordinateView *view, QColor color, QColor secondaryColor)
{
    clear();

    m_pAlgorithm = algorithm;
    m_color = color;
    m_pView = view;


    m_secondaryColor = secondaryColor;


    _init();

    this->setEnabled(true);



}

CDebugModeBox::CDebugModeBox(QWidget *parent)
    :QGroupBox(parent),
      ui(new Ui::CDebugModeBox)
{
    ui->setupUi(this);

    m_pAlgorithm = NULL;

    connect(ui->btnNextStep,SIGNAL(clicked()),this,SLOT(nextStep()));
    connect(ui->btnPreviosStep,SIGNAL(clicked()),this,SLOT(previosStep()));
    connect(ui->btnToBegin,SIGNAL(clicked()),this,SLOT(goToBegin()));
    connect(ui->btnToEnd,SIGNAL(clicked()),this,SLOT(goToEnd()));
    connect(&m_undoStack,SIGNAL(indexChanged(int)),this,SLOT(stackIndexChanged(int)));

    //connect(ui->pushBtnNextTh,SIGNAL(clicked()),this,SLOT(nextStepTh()));
    //connect(ui->pushBtnPrevTh,SIGNAL(clicked()),this,SLOT(prevStepTh()));
    connect(ui->pushBtnStartTh,SIGNAL(clicked()),this,SLOT(startTh()));

    connect(ui->timeSlider,SIGNAL(valueChanged(int)),this,SLOT(valueChanged(int)));

//    ui->btnNextStep->setShortcut(Qt::CTRL + Qt::Key_N);
//    ui->btnPreviosStep->setShortcut(Qt::CTRL + Qt::Key_P);
//    ui->btnToBegin->setShortcut(Qt::CTRL + Qt::Key_S);
//    ui->btnToEnd->setShortcut(Qt::CTRL + Qt::Key_E);


    m_pAnimationThread = new QThread();
    m_pDebugAnimation = new CDebugAnimation(m_pView,this,timerInterval(),m_pAnimationThread);

    QObject::connect(m_pAnimationThread,SIGNAL(started()),m_pDebugAnimation,SLOT(process()));
    QObject::connect(this,SIGNAL(startAnimation()),m_pDebugAnimation,SLOT(start()));
    //m_pDebugAnimation->moveToThread(m_pAnimationThread);
    m_pAnimationThread->start();
    QObject::connect(m_pDebugAnimation,SIGNAL(finished()),this,SLOT(finishThread()));
    //QObject::connect(m_pDebugAnimation,SIGNAL(finished()),m_pDebugAnimation,SLOT(deleteLater()));
    //QObject::connect(m_pAnimationThread,SIGNAL(finished()),m_pAnimationThread,SLOT(deleteLater()));

    m_bIsDebugEnable = false;


}

void CDebugModeBox::_init()
{

    // создаём стек точек и текстовой информации
    m_pAlgorithm->reset();
    StepPoints stepPoints;
    QPoint point;
    std::vector<QUndoCommand *> undoCommands;

    StepPoints mainPoints = m_pAlgorithm->getMainPoints();
    StepPoints::iterator it;

    for(it=mainPoints.begin(); it!=mainPoints.end(); it++)
    {
        point = *it;
        m_undoStackMainPoints.push(new CChangeCellColorCommand(m_pView, point.x(), point.y(),m_secondaryColor));
    }

    // добавляем начальную информацию
    m_undoStack.push(new CChangeBrowserTextCommand(ui->textBrowser,m_pAlgorithm->getInitInfo()));

    while(m_pAlgorithm->nextStep())
    {
        undoCommands.clear();
        stepPoints.clear();
        stepPoints =  m_pAlgorithm->getStepDrawPoint();
        StepPoints::iterator it;

        if(stepPoints.isEmpty())
            continue;


        for(it = stepPoints.begin(); it != stepPoints.end(); it++)
        {
            point = *it;
            undoCommands.push_back(new CChangeCellColorCommand(m_pView,point.x(),point.y(),m_color));
        }
        undoCommands.push_back(new CChangeBrowserTextCommand(ui->textBrowser,m_pAlgorithm->getInfo()));
        m_undoStack.push( new CCommandGroup(undoCommands));
        //qDebug()<< m_undoStack.count();
    }



    goToBegin();
}

CDebugModeBox::~CDebugModeBox()
{
    qDebug() << "CDebugModeBox::~CDebugModeBox()";
    clear();
    delete ui;
}



void CDebugModeBox::goToBegin()
{
    if(m_undoStack.count()>=1) m_undoStack.setIndex(1);
    _firstItem();
}


void CDebugModeBox::goToEnd()
{
    m_undoStack.setIndex(m_undoStack.count());
    _lastItem();
}


void CDebugModeBox::nextStep()
{
    m_undoStack.redo();
    if(!m_undoStack.canRedo())
        _lastItem();
}


void CDebugModeBox::previosStep()
{
    m_undoStack.undo();
    if(!m_undoStack.canUndo())
        _firstItem();
}

void CDebugModeBox::_lastItem()
{
    ui->btnToEnd->setDisabled(true);
    ui->btnToBegin->setEnabled(true);
    ui->btnPreviosStep->setEnabled(true);
    ui->btnNextStep->setDisabled(true);
}

void CDebugModeBox::_firstItem()
{
    ui->btnToBegin->setDisabled(true);
    ui->btnToEnd->setEnabled(true);
    ui->btnNextStep->setEnabled(true);
    ui->btnPreviosStep->setDisabled(true);
}



void CDebugModeBox::stackIndexChanged(int index)
{
    if(index == 1)
        _firstItem();
    else if(index == m_undoStack.count())
        _lastItem();
    else
        _middleItem();

}


void CDebugModeBox::_middleItem()
{
    ui->btnNextStep->setEnabled(true);
    ui->btnPreviosStep->setEnabled(true);
    ui->btnToBegin->setEnabled(true);
    ui->btnToEnd->setEnabled(true);
}

int CDebugModeBox::timerInterval()
{
    qDebug() << ui->timeSlider->value()*10+1;
    return ui->timeSlider->value()*10+1;
}

void CDebugModeBox::clear()
{
    this->setDisabled(true);
    goToBegin();
    ui->textBrowser->clear();
    m_undoStack.clear();

    while(m_undoStackMainPoints.canUndo())
        m_undoStackMainPoints.undo();
    m_undoStackMainPoints.clear();
}


void CDebugModeBox::fix()
{

    m_pDebugAnimation->stop();

    while(m_undoStackMainPoints.canUndo())
        m_undoStackMainPoints.undo();
    m_undoStackMainPoints.clear();
    goToBegin();
    goToEnd();
    m_undoStack.clear();

    clear();

}


void CDebugModeBox::hideMainPoints()
{
    while(m_undoStackMainPoints.canUndo())
        m_undoStackMainPoints.undo();
}


void CDebugModeBox::showMainPoints()
{
    while(m_undoStackMainPoints.canRedo())
        m_undoStackMainPoints.redo();
}


bool CDebugModeBox::canRedo()
{
    return m_undoStack.canRedo();
}

bool CDebugModeBox::canUndo()
{
    return m_undoStack.canUndo();
}

void CDebugModeBox::undo()
{
    previosStep();
}


void CDebugModeBox::redo()
{
    nextStep();
}


void CDebugModeBox::nextStepTh()
{

}


void CDebugModeBox::prevStepTh()
{

}


void CDebugModeBox::startTh()
{

    if(!m_bIsDebugEnable)
    {
        ui->pushBtnStartTh->setText("Стоп");
        //m_pThread->pause();
        m_bIsDebugEnable = true;
        m_pDebugAnimation->setInterval(timerInterval());
        m_pDebugAnimation->start();
        //QMetaObject::invokeMethod()
        //emit startAnimation();
        //m_pDebugAnimation->start();
    }
    else
    {
        m_pDebugAnimation->stop();
        ui->pushBtnStartTh->setText("Старт");
        m_bIsDebugEnable = false;
    }
}



void CDebugModeBox::finishThread()
{
    ui->pushBtnStartTh->setText("Старт");
    m_bIsDebugEnable = false;
}

void CDebugModeBox::valueChanged(int value)
{
    m_pDebugAnimation->setInterval(timerInterval());
}
