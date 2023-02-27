//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	DFT setting dialog                                          //
//	file				:	dftsettingdialog.h                           				//
//	Description			:	use for DFT dialog setting design in servo system       		//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g   		|	2022/12/21	|	   liu.g        |		2022 - 2032			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DFTSETTINGDIALOG_H__
#define __DFTSETTINGDIALOG_H__

#include <QDialog>
#include "ui_dftsettingdialog.h"


typedef enum
{
    MA_CURR_EXCI_UNIT       =   0,
    A_CURR_EXCI_UNIT        =   1
} CurrUnitSel;


typedef enum
{
    RPM_VEL_EXCI_UNIT       =   0,
    RADS_VEL_EXCI_UNIT      =   1,
    RPS_VEL_EXCI_UNIT       =   2,
} VelUnitSel;


typedef enum
{
    P_CTL_STR               =   0,
    PI_CTL_STR              =   1,
    PI_LPF_CTL_STR          =   2,
    PI_LPF_NCH_CTL_STR      =   3,
    PI_NCH_CTL_STR          =   4,
}CtlStruSel;


typedef enum
{
    L_BODE_PLOT             =   0,
    C_BODE_PLOT             =   1,
    C_PLUS_L_BODE_PLOT      =   2,
}BodePlotSel;



typedef enum
{
    F10_HZ_FRE               =   0,
    F20_HZ_FRE               =   1,
    F30_HZ_FRE               =   2,
    F40_HZ_FRE               =   3,
    F50_HZ_FRE               =   4,
    F60_HZ_FRE               =   5,
    F70_HZ_FRE               =   6,
    F80_HZ_FRE               =   7,
    F90_HZ_FRE               =   8,
    F100_HZ_FRE              =   9
} FreSelOfBode;



class DFTSettingDialog : public QDialog, public Ui::DFTSettingDialog
{
    Q_OBJECT
public:
    DFTSettingDialog(QWidget *parent = 0);
    ~DFTSettingDialog();
public:
    void setFreResData(QVector<double> * freq_vec, QVector<double> * amp_vec, QVector<double> * phase_vec);
private:
    void initDialogUi();
    void setSignalSlotConnections();
private slots:
    void onPushButtonCalculateClicked(bool);
    void onPushButtonUpdateClicked(bool);
    void onPushButtonAutoClicked(bool);

    void onPlotAmplitudeMouseMoved(QMouseEvent *event);
    void onPlotPhaseMouseMoved(QMouseEvent *event);
    void onComboBoxControlerChanged(int index);
    void onBtnSaveClicked();
private:
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    QVector<double>             * m_freq;
    QVector<double>             * m_amp;
    QVector<double>             * m_phase;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    QVector<double>             mod_amp_norm;

    QVector<double>             cl_amp;
    QVector<double>             cl_phase;

    QVector<double>             ctl_amp;
    QVector<double>             ctl_phase;

    QVector<double>             cl_amp_tmp;
    QVector<double>             cl_phase_tmp;

    QVector<double>             ctl_amp_tmp;
    QVector<double>             ctl_phase_tmp;

    double                      cross_freq;

    double                      peak_freq;
    double                      peak_db;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    double                      fn_c;
    double                      ti_c;
    double                      kn_c;

    double                      fn_lpf1;

    double                      fn_nch;                                                                 // center frequency of notch filter | unit[HZ]
    double                      qn_nch;                                                                 // damping of notch filter | unit[1.0]
    double                      kn_nch;                                                                 // depth of notch filter | unit[1.0]

    CtlStruSel                  ctl_sel;
    BodePlotSel                 plot_sel;

    double                      phase_margin;
    double                      gain_margin;
 //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    double                      tqr_factor;
    CurrUnitSel                 curr_unit;
    VelUnitSel                  vel_unit;

    FreSelOfBode                start_fn;
    FreSelOfBode                end_fn;

    double                      Jall;                                                                   // 10^-6 kg.m^2
    double                      kg_adj;

    double                      curr_unit_coef;                                                         // coefficient for current unit adjust
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
};


















#endif

//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
