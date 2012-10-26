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

    QMap<QObject*, CAbstractListener*>::iterator it = m_listenersMap.begin();
    CAbstractListener *listener;
    qDebug() << m_listenersMap.size();
    while( it != m_listenersMap.end())
    {
        listener = *it;
        delete listener;
        it++;
    }


    if(m_pDebugBox!=NULL) delete m_pDebugBox;
    if(m_pView != NULL) delete m_pView;


    delete ui;



}


void MainWindow::_init()
{
    m_pView = new CCoordinateView(0);


    ui->viewFrameGrid->addWidget(m_pView);

    m_pDebugBox = new CDebugModeBox(this);
    ui->sidePanel->addWidget(m_pDebugBox);
    m_pDebugBox->setDisabled(true);

    m_pTmpUndoStack.clear();

    m_firstPoint = QPoint(0,0);
    m_secondPoint = QPoint(0,0);

    m_btnClickState = MCS_UNDEFINED;

    m_pCurrentListener = NULL;

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
    //defaultModeEnable();

    //ui->debugInfoBrowser->setUndoRedoEnabled(true);

    m_drawShapeType = DST_LINE;

    //m_pListener = new CListenerLineDDA(m_pView, m_pDebugBox,QColor(Qt::red), QColor(Qt::blue));

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

    connect(ui->tabAlgorithms,SIGNAL(currentChanged(int)),this,SLOT(algorithmTabIndexChanged(int)));

    ui->radioBtnAlgDDA->setChecked(true);
    ui->radioBtnAlgBrezenhema->setChecked(false);
    ui->radioBtnDefaultMode->setChecked(true);

//    for(int i=0; i<250; i++)
//        for(int j=1;j<250;j++)
//        {
//            m_pView->setCellColor(QPoint(i-130,j-130),QColor(Qt::green));
//        }
    createListeners();
    ui->radioBtnAlgDDA->click();
}


void MainWindow::mouseClickOnCell(int x, int y)
{
    if(m_pCurrentListener != NULL)
        m_pCurrentListener->mousePressEvent(QPoint(x,y));
}


void MainWindow::mouseMoveOnCell(int x, int y)
{
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage(QString("Текущая позиция курсора (%1,%2)").arg(QString::number(x)).arg(QString::number(y)));
    if(m_pCurrentListener != NULL)
        m_pCurrentListener->mouseMoveEvent(QPoint(x,y));
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
    if(m_pCurrentListener!=NULL)
    {
        m_pCurrentListener->reset();
        m_mode = MODE_NORMAL;
        m_pCurrentListener->setMode(m_mode);
    }
}


void MainWindow::debugModeEnable()
{
    if(m_pCurrentListener!=NULL){
        m_pCurrentListener->reset();
        m_mode = MODE_DEBUG;
        m_pCurrentListener->setMode(m_mode);
    }
}


void MainWindow::clearView()
{

    m_pDebugBox->clear();
    if(m_pCurrentListener != NULL)
        m_pCurrentListener->reset();
     m_pView->clear();
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


void MainWindow::drawAlgorithmChanged()
{
    qDebug() << "drawAlgorithmChanged";
    QObject *objSender = sender();
    if(objSender == NULL) return;
    QMap<QObject*, CAbstractListener*>::iterator it=m_listenersMap.find(objSender);
    if(it!=m_listenersMap.end())
    {
        if( m_pCurrentListener != NULL ) m_pCurrentListener->reset();
        m_pCurrentListener = *it;
        qDebug() << "current listener is " << m_pCurrentListener->name();
    }
    else
    {
        qCritical("MainWindow::drawAlgorithmChanged() undef algorithm" );
        if( m_pCurrentListener != NULL ) m_pCurrentListener->reset();
        m_pCurrentListener = NULL;
    }

}


void MainWindow::createListeners()
{
    m_listenersMap.insert(ui->radioBtnAlgDDA, new CListenerLineDDA(m_pView,m_pDebugBox,m_mainColor,m_secondaryColor));
    m_listenersMap.insert(ui->radioBtnAlgBrezenhema, new CListenerLineBresenham(m_pView,m_pDebugBox,m_mainColor,m_secondaryColor));
    //m_listenersMap.insert(ui->radioBtnAlgBrezenhema, new CListenerDDA(m_pView,m_pDebugBox,m_mainColor,m_secondaryColor));
}


void MainWindow::algorithmTabIndexChanged(int index)
{
    qDebug() << index;
    QWidget *curTabWidget = ui->tabAlgorithms->widget(index);
    if(m_pCurrentListener != NULL)
        m_pCurrentListener->reset();
    if(curTabWidget == ui->algorithmLinesTab)
    {
        ui->radioBtnAlgDDA->click();
    }
    else{
        qCritical() << "void MainWindow::algorithmTabIndexChanged(int index) undefined tab ";
        m_pCurrentListener = NULL;
    }
}
