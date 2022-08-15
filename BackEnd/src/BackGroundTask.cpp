//=========================================================================================================
// project		:	background task define
// File			:	BackGroundTask.cpp
// discription	:	background task define
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g/1487
// date			:	2022/06/29
// copyright(C)	:	liu.g	(2022-2030)
//=========================================================================================================
#include <cmath>
#include "Cia402AppEmu.h"
#include "BackGroundTask.h"

PmsmDrvMechModel    gMechModel;
SERVO_DRV           gSevDrv;

WaveBuf::WaveBuf(QObject *parent)
{
// parameter initialization
    this->enp                       =   false;
    this->samp_div_tims             =   1;
    this->graph_num                 =   8;
    this->data_space_ulim           =   96000;
    this->clu_cyc_ts                =   0.00003125;
// variable initialization
    QVector<qreal>		*vtmp       =   new QVector<qreal>;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    this->data_list.clear();
    this->key_vec.clear();

    vtmp->append(0.0);
    for (int16 i = 0; i < g_MAX_WAVE_PLOT_NUM; i++)
    {
        this->data_list.append(*vtmp);
        this->obj_inx[i]            =   i;
    }
    this->key_vec.append(0.0);

    this->curr_key                  =   0.0;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}
void    WaveBuf::ClearWaveVecBuf(void)
{
    for (int16 i = 0; i < g_MAX_WAVE_PLOT_NUM; i++)
    {
        this->data_list[i].clear();

    }
    this->key_vec.clear();
}

WaveBuf::~WaveBuf()
{
    for (int16 i = 0; i < g_MAX_WAVE_PLOT_NUM; i++)
    {
        this->data_list[i].clear();

    }
    this->data_list.clear();
    this->key_vec.clear();
}


int16 WaveBuf::FillWaveToBuffer()
{
    QMutexLocker locker(&mutex);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if ((this->key_vec.count() <= this->data_space_ulim) && (this->enp == true))
    {
        this->curr_key = this->curr_key + this->clu_cyc_ts;

        double  dtmp    =   0;

        for (int i = 0; i < this->graph_num; i++)
        {
            CpiReadRamVarByDicInx(this->obj_inx[i], &dtmp);
            this->data_list[i].append(dtmp);
        }

        this->key_vec.append(this->curr_key);
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}


bool WaveBuf::GetWaveData(QVector<qreal> * pkey, QList<QVector<qreal>> * pvalue)
{
    int32	buf_num;
    QVector<qreal> * vtmp;
    QMutexLocker locker(&mutex);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    buf_num		=	this->key_vec.count();
    if (buf_num > 0)
    {
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        for (int i = 0; i < buf_num; i++)
        {
            pkey->append(this->key_vec.at(i));
        }
        for (int i = 0; i < this->graph_num; i++)
        {
            vtmp        =   new QVector<qreal>;

            pvalue->append(*vtmp);

            for (int j = 0; j < buf_num; j++)
            {
                (*pvalue)[i].append(this->data_list[i].at(j));
            }
        }       
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        for (int i = 0; i < this->graph_num; i++)
        {
            this->data_list[i].remove(0, buf_num);
        }
        key_vec.remove(0, buf_num);

        vtmp->clear();

        return  true;
    }
    else
    {
        return  false;
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}



//*********************************************************************************************************
//*                                    BACK GROUND MODULE INITIALIZATION
//*
//* Description: This function is used to initialize background task module in servo system
//*
//*
//* Arguments  : m_bkgd		is a pointer to servo system background task object
//*
//* Returns    : -1/initialize Failure, else/success
//*********************************************************************************************************
bkgdTask::bkgdTask(QObject *parent)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    this->prm.model_task_scan_tim                           =   1;
    this->prm.ccld_task_scan_tim                            =   5;
    this->prm.pvcld_task_scan_tim                           =   10;
    this->prm.prochd_task_scan_tim                          =   160;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    KpiInitServoDriverSys(&gSevDrv);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

bkgdTask::~bkgdTask(void)
{
}



int16	bkgdTask::BackGroundCnt(void)
{
    this->mtk_cnt++;
    this->ctk_cnt++;
    this->ptk_cnt++;
    this->stk_cnt++;
//---------------------------------------------------------------------------------------------------------
    if (this->mtk_cnt >= this->prm.model_task_scan_tim)
    {
        this->flag.bit.MTF                  =	TRUE;
        this->mtk_cnt						=	0;
    }

    if (this->ctk_cnt >= this->prm.ccld_task_scan_tim)
    {
        this->flag.bit.CTF                  =	TRUE;
        this->ctk_cnt						=	0;
    }

    if (this->ptk_cnt >= this->prm.pvcld_task_scan_tim)
    {
        this->flag.bit.PTF  				=	TRUE;
        this->ptk_cnt						=	0;
    }

    if (this->stk_cnt >= this->prm.prochd_task_scan_tim)
    {
        this->flag.bit.STF  				=	TRUE;
        this->stk_cnt						=	0;
    }
//---------------------------------------------------------------------------------------------------------
    return	TRUE;
}

int16	bkgdTask::BackGroundTaskSched(void)
{
//---------------------------------------------------------------------------------------------------------
    if (this->flag.bit.MTF == TRUE)
    {
        this->BackGroundTaskModel();
        this->flag.bit.MTF                  =	FALSE;
    }
//---------------------------------------------------------------------------------------------------------
    if (this->flag.bit.CTF == TRUE)
    {
        this->BackGroundTaskCcld();
        this->flag.bit.CTF  				=	FALSE;
    }
//---------------------------------------------------------------------------------------------------------
    if (this->flag.bit.PTF == TRUE)
    {
        this->BackGroundTaskPvcld();
        this->flag.bit.PTF                  =	FALSE;
    }
//---------------------------------------------------------------------------------------------------------
    if (this->flag.bit.STF == TRUE)
    {
        this->BackGroundTaskProchd();
        this->flag.bit.STF                  =	FALSE;
    }

//---------------------------------------------------------------------------------------------------------
        return TRUE;
}

int16	bkgdTask::BackGroundTaskModel(void)
{
    gMechModel.PmsMotorModeling();

    return  TRUE;
}


int16   bkgdTask::BackGroundTaskCcld(void)
{
    KpiServoSensorSignalPro(&gSevDrv);
    KpiServoTaskCallOne(&gSevDrv);

    return  TRUE;
}


int16   bkgdTask::BackGroundTaskPvcld(void)
{
    KpiServoTaskCallTwo(&gSevDrv);


    return  TRUE;
}


int16   bkgdTask::BackGroundTaskProchd(void)
{
    KpiServoBackGroundTask(&gSevDrv);
    return  TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
threadTask::threadTask(QObject *parent)
    :QThread(parent)
{
    m_buf       =   new WaveBuf(parent);
    m_bktask    =   new bkgdTask(parent);

    stopped     =   false;
}


threadTask::~threadTask()
{
    stopped     =   true;
    delete      m_buf;
    delete      m_bktask;
}


void threadTask::run()
{
    while(1)
    {
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        m_bktask->BackGroundCnt();

        if (m_bktask->flag.bit.CTF == TRUE)
        {
            m_buf->FillWaveToBuffer();
        }

        m_bktask->BackGroundTaskSched();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        {
            QMutexLocker locker(&mutex);
            if (stopped)
            {
                stopped = false;
                break;
            }
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    }
}


void threadTask::stop()
{
    stopped     =   true;
}







//////////////////////////////////////////////// no more //////////////////////////////////////////////////
