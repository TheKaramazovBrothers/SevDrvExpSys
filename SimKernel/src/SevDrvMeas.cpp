//=========================================================================================================
// project		:	servo system measure
// File			:	SevDrvMeas.C
// discription	:	use in servo system task scheduling
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g
// date			:	2022/07/14
// copyright(C)	:	googoltech	(2022-2032)
//=========================================================================================================
#include "Cia402AppEmu.h"
#include "SevCtlPrmTblDef.h"
#include "SevDrvMeas.h"
#include "SevHardRes.h"


int16   KpiInitSensMeasModule(SENS_MEAS * m_sens)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    double  ts_tmp;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (SEV_PRM_FROM_EX_MEM_EN == DISABLE)
    {
        m_sens->prm.enc_line_num    =   16777216;
        ts_tmp                      =   31250;
    }
    else
    {
        CpiReadRamPrmByDicInx(TS_ISR_PRM_ID32_OBJW_2010H, &ts_tmp);
    }

    m_sens->kspd                =   ((1000000000.0/ts_tmp)/(double)(m_sens->prm.enc_line_num))*PI2_CIRCULAR_CONSTANT;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_sens->ia                  =   0;
    m_sens->ib                  =   0;
    m_sens->ic                  =   0;

    m_sens->phim                =   0;
    m_sens->phil                =   0;
    m_sens->mot_spd             =   0;

    m_sens->pos_in              =   0;
    m_sens->pos_cnt             =   0;
    m_sens->pos_cnt_lst         =   0;
    m_sens->dpos                =   0;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}



int16   KpiGetCurrSensorValue(SENS_MEAS * m_sens)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    HalGetCurrSensorValue(&m_sens->ia, &m_sens->ib, &m_sens->ic);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}

int16   KpiGetEncValue(SENS_MEAS * m_sens)
{
    int64   lltmp;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    HalGetAbsPosValue(&m_sens->phim, &m_sens->phil);


    m_sens->pos_cnt                     =   (m_sens->phim / PI2_CIRCULAR_CONSTANT) * (double)(m_sens->prm.enc_line_num);

    m_sens->dpos                        =   m_sens->pos_cnt - m_sens->pos_cnt_lst;
    m_sens->pos_cnt_lst                 =   m_sens->pos_cnt;


    lltmp                               =   (int32)(m_sens->pos_in)  + m_sens->dpos;

    if (lltmp > m_sens->prm.enc_line_num)
    {
        m_sens->pos_in                  =   lltmp - m_sens->prm.enc_line_num;
    }
    else if (lltmp < 0)
    {
        m_sens->pos_in                  =   lltmp + m_sens->prm.enc_line_num;
    }
    else
    {
        m_sens->pos_in                  =   lltmp;
    }

    m_sens->mot_spd                     =   (double)(m_sens->dpos) * m_sens->kspd;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}




int16   KpiThreeVoltageOutput(double * ua, double * ub, double * uc)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    HalSetThreePhaVoltage(ua, ub, uc);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}











/////////////////////////////////////////////////// no more //////////////////////////////////////////////
