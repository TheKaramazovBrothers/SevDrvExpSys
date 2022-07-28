//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	thread task for servo control                               //
//	file				:	BackGroundTask.h                                            //
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
#include "MechModel.h"
#include "SevDrvTask.h"


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
// back ground task define
//-------------------------------------------------------------------------------------
//								BACKGROUND TASK STRUCT
//-------------------------------------------------------------------------------------
typedef		struct	bkgd_task_prm
{
// back ground task module parameter define
    int16			model_task_scan_tim;														// scan time of modeling task | unit[scan]
    int16			ccld_task_scan_tim;                                                         // scan time of current control task | unit[scan]
    int16			pvcld_task_scan_tim;														// scan time of pos&vel control task | unit[scan]
    int16           prochd_task_scan_tim;                                                       // scan time of protect&schedule | unit[scan]
}BKGD_TASK_PRM;

//-------------------------------------------------------------------------------------
//					   				TASK FINISH FLAG
//-------------------------------------------------------------------------------------
typedef struct	bkgd_task_flag_bits
{
    Uint16		MTF		: 1;																// finish flag of modeling task
    Uint16		CTF		: 1;																// finish flag of current control task
    Uint16		PTF		: 1;																// finish flag of pos&vel control task
    Uint16      STF     : 1;                                                                // finish flag of protect&schedule task

    Uint16		rsvd	: 12;																// rsvd
}BKGD_TASK_FLAG_BITS;


typedef	union
{
    Uint16						all;
    BKGD_TASK_FLAG_BITS			bit;
}tBkgdTaskFlag;


//-------------------------------------------------------------------------------------
//					   define the type of background task structure
//-------------------------------------------------------------------------------------
class	bkgdTask
{
public:
    bkgdTask(QObject *parent);
    ~bkgdTask(void);
public:
    int16	BackGroundCnt(void);
    int16	BackGroundTaskSched(void);

    int16	BackGroundTaskModel(void);
    int16	BackGroundTaskCcld(void);
    int16	BackGroundTaskPvcld(void);
    int16	BackGroundTaskProchd(void);
private:
// back ground task module parameter define
    BKGD_TASK_PRM		prm;
public:
    tBkgdTaskFlag		flag;
    int16				mtk_cnt;
    int16				ctk_cnt;
    int16				ptk_cnt;
    int16				stk_cnt;
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
    WaveBuf             *m_buf;
    bkgdTask            *m_bktask;
private:
    volatile bool       stopped;
    QMutex              mutex;
};


// servo model design
extern  PmsmDrvMechModel    gMechModel;
extern  SERVO_DRV           gSevDrv;

#endif







//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
