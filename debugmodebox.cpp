#include "debugmodebox.h"
#include "ui_debugmodebox.h"

void CDebugModeBox::setData(CAbstractPaintAlgorithm *algorithm, CCoordinateView *view, QColor color)
{
    clear();

    m_pAlgorithm = algorithm;
    m_color = color;
    m_pView = view;

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

}

void CDebugModeBox::_init()
{

    // создаём стек точек и текстовой информации
    m_pAlgorithm->reset();
    StepPoints stepPoints;
    std::vector<QUndoCommand *> undoCommands;

    // добавляем начальную информацию
    m_undoStack.push(new CChangeBrowserTextCommand(ui->textBrowser,m_pAlgorithm->getInitInfo()));

    while(m_pAlgorithm->nextStep())
    {
        undoCommands.clear();
        stepPoints.clear();
        stepPoints =  m_pAlgorithm->getStepDrawPoint();
        StepPoints::iterator it;

        QPoint point;
        for(it = stepPoints.begin(); it != stepPoints.end(); it++)
        {
            point = *it;
            undoCommands.push_back(new CChangeCellColorCommand(m_pView,point.x(),point.y(),m_color));
        }
        undoCommands.push_back(new CChangeBrowserTextCommand(ui->textBrowser,m_pAlgorithm->getInfo()));
        m_undoStack.push( new CCommandGroup(undoCommands));
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

void CDebugModeBox::clear()
{
    this->setDisabled(true);
    goToBegin();
    ui->textBrowser->clear();
    //if(m_pAlgorithm!=NULL) {delete m_pAlgorithm; m_pAlgorithm = NULL;}
    m_undoStack.clear();
}


void CDebugModeBox::fix()
{
    goToEnd();
    m_undoStack.clear();
    clear();
}
