//=========================================================================================================
// project		:	dft dialog module design
// File			:	dftdialog.cpp
// discription	:	use for dft dialog module design for servo system
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g
// date			:	2022/09/09
// copyright(C)	:	liu.g	(2022-2032)
//=========================================================================================================

#include "SignalAnalysis.h"
#include "plotunitgraph.h"
#include "dialogselectcurve.h"
#include "OrthCorelAnalysis.h"
#include "Cia402AppEmu.h"

#include "my_fft.h"
#include "my_prbs_idf_n4sid.h"
#include "dftdialog.h"


DFTDialog::DFTDialog(QWidget *parent):QDialog(parent)
{
    setupUi(this);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    initDialogUi();
    setSignalSlotConnections();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    double  dtmp, dtmp2 ;

    CpiReadRamPrmByDicInx(SIN_HZ_START_EXCI_SIG_PRM_ID16_OBJW_203AH, &dtmp);
    m_sin_hz_start                  =   dtmp;                                                           // HZ

    CpiReadRamPrmByDicInx(SIN_HZ_STEP_EXCI_SIG_PRM_ID16_OBJW_203BH, &dtmp);
    m_sin_hz_step                   =   dtmp;                                                           // HZ

    CpiReadRamPrmByDicInx(SIN_HARM_NUM_EXCI_SIG_PRM_ID16_OBJW_203CH, &dtmp);
    m_sin_harm_num                  =   dtmp;                                                            // Harmonic number

    CpiReadRamPrmByDicInx(DELAY_TIM_EXCI_SIG_PRM_ID32_OBJW_2039H, &dtmp);
    CpiReadRamPrmByDicInx(TS_EXCI_SIG_PRM_ID32_OBJW_2036H, &dtmp2);

    m_sin_delay_tim                 =   dtmp * (dtmp2/1000000000.0);

    CpiReadRamPrmByDicInx(STEADY_TIM_EXCI_SIG_PRM_ID32_OBJW_2038H, &dtmp);
    m_sin_steady_tim                =   dtmp * (dtmp2/1000000000.0);                                    // by TS
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

void DFTDialog::initDialogUi()
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
    QSize iconSize(24,24);

    setWindowIcon(QIcon(":/res/images/view.png"));

    tbtn_fft_add->setIcon(QIcon(":/res/images/add.png"));
    tbtn_fft_add->setIconSize(iconSize);

    tbtn_fft_clear->setIcon(QIcon(":/res/images/clear.png"));
    tbtn_fft_clear->setIconSize(iconSize);

    tbtn_fft_fit->setIcon(QIcon(":/res/images/fit.png"));
    tbtn_fft_fit->setIconSize(iconSize);

    tbtn_fft_open->setIcon(QIcon(":/res/images/plot_open.png"));
    tbtn_fft_open->setIconSize(iconSize);

    tbtn_fft_amp->setIcon(QIcon(":/res/images/plot_fft_amp.png"));
    tbtn_fft_amp->setIconSize(iconSize);

    tbtn_fft_phase->setIcon(QIcon(":/res/images/plot_fft_pha.png"));
    tbtn_fft_phase->setIconSize(iconSize);

    tbtn_fft_remove->setIcon(QIcon(":/res/images/remove.png"));
    tbtn_fft_remove->setIconSize(iconSize);

    tbtn_fft_save->setIcon(QIcon(":/res/images/save.png"));
    tbtn_fft_save->setIconSize(iconSize);

    tbtn_fft_selectAll->setIcon(QIcon(":/res/images/all.png"));
    tbtn_fft_selectAll->setIconSize(iconSize);

    tbtn_fft_setting->setIcon(QIcon(":/res/images/plot_config.png"));
    tbtn_fft_setting->setIconSize(iconSize);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    progressBar->setValue(0);
    progressBar->setVisible(false);
    label_fft_processInfo->setVisible(false);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setMouseTracking(true);
    tableWidget->setColumnWidth(0, 120);
    tableWidget->horizontalHeader()->setStretchLastSection(true);

    for (int i = 0; i < MAX_TABLE_WAVE_NUM; i++)
    {
        wave_vis_tbl[i]             =   true;
    }
    all_show_flag           =   true;

    m_showColor             =   QColor(Qt::white);
    m_hideColor             =   QColor(Qt::gray);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    plot_amp->xAxis->setRange(1, 10000);
    plot_amp->yAxis->setRange(-50, 50);
    plot_phase->xAxis->setRange(1, 10000);
    plot_phase->yAxis->setRange(-180, 180);

    plot_amp->replot();
    plot_phase->replot();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_anys_type             =   ANALYSIS_SIGNAL;
    radioBtn_signal->setChecked(true);
    label_fft_output->setVisible(false);
    comboBox_fft_output->setVisible(false);

    label_fft_method->setVisible(false);
    comboBox_fft_method->setVisible(false);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

void DFTDialog::setSignalSlotConnections()
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    connect(tbtn_fft_amp, SIGNAL(clicked(bool)), this, SLOT(onBtnAmpClicked(bool)));
    connect(tbtn_fft_phase, SIGNAL(clicked(bool)), this, SLOT(onBtnPhaClicked(bool)));
    connect(radioBtn_signal, SIGNAL(clicked()), this, SLOT(onBtnSignalClicked()));
    connect(radioBtn_system, SIGNAL(clicked()), this, SLOT(onBtnSignalClicked()));
    connect(tbtn_fft_setting, SIGNAL(clicked()), this, SLOT(onBtnSettingClicked()));
    connect(tbtn_fft_fit, SIGNAL(clicked()), this, SLOT(onBtnFitClicked()));
    connect(tbtn_fft_open, SIGNAL(clicked()), this, SLOT(onBtnOpenClicked()));
    connect(tbtn_fft_save, SIGNAL(clicked()), this, SLOT(onBtnSaveClicked()));
    connect(tbtn_fft_add, SIGNAL(clicked()), this, SLOT(onBtnAddClicked()));
    connect(tbtn_fft_remove, SIGNAL(clicked()), this, SLOT(onBtnRemoveClicked()));
    connect(tbtn_fft_clear, SIGNAL(clicked()), this, SLOT(onBtnClearClicked()));
    connect(tbtn_fft_selectAll, SIGNAL(clicked()), this, SLOT(onBtnAllClicked()));
    connect(comboBox_fft_input, SIGNAL(activated(int)), this, SLOT(onComboBoxActivated(int)));

    connect(plot_amp, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onPlotAmplitudeMouseMoved(QMouseEvent*)));
    connect(plot_phase, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onPlotPhaseMouseMoved(QMouseEvent*)));

    connect(tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onTableItemClicked(QTableWidgetItem*)));
    connect(tableWidget, SIGNAL(cellEntered(int, int)), this, SLOT(onTableWidgetCellEnteredMoreDetail(int, int)));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


void DFTDialog::onBtnSignalClicked()
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (radioBtn_signal->isChecked())
    {
        m_anys_type             =   ANALYSIS_SIGNAL;
        label_fft_output->setVisible(false);
        comboBox_fft_output->setVisible(false);

        label_fft_method->setVisible(false);
        comboBox_fft_method->setVisible(false);
    }
    else
    {
        m_anys_type             =   ANALYSIS_SYSTEM;
        label_fft_output->setVisible(true);
        comboBox_fft_output->setVisible(true);

        label_fft_method->setVisible(true);
        comboBox_fft_method->setVisible(true);
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


void DFTDialog::onBtnAmpClicked(bool checked)
{
    if (checked)
    {
        plot_amp->setVisible(true);
        label_amp->setVisible(true);
    }
    else
    {
        plot_amp->setVisible(false);
        label_amp->setVisible(false);
    }
}


void DFTDialog::onBtnPhaClicked(bool checked)
{
    if (checked)
    {
        plot_phase->setVisible(true);
        label_phase->setVisible(true);
    }
    else
    {
        plot_phase->setVisible(false);
        label_phase->setVisible(false);
    }
}

void DFTDialog::onBtnSettingClicked()
{

}

void DFTDialog::onAxisRangeChanged(QVector<double> limitList)
{

}

void DFTDialog::onBtnFitClicked()
{    plot_amp->rescaleAxes(true);
     double low         = plot_amp->yAxis->range().lower;
     double upper       = plot_amp->yAxis->range().upper;
     double size        = plot_amp->yAxis->range().size();
     double dsize       = 0.1 * size;
     QCPRange plottableRange(low - dsize, upper + dsize);
     plot_amp->yAxis->setRange(plottableRange);
     plot_amp->replot();

     plot_phase->rescaleAxes(true);
     low                = plot_phase->yAxis->range().lower;
     upper              = plot_phase->yAxis->range().upper;
     size               = plot_phase->yAxis->range().size();
     dsize              = 0.1 * size;
     QCPRange plottableRange_phase(low - dsize, upper + dsize);
     plot_phase->yAxis->setRange(plottableRange_phase);
     plot_phase->replot();

}

void DFTDialog::onBtnOpenClicked()
{

}

void DFTDialog::onBtnSaveClicked()
{

}

void DFTDialog::onBtnAllClicked()
{
    int rowCount        =   tableWidget->rowCount();

    if (all_show_flag == false)
    {
        for (int i = 0; i < rowCount; i++)
        {
            tableWidget->item(i,0)->setBackgroundColor(m_showColor);
            plot_amp->graph(i)->setVisible(true);
            plot_phase->graph(i)->setVisible(true);
            wave_vis_tbl[i]         =   true;
        }
        all_show_flag               =   true;
    }
    else
    {
        for (int i = 0; i < rowCount; i++)
        {
            tableWidget->item(i,0)->setBackgroundColor(m_hideColor);
            plot_amp->graph(i)->setVisible(false);
            plot_phase->graph(i)->setVisible(false);
            wave_vis_tbl[i]         =   false;
        }
        all_show_flag               =   false;
    }

    plot_amp->replot();
    plot_phase->replot();
}

void DFTDialog::onBtnClearClicked()
{
    if (tableWidget->rowCount() >= 0)
    {
        plot_amp->clearGraphs();
        plot_phase->clearGraphs();
        tableWidget->setRowCount(0);
        tableWidget->clearContents();
        plot_amp->replot();
        plot_phase->replot();
    }
}

void DFTDialog::onBtnRemoveClicked()
{
    int row = 0;
    row = tableWidget->currentRow();
    if (row >= 0)
    {
        plot_amp->removeGraph(row);
        plot_phase->removeGraph(row);
        tableWidget->removeRow(row);
        plot_amp->replot();
        plot_phase->replot();
    }
}

void DFTDialog::onBtnAddClicked()
{
    QString str_ID, str_Name;
    double  startT, endT, minT, maxT, total_t, samplingFreq;
    double  *in, *out, *dbb, *phh, *m_dbb, *m_phh;
    int     inx, outx, length, startIndex, endIndex;

    if ((m_wave_name_tbl->rowCount() != 0) && (tableWidget->rowCount() < MAX_TABLE_WAVE_NUM))
    {
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        startT      =       doubleSpinBox_fft_start->value();
        endT        =       doubleSpinBox_fft_terminal->value();

        if (endT < startT)
        {
            doubleSpinBox_fft_start->setValue(endT);
            doubleSpinBox_fft_terminal->setValue(startT);

            startT      =       doubleSpinBox_fft_start->value();
            endT        =       doubleSpinBox_fft_terminal->value();
        }

        minT         =       m_key_list->first();
        maxT         =       m_key_list->last();

        if (startT < minT)
        {
            QMessageBox::information(0, tr("Range Error"), tr("StartTime out range"));
            return;
        }
        if (endT > maxT)
        {
            QMessageBox::information(0,tr("Range Error"),tr("EndTime out range"));
            return;
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        inx                     =   comboBox_fft_input->currentIndex();
        outx                    =   comboBox_fft_output->currentIndex();

        m_amp.clear();
        m_freq.clear();
        m_phase.clear();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        total_t                 =   maxT - minT;

        startIndex              =   ((startT-minT) / total_t) * m_key_list->count();
        endIndex                =   ((endT-minT) / total_t) * m_key_list->count();

        if ((endIndex - startIndex + 1) % 2 != 0)
        {
            endIndex = endIndex - 1;
        }

        length = endIndex - startIndex + 1;

        in          = new double[length];
        out         = new double[length];

        dbb         = new double[length];
        phh         = new double[length];

        for (int i = 0; i < length; i++)
        {
            in[i] = m_value_list->at(inx).at(i+startIndex);
            out[i] = m_value_list->at(outx).at(i+startIndex);
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        if(m_anys_type == ANALYSIS_SIGNAL)
        {          
            samplingFreq        = 1.0 / m_samp_tim;
            for (int i = 0; i < length / 2; i++)
            {
                m_freq.append(samplingFreq * i / length);
            }
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//            SignalAnalysisFFT(in, dbb, phh, length);
            my_fftInitialize();

            mwArray in_u0(1,length,mxDOUBLE_CLASS);
            mwArray out_phh(1,length,mxDOUBLE_CLASS);
            mwArray out_dbb(1,length,mxDOUBLE_CLASS);

            in_u0.SetData(in,length);

            my_fft(2,out_dbb,out_phh,in_u0);

            out_dbb.GetData(dbb,length);
            out_phh.GetData(phh,length);

///////////////////////////////////////////////////////////////////////////////////////////////////////////
            for(int i = 0; i < length / 2; i++)
            {
                m_amp.append(dbb[i]);
                m_phase.append((phh[i]/3.1415926532)*180.0);
            }
        }
        else
        {                             

            if (comboBox_fft_method->currentIndex() == 0)
            {
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                OrthgCorelAnalysis  m_orthAnys;
                m_orthAnys.setAnalySignalComp(m_sin_hz_start, m_sin_hz_step, m_samp_tim, m_sin_harm_num, m_sin_delay_num, m_sin_data_num);

                QVector<qreal> v_rin, v_rout;

                for (int i = 0; i < length; i++)
                {
                    v_rin.append(in[i]);
                    v_rout.append(m_value_list->at(outx).at(i+startIndex));

                }

                m_orthAnys.RespAnalysisInSinSteadyState(&v_rin, &v_rout, m_amp, m_phase);

                for (int i = 0; i < m_sin_harm_num; i ++)
                {
                    m_freq.append(m_sin_hz_start + i*m_sin_hz_step);
                }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            }
            else
            {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                my_prbs_idf_n4sidInitialize();

                m_dbb         = new double[N4SID_FRE_NUM_END];
                m_phh         = new double[N4SID_FRE_NUM_END];

                mwArray idf_ts(1,1,mxDOUBLE_CLASS);
                mwArray idf_u0(1,length,mxDOUBLE_CLASS);
                mwArray idf_y0(1,length,mxDOUBLE_CLASS);
                mwArray idf_phh(1,N4SID_FRE_NUM_END,mxDOUBLE_CLASS);
                mwArray idf_dbb(1,N4SID_FRE_NUM_END,mxDOUBLE_CLASS);

                idf_u0.SetData(in,length);
                idf_y0.SetData(out,length);
                idf_ts.SetData(&m_samp_tim,1);

                my_prbs_idf_n4sid(2, idf_dbb, idf_phh, idf_u0, idf_y0, idf_ts);

                idf_dbb.GetData(m_dbb,N4SID_FRE_NUM_END);
                idf_phh.GetData(m_phh,N4SID_FRE_NUM_END);

                for(int i = N4SID_FRE_NUM_START; i < N4SID_FRE_NUM_END; i++)
                {
                    m_amp.append(m_dbb[i]);
                    m_phase.append(m_phh[i]);
                }

                for (int i = N4SID_FRE_NUM_START; i < N4SID_FRE_NUM_END; i ++)
                {
                    m_freq.append(i/100.0);
                }

                delete []m_dbb;
                delete []m_phh;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            }
        }

        delete []in;
        delete []out;
        delete []dbb;
        delete []phh;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        int rowCount = tableWidget->rowCount();
        tableWidget->insertRow(rowCount);

        QTableWidgetItem *item = new QTableWidgetItem();
        str_ID                  =   m_wave_name_tbl->item(inx,0)->text();
        item->setText(str_ID);
        item->setFlags(Qt::ItemIsEnabled);
        tableWidget->setItem(rowCount, 0, item);

        item = new QTableWidgetItem();
        str_Name                =   m_wave_name_tbl->item(inx,1)->text();
        item->setText(str_Name);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item->setFlags(Qt::ItemIsEnabled);
        tableWidget->setItem(rowCount, 1, item);

        tableWidget->item(rowCount,0)->setTextColor(tbl_col[rowCount%MAX_TABLE_WAVE_NUM]);
        tableWidget->item(rowCount,1)->setTextColor(tbl_col[rowCount%MAX_TABLE_WAVE_NUM]);

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        plot_amp->addGraph();
        plot_amp->graph(rowCount)->setPen(QPen(tbl_col[rowCount%MAX_TABLE_WAVE_NUM]));
        plot_amp->graph(rowCount)->addData(m_freq, m_amp);
        plot_amp->rescaleAxes(true);

        plot_phase->addGraph();
        plot_phase->graph(rowCount)->setPen(QPen(tbl_col[rowCount%MAX_TABLE_WAVE_NUM]));
        plot_phase->graph(rowCount)->addData(m_freq, m_phase);
        plot_phase->rescaleAxes(true);

        plot_amp->xAxis->setScaleType(QCPAxis::stLogarithmic);
        plot_phase->xAxis->setScaleType(QCPAxis::stLogarithmic);

        plot_amp->replot();
        plot_phase->replot();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        wave_vis_tbl[rowCount]          =   true;

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }
    else
    {
        QMessageBox::information(0, tr("Range Error"), tr("wave table out range"));
    }

}

void DFTDialog::onPlotAmplitudeMouseMoved(QMouseEvent *event)
{
    double dx = plot_amp->xAxis->pixelToCoord(event->x());
    double dy = plot_amp->yAxis->pixelToCoord(event->y());

    QCPRange cpX = plot_amp->xAxis->range();
    QCPRange cpY = plot_amp->yAxis->range();

    if (cpX.contains(dx) && cpY.contains(dy)) {
        label_amp->setText(tr("Amplitude Information:  frequency: %1 HZ , AMP: %2 DB")\
                                       .arg(QString::number(dx, 'E', 4))\
                                       .arg(QString::number(dy, 'f', 2)));
    }
}

void DFTDialog::onPlotPhaseMouseMoved(QMouseEvent *event)
{
    double dx = plot_phase->xAxis->pixelToCoord(event->x());
    double dy = plot_phase->yAxis->pixelToCoord(event->y());

    QCPRange cpX = plot_phase->xAxis->range();
    QCPRange cpY = plot_phase->yAxis->range();

    if (cpX.contains(dx) && cpY.contains(dy)) {
        label_phase->setText(tr("Phase Information:  frequency: %1 HZ , Phase: %2 deg")\
                                       .arg(QString::number(dx, 'E', 4))\
                                       .arg(QString::number(dy, 'f', 2)));
    }
}

void DFTDialog::onTableItemClicked(QTableWidgetItem * item)
{
    int row = item->row();
    int graph_num   =   plot_amp->graphCount();

    if((item->column() == 0) && (graph_num > row))
    {
      if (wave_vis_tbl[row] == false)
      {
          item->setBackgroundColor(m_showColor);
          plot_amp->graph(row)->setVisible(true);
          plot_phase->graph(row)->setVisible(true);

          plot_amp->replot();
          plot_phase->replot();

          wave_vis_tbl[row]         =   true;
      }
      else
      {
          item->setBackgroundColor(m_hideColor);
          plot_amp->graph(row)->setVisible(false);
          plot_phase->graph(row)->setVisible(false);

          plot_amp->replot();
          plot_phase->replot();

          wave_vis_tbl[row]         =   false;
      }
    }
}



void DFTDialog::setCurveList(QTableWidget * wave_tbl, QVector<qreal> * key_list, QList<QVector<qreal>> * value_list)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_wave_name_tbl             =   wave_tbl;
    m_key_list                  =   key_list;
    m_value_list                =   value_list;


    comboBox_fft_input->clear();
    comboBox_fft_output->clear();
    for (int i = 0; i < m_wave_name_tbl->rowCount(); i++)
    {
        QString curveStr = m_wave_name_tbl->item(i,1)->text();

        comboBox_fft_input->addItem(curveStr);
        comboBox_fft_output->addItem(curveStr);
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

void DFTDialog::setCurveTime(double start_tim, double final_tim, double samp_tim)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_start_tim                 =   start_tim;
    m_final_tim                 =   final_tim;
    m_samp_tim                  =   samp_tim;

    m_sin_delay_num             =   (m_sin_delay_tim/m_samp_tim + 0.5);
    m_sin_data_num              =   (m_sin_steady_tim/m_samp_tim + 0.5);

    doubleSpinBox_fft_start->setValue(m_start_tim);
    doubleSpinBox_fft_terminal->setValue(m_final_tim);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


DFTDialog::~DFTDialog()
{

}















//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
