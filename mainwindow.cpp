#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qttreemanager.h"
#include "ui_plotunitgraph.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("expert system"));
    setWindowIcon(QIcon(":/res/images/person.png"));
    showMaximized();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    initNavgTree();
    createActions();

    uiPlot  =   new PlotUnitGraph(ui->stackedWidget);
    QWidget *w;
    w = static_cast<QWidget *>(uiPlot->splitter_plot_curve);

    ui->stackedWidget->addWidget(w);
    ui->stackedWidget->setVisible(true);

    ui->stackedWidget->setCurrentWidget(w);
    ui->stackedWidget->show();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initNavgTree()
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    treewidgetNav  =   QtTreeManager::createTreeWidgetFromXmlFile(QString(":/res/xml/NavgationTree.ui"));
    treewidgetNav->setHeaderHidden(true);
    treewidgetNav->setColumnHidden(1,true);
    treewidgetNav->expandAll();

    ui->dockWidgetNav->setWidget(treewidgetNav);
    treewidgetNav->setVisible(true);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

//***************************************************************************************************************************
//*                                     CREATE ACTION
//*
//* Description: This function is used to create action for main window
//*
//*
//* Arguments  : none
//*
//* Returns    : none
//***************************************************************************************************************************
void MainWindow::createActions()
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->mainToolBar->setIconSize(QSize(24,24));

    m_actnConnect   =   new QAction(this);
    m_actnConnect->setText(tr("connect"));
    m_actnConnect->setStatusTip(tr("connect to servo:you can manul to load by change"));

    m_actnDisNet    =   new QAction(this);
    m_actnDisNet->setText(tr("discnet"));

    m_actnConnect->setCheckable(true);
    m_actnDisNet->setCheckable(true);

    m_actnConnect->setChecked(false);
    m_actnDisNet->setChecked(true);

    m_actnDownload  =   new QAction(this);
    m_actnDownload->setText(tr("dnload"));
    m_actnDownload->setStatusTip(tr("download the  parameters to device"));

    m_actnUpload    =   new QAction(this);
    m_actnUpload->setText(tr("upload"));
    m_actnUpload->setStatusTip(tr("save the device parameters to xml files"));

    m_actnConfig    =   new QAction(this);
    m_actnConfig->setText(tr("config"));
    m_actnConfig->setStatusTip(tr("download the parameters to device and immediately active"));

    m_actnSave      =   new QAction(this);
    m_actnSave->setText(tr("save"));
    m_actnSave->setStatusTip(tr("permanently save the parameters to device\nyou should reset the system to make it active"));

    ui->mainToolBar->addAction(m_actnConnect);
    ui->mainToolBar->addAction(m_actnDisNet);

    ui->mainToolBar->addAction(m_actnDownload);
    ui->mainToolBar->addAction(m_actnUpload);
    ui->mainToolBar->addAction(m_actnConfig);
    ui->mainToolBar->addAction(m_actnSave);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_actnConnect->setIcon(QIcon(":/res/images/connect.png"));
    m_actnDisNet->setIcon(QIcon(":/res/images/disconnect.png"));
    m_actnDownload->setIcon(QIcon(":/res/images/menu_download.png"));
    m_actnUpload->setIcon(QIcon(":/res/images/menu_servo2file.png"));
    m_actnConfig->setIcon(QIcon(":/res/images/func_config.png"));
    m_actnSave->setIcon(QIcon(":/res/images/func_save.png"));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}




////////////////////////////////////////////////////// no more //////////////////////////////////////////////////////
