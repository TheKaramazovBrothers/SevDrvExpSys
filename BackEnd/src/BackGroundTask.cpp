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
#include "BackGroundTask.h"
#include <cmath>


WaveBuf::WaveBuf(QObject *parent)
{
// parameter initialization
    this->enp                       =   false;
    this->samp_div_tims             =   1;
    this->graph_num                 =   8;
    this->data_space_ulim           =   96000;
    this->clu_cyc_ts                =   0.0000625;
// variable initialization
    QVector<qreal>		*vtmp       =   new QVector<qreal>;
//---------------------------------------------------------------------------------------------------------
    this->data_list.clear();
    this->key_vec.clear();

    vtmp->append(0.0);
    for (int16 i = 0; i < g_MAX_WAVE_PLOT_NUM; i++)
    {
        this->data_list.append(*vtmp);
    }
    this->key_vec.append(0.0);

    this->curr_key                  =   0.0;
//---------------------------------------------------------------------------------------------------------
}


WaveBuf::~WaveBuf()
{

}


int16 WaveBuf::FillWaveToBuffer()
{
    QMutexLocker locker(&mutex);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (this->key_vec.count() <= this->data_space_ulim)
    {
        this->curr_key = this->curr_key + this->clu_cyc_ts;

        for (int16 i = 0; i < this->graph_num; i++)
        {
            double   dtmp				=	this->curr_key * sin(this->curr_key*2*g_PI + i*(g_PI/4));
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
            this->data_list[i].clear();
        }
        this->key_vec.clear();

        return  true;
    }
    else
    {
        return  false;
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
threadTask::threadTask(QObject *parent)
    :QThread(parent)
{
    m_buf       =   new WaveBuf(parent);
    stopped     =   false;
}


threadTask::~threadTask()
{

}


void threadTask::run()
{
    while(1)
    {
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        m_buf->FillWaveToBuffer();
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
