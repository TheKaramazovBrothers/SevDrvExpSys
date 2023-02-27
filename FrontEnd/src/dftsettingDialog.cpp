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
    tqr_factor      =       0.0999;
    curr_unit       =       MA_CURR_EXCI_UNIT;
    vel_unit        =       RPM_VEL_EXCI_UNIT;

    start_fn        =       F20_HZ_FRE;
    end_fn          =       F40_HZ_FRE;
    Jall            =       0.0;

    kg_adj          =       1.0;
    curr_unit_coef  =       0.6667;

    ctl_sel         =       P_CTL_STR;
    plot_sel        =       L_BODE_PLOT;

    fn_c            =       100.0;
    ti_c            =       10.0;
    kn_c            =       1.0;

    fn_lpf1         =       300.0;
    fn_nch          =       400;
    qn_nch          =       0.7;
    kn_nch          =       0.5;

    gain_margin     =       3.0;
    phase_margin    =       90.0;
    cross_freq      =       0.0;

    peak_freq       =       1.0;
    peak_db         =       0.0;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    comboBox_controler->setCurrentIndex(ctl_sel);
    comboBox_bode_sel->setCurrentIndex(plot_sel);

    doubleSpinBox_fn->setValue(fn_c);
    doubleSpinBox_ti->setValue(ti_c);

    doubleSpinBox_fn_lpf->setValue(fn_lpf1);

    doubleSpinBox_fn_nch->setValue(fn_nch);
    doubleSpinBox_qn_nch->setValue(qn_nch);
    doubleSpinBox_kn_nch->setValue(kn_nch);

    doubleSpinBox_gain_margin->setValue(gain_margin);
    doubleSpinBox_phase_margin->setValue(phase_margin);
    doubleSpinBox_cross_freq->setValue(cross_freq);

    doubleSpinBox_peak_freq->setValue(peak_freq);
    doubleSpinBox_peak_gain->setValue(peak_db);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    comboBox_current_unit->setCurrentIndex(curr_unit);
    comboBox_velocity_unit->setCurrentIndex(vel_unit);

    doubleSpinBox_tqr_factor->setValue(tqr_factor);
    doubleSpinBox_curr_unit_coef->setValue(curr_unit_coef);

//    QRegExp regexp_0To360("^([0-9]|[1-9]\\d|[1-2]\\d{0,2}|3[0-5]\\d|360)$");
//    QRegExp regexp_0To100("^([0-9]|[1-9]\\d|[1][0][0])$");
//    QRegExp regexp_D0To100("^([0-9]|[0-9]\\.[0-9]|[1-9][0-9]|[1-9][0-9]\\.[0-9]|[1][0][0]|[1][0][0]\\.[0])$");

//    QRegExp regexp_D0To1000_4("^([0-9]|[0-9]\\.[0-9]{0,4}|[1-9][0-9]|[1-9][0-9]\\.[0-9]{0,4}|[1-9][0-9][0-9]|[1-9][0-9][0-9]\\.[0-9]{0,4}|[1][0][0][0]|[1][0][0][0]\\.[0])$");

    QString str;

    comboBox_start_fre->setCurrentIndex(start_fn);
    comboBox_end_fre->setCurrentIndex(end_fn);
    str             =       QString::number(Jall);
    lineEdit_inertia_result->setText(str);
    lineEdit_inertia_result->setEnabled(false);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    label_ti_name->setVisible(false);
    label_ti_unit->setVisible(false);
    doubleSpinBox_ti->setVisible(false);

    label_fn_lpf_name->setVisible(false);
    label_fn_lpf_unit->setVisible(false);
    doubleSpinBox_fn_lpf->setVisible(false);

    label_fn_nch_name->setVisible(false);
    label_fn_nch_unit->setVisible(false);
    doubleSpinBox_fn_nch->setVisible(false);

    label_qn_nch_name->setVisible(false);
    label_qn_nch_unit->setVisible(false);
    doubleSpinBox_qn_nch->setVisible(false);

    label_kn_nch_name->setVisible(false);
    label_kn_nch_unit->setVisible(false);
    doubleSpinBox_kn_nch->setVisible(false);

    pushButton_auto->setVisible(false);
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
    connect(pushButton_calculate,SIGNAL(clicked(bool)),this,SLOT(onPushButtonCalculateClicked(bool)));
    connect(pushButton_update,SIGNAL(clicked(bool)),this,SLOT(onPushButtonUpdateClicked(bool)));
    connect(pushButton_auto,SIGNAL(clicked(bool)),this,SLOT(onPushButtonAutoClicked(bool)));

    connect(widget_plot_amp, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onPlotAmplitudeMouseMoved(QMouseEvent*)));
    connect(widget_plot_phase, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onPlotPhaseMouseMoved(QMouseEvent*)));

    connect(comboBox_controler, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxControlerChanged(int)));

    connect(toolButton_save, SIGNAL(clicked()), this, SLOT(onBtnSaveClicked()));
}

void DFTSettingDialog::onBtnSaveClicked()
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    auto file_name = QFileDialog::getSaveFileName(this, tr("Save wave"), "../bode.txt",tr("*.txt"));
    if(file_name.isEmpty())
    {
        return;
    }

    QFile fdata(file_name);

    if (fdata.open(QFile::WriteOnly | QFile::Truncate | QIODevice::Text))
    {
        QTextStream out(&fdata);

        QString nameStr;
        out.setFieldAlignment(QTextStream::AlignLeft);
        out.setRealNumberPrecision(11);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        QString str_ID, str_Name;
        str_ID      =   "system";
        str_Name    =   "input->ouput";

        out << qSetFieldWidth(20)  << str_ID << qSetFieldWidth(20) << str_Name;
        out << qSetFieldWidth(0) << endl;
        out << qSetFieldWidth(20)  << tr("fn[hz]") << qSetFieldWidth(20) <<  tr("amp[db]") << qSetFieldWidth(20) <<  tr("pha[deg]");
        out << qSetFieldWidth(0) << endl ;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        int wave_lth      =     m_freq->count();

        for (int i = 0; i < wave_lth; i++)
        {
            out << qSetFieldWidth(20) << m_freq->at(i);
            if (cl_amp.count() > 2)
            {
                out << qSetFieldWidth(20) << cl_amp.at(i);
                out << qSetFieldWidth(20) << cl_phase.at(i);
            }
            else if (mod_amp_norm.count() >2)
            {
                out << qSetFieldWidth(20) << mod_amp_norm.at(i);
                out << qSetFieldWidth(20) << m_phase->at(i);
            }
            else
            {
                out << qSetFieldWidth(20) << m_amp->at(i);
                out << qSetFieldWidth(20) << m_phase->at(i);
            }
            out << qSetFieldWidth(0) << endl;
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }
    fdata.close();
 //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


void DFTSettingDialog::onComboBoxControlerChanged(int index)
{
    ctl_sel             =   (CtlStruSel)(index);

    if (ctl_sel == P_CTL_STR)
    {
        label_ti_name->setVisible(false);
        label_ti_unit->setVisible(false);
        doubleSpinBox_ti->setVisible(false);

        label_fn_lpf_name->setVisible(false);
        label_fn_lpf_unit->setVisible(false);
        doubleSpinBox_fn_lpf->setVisible(false);

        label_fn_nch_name->setVisible(false);
        label_fn_nch_unit->setVisible(false);
        doubleSpinBox_fn_nch->setVisible(false);

        label_qn_nch_name->setVisible(false);
        label_qn_nch_unit->setVisible(false);
        doubleSpinBox_qn_nch->setVisible(false);

        label_kn_nch_name->setVisible(false);
        label_kn_nch_unit->setVisible(false);
        doubleSpinBox_kn_nch->setVisible(false);

        pushButton_auto->setVisible(false);
    }
    else if (ctl_sel == PI_CTL_STR)
    {
        label_ti_name->setVisible(true);
        label_ti_unit->setVisible(true);
        doubleSpinBox_ti->setVisible(true);

        label_fn_lpf_name->setVisible(false);
        label_fn_lpf_unit->setVisible(false);
        doubleSpinBox_fn_lpf->setVisible(false);

        label_fn_nch_name->setVisible(false);
        label_fn_nch_unit->setVisible(false);
        doubleSpinBox_fn_nch->setVisible(false);

        label_qn_nch_name->setVisible(false);
        label_qn_nch_unit->setVisible(false);
        doubleSpinBox_qn_nch->setVisible(false);

        label_kn_nch_name->setVisible(false);
        label_kn_nch_unit->setVisible(false);
        doubleSpinBox_kn_nch->setVisible(false);

        pushButton_auto->setVisible(false);
    }
    else if (ctl_sel == PI_LPF_CTL_STR)
    {
        label_ti_name->setVisible(true);
        label_ti_unit->setVisible(true);
        doubleSpinBox_ti->setVisible(true);

        label_fn_lpf_name->setVisible(true);
        label_fn_lpf_unit->setVisible(true);
        doubleSpinBox_fn_lpf->setVisible(true);

        label_fn_nch_name->setVisible(false);
        label_fn_nch_unit->setVisible(false);
        doubleSpinBox_fn_nch->setVisible(false);

        label_qn_nch_name->setVisible(false);
        label_qn_nch_unit->setVisible(false);
        doubleSpinBox_qn_nch->setVisible(false);

        label_kn_nch_name->setVisible(false);
        label_kn_nch_unit->setVisible(false);
        doubleSpinBox_kn_nch->setVisible(false);

        pushButton_auto->setVisible(false);
    }
    else if (ctl_sel == PI_LPF_NCH_CTL_STR)
    {
        label_ti_name->setVisible(true);
        label_ti_unit->setVisible(true);
        doubleSpinBox_ti->setVisible(true);

        label_fn_lpf_name->setVisible(true);
        label_fn_lpf_unit->setVisible(true);
        doubleSpinBox_fn_lpf->setVisible(true);

        label_fn_nch_name->setVisible(true);
        label_fn_nch_unit->setVisible(true);
        doubleSpinBox_fn_nch->setVisible(true);

        label_qn_nch_name->setVisible(true);
        label_qn_nch_unit->setVisible(true);
        doubleSpinBox_qn_nch->setVisible(true);

        label_kn_nch_name->setVisible(true);
        label_kn_nch_unit->setVisible(true);
        doubleSpinBox_kn_nch->setVisible(true);

        pushButton_auto->setVisible(true);
    }
    else if (ctl_sel == PI_NCH_CTL_STR)
    {
        label_ti_name->setVisible(true);
        label_ti_unit->setVisible(true);
        doubleSpinBox_ti->setVisible(true);

        label_fn_lpf_name->setVisible(false);
        label_fn_lpf_unit->setVisible(false);
        doubleSpinBox_fn_lpf->setVisible(false);

        label_fn_nch_name->setVisible(true);
        label_fn_nch_unit->setVisible(true);
        doubleSpinBox_fn_nch->setVisible(true);

        label_qn_nch_name->setVisible(true);
        label_qn_nch_unit->setVisible(true);
        doubleSpinBox_qn_nch->setVisible(true);

        label_kn_nch_name->setVisible(true);
        label_kn_nch_unit->setVisible(true);
        doubleSpinBox_kn_nch->setVisible(true);

        pushButton_auto->setVisible(true);
    }

    else
    { ; }
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
    tqr_factor                  =   doubleSpinBox_tqr_factor->value();
    curr_unit_coef              =   doubleSpinBox_curr_unit_coef->value();
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

    kg_adj              =   (1/(tqr_factor/sqrt(2.0)))/curr_unit_coef;

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


void DFTSettingDialog::onPushButtonUpdateClicked(bool)
{
    double  adj_db, adj_pha, dtmp, dtmp2, dtmp3, deta_amp, deta_pha;
    double  lpf_amp, lpf_pha, nch_amp, nch_pha, wn_tmp;
    double  wn_nch, w_nch, zeta1_nch, zeta2_nch;
    int inx, cnt, fre, num;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    ctl_sel             =   (CtlStruSel)(comboBox_controler->currentIndex());
    plot_sel            =   (BodePlotSel)(comboBox_bode_sel->currentIndex());

    fn_c                =   doubleSpinBox_fn->value();
    ti_c                =   doubleSpinBox_ti->value();
    fn_lpf1             =   doubleSpinBox_fn_lpf->value();

    fn_nch              =   doubleSpinBox_fn_nch->value();
    qn_nch              =   doubleSpinBox_qn_nch->value();
    kn_nch              =   doubleSpinBox_kn_nch->value();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (mod_amp_norm.count() <= 5)
    {
        return;
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    cl_amp.clear();
    cl_phase.clear();
    ctl_amp.clear();
    ctl_phase.clear();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    kn_c                =   6.2831853 * fn_c * (Jall/1000000.0);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (ctl_sel == P_CTL_STR)
    {
        for (int i = 0; i < m_freq->count(); i++)
        {
            adj_db          =   20 * log10(kn_c);
            cl_amp.append((mod_amp_norm.at(i)+adj_db));
        }
        cl_phase            =   *m_phase;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }
    else if (ctl_sel == PI_CTL_STR)
    {
        if (ti_c < 1.0)
        {
            for (int i = 0; i < m_freq->count(); i++)
            {
                adj_db          =   20 * log10(kn_c);
                cl_amp.append((mod_amp_norm.at(i)+adj_db));
            }
            cl_phase            =   *m_phase;
        }
        else
        {
             for (int i = 0; i < m_freq->count(); i++)
             {
                 wn_tmp         =   6.2831853 * m_freq->at(i);
                 dtmp           =   1000.0/ti_c;
                 deta_amp       =   sqrt(dtmp*dtmp + wn_tmp*wn_tmp)/wn_tmp;
                 adj_db         =   20 * log10(kn_c * deta_amp);
                 cl_amp.append((mod_amp_norm.at(i)+adj_db));
                 ctl_amp.append(adj_db);

                 deta_pha       =   (atan(wn_tmp/dtmp)*180.0)/M_PI - 90.0;
                 ctl_phase.append(deta_pha);

                 dtmp           =   m_phase->at(i)+deta_pha;
                 cl_phase.append(dtmp);
             }
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }
    else if (ctl_sel == PI_LPF_CTL_STR)
    {
        for (int i = 0; i < m_freq->count(); i++)
        {
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            if (ti_c < 1.0)
            {
                deta_amp        =   1.0;
                deta_pha        =   0.0;
            }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            else
            {
                wn_tmp          =   6.2831853 * m_freq->at(i);
                dtmp            =   1000.0/ti_c;
                deta_amp        =   sqrt(dtmp*dtmp + wn_tmp*wn_tmp)/wn_tmp;
                deta_pha        =   (atan(wn_tmp/dtmp)*180.0)/M_PI - 90.0;
            }

            dtmp                =   6.2831853 * fn_lpf1;
            wn_tmp              =   6.2831853 * m_freq->at(i);

            lpf_amp             =   dtmp / sqrt(dtmp*dtmp + wn_tmp*wn_tmp);
            lpf_pha             =   -(atan(wn_tmp/dtmp)*180.0)/M_PI;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            adj_db              =   20 * log10(kn_c * deta_amp * lpf_amp);

            cl_amp.append((mod_amp_norm.at(i)+adj_db));
            ctl_amp.append(adj_db);

            ctl_phase.append(deta_pha+lpf_pha);

            dtmp           =   m_phase->at(i) + deta_pha + lpf_pha;
            cl_phase.append(dtmp);
        }
    }
    else if (ctl_sel == PI_LPF_NCH_CTL_STR)
    {
        for (int i = 0; i < m_freq->count(); i++)
        {
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            if (ti_c < 1.0)
            {
                deta_amp        =   1.0;
                deta_pha        =   0.0;
            }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            else
            {
                wn_tmp          =   6.2831853 * m_freq->at(i);
                dtmp            =   1000.0/ti_c;
                deta_amp        =   sqrt(dtmp*dtmp + wn_tmp*wn_tmp)/wn_tmp;
                deta_pha        =   (atan(wn_tmp/dtmp)*180.0)/M_PI - 90.0;
            }

            dtmp                =   6.2831853 * fn_lpf1;
            wn_tmp              =   6.2831853 * m_freq->at(i);

            lpf_amp             =   dtmp / sqrt(dtmp*dtmp + wn_tmp*wn_tmp);
            lpf_pha             =   -(atan(wn_tmp/dtmp)*180.0)/M_PI;

            wn_nch              =   6.2831853 * fn_nch;
            zeta2_nch           =   qn_nch;
            zeta1_nch           =   kn_nch*qn_nch;

            dtmp                =   (wn_nch*wn_nch - wn_tmp*wn_tmp);
            dtmp                =   dtmp * dtmp;

            dtmp2               =   2*wn_nch*wn_tmp*zeta1_nch;
            dtmp2               =   dtmp2 * dtmp2;

            dtmp3               =   2*wn_nch*wn_tmp*zeta2_nch;
            dtmp3               =   dtmp3 * dtmp3;

            nch_amp             =   sqrt((dtmp + dtmp2)/(dtmp + dtmp3));

            nch_pha             =   atan((2*wn_nch*wn_tmp*zeta1_nch)/(wn_nch*wn_nch - wn_tmp * wn_tmp)) -\
                                    atan((2*wn_nch*wn_tmp*zeta2_nch)/(wn_nch*wn_nch - wn_tmp * wn_tmp));

            nch_pha             =   (nch_pha*180.0)/M_PI;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            adj_db              =   20 * log10(kn_c * deta_amp * lpf_amp * nch_amp);

            cl_amp.append((mod_amp_norm.at(i)+adj_db));
            ctl_amp.append(adj_db);

            ctl_phase.append(deta_pha+lpf_pha+nch_pha);

            dtmp           =   m_phase->at(i) + deta_pha + lpf_pha + nch_pha;
            cl_phase.append(dtmp);
        }
    }
    else if (ctl_sel == PI_NCH_CTL_STR)
    {
        for (int i = 0; i < m_freq->count(); i++)
        {
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            if (ti_c < 1.0)
            {
                deta_amp        =   1.0;
                deta_pha        =   0.0;
            }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            else
            {
                wn_tmp          =   6.2831853 * m_freq->at(i);
                dtmp            =   1000.0/ti_c;
                deta_amp        =   sqrt(dtmp*dtmp + wn_tmp*wn_tmp)/wn_tmp;
                deta_pha        =   (atan(wn_tmp/dtmp)*180.0)/M_PI - 90.0;
            }

            wn_tmp              =   6.2831853 * m_freq->at(i);
            wn_nch              =   6.2831853 * fn_nch;
            zeta2_nch           =   qn_nch;
            zeta1_nch           =   kn_nch*qn_nch;

            dtmp                =   (wn_nch*wn_nch - wn_tmp*wn_tmp);
            dtmp                =   dtmp * dtmp;

            dtmp2               =   2*wn_nch*wn_tmp*zeta1_nch;
            dtmp2               =   dtmp2 * dtmp2;

            dtmp3               =   2*wn_nch*wn_tmp*zeta2_nch;
            dtmp3               =   dtmp3 * dtmp3;

            nch_amp             =   sqrt((dtmp + dtmp2)/(dtmp + dtmp3));

            nch_pha             =   atan((2*wn_nch*wn_tmp*zeta1_nch)/(wn_nch*wn_nch - wn_tmp * wn_tmp)) -\
                                    atan((2*wn_nch*wn_tmp*zeta2_nch)/(wn_nch*wn_nch - wn_tmp * wn_tmp));

            nch_pha             =   (nch_pha*180.0)/M_PI;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            adj_db              =   20 * log10(kn_c * deta_amp * nch_amp);

            cl_amp.append((mod_amp_norm.at(i)+adj_db));
            ctl_amp.append(adj_db);

            ctl_phase.append(deta_pha + nch_pha);

            dtmp           =   m_phase->at(i) + deta_pha + nch_pha;
            cl_phase.append(dtmp);
        }
    }
    else
    {
        cl_amp              =   mod_amp_norm;
        cl_phase            =   *m_phase;

        ctl_amp             =   cl_amp;
        ctl_phase           =   cl_phase;
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    widget_plot_amp->clearGraphs();
    widget_plot_phase->clearGraphs();
    if (plot_sel == L_BODE_PLOT)
    {
        widget_plot_amp->addGraph();
        widget_plot_amp->graph(0)->setPen(QPen(tbl_col[0]));
        widget_plot_amp->graph(0)->addData(*m_freq, cl_amp);
        widget_plot_amp->rescaleAxes(true);

        widget_plot_phase->addGraph();
        widget_plot_phase->graph(0)->setPen(QPen(tbl_col[0]));
        widget_plot_phase->graph(0)->addData(*m_freq, cl_phase);
        widget_plot_phase->rescaleAxes(true);
    }
    else if (plot_sel == C_BODE_PLOT)
    {
        widget_plot_amp->addGraph();
        widget_plot_amp->graph(0)->setPen(QPen(tbl_col[0]));
        widget_plot_amp->graph(0)->addData(*m_freq, ctl_amp);
        widget_plot_amp->rescaleAxes(true);

        widget_plot_phase->addGraph();
        widget_plot_phase->graph(0)->setPen(QPen(tbl_col[0]));
        widget_plot_phase->graph(0)->addData(*m_freq, ctl_phase);
        widget_plot_phase->rescaleAxes(true);
    }
    else if (plot_sel == C_PLUS_L_BODE_PLOT)
    {
        widget_plot_amp->addGraph();
        widget_plot_amp->graph(0)->setPen(QPen(tbl_col[0]));
        widget_plot_amp->graph(0)->addData(*m_freq, cl_amp);
        widget_plot_amp->rescaleAxes(true);

        widget_plot_phase->addGraph();
        widget_plot_phase->graph(0)->setPen(QPen(tbl_col[0]));
        widget_plot_phase->graph(0)->addData(*m_freq, cl_phase);
        widget_plot_phase->rescaleAxes(true);

        widget_plot_amp->addGraph();
        widget_plot_amp->graph(1)->setPen(QPen(tbl_col[1]));
        widget_plot_amp->graph(1)->addData(*m_freq, ctl_amp);
        widget_plot_amp->rescaleAxes(true);

        widget_plot_phase->addGraph();
        widget_plot_phase->graph(1)->setPen(QPen(tbl_col[1]));
        widget_plot_phase->graph(1)->addData(*m_freq, ctl_phase);
        widget_plot_phase->rescaleAxes(true);
    }
    else
    {
        widget_plot_amp->addGraph();
        widget_plot_amp->graph(0)->setPen(QPen(tbl_col[0]));
        widget_plot_amp->graph(0)->addData(*m_freq, mod_amp_norm);
        widget_plot_amp->rescaleAxes(true);

        widget_plot_phase->addGraph();
        widget_plot_phase->graph(0)->setPen(QPen(tbl_col[0]));
        widget_plot_phase->graph(0)->addData(*m_freq, *m_phase);
        widget_plot_phase->rescaleAxes(true);
    }

    widget_plot_amp->xAxis->setScaleType(QCPAxis::stLogarithmic);
    widget_plot_phase->xAxis->setScaleType(QCPAxis::stLogarithmic);

    widget_plot_amp->replot();
    widget_plot_phase->replot();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    cnt         =   0;
    num         =   cl_amp.count();

    while ((cl_amp.at(cnt) >= 0) && (cnt < num))
    {
        cnt++;
    }

    if (cnt >= num)
    {
        cnt     =   num - 1;
    }
    phase_margin            =   cl_phase.at(cnt) + 180.0;
    cross_freq              =   m_freq->at(cnt);

    while (cnt < (num-1))
    {
        if ((cl_amp.at(cnt) > 0) && (cl_amp.at(cnt+1) < 0))
        {
            dtmp                =   cl_phase.at(cnt) + 180.0;
            phase_margin        =   (phase_margin > dtmp) ? dtmp : phase_margin;
            cross_freq          =   m_freq->at(cnt);
            break;
        }
        cnt++;
    }

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    cnt         =   0;
    while (cnt < (num-1))
    {
        if (cl_phase.at(cnt) <= -180.0)
        {
            break;
        }
        cnt++;
    }

    if (cnt >= (num-1))
    {
        gain_margin         =   10000.0;
    }
    else
    {
        gain_margin         =   -cl_amp.at(cnt);
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    doubleSpinBox_gain_margin->setValue(gain_margin);
    doubleSpinBox_phase_margin->setValue(phase_margin);
    doubleSpinBox_cross_freq->setValue(cross_freq);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


void DFTSettingDialog::onPushButtonAutoClicked(bool)
{
    double  pi_amp, pi_pha, kn_c, w_tmp, dtmp, dtmp2, dtmp3, amp_tmp;
    double  lpf_amp, lpf_pha, adj_db, qn_nch_tmp;
    double  phase_margin_max, gain_margin_max, Vector_gain_min, Vector_margin_max, fre_tmp;
    double  nch_amp, nch_pha, wn_tmp;
    double  wn_nch, w_nch, zeta1_nch, zeta2_nch;

    int cnt, num;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    phase_margin_max        =   0.0;
    gain_margin_max         =   0.0;
    Vector_margin_max       =   0.0;
    Vector_gain_min         =   10000.0;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    ctl_sel             =   (CtlStruSel)(comboBox_controler->currentIndex());
    plot_sel            =   (BodePlotSel)(comboBox_bode_sel->currentIndex());
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (mod_amp_norm.count() <= 5)
    {
        return;
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    cl_amp.clear();
    cl_phase.clear();
    ctl_amp.clear();
    ctl_phase.clear();

    cl_amp_tmp.clear();
    cl_phase_tmp.clear();
    ctl_amp_tmp.clear();
    ctl_phase_tmp.clear();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    fn_c                =   doubleSpinBox_fn->value();
    ti_c                =   doubleSpinBox_ti->value();
    fn_lpf1             =   doubleSpinBox_fn_lpf->value();

    fn_nch              =   doubleSpinBox_fn_nch->value();
    qn_nch              =   doubleSpinBox_qn_nch->value();
    kn_nch              =   doubleSpinBox_kn_nch->value();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (fn_c >= 500.0)
    {
        fn_c                    =   500.0;
        doubleSpinBox_fn->setValue(fn_c);
    }

    kn_c                =   6.2831853 * fn_c * (Jall/1000000.0);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    for (int i = 0; i < m_freq->count(); i++)
    {
        w_tmp               =   6.2831853 * m_freq->at(i);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        if (ti_c < 1.0)
        {
            pi_amp        =   1.0;
            pi_pha        =   0.0;
        }
        else
        {
            dtmp                =   1000.0/ti_c;
            pi_amp              =   sqrt(dtmp*dtmp + w_tmp*w_tmp)/w_tmp;
            pi_pha              =   (atan(w_tmp/dtmp)*180.0)/M_PI - 90.0;
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        if (ctl_sel == PI_LPF_NCH_CTL_STR)
        {
            dtmp                =   6.2831853 * fn_lpf1;
            w_tmp               =   6.2831853 * m_freq->at(i);

            lpf_amp             =   dtmp / sqrt(dtmp*dtmp + w_tmp*w_tmp);
            lpf_pha             =   -(atan(w_tmp/dtmp)*180.0)/M_PI;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            adj_db              =   20 * log10(kn_c * pi_amp * lpf_amp);

            cl_amp_tmp.append((mod_amp_norm.at(i)+adj_db));
            ctl_amp_tmp.append(adj_db);

            ctl_phase_tmp.append(pi_pha+lpf_pha);

            dtmp           =   m_phase->at(i) + pi_pha + lpf_pha;
            cl_phase_tmp.append(dtmp);
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        else if (ctl_sel == PI_NCH_CTL_STR)
        {
            adj_db          =   20 * log10(kn_c * pi_amp);
            cl_amp_tmp.append((mod_amp_norm.at(i)+adj_db));
            ctl_amp_tmp.append(adj_db);

            ctl_phase_tmp.append(pi_pha);
            dtmp           =   m_phase->at(i) + pi_pha;
            cl_phase_tmp.append(dtmp);
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        else
        {
            return;
        }
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    cnt         =   0;
    num         =   cl_amp_tmp.count();

    while ((cl_amp_tmp.at(cnt) >= 0) && (cnt < num))
    {
        cnt++;
    }

    if (cnt >= num)
    {
        return;
    }

    phase_margin            =   cl_phase_tmp.at(cnt) + 180.0;
    cross_freq              =   m_freq->at(cnt);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    while (phase_margin < 30.0)
    {
        fn_c                =   fn_c*0.8;
        adj_db              =   20 * log10(0.8);

        for (int i = 0; i < m_freq->count(); i++)
        {
            cl_amp_tmp[i]           =   cl_amp_tmp.at(i)+adj_db;
            ctl_amp_tmp[i]          =   ctl_amp_tmp.at(i)+adj_db;
        }

        cnt         =   0;
        while ((cl_amp_tmp.at(cnt) >= 0) && (cnt < num))
        {
            cnt++;
        }
        if (cnt >= num)
        {
            break;
        }

        phase_margin            =   cl_phase_tmp.at(cnt) + 180.0;
        cross_freq              =   m_freq->at(cnt);

        doubleSpinBox_fn->setValue(fn_c);
        doubleSpinBox_gain_margin->setValue(gain_margin);
        doubleSpinBox_phase_margin->setValue(phase_margin);
        doubleSpinBox_cross_freq->setValue(cross_freq);
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    while (cnt < (num-1))
    {
        if ((cl_amp_tmp.at(cnt) > (cl_amp_tmp.at(cnt-1))) && (cl_amp_tmp.at(cnt) > cl_amp_tmp.at(cnt+1)) && (cl_amp_tmp.at(cnt) > 0))
        {
            peak_freq               =   m_freq->at(cnt);
            peak_db                 =   cl_amp_tmp.at(cnt);

            break;
        }
        cnt++;
    }

    if (cnt >= (num-1))
    {
        peak_freq               =   0.0;
        peak_db                 =   0.0;
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    doubleSpinBox_peak_freq->setValue(peak_freq);
    doubleSpinBox_peak_gain->setValue(peak_db);

    cl_amp                      =   cl_amp_tmp;
    cl_phase                    =   cl_phase_tmp;
    ctl_amp                     =   ctl_amp_tmp;
    ctl_phase                   =   ctl_phase_tmp;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if ((peak_freq > 100.0) && (peak_db > 0.0))
    {
        fn_nch                  =   peak_freq;

        dtmp                    =   (peak_db + 6.0)/20.0;
        dtmp                    =   pow(10,dtmp);
        kn_nch                  =   1/dtmp;

        qn_nch_tmp              =   0.05;

        while (qn_nch_tmp <= 1.0)
        {
            cl_amp.clear();
            cl_phase.clear();
            ctl_amp.clear();
            ctl_phase.clear();

            for (int i = 0; i < m_freq->count(); i++)
            {
                wn_tmp              =   6.2831853 * m_freq->at(i);

                wn_nch              =   6.2831853 * fn_nch;
                zeta2_nch           =   qn_nch_tmp;
                zeta1_nch           =   kn_nch*qn_nch_tmp;

                dtmp                =   (wn_nch*wn_nch - wn_tmp*wn_tmp);
                dtmp                =   dtmp * dtmp;

                dtmp2               =   2*wn_nch*wn_tmp*zeta1_nch;
                dtmp2               =   dtmp2 * dtmp2;

                dtmp3               =   2*wn_nch*wn_tmp*zeta2_nch;
                dtmp3               =   dtmp3 * dtmp3;

                nch_amp             =   sqrt((dtmp + dtmp2)/(dtmp + dtmp3));

                nch_pha             =   atan((2*wn_nch*wn_tmp*zeta1_nch)/(wn_nch*wn_nch - wn_tmp * wn_tmp)) -\
                                        atan((2*wn_nch*wn_tmp*zeta2_nch)/(wn_nch*wn_nch - wn_tmp * wn_tmp));

                nch_pha             =   (nch_pha*180.0)/M_PI;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
                adj_db              =   20 * log10(nch_amp);
                cl_amp.append(cl_amp_tmp.at(i) + adj_db);
                ctl_amp.append(ctl_amp_tmp.at(i) + adj_db);

                ctl_phase.append(ctl_phase_tmp.at(i) + nch_pha);
                cl_phase.append(cl_phase_tmp.at(i) + nch_pha);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            }
/*
///////////////////////////////////////////////////////////////////////////////////////////////////////////
            cnt         =   0;
            num         =   cl_amp.count();

            while ((cl_amp.at(cnt) >= 0) && (cnt < num))
            {
                cnt++;
            }

            if (cnt >= num)
            {
                break;
            }

            phase_margin            =   cl_phase.at(cnt) + 180.0;

            if (phase_margin_max < phase_margin)
            {
                phase_margin_max        =   phase_margin;
                qn_nch                  =   qn_nch_tmp;
            }
///////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
            Vector_gain_min             =   10000.0;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            for (int i = 0; i < cl_amp.count(); i++)
            {
                dtmp        =   (cl_phase.at(i)/180.0)*M_PI;
                dtmp2       =   cl_amp.at(i)/20.0;
                amp_tmp     =   pow(10,dtmp2);

                dtmp2       =   amp_tmp*cos(dtmp) + 1;
                dtmp2       =   dtmp2 * dtmp2;

                dtmp3       =   amp_tmp*sin(dtmp);
                dtmp3       =   dtmp3 * dtmp3;

                dtmp        =   sqrt(dtmp2 + dtmp3);

                if (Vector_gain_min > dtmp)
                {
                    Vector_gain_min         =   dtmp;
                    fre_tmp                 =   m_freq->at(i);
                }
            }

            if (Vector_margin_max < Vector_gain_min)
            {
                Vector_margin_max           =   Vector_gain_min;
                qn_nch                      =   qn_nch_tmp;
            }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            doubleSpinBox_qn_nch->setValue(qn_nch_tmp);
            doubleSpinBox_phase_margin->setValue(phase_margin_max);

            qn_nch_tmp              =   qn_nch_tmp + 0.05;
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        cl_amp.clear();
        cl_phase.clear();
        ctl_amp.clear();
        ctl_phase.clear();

        for (int i = 0; i < m_freq->count(); i++)
        {
            wn_tmp              =   6.2831853 * m_freq->at(i);

            wn_nch              =   6.2831853 * fn_nch;
            zeta2_nch           =   qn_nch;
            zeta1_nch           =   kn_nch*qn_nch;

            dtmp                =   (wn_nch*wn_nch - wn_tmp*wn_tmp);
            dtmp                =   dtmp * dtmp;

            dtmp2               =   2*wn_nch*wn_tmp*zeta1_nch;
            dtmp2               =   dtmp2 * dtmp2;

            dtmp3               =   2*wn_nch*wn_tmp*zeta2_nch;
            dtmp3               =   dtmp3 * dtmp3;

            nch_amp             =   sqrt((dtmp + dtmp2)/(dtmp + dtmp3));

            nch_pha             =   atan((2*wn_nch*wn_tmp*zeta1_nch)/(wn_nch*wn_nch - wn_tmp * wn_tmp)) -\
                                    atan((2*wn_nch*wn_tmp*zeta2_nch)/(wn_nch*wn_nch - wn_tmp * wn_tmp));

            nch_pha             =   (nch_pha*180.0)/M_PI;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            adj_db              =   20 * log10(nch_amp);
            cl_amp.append(cl_amp_tmp.at(i) + adj_db);
            ctl_amp.append(ctl_amp_tmp.at(i) + adj_db);

            ctl_phase.append(ctl_phase_tmp.at(i) + nch_pha);
            cl_phase.append(cl_phase_tmp.at(i) + nch_pha);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        widget_plot_amp->clearGraphs();
        widget_plot_phase->clearGraphs();
        if (plot_sel == L_BODE_PLOT)
        {
            widget_plot_amp->addGraph();
            widget_plot_amp->graph(0)->setPen(QPen(tbl_col[0]));
            widget_plot_amp->graph(0)->addData(*m_freq, cl_amp);
            widget_plot_amp->rescaleAxes(true);

            widget_plot_phase->addGraph();
            widget_plot_phase->graph(0)->setPen(QPen(tbl_col[0]));
            widget_plot_phase->graph(0)->addData(*m_freq, cl_phase);
            widget_plot_phase->rescaleAxes(true);
        }
        else if (plot_sel == C_BODE_PLOT)
        {
            widget_plot_amp->addGraph();
            widget_plot_amp->graph(0)->setPen(QPen(tbl_col[0]));
            widget_plot_amp->graph(0)->addData(*m_freq, ctl_amp);
            widget_plot_amp->rescaleAxes(true);

            widget_plot_phase->addGraph();
            widget_plot_phase->graph(0)->setPen(QPen(tbl_col[0]));
            widget_plot_phase->graph(0)->addData(*m_freq, ctl_phase);
            widget_plot_phase->rescaleAxes(true);
        }
        else if (plot_sel == C_PLUS_L_BODE_PLOT)
        {
            widget_plot_amp->addGraph();
            widget_plot_amp->graph(0)->setPen(QPen(tbl_col[0]));
            widget_plot_amp->graph(0)->addData(*m_freq, cl_amp);
            widget_plot_amp->rescaleAxes(true);

            widget_plot_phase->addGraph();
            widget_plot_phase->graph(0)->setPen(QPen(tbl_col[0]));
            widget_plot_phase->graph(0)->addData(*m_freq, cl_phase);
            widget_plot_phase->rescaleAxes(true);

            widget_plot_amp->addGraph();
            widget_plot_amp->graph(1)->setPen(QPen(tbl_col[1]));
            widget_plot_amp->graph(1)->addData(*m_freq, ctl_amp);
            widget_plot_amp->rescaleAxes(true);

            widget_plot_phase->addGraph();
            widget_plot_phase->graph(1)->setPen(QPen(tbl_col[1]));
            widget_plot_phase->graph(1)->addData(*m_freq, ctl_phase);
            widget_plot_phase->rescaleAxes(true);
        }
        else
        {
            widget_plot_amp->addGraph();
            widget_plot_amp->graph(0)->setPen(QPen(tbl_col[0]));
            widget_plot_amp->graph(0)->addData(*m_freq, mod_amp_norm);
            widget_plot_amp->rescaleAxes(true);

            widget_plot_phase->addGraph();
            widget_plot_phase->graph(0)->setPen(QPen(tbl_col[0]));
            widget_plot_phase->graph(0)->addData(*m_freq, *m_phase);
            widget_plot_phase->rescaleAxes(true);
        }

        widget_plot_amp->xAxis->setScaleType(QCPAxis::stLogarithmic);
        widget_plot_phase->xAxis->setScaleType(QCPAxis::stLogarithmic);

        widget_plot_amp->replot();
        widget_plot_phase->replot();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        cnt         =   0;
        num         =   cl_amp.count();

        while ((cl_amp.at(cnt) >= 0) && (cnt < num))
        {
            cnt++;
        }

        if (cnt >= num)
        {
            cnt     =   num - 1;
        }
        phase_margin            =   cl_phase.at(cnt) + 180.0;
        cross_freq              =   m_freq->at(cnt);

        while (cnt < (num-1))
        {
            if ((cl_amp.at(cnt) > 0) && (cl_amp.at(cnt+1) < 0))
            {
                dtmp                =   cl_phase.at(cnt) + 180.0;
                phase_margin        =   (phase_margin > dtmp) ? dtmp : phase_margin;
                cross_freq          =   m_freq->at(cnt);
                break;
            }
            cnt++;
        }

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        cnt         =   0;
        while (cnt < (num-1))
        {
            if (cl_phase.at(cnt) <= -180.0)
            {
                break;
            }
            cnt++;
        }

        if (cnt >= (num-1))
        {
            gain_margin         =   10000.0;
        }
        else
        {
            gain_margin         =   -cl_amp.at(cnt);
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        doubleSpinBox_gain_margin->setValue(gain_margin);
        doubleSpinBox_phase_margin->setValue(phase_margin);
        doubleSpinBox_cross_freq->setValue(cross_freq);

        doubleSpinBox_fn_nch->setValue(fn_nch);
        doubleSpinBox_qn_nch->setValue(qn_nch);
        doubleSpinBox_kn_nch->setValue(kn_nch);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}



DFTSettingDialog::~DFTSettingDialog()
{
    mod_amp_norm.clear();

    cl_amp.clear();
    cl_phase.clear();

    ctl_amp.clear();
    ctl_phase.clear();

    cl_amp_tmp.clear();
    cl_phase_tmp.clear();

    ctl_amp_tmp.clear();
    ctl_phase_tmp.clear();
}










//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
