#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "command.h"

#include <QDebug>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _init();
}

MainWindow::~MainWindow()
{

    qDebug() << "MainWindow::~MainWindow()";
    if(m_pDebugBox!=NULL) delete m_pDebugBox;
    if(m_pView != NULL) delete m_pView;
    delete ui;
}


void MainWindow::_init()
{
    m_pView = new CCoordinateView(0);



    connect(m_pView,SIGNAL(clickOnCell(int,int)),this,SLOT(mouseClickOnCell(int,int)));
    connect(m_pView,SIGNAL(moveOnCell(int,int)),this,SLOT(mouseMoveOnCell(int,int)));
    connect(ui->btnZoomIn,SIGNAL(clicked()),m_pView,SLOT(zoomIn()));
    connect(ui->btnZoomOut,SIGNAL(clicked()),m_pView,SLOT(zoomOut()));

    connect(ui->btnMainColor,SIGNAL(clicked()),this,SLOT(setMainColor()));
    connect(ui->btnSecondaryColor,SIGNAL(clicked()),this,SLOT(setSecondaryColor()));

    connect(ui->btnClear,SIGNAL(clicked()),this,SLOT(clearView()));

    connect(ui->radioBtnDebugMode,SIGNAL(clicked()),this,SLOT(debugModeEnable()));
    connect(ui->radioBtnDefaultMode,SIGNAL(clicked()),this,SLOT(defaultModeEnable()));


    connect(ui->checkBoxHightlightEndPoints,SIGNAL(clicked()),this,SLOT(highlightEndPoints()));

    connect(ui->radioBtnAlgBrezenhema,SIGNAL(clicked()),this,SLOT(drawAlgorithmChanged()));
    connect(ui->radioBtnAlgDDA,SIGNAL(clicked()),this,SLOT(drawAlgorithmChanged()));

    ui->viewFrameGrid->addWidget(m_pView);

    m_pDebugBox = new CDebugModeBox(this);
    ui->sidePanel->addWidget(m_pDebugBox);
    m_pDebugBox->setDisabled(true);

    m_pTmpUndoStack.clear();

    m_firstPoint = QPoint(0,0);
    m_secondPoint = QPoint(0,0);

    m_btnClickState = MCS_UNDEFINED;

    m_bHighlightInitPoints = false;
    m_mainColor = QColor(Qt::blue);
    //m_mainColor.setAlpha(10);
    m_secondaryColor = QColor(Qt::red);


    ui->btnSecondaryColor->setAutoFillBackground(true);
    ui->btnMainColor->setAutoFillBackground(true);

    _setMainColor(m_mainColor);
    _setSecondaryColor(m_secondaryColor);


    ui->radioBtnAlgDDA->setChecked(true);
    ui->radioBtnAlgBrezenhema->setChecked(false);

    ui->radioBtnDefaultMode->setChecked(true);
    defaultModeEnable();

    //ui->debugInfoBrowser->setUndoRedoEnabled(true);

    m_drawShapeType = DST_LINE;

    m_pListener = new CListenerDDA(m_pView, m_pDebugBox,QColor(Qt::red), QColor(Qt::blue));


//    for(int i=0; i<250; i++)
//        for(int j=1;j<250;j++)
//        {
//            m_pView->setCellColor(QPoint(i-130,j-130),QColor(Qt::green));
//        }

}


void MainWindow::mouseClickOnCell(int x, int y)
{
//    qDebug() << "MainWindow::buttonClickOnCell (" << x << ", " << y << ")";

    m_pListener->mousePressEvent(QPoint(x,y));


//    switch(m_btnClickState){
//        case(MCS_UNDEFINED):
//            _mouseFirstClick(QPoint(x,y));
//            break;
//        case(MCS_FIRST_CLICK):
//            _mouseSecondClick(QPoint(x,y));
//            break;
//        default:
//            Q_ASSERT(!"UNDEFINED STATE IN SWITCH. ADD NEW CASE");
//    }

}


void MainWindow::mouseMoveOnCell(int x, int y)
{
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage(QString("Текущая позиция курсора (%1,%2)").arg(QString::number(x)).arg(QString::number(y)));
    m_pListener->mouseMoveEvent(QPoint(x,y));
//    switch(m_btnClickState){
//        case(MCS_UNDEFINED):
//            return;
//            break;
//        case(MCS_FIRST_CLICK):
//            _drawTempararyObjectAfterFirstClick(QPoint(x,y));
//            break;
//        default:
//            Q_ASSERT(!"UNDEFINED STATE IN SWITCH. ADD NEW CASE");
//    }
}


void MainWindow::_mouseFirstClick(QPoint cellPos)
{
    switch(m_drawShapeType)
    {
    case(DST_LINE):
        m_pDebugBox->fix();
        _fixTemporaryObject();
        m_firstPoint = cellPos;
        m_btnClickState = MCS_FIRST_CLICK;
        break;
    default:
        Q_ASSERT(!"UNDEFINED STATE IN SWITCH. ADD NEW CASE");
    }
}


void MainWindow::_mouseSecondClick(QPoint cellPos)
{
    switch(m_drawShapeType)
    {
    case(DST_LINE):
        m_secondPoint = cellPos;
        m_btnClickState = MCS_UNDEFINED;
        _drawCommonLine(m_firstPoint,m_secondPoint);
        break;
    default:
        Q_ASSERT(!"UNDEFINED STATE IN SWITCH. ADD NEW CASE");
    }
}

void MainWindow::_drawCommonLine(QPoint startPoint, QPoint endPoint)
{
    if(m_bDebugModeEnable)
    {
        _drawDebugLine(startPoint,endPoint);
    }
    else
    {
        _drawDefaultLine(startPoint,endPoint);
    }
}

void MainWindow::_drawDefaultLine(QPoint startPoint, QPoint endPoint)
{

    _removeTemporaryObject();
    CAbstractPaintAlgorithm *algorithm = _getCurrentPaintAlgorithm();

    CPainter::drawLine(m_pView,algorithm,startPoint,endPoint,_mainColor(),_secondaryColor());

    if(algorithm!=NULL)delete algorithm;

}


CAbstractPaintAlgorithm* MainWindow::_getCurrentPaintAlgorithm()
{
    if(ui->radioBtnAlgBrezenhema->isChecked())
    {
        return new CAlgorithmBresenham(m_firstPoint,m_secondPoint);
    }
    else if(ui->radioBtnAlgDDA->isChecked())
    {
        return  new CAlgorithmDDA(m_firstPoint,m_secondPoint);
    }
}

void MainWindow::_drawDebugLine(QPoint startPoint, QPoint endPoint)
{
    _removeTemporaryObject();
    m_pDebugBox->setData(_getCurrentPaintAlgorithm(),m_pView,_mainColor());
}


QColor MainWindow::_mainColor()
{
    return m_mainColor;
}


QColor MainWindow::_secondaryColor()
{
    if(m_bHighlightInitPoints)
        return m_secondaryColor;
    else return m_mainColor;
}



void MainWindow::setMainColor()
{
    _setMainColor(QColorDialog::getColor(m_mainColor,this));

}


void MainWindow::setSecondaryColor()
{
    _setSecondaryColor(QColorDialog::getColor(m_secondaryColor,this));
}


void MainWindow::_setMainColor(QColor color)
{
    if(!color.isValid())
        return;
    m_mainColor = color;
    ui->btnMainColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3); color: rgb(255, 255, 255)")
                                    .arg(QString::number(m_mainColor.red()))
                                    .arg(QString::number(m_mainColor.green()))
                                    .arg(QString::number(m_mainColor.blue())));
}


void MainWindow::_setSecondaryColor(QColor color)
{
    if(!color.isValid())
        return;
    m_secondaryColor = color;
    ui->btnSecondaryColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3); color: rgb(255, 255, 255)")
                                    .arg(QString::number(m_secondaryColor.red()))
                                    .arg(QString::number(m_secondaryColor.green()))
                                    .arg(QString::number(m_secondaryColor.blue())));
}



void MainWindow::defaultModeEnable()
{
    _removeTemporaryObject();
    m_pDebugBox->fix();
    m_bDebugModeEnable = false;
    _switchMode();
}


void MainWindow::debugModeEnable()
{
    _removeTemporaryObject();
    m_bDebugModeEnable = true;
    _switchMode();
}


void MainWindow::clearView()
{
    m_pView->clear();
    _removeTemporaryObject();
    m_btnClickState = MCS_UNDEFINED;
    m_pDebugBox->clear();
}


void MainWindow::zoomIn()
{

}

void MainWindow::zoomOut()
{

}


void MainWindow::highlightEndPoints()
{
    if(ui->checkBoxHightlightEndPoints->isChecked())
        m_bHighlightInitPoints = true;
    else m_bHighlightInitPoints = false;
}


void MainWindow::_switchMode()
{
    m_btnClickState = MCS_UNDEFINED;

}


void MainWindow::_drawTempararyObjectAfterFirstClick(QPoint curentPos)
{
    switch(m_drawShapeType)
    {
     case (DST_LINE):
        _removeTemporaryObject();
        m_secondPoint = curentPos;
        _drawTemporaryLine(m_firstPoint,curentPos);
        break;
    default:
        Q_ASSERT(!"UNDEFINED STATE IN SWITCH. ADD NEW CASE");
    }
}



void MainWindow::_removeTemporaryObject()
{
    while(m_pTmpUndoStack.canUndo())
        m_pTmpUndoStack.undo();
    m_pTmpUndoStack.clear();
}


void MainWindow::_drawTemporaryLine(QPoint startPoint, QPoint endPoint)
{
    CAbstractPaintAlgorithm *alg = _getCurrentPaintAlgorithm();
    StepPoints points = alg->getDrawPoints();
    StepPoints::iterator it;
    QPoint point;
    for(it = points.begin(); it!=points.end(); it++)
    {
        point = *it;
        QColor color = _mainColor();
        color.setAlpha(100);
        m_pTmpUndoStack.push(new CChangeCellColorCommand(m_pView,point.x(),point.y(),color));
    }
}

void MainWindow::_fixTemporaryObject()
{
    while(m_pTmpUndoStack.canRedo())
        m_pTmpUndoStack.redo();
    m_pTmpUndoStack.clear();
}



void MainWindow::drawAlgorithmChanged()
{
    _removeTemporaryObject();
    m_btnClickState = MCS_UNDEFINED;
}
