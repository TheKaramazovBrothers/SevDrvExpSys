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
    void onLineEditTqrFactorValueEdited(const QString & value);
    void onLineEditTqrFactorreturnPressed(void);

    void onPushButtonCalculateClicked(bool);

    void onPlotAmplitudeMouseMoved(QMouseEvent *event);
    void onPlotPhaseMouseMoved(QMouseEvent *event);
private:
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    QVector<double>             * m_freq;
    QVector<double>             * m_amp;
    QVector<double>             * m_phase;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    QVector<double>             mod_amp_norm;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    double                      tqr_factor;
    CurrUnitSel                 curr_unit;
    VelUnitSel                  vel_unit;

    FreSelOfBode                start_fn;
    FreSelOfBode                end_fn;

    double                      Jall;
    double                      kg_adj;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
};


















#endif

//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
