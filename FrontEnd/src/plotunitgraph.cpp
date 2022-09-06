//=========================================================================================================
// project		:	plot graph on terminal
// File			:	plotunitgraph.c
// discription	:	plot graph on terminal
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g/1487
// date			:	2022/06/21
// copyright(C)	:	liu.g	(2022-2030)
//=========================================================================================================

#include "dialogselectcurve.h"
#include "Cia402AppEmu.h"
#include "plotunitgraph.h"

const   int    g_WAVE_PLOT_UPDATE_TIM           =   100;                                                // unit[ms]
const   int    g_WAVE_PLOT_RES_NUMBER           =   1000;                                               // wave disp resolution | unit[line number]

Qt::GlobalColor tbl_col[20] =     \
                {Qt::red, Qt::green, Qt::blue, Qt::black, Qt::magenta,\
                 Qt::cyan, Qt::darkRed, Qt::darkGreen, Qt::darkBlue, Qt::darkCyan,\
                 Qt::darkMagenta, Qt::darkYellow, Qt::gray, Qt::darkGray, Qt::lightGray,\
                 Qt::yellow, Qt::red, Qt::green, Qt::blue, Qt::black};


PlotUnitGraph::PlotUnitGraph(QWidget *parent)
{
    setupUi(parent);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_task                  =   new threadTask(parent);

// parameter initialization

    wave_samp_ts            =   m_task->m_buf->clu_cyc_ts * m_task->m_buf->samp_div_tims;
    wave_disp_range         =   10.0;
    wave_storage_range      =   40.0;

    wave_data_storage_num   =   wave_storage_range/m_task->m_buf->clu_cyc_ts;


    wave_disp_interval      =   (wave_disp_range / wave_samp_ts)/g_WAVE_PLOT_RES_NUMBER;

// variable initialization
    wave_plot_en            =   false;
    key                     =   0.0;
    wave_disp_cnt           =   0;
    tab_wave_cnt            =   0;

    m_showColor             =   QColor(Qt::white);
    m_hideColor             =   QColor(Qt::gray);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    QVector<qreal>		*vtmp = new QVector<qreal>;

    value_list.clear();
    key_vec.clear();

    vtmp->append(0.0);
    for (int i = 0; i < m_task->m_buf->graph_num; i++)
    {
        value_list.append(*vtmp);
    }
    key_vec.append(0.0);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    connect(&data_timer, SIGNAL(timeout()), this, SLOT(realTimeDataPlot()));

    data_timer.start(g_WAVE_PLOT_UPDATE_TIM);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//    this->splitter_plot_curve->setStretchFactor(0,1);
//    this->splitter_plot_curve->setStretchFactor(1,0);

//    this->splitter_plot_tab->setStretchFactor(0,1);
//    this->splitter_plot_tab->setStretchFactor(1,0);

    this->tbtn_plot_floatin->setCheckable(true);
    this->tbtn_plot_floatin->setChecked(true);
    this->tbtn_plot_startSampling->setCheckable(true);
    this->tbtn_plot_startSampling->setChecked(false);
    this->tbtn_plot_mea_horizontal->setCheckable(true);
    this->tbtn_plot_mea_vertical->setCheckable(true);
    this->tbtn_plot_auto->setCheckable(true);
    this->tbtn_plot_auto->setChecked(false);

    this->tbtn_plot_startSampling->setToolTip(tr("startSampling"));
    this->tbtn_plot_auto->setToolTip(tr("auto fit window"));
    this->tbtn_plot_fit->setToolTip(tr("fit window"));
    this->tbtn_plot_mea_horizontal->setToolTip(tr("horizontal measure"));
    this->tbtn_plot_mea_vertical->setToolTip(tr("vertical measure"));
    this->tbtn_plot_open->setToolTip(tr("open hostory curve"));
    this->tbtn_plot_save->setToolTip(tr("save all curves"));
    this->tbtn_plot_show_all->setToolTip(tr("load all range curves "));
    this->tbtn_plot_floatin->setToolTip(tr("full screen switch"));
    this->tbtn_plot_open->setCheckable(true);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    setPlotUintGraphIcons();
    InitPlotWave();
    createSignalSlotsConnect();
    InitTableWidgetPloCurve();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


PlotUnitGraph::~PlotUnitGraph()
{
    value_list.clear();
    key_vec.clear();

    wave_plot_en                    =   FALSE;
    m_task->m_buf->enp              =   false;
    m_task->stop();

    tableWidget_plot_curve->clear();
}

void PlotUnitGraph::setPlotUintGraphIcons()
{
    QSize iconSize(24,24);
    QIcon samplStartIcon;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    samplStartIcon.addPixmap(QPixmap(":/res/images/start.png"),QIcon::Selected,QIcon::Off);
    samplStartIcon.addPixmap(QPixmap(":/res/images/stop.png"),QIcon::Selected,QIcon::On);

    this->tbtn_plot_startSampling->setIcon(samplStartIcon);
    this->tbtn_plot_startSampling->setIconSize(iconSize);

    this->tbtn_plot_floatin->setIcon(QIcon(":/res/images/expenses.png"));
    this->tbtn_plot_floatin->setIconSize(iconSize);

    this->tbtn_plot_auto->setIcon(QIcon(":/res/images/auto.png"));
    this->tbtn_plot_auto->setIconSize(iconSize);

    this->tbtn_plot_fit->setIcon(QIcon(":/res/images/fit.png"));
    this->tbtn_plot_fit->setIconSize(iconSize);

    this->tbtn_plot_mea_horizontal->setIcon(QIcon(":/res/images/measureH.png"));
    this->tbtn_plot_mea_horizontal->setIconSize(iconSize);

    this->tbtn_plot_mea_vertical->setIcon(QIcon(":/res/images/measureV.png"));
    this->tbtn_plot_mea_vertical->setIconSize(iconSize);

    this->tbtn_plot_open->setIcon(QIcon(":/res/images/open.png"));
    this->tbtn_plot_open->setIconSize(iconSize);

    this->tbtn_plot_save->setIcon(QIcon(":/res/images/save.png"));
    this->tbtn_plot_save->setIconSize(iconSize);

    this->tbtn_plot_curveAll->setIcon(QIcon(":/res/images/all.png"));
    this->tbtn_plot_curveAll->setIconSize(iconSize);

    this->tbtn_plot_curveAdd->setIcon(QIcon(":/res/images/add.png"));
    this->tbtn_plot_curveAdd->setIconSize(iconSize);

    this->tbtn_plot_curveRemove->setIcon(QIcon(":/res/images/remove.png"));
    this->tbtn_plot_curveRemove->setIconSize(iconSize);

    this->tbtn_plot_curveClear->setIcon(QIcon(":/res/images/clear.png"));
    this->tbtn_plot_curveClear->setIconSize(iconSize);

    this->tbtn_plot_show_all->setIcon(QIcon(":/res/images/ok.png"));
    this->tbtn_plot_show_all->setIconSize(iconSize);

    this->tbtn_plot_fft->setIcon(QIcon(":/res/images/eye.png"));
    this->tbtn_plot_fft->setIconSize(iconSize);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

void PlotUnitGraph::InitPlotWave()
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    this->plot->clearGraphs();
    // wave plot module initialization
    for (int i = 0; i < m_task->m_buf->graph_num; i++)
    {
        this->plot->addGraph();
        this->plot->graph(i)->setPen(QPen(tbl_col[i]));
        this->plot->graph(i)->setLineStyle(QCPGraph::lsLine);
    }

    this->plot->axisRect()->setupFullAxesBox();

    this->plot->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->plot->xAxis2->setVisible(false);
    this->plot->xAxis2->setTickLabels(false);
    this->plot->yAxis2->setVisible(false);
    this->plot->yAxis2->setTickLabels(false);
    this->plot->setBackground(QBrush(QColor(240,240,240)));
    this->plot->setOpenGl(false);

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

void    PlotUnitGraph::InitTableWidgetPloCurve()
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    QStringList headers;
    headers << "Index" << "Name";

    tableWidget_plot_curve->setColumnCount(2);

    tableWidget_plot_curve->setHorizontalHeaderLabels(headers);
    tableWidget_plot_curve->setStyleSheet("background-color:rgb(255,255,255)");

    tableWidget_plot_curve->horizontalHeader()->setVisible(false);
    tableWidget_plot_curve->horizontalHeader()->setStretchLastSection(true);

    tableWidget_plot_curve->resizeColumnsToContents();
    tableWidget_plot_curve->setColumnWidth(0, 80);
    tableWidget_plot_curve->show();

    for (int i = 0; i < g_MAX_TAB_WAVE_NUM; i++)
    {
        wave_vis_tab[i]             =   true;
    }

    all_show_flag               =   true;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

void PlotUnitGraph::setupSimpleDemo()
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // add two new graphs and set their look:
    this->plot->addGraph();
    this->plot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    this->plot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    this->plot->addGraph();
    this->plot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    // generate some points of data (y0 for first, y1 for second graph):
    QVector<double> x(251), y0(251), y1(251);
    for (int i=0; i<251; ++i)
    {
      x[i] = i;
      y0[i] = 100*qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
      y1[i] = 100*qExp(-i/150.0);              // exponential envelope
    }
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    this->plot->xAxis2->setVisible(true);
    this->plot->xAxis2->setTickLabels(false);
    this->plot->yAxis2->setVisible(true);
    this->plot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(this->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this->plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(this->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), this->plot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    this->plot->graph(0)->setData(x, y0);
    this->plot->graph(1)->setData(x, y1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    this->plot->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    this->plot->graph(1)->rescaleAxes(true);
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    this->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom );

    this->plot->setSelectionRectMode(QCP::srmNone);

    this->plot->setInteraction(QCP::iSelectItems,true);
    this->plot->setInteraction(QCP::iMultiSelect,true);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


void PlotUnitGraph::createSignalSlotsConnect()
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    connect(this->tbtn_plot_floatin,SIGNAL(clicked(bool)),this,SLOT(onBtnFloatInClicked(bool)));

    connect(this->tbtn_plot_mea_horizontal,SIGNAL(clicked(bool)),this,SLOT(onBtnMeaHClicked(bool)));
    connect(this->tbtn_plot_mea_vertical,SIGNAL(clicked(bool)),this,SLOT(onBtnMeaVClicked(bool)));
    connect(this->tbtn_plot_fit,SIGNAL(clicked(bool)),this,SLOT(onBtnFitClicked()));
    connect(this->tbtn_plot_show_all,SIGNAL(clicked(bool)),this,SLOT(onBtnLoadAllCurveClicked()));
    connect(this->tbtn_plot_startSampling,SIGNAL(clicked(bool)),this,SLOT(onBtnStartSampleClicked(bool)));
    connect(this->tbtn_plot_open,SIGNAL(clicked(bool)),this,SLOT(onBtnOpenCurveClicked(bool)));
    connect(this->tbtn_plot_save,SIGNAL(clicked(bool)),this,SLOT(onBtnSaveCurveClicked()));
    connect(this->tbtn_plot_fft, SIGNAL(clicked(bool)), this, SLOT(onBtnFFTClicked(bool)));

    connect(this->plot,SIGNAL(currentPosChanged(QPointF)),this,SLOT(onPlotPosHoverChanged(QPointF)));
    connect(this->plot,SIGNAL(horizMeaDataChanged(qreal,qreal,qreal)),this,SLOT(onPlotMeaHposChanged(qreal,qreal,qreal)));
    connect(this->plot,SIGNAL(vertiMeaDataChanged(qreal,qreal,qreal)),this,SLOT(onPlotMeaVposChanged(qreal,qreal,qreal)));

    connect(this->tbtn_plot_curveAdd,SIGNAL(clicked(bool)),this,SLOT(onBtnCurveAddClicked()));
    connect(this->tbtn_plot_curveAll,SIGNAL(clicked(bool)),this,SLOT(onBtnCurveShowAllClicked()));
    connect(this->tbtn_plot_curveClear,SIGNAL(clicked(bool)),this,SLOT(onBtnCurveClearClicked()));
    connect(this->tbtn_plot_curveRemove,SIGNAL(clicked(bool)),this,SLOT(onBtnCurveRemoveClicked()));
    connect(tableWidget_plot_curve, &QTableWidget::itemClicked, \
            this, &PlotUnitGraph::onCurveTableItemClicked);


    connect(this,SIGNAL(selectionRectFinish()),this,SLOT(onPlotSelectionRectFinish()));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


void    PlotUnitGraph::onBtnFloatInClicked(bool checked)
{

}

void    PlotUnitGraph::onBtnStartSampleClicked(bool checked)
{
    QVector<qreal>		*vtmp = new QVector<qreal>;

    if (tab_wave_cnt < 1)
    {
        return;
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (checked)
    {
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        m_task->m_buf->graph_num                =   tab_wave_cnt;

        this->plot->clearGraphs();

        QColor     color_tmp;
        // wave plot module initialization
        for (int i = 0; i < m_task->m_buf->graph_num; i++)
        {
            this->plot->addGraph();
            color_tmp                           =   tableWidget_plot_curve->item(i,0)->textColor();
            this->plot->graph(i)->setPen(QPen(color_tmp));

            if (wave_vis_tab[i] == true)
            {
                plot->graph(i)->setVisible(true);
            }
            else
            {
                plot->graph(i)->setVisible(false);
            }

            Uint16 inx_tmp = 0;
            bool    en_ok   =   true;
            inx_tmp         =   tableWidget_plot_curve->item(i, 0)->text().toInt(&en_ok,16) - 0x3000;

            m_task->m_buf->obj_inx[i]           =   inx_tmp;
        }

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        value_list.clear();
        key_vec.clear();

        vtmp->append(0.0);
        key_vec.append(key);

        for (int i = 0; i < m_task->m_buf->graph_num; i++)
        {
            value_list.append(*vtmp);
            this->plot->graph(i)->data().data()->clear();
        }

        this->plot->rescaleAxes(true);
        vtmp->clear();

        m_task->m_buf->ClearWaveVecBuf();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        wave_plot_en                            =   TRUE;
        m_task->m_buf->enp                      =   true;

        m_task->start();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }
    else
    {
        wave_plot_en                            =   FALSE;
        m_task->m_buf->enp                      =   false;

        m_task->stop();
        for (int i = 0; i < m_task->m_buf->graph_num; i++)
        {
            this->plot->graph(i)->setData(key_vec, value_list.at(i), true);
        }
        key                 =   key_vec.last();
        double wave_size    =   key >= wave_storage_range ? wave_storage_range:key;
        this->plot->xAxis->setRange(key, wave_size, Qt::AlignRight);

 ///////////////////////////////////////////////////////////////////////////////////////////////
        this->plot->replot();
    }
}

void    PlotUnitGraph::onBtnMeaHClicked(bool checked)
{
    if(checked)
    {
        plot->createVertiMea();
    }
    else
    {
        plot->clearVertiMea();
    }
}

void    PlotUnitGraph::onBtnMeaVClicked(bool checked)
{
    if(checked)
    {
        plot->createHorizMea();
    }
    else
    {
        plot->clearHorizMea();
    }
}

void    PlotUnitGraph::onBtnFitClicked()
{
    plot->rescaleAxes(true);

    double low = plot->yAxis->range().lower;
    double upper = plot->yAxis->range().upper;
    double size = plot->yAxis->range().size();
    double dsize = 0.1*size;
    QCPRange plottableRange(low - dsize,upper + dsize);

    plot->yAxis->setRange(plottableRange);
    plot->replot();
}

void    PlotUnitGraph::onBtnLoadAllCurveClicked()
{

}

void    PlotUnitGraph::onBtnOpenCurveClicked(bool checked)
{

}

void    PlotUnitGraph::onBtnSaveCurveClicked()
{

}

void    PlotUnitGraph::onBtnFFTClicked(bool checked)
{

}

void    PlotUnitGraph::onPlotPosHoverChanged(const QPointF &point)
{
    label_plot_x->setText(QString("X=%1 ms").arg(QString::number(point.x()*1000,'f',2)));
    label_plot_y->setText(QString(" Y=%1").arg(QString::number(point.y(),'f',2)));
}

void    PlotUnitGraph::onPlotMeaVposChanged(qreal v1, qreal v2, qreal dv)
{
    label_plot_dy->setText(QString(" dY=%1").arg(QString::number(dv,'f',2)));
}

void    PlotUnitGraph::onPlotMeaHposChanged(qreal v1, qreal v2, qreal dv)
{
    label_plot_dx->setText(QString("dX=%1 ms ,Freq=%2 HZ").arg(QString::number(dv*1000,'f',2)).arg(QString::number(1/dv,'f',2)));
}



void    PlotUnitGraph::onBtnCurveAddClicked()
{
    DialogSelectCurve   * pCurveSelect  =   new DialogSelectCurve(this);

    pCurveSelect->exec();
}

void    PlotUnitGraph::onBtnCurveRemoveClicked()
{
    int row     =   tableWidget_plot_curve->currentRow();

    if(row >= 0)
    {
        tableWidget_plot_curve->removeRow(row);
        tab_wave_cnt--;
    }
}

void    PlotUnitGraph::onBtnCurveClearClicked()
{
    if (tab_wave_cnt > 0)
    {
        tableWidget_plot_curve->setRowCount(0);
        tableWidget_plot_curve->clearContents();
        tab_wave_cnt    =   0;
    }
}

void    PlotUnitGraph::onBtnCurveShowAllClicked()
{
    if (all_show_flag == false)
    {
        for (int i = 0; i < tab_wave_cnt; i++)
        {
            tableWidget_plot_curve->item(i,0)->setBackgroundColor(m_showColor);
            plot->graph(i)->setVisible(true);
            wave_vis_tab[i]         =   true;
        }
        all_show_flag               =   true;
    }
    else
    {
        for (int i = 0; i < tab_wave_cnt; i++)
        {
            tableWidget_plot_curve->item(i,0)->setBackgroundColor(m_hideColor);
            plot->graph(i)->setVisible(false);
            wave_vis_tab[i]         =   false;
        }
        all_show_flag               =   false;
    }

    plot->replot();
}


void    PlotUnitGraph::OnWaveTableItemDoubleClicked(int row, int column)
{
    QString     str, str2;
    int16       inx;
//----------------------------------------------------------------------------------------------------------------
    inx         =       row;
    if ((inx >= 0) && (inx < VAR_SERVO_OBJW_INX_MAX_NUM) && (tab_wave_cnt < g_MAX_TAB_WAVE_NUM))
    {
       tableWidget_plot_curve->setRowCount(tab_wave_cnt+1);

       tableWidget_plot_curve->setItem(tab_wave_cnt, 0, new QTableWidgetItem());
       tableWidget_plot_curve->setItem(tab_wave_cnt, 1, new QTableWidgetItem());

       tableWidget_plot_curve->item(tab_wave_cnt,0)->setTextColor(tbl_col[tab_wave_cnt%g_MAX_TAB_WAVE_NUM]);
       tableWidget_plot_curve->item(tab_wave_cnt,1)->setTextColor(tbl_col[tab_wave_cnt%g_MAX_TAB_WAVE_NUM]);

       str      =       QString::number(DefCiA402VarObjDic[inx].Index, 16);
       str2     =       (char *)(DefCiA402VarObjDic[inx].pName);

       tableWidget_plot_curve->item(tab_wave_cnt, 0)->setText(str);
       tableWidget_plot_curve->item(tab_wave_cnt, 1)->setText(str2);

       tableWidget_plot_curve->item(tab_wave_cnt, 0)->setFlags(Qt::ItemIsEnabled);
       tableWidget_plot_curve->item(tab_wave_cnt, 1)->setFlags(Qt::ItemIsEnabled);

       tab_wave_cnt++;
    }
}


void    PlotUnitGraph::onCurveTableItemClicked(QTableWidgetItem *item)
{
    if(item->column() == 0)
    {
      int row = item->row();

      if (wave_vis_tab[row] == false)
      {
          item->setBackgroundColor(m_showColor);
          plot->graph(row)->setVisible(true);
          plot->replot();
          wave_vis_tab[row]         =   true;
      }
      else
      {
          item->setBackgroundColor(m_hideColor);
          plot->graph(row)->setVisible(false);
          plot->replot();

          wave_vis_tab[row]         =   false;
      }
    }
}

void    PlotUnitGraph::realTimeDataPlot()
{
    int                          m, delta_cnt;
    QVector<qreal>               *tkey		=   new QVector<qreal>;
    QList<QVector<qreal>>        *tvalue	=	new QList<QVector<qreal>>;

///////////////////////////////////////////////////////////////////////////////////////////////
    if (wave_plot_en == true)
    {
        m_task->m_buf->GetWaveData(tkey, tvalue);

// return when not get only data
        if (!tkey->isEmpty())
        {
//---------------------------------------------------------------------------------------------
            key = tkey->last();
//---------------------------------------------------------------------------------------------
            for (int j = 0; j < tkey->count(); j++)
            {
                for (int i = 0; i < m_task->m_buf->graph_num; i++)
                {
                    value_list[i].append(tvalue->at(i).at(j) );
                }

                key_vec.append(tkey->at(j));
            }
            m = key_vec.count();

            if (m > wave_data_storage_num)
            {
                delta_cnt = m - wave_data_storage_num;

                for (int i = 0; i < m_task->m_buf->graph_num; i++)
                {
                    value_list[i].remove(0, delta_cnt);
                }
                key_vec.remove(0, delta_cnt);
            }
//--------------------------------------------------------------------------------------------
            for (int j = 0; j < tkey->count(); j++)
            {
                if (wave_disp_cnt == 0)
                {
                    for (int i = 0; i < m_task->m_buf->graph_num; i++)
                    {
                        this->plot->graph(i)->addData(tkey->at(j), tvalue->at(i).at(j));
                    }
                }
                wave_disp_cnt++;
                wave_disp_cnt = (wave_disp_cnt >= wave_disp_interval) ? 0 : wave_disp_cnt;

            }
//--------------------------------------------------------------------------------------------
            double wave_size    =   key >= wave_disp_range ? wave_disp_range:key;
            this->plot->xAxis->setRange(key, wave_size, Qt::AlignRight);
            this->plot->setPlottingHint(QCP::phFastPolylines);

            for (int i = 0; i < m_task->m_buf->graph_num; i++)
            {
                this->plot->graph(i)->rescaleValueAxis(true, true);
            }
//////////////////////////////////////////////////////////////////////////////////////////////////////////
            this->plot->replot();
        }

    }

    tkey->clear();
    tvalue->clear();
//////////////////////////////////////////////////////////////////////////////////////////////////////////
}

///////////////////////////////////////////////// NO MORE ////////////////////////////////////////////////
