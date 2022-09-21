//=========================================================================================================
// project		:	servo system virtual hardware resource realization
// File			:	TuningCmd.cpp
// discription	:	use in servo system virtual tuning command design
//	
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g		
// date			:	2016/07/04
// copyright(C)	:	googoltech	(2016-2020)	
//=========================================================================================================

#include "DspCpu.h"
#include "BackGroundTask.h"

#include <QMutex>
#include "TuningCmd.h"

QMutex      m_mutex;


int16	VpiServoEnable(bool m_en)                                              // servo enable function declare | true/enable, false.disable
{
    QMutexLocker locker(&m_mutex);
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (m_en == true)
    {
        gSevDrv.obj.seq.prm.ctl_word_tmp.bit.SO     =   TRUE;
    }
    else
    {
        gSevDrv.obj.seq.prm.ctl_word_tmp.bit.SO     =   FALSE;
    }
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     return  TRUE;
}


int16	VpiEnableOperate(bool m_en)                                              // servo enable function declare | true/enable, false.disable
{
    QMutexLocker locker(&m_mutex);
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (m_en == true)
    {
        gSevDrv.obj.seq.prm.ctl_word_tmp.bit.EO     =   TRUE;
    }
    else
    {
        gSevDrv.obj.seq.prm.ctl_word_tmp.bit.EO     =   FALSE;
    }
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     return  TRUE;
}


int16	VpiSetServoWorkMode(tSeqWorkMode m_mod)                                // set servo work mode
{
    QMutexLocker locker(&m_mutex);
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    gSevDrv.obj.seq.prm.usr_mode_tmp            =   m_mod;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}

// servo reference interface function define
int16	VpiSetIdRef(double id_ref)
{
    QMutexLocker locker(&m_mutex);
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    gSevDrv.obj.seq.idr_tmp                     =   id_ref;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}

int16	VpiSetIqRef(double iq_ref)
{
    QMutexLocker locker(&m_mutex);
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    gSevDrv.obj.seq.iqr_tmp                     =   iq_ref;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}

int16	VpiSetUdRef(double ud_ref)
{
    QMutexLocker locker(&m_mutex);
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    gSevDrv.obj.seq.udr_tmp                     =   ud_ref;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}


int16	VpiSetUqRef(double uq_ref)
{
    QMutexLocker locker(&m_mutex);
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    gSevDrv.obj.seq.uqr_tmp                     =   uq_ref;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}

int16	VpiSetUaRef(double ua_ref)
{
    QMutexLocker locker(&m_mutex);
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    gSevDrv.obj.seq.uar_tmp                     =   ua_ref;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}

int16	VpiSetUbRef(double ub_ref)
{
    QMutexLocker locker(&m_mutex);
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    gSevDrv.obj.seq.ubr_tmp                     =   ub_ref;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}

int16	VpiSetUcRef(double uc_ref)
{
    QMutexLocker locker(&m_mutex);
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    gSevDrv.obj.seq.ucr_tmp                     =   uc_ref;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}



int16	VpiSetSpdRef(double spd_ref)
{
    QMutexLocker locker(&m_mutex);
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    gSevDrv.obj.seq.spdr_tmp                     =   spd_ref;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}

int16	VpiSetPosRef(double pos_ref)
{
    QMutexLocker locker(&m_mutex);
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    gSevDrv.obj.seq.posr_tmp                     =   pos_ref;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// servo reference interface function define
double	VpiGetIdRef(void)
{
    QMutexLocker locker(&m_mutex);
    return  gSevDrv.obj.seq.idr_tmp ;
}

double	VpiGetIqRef(void)
{
    QMutexLocker locker(&m_mutex);
    return  gSevDrv.obj.seq.iqr_tmp ;
}

double	VpiGetUdRef(void)
{
    QMutexLocker locker(&m_mutex);
    return  gSevDrv.obj.seq.udr_tmp ;
}

double	VpiGetUqRef(void)
{
    QMutexLocker locker(&m_mutex);
    return  gSevDrv.obj.seq.uqr_tmp ;
}

double	VpiGetUaRef(void)
{
    QMutexLocker locker(&m_mutex);
    return  gSevDrv.obj.seq.uar_tmp ;
}

double	VpiGetUbRef(void)
{
    QMutexLocker locker(&m_mutex);
    return  gSevDrv.obj.seq.ubr_tmp ;
}

double	VpiGetUcRef(void)
{
    QMutexLocker locker(&m_mutex);
    return  gSevDrv.obj.seq.ucr_tmp ;
}

double	VpiGetSpdRef(void)
{
    QMutexLocker locker(&m_mutex);
    return  gSevDrv.obj.seq.spdr_tmp ;
}

double	VpiGetPosRef(void)
{
    QMutexLocker locker(&m_mutex);
    return  gSevDrv.obj.seq.posr_tmp ;
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


/////////////////////////////////////////////// no more ///////////////////////////////////////////////////
