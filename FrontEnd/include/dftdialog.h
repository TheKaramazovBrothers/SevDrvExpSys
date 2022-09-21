//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	DFT dialog module design               						//
//	file				:	dftdialog.h                             					//
//	Description			:	use for DFT dialog module design in servo system       		//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g   		|	2022/09/09	|	   liu.g        |		2022 - 2032			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DFTDIALOG_H__
#define __DFTDIALOG_H__


#include <QDialog>
#include "ui_dftdialog.h"

typedef enum {
    ANALYSIS_SIGNAL = 0,
    ANALYSIS_SYSTEM = 1
} AnalysisType;

#define     MAX_TABLE_WAVE_NUM    20

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class DFTDialog : public QDialog, public Ui::DFTDialog
{
    Q_OBJECT
public:
    DFTDialog(QWidget *parent = 0);
    ~DFTDialog();
public:
    void setCurveList(QTableWidget * name_list, QVector<qreal> * key_list, QList<QVector<qreal>> * value_list);
    void setCurveTime(double start_tim, double final_tim, double samp_tim);
private:
    void initDialogUi();
    void setSignalSlotConnections();
private slots:
    void onBtnAmpClicked(bool checked);
    void onBtnPhaClicked(bool checked);
    void onBtnSignalClicked();
    void onBtnSettingClicked();
    void onAxisRangeChanged(QVector<double> limitList);
    void onBtnFitClicked();
    void onBtnOpenClicked();
    void onBtnSaveClicked();
    void onBtnAllClicked();
    void onBtnClearClicked();
    void onBtnRemoveClicked();
    void onBtnAddClicked();

    void onPlotAmplitudeMouseMoved(QMouseEvent *event);
    void onPlotPhaseMouseMoved(QMouseEvent *event);

    void onTableItemClicked(QTableWidgetItem * item);
private:
    QTableWidget                * m_wave_name_tbl;                                                  // vector for storage curve name
    QList<QVector<qreal>>       * m_value_list;                                                     // wave value list
    QVector<qreal>              * m_key_list;                                                       // wave key list

    double                      m_start_tim;                                                        // start time
    double                      m_final_tim;                                                        // final tim
    double                      m_samp_tim;                                                         // sample time | unit[s]

    AnalysisType                m_anys_type;                                                        // analysis type

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    QVector<double>             m_freq;
    QVector<double>             m_amp;
    QVector<double>             m_phase;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    bool                        wave_vis_tbl[MAX_TABLE_WAVE_NUM];
    bool                        all_show_flag;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    QColor                      m_showColor;
    QColor                      m_hideColor;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    double                      m_sin_hz_start;                                                       // HZ
    double                      m_sin_hz_step;                                                        // HZ
    int                         m_sin_harm_num;                                                       // Harmonic number

    double                      m_sin_delay_tim;                                                      // delay time | unit[s]
    double                      m_sin_steady_tim;                                                     // steady time | unit[s]

    int                         m_sin_delay_num;                                                      // delay length number
    int                         m_sin_data_num;                                                       // effective data length number
};
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=







#endif





//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
