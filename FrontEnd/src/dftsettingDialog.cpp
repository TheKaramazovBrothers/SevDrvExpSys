//=========================================================================================================
// project		:	dft dialog setting module design
// File			:	dftsettingDialog.cpp
// discription	:	use for dft setting dialog module design for servo system
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g
// date			:	2022/12/21
// copyright(C)	:	liu.g	(2022-2032)
//=========================================================================================================
#include "SignalAnalysis.h"
#include "plotunitgraph.h"
#include "dialogselectcurve.h"
#include "OrthCorelAnalysis.h"
#include "Cia402AppEmu.h"

#include "dftsettingDialog.h"

#include <math.h>

DFTSettingDialog::DFTSettingDialog(QWidget *parent):QDialog(parent)
{
    setupUi(this);
    initDialogUi();
    setSignalSlotConnections();
}


void DFTSettingDialog::setFreResData(QVector<double> * freq_vec, QVector<double> * amp_vec, QVector<double> * phase_vec)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_freq          =       freq_vec;
    m_amp           =       amp_vec;
    m_phase         =       phase_vec;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

void DFTSettingDialog::initDialogUi()
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);

    QSize iconSize(24,24);

    setWindowIcon(QIcon(":/res/images/view.png"));

    toolButton_open->setIcon(QIcon(":/res/images/plot_open.png"));
    toolButton_open->setIconSize(iconSize);

    toolButton_save->setIcon(QIcon(":/res/images/save.png"));
    toolButton_save->setIconSize(iconSize);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    tqr_factor      =       0.4;
    curr_unit       =       A_CURR_EXCI_UNIT;
    vel_unit        =       RADS_VEL_EXCI_UNIT;

    start_fn        =       F20_HZ_FRE;
    end_fn          =       F40_HZ_FRE;
    Jall            =       0.0;

    kg_adj          =       1.0;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    comboBox_current_unit->setCurrentIndex(curr_unit);
    comboBox_velocity_unit->setCurrentIndex(vel_unit);

    QString     str;
    str             =       QString::number(tqr_factor);
    lineEdit_tqr_factor->setText(str);

//    QRegExp regexp_0To360("^([0-9]|[1-9]\\d|[1-2]\\d{0,2}|3[0-5]\\d|360)$");
//    QRegExp regexp_0To100("^([0-9]|[1-9]\\d|[1][0][0])$");
//    QRegExp regexp_D0To100("^([0-9]|[0-9]\\.[0-9]|[1-9][0-9]|[1-9][0-9]\\.[0-9]|[1][0][0]|[1][0][0]\\.[0])$");

    QRegExp regexp_D0To1000_4("^([0-9]|[0-9]\\.[0-9]{0,4}|[1-9][0-9]|[1-9][0-9]\\.[0-9]{0,4}|[1-9][0-9][0-9]|[1-9][0-9][0-9]\\.[0-9]{0,4}|[1][0][0][0]|[1][0][0][0]\\.[0])$");


    lineEdit_tqr_factor->setValidator(new QRegExpValidator(regexp_D0To1000_4));

    comboBox_start_fre->setCurrentIndex(start_fn);
    comboBox_end_fre->setCurrentIndex(end_fn);
    str             =       QString::number(Jall);
    lineEdit_inertia_result->setText(str);
    lineEdit_inertia_result->setEnabled(false);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    widget_plot_amp->xAxis->setRange(1, 10000);
    widget_plot_amp->yAxis->setRange(-50, 50);
    widget_plot_phase->xAxis->setRange(1, 10000);
    widget_plot_phase->yAxis->setRange(-180, 180);

    widget_plot_amp->replot();
    widget_plot_phase->replot();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


void DFTSettingDialog::setSignalSlotConnections()
{
    connect(lineEdit_tqr_factor,SIGNAL(textEdited(const QString &)),this,SLOT(onLineEditTqrFactorValueEdited(const QString &)));
    connect(lineEdit_tqr_factor,SIGNAL(returnPressed()),this,SLOT(onLineEditTqrFactorreturnPressed()));

    connect(pushButton_calculate,SIGNAL(clicked(bool)),this,SLOT(onPushButtonCalculateClicked(bool)));

    connect(widget_plot_amp, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onPlotAmplitudeMouseMoved(QMouseEvent*)));
    connect(widget_plot_phase, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onPlotPhaseMouseMoved(QMouseEvent*)));
}



void DFTSettingDialog::onLineEditTqrFactorValueEdited(const QString & value)
{
    lineEdit_tqr_factor->setStyleSheet("color:red");
}

void DFTSettingDialog::onLineEditTqrFactorreturnPressed(void)
{
    tqr_factor                  =   lineEdit_tqr_factor->text().toDouble();

    lineEdit_tqr_factor->setStyleSheet("color:black");
}


void DFTSettingDialog::onPlotAmplitudeMouseMoved(QMouseEvent *event)
{
    double dx = widget_plot_amp->xAxis->pixelToCoord(event->x());
    double dy = widget_plot_amp->yAxis->pixelToCoord(event->y());

    QCPRange cpX = widget_plot_amp->xAxis->range();
    QCPRange cpY = widget_plot_amp->yAxis->range();

    if (cpX.contains(dx) && cpY.contains(dy)) {
        label_amp->setText(tr("Amplitude Information:  frequency: %1 HZ , AMP: %2 DB")\
                                       .arg(QString::number(dx, 'E', 4))\
                                       .arg(QString::number(dy, 'f', 2)));
    }
}

void DFTSettingDialog::onPlotPhaseMouseMoved(QMouseEvent *event)
{
    double dx = widget_plot_phase->xAxis->pixelToCoord(event->x());
    double dy = widget_plot_phase->yAxis->pixelToCoord(event->y());

    QCPRange cpX = widget_plot_phase->xAxis->range();
    QCPRange cpY = widget_plot_phase->yAxis->range();

    if (cpX.contains(dx) && cpY.contains(dy)) {
        label_phase->setText(tr("Phase Information:  frequency: %1 HZ , Phase: %2 deg")\
                                       .arg(QString::number(dx, 'E', 4))\
                                       .arg(QString::number(dy, 'f', 2)));
    }
}



void DFTSettingDialog::onPushButtonCalculateClicked(bool checked)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    curr_unit                   =   (CurrUnitSel)(comboBox_current_unit->currentIndex());
    vel_unit                    =   (VelUnitSel)(comboBox_velocity_unit->currentIndex());
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    start_fn                    =   (FreSelOfBode)(comboBox_start_fre->currentIndex());
    end_fn                      =   (FreSelOfBode)(comboBox_end_fre->currentIndex());

    if (end_fn <= start_fn)
    {
        if (end_fn == start_fn)
        {
            if (end_fn == F10_HZ_FRE)
            {
                end_fn      =   F20_HZ_FRE;
            }
            else if (start_fn == F100_HZ_FRE)
            {
                start_fn    =   F90_HZ_FRE;
            }
            else
            {
                end_fn      =   (FreSelOfBode)((int)(end_fn) + 1);
            }

        }
        else
        {
            FreSelOfBode        fre_tmp     =   end_fn;
            end_fn                          =   start_fn;
            start_fn                        =   fre_tmp;
        }

        comboBox_start_fre->setCurrentIndex(start_fn);
        comboBox_end_fre->setCurrentIndex(end_fn);
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    double start_hz;
    double end_hz;

    int start_inx;
    int end_inx;

    double  start_db, start_amp;
    double  end_db, end_amp;
    double  a2, a1, dtmp, w2, w1, adj_db;

    start_hz            =   ((int)(start_fn) + 1) * 10;
    end_hz              =   ((int)(end_fn) + 1) * 10;

    start_inx           =   m_freq->indexOf(start_hz);
    end_inx             =   m_freq->indexOf(end_hz);

    if ((start_inx < 0) || (end_inx < 0))
    {
        return;
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    start_db            =   m_amp->at(start_inx)/20.0;
    end_db              =   m_amp->at(end_inx)/20.0;

    start_amp           =   pow(10,start_db);
    end_amp             =   pow(10,end_db);

    kg_adj              =   1/(tqr_factor/sqrt(2.0));

    if (curr_unit == MA_CURR_EXCI_UNIT)
    {
        kg_adj          =   kg_adj*1000.0;
    }

    if (vel_unit == RPM_VEL_EXCI_UNIT)
    {
        kg_adj          =   kg_adj * 0.104719755;
    }
    else if (vel_unit == RPS_VEL_EXCI_UNIT)
    {
        kg_adj          =   kg_adj * 6.2831853;
    }

    a1                  =   kg_adj * start_amp;
    a2                  =   kg_adj * end_amp;

    w1                  =   start_hz * 6.2831853;
    w2                  =   end_hz * 6.2831853;

    dtmp                =   (1.0/(a2*a2) - 1.0/(a1*a1))/(w2*w2 - w1*w1);
    dtmp                =   sqrt(abs(dtmp));

    Jall                =   dtmp*1000000.0;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    QString     str;
    str                 =       QString::number(Jall);
    lineEdit_inertia_result->setText(str);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    mod_amp_norm.clear();
    adj_db              =   20 * log10(kg_adj);

    for (int i = 0; i < m_freq->count(); i++)
    {
        mod_amp_norm.append((m_amp->at(i)+adj_db));
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    widget_plot_amp->clearGraphs();
    widget_plot_phase->clearGraphs();

    widget_plot_amp->addGraph();
    widget_plot_amp->graph(0)->setPen(QPen(tbl_col[0]));
    widget_plot_amp->graph(0)->addData(*m_freq, mod_amp_norm);
    widget_plot_amp->rescaleAxes(true);

    widget_plot_phase->addGraph();
    widget_plot_phase->graph(0)->setPen(QPen(tbl_col[0]));
    widget_plot_phase->graph(0)->addData(*m_freq, *m_phase);
    widget_plot_phase->rescaleAxes(true);

    widget_plot_amp->xAxis->setScaleType(QCPAxis::stLogarithmic);
    widget_plot_phase->xAxis->setScaleType(QCPAxis::stLogarithmic);

    widget_plot_amp->replot();
    widget_plot_phase->replot();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


DFTSettingDialog::~DFTSettingDialog()
{
    mod_amp_norm.clear();
}










//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
