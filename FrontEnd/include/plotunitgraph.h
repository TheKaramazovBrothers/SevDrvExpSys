//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	plot graph in terminal              						//
//	file				:	plotunitgraph.h                         					//
//	Description			:	use for plot graph in terminal                      		//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g   		|	2022/06/12	|	   liu.g        |		2022 - 2030			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////


#ifndef __PLOTUNITGRAPH_H__
#define __PLOTUNITGRAPH_H__

#include <QWidget>
#include "ui_plotunitgraph.h"
#include "BackGroundTask.h"



/////////////////////////////////////////////////////////////////////////////////////////////////////////
class PlotUnitGraph : public QWidget, public Ui::PlotUnitGraph
{
    Q_OBJECT
public:
    PlotUnitGraph(QWidget *parent = 0);
    ~PlotUnitGraph();
//*******************************************************************************************************
private slots:
    void    onBtnFloatInClicked(bool checked);
    void    onBtnStartSampleClicked(bool checked);
    void    onBtnMeaHClicked(bool checked);
    void    onBtnMeaVClicked(bool checked);

    void    onBtnFitClicked();
    void    onBtnLoadAllCurveClicked();
    void    onBtnOpenCurveClicked(bool checked);
    void    onBtnSaveCurveClicked();
    void    onBtnFFTClicked(bool checked);

    void    onPlotPosHoverChanged(const QPointF &point);
    void    onPlotMeaVposChanged(qreal v1, qreal v2, qreal dv);
    void    onPlotMeaHposChanged(qreal v1, qreal v2, qreal dv);

    void    onBtnCurveAddClicked();
    void    onBtnCurveRemoveClicked();
    void    onBtnCurveClearClicked();
    void    onBtnCurveShowAllClicked();
//*******************************************************************************************************
private:
    void    setPlotUintGraphIcons();
    void    InitPlotWave();
    void    setupSimpleDemo();
    void    createSignalSlotsConnect();
private slots:
    void    realTimeDataPlot();
public:
    threadTask              *m_task;
private:
    QTimer                  data_timer;                                                     // use for wave plot
// parameter define
    int                     wave_data_storage_num;                                          // the total number for wave storage
    int                     wave_disp_interval;                                             // display interval number

    double                  wave_disp_range;                                                // wave display range | unit[s]
    double                  wave_storage_range;                                             // wave storage range | unit[s]
    double                  wave_samp_ts;                                                   // sample time for wave display | unit[s]
//  variable define
    bool                    wave_plot_en;                                                   // wave plot enable flag
    int                     wave_disp_cnt;                                                  // count variable for wave display


    double                  key;                                                            // current key value in wave plot
    QList<QVector<qreal>>   value_list;                                                     // wave value list
    QVector<qreal>			key_vec;                                                        // wave key list
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////








#endif





//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
