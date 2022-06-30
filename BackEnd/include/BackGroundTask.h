//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	thread task for servo control                               //
//	file				:	threadtask.h                                                //
//	Description			:	use for thread task work                              		//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g   		|	2022/06/28	|	   liu.g        |		2022 - 2030			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __BACKGROUNDTASK_H__
#define __BACKGROUNDTASK_H__


#include <QThread>
#include <QMutex>
#include <QWidget>
#include <QTimer>
#include "DspCpu.h"

const   Uint16  g_MAX_WAVE_PLOT_NUM     =   20;
const   double  g_PI                    =   3.14159265358979;
//##############################################################################################################################

class	WaveBuf
{
public:
    WaveBuf(QObject *parent);
    ~WaveBuf(void);
public:
// parameter define
    bool                    enp;																	// wave plot enable bit | 1/enable,0/disable
    Uint16                  samp_div_tims;                                                          // sample times
    Uint16                  graph_num;																	// wave graph numbers
    int32                   data_space_ulim;                                                        // upper limit indicate buffer is full

    double                  clu_cyc_ts;                                                             // closed loop update cycle times | unit[s]
 // variable define
    double                  curr_key;                                                               // current key value for wave plot | unit[s]

    QList<QVector<qreal>>   data_list;                                                              // wave data value list
    QVector<qreal>			key_vec;                                                                // wave key value vector

    QMutex                  mutex;                                                                  // mutex variable define

public:
    int16	FillWaveToBuffer(void);                                                                 // function to fill data to data buffer
    bool	GetWaveData(QVector<qreal> * pkey, QList<QVector<qreal>> * pvalue);                     // get wave data function

};




//##############################################################################################################################
class threadTask : public QThread
{
public:
    threadTask(QObject *parent);
    ~threadTask();
    void stop();
protected:
    void run();

public:
    WaveBuf *   m_buf;
private:
    volatile bool stopped;
    QMutex      mutex;
};






#endif







//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
