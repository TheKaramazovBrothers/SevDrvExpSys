//=========================================================================================================
// project		:	main window
// File			:	mainwindow.cpp
// discription	:
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g
// date			:	2022/07/01
// copyright(C)	:	liu.g	(2022-2032)
//=========================================================================================================

#include "ui_mainwindow.h"
#include "qttreemanager.h"
#include "ui_plotunitgraph.h"
#include "BackGroundTask.h"
#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/res/images/person.png"));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    initNavgTree();
    createActions();

    InitServoCtlTask();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    m_ram_obj_tbl           =   new SevPrmVarRamTable(this);
    m_flash_obj_tbl         =   new SevPrmFlashTable(this);

    ui->stackedWidget->addWidget(m_ram_obj_tbl);
    ui->stackedWidget->addWidget(m_flash_obj_tbl);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    uiPlot                  =   new PlotUnitGraph(this);
    wPlot                   =   static_cast<QWidget *>(uiPlot->splitter_plot_curve);

    ui->stackedWidget->addWidget(wPlot);
    ui->stackedWidget->setVisible(true);

    ui->stackedWidget->setCurrentWidget(wPlot);
    ui->stackedWidget->show();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_prm_service           =   new ConfigService;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    showMaximized();
    setWindowTitle(tr("expert system"));
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

MainWindow::~MainWindow()
{
    delete  m_ram_obj_tbl;
    delete  m_flash_obj_tbl;
    delete  uiPlot;
    delete  m_prm_service;

    delete  ui;
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
    connect(treewidgetNav, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(OnNavgTreeItemClicked(QTreeWidgetItem*)));
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
    connect(m_actnDownload, SIGNAL(triggered(bool)), this, SLOT(onLoadPrmButtonclicked(bool)));
    connect(m_actnUpload, SIGNAL(triggered(bool)), this, SLOT(onWritePrmButtonclicked(bool)));

    connect(m_actnSave, SIGNAL(triggered(bool)), this, SLOT(onSavePrmButtonclicked(bool)));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


void MainWindow::InitServoCtlTask()
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    TpiInitServoTask(&gSevDrv.task);

    CpiInitCiA402PrmObjPtr();
    CpiInitCiA402VarObjPtr();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    auto file   =   tr("./res/xml/PrmDefault");
    m_prm_service->load(file);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    TpiInitServoObjModule(&gSevDrv.obj);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


void MainWindow::onWritePrmButtonclicked(bool checked)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    auto file = QFileDialog::getSaveFileName(this);
    if(file.isEmpty())
        return;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_prm_service->write(file);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

void MainWindow::onLoadPrmButtonclicked(bool checked)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    auto file = QFileDialog::getOpenFileName(this);
    if(file.isEmpty())
        return;

    m_prm_service->load(file);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    TpiInitServoObjModule(&gSevDrv.obj);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


void MainWindow::onSavePrmButtonclicked(bool checked)
{
//    m_flash_obj_tbl
    Uint16  utmp;
    Uint32  lutmp;
    QString str;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    for (int i = 0; i < PRM_SERVO_OBJW_INX_MAX_NUM; i++)
    {
        str             =   m_flash_obj_tbl->item(i,1)->text();

        if (DefCiA402PrmObjDic[i].ObjDesc.DataType == DEFTYPE_UNSIGNED32)
        {
            lutmp               =   str.toULong();
            SclWriteFramPrmByID32(&lutmp, DefCiA402PrmObjDic[i].NonVolatileOffset);

        }
        else
        {
            utmp                =   str.toUShort();
            SclWriteFramPrmByID16(&utmp, DefCiA402PrmObjDic[i].NonVolatileOffset);
        }

        m_flash_obj_tbl->item(i,1)->setBackgroundColor(Qt::white);
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    ServoPrmReadFromFlashToRam();

    TpiInitServoObjModule(&gSevDrv.obj);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


void MainWindow::OnNavgTreeItemClicked(QTreeWidgetItem * item)
{
    int tmp                  =  item->text(1).toInt();

    switch (tmp)
    {
        case    112:
        {
            ui->stackedWidget->setCurrentWidget(m_ram_obj_tbl);
            m_ram_obj_tbl->updatePrmVarTableData();
            break;
        }
        case    113:
        {
            ui->stackedWidget->setCurrentWidget(m_flash_obj_tbl);
            m_flash_obj_tbl->updateFlashTableData();
            break;
        }
        default:
        {
            ui->stackedWidget->setCurrentWidget(wPlot);
            break;
        }
    }
    ui->stackedWidget->show();
//---------------------------------------------------------------------------------------
}

////////////////////////////////////////////////////// no more //////////////////////////////////////////////////////
