//=========================================================================================================
// project		:	servo system position trajectory produce realization
// File			:	PosTrajProd.cpp
// discription	:	use in servo system position trajectory module realization
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g
// date			:	2022/08/31
// copyright(C)	:	liu.g	(2022-2032)
//=========================================================================================================
#include <cmath>
#include "Cia402AppEmu.h"
#include "SevCtlPrmTblDef.h"
#include "PosTrajProd.h"

//*********************************************************************************************************
//*                             POSITION TRAJECTORY MODULE INITIALIZATION
//*
//* Description: This function is used to initialize position trajectory module in servo system
//*
//*
//* Arguments  : m_ctl		is a pointer to servo system position trajectory object
//*
//* Returns    : -1/initialize Failure, else/success
//*********************************************************************************************************
int16	KpiInitPosTrajProdModule(POS_TRAJ * m_ctl)
{
//**************************************************************************************************************************
// parameter initialization
    if (SEV_PRM_FROM_EX_MEM_EN == DISABLE)
    {
        m_ctl->prm.ts                       =   62500;
        m_ctl->prm.accrate                  =   1300;
        m_ctl->prm.decrate                  =   1300;
        m_ctl->prm.maxspd                   =   3000;
        m_ctl->prm.rot_res                  =   16777216;
        m_ctl->prm.cfg_opt.all              =   0;

        m_ctl->prm.recip_num                =   100;                                                          // reciprocating motion times
        m_ctl->prm.interv_tim               =   1600;                                                         // interval time between motion | unit[scan]
        m_ctl->prm.spdr_hold_tim            =   16000;                                                        // speed command hold time in reciprocate motion | unit[scan]
    }
// temper parameter initialization
    m_ctl->vel_max                      =   ((double)(m_ctl->prm.maxspd)/60.0)*(double)(m_ctl->prm.rot_res);
    m_ctl->acc_max                      =   (double)(m_ctl->prm.accrate) * 10000.0;
//**************************************************************************************************************************
//  variable initialization
    m_ctl->ptraj_set                    =   0;                                                              // position command set value
    m_ctl->ptraj_in                     =   0;                                                              // position command input value
    m_ctl->ptraj_out                    =   0;                                                              // position command output value

    m_ctl->xq0                          =   0;                                                              // initialize position | unit[pulse]
    m_ctl->xq1                          =   0;                                                              // finish position | unit [pulse]
    m_ctl->xq_real                      =   0;                                                              // real position | unit [pulse]
    m_ctl->xqh                          =   0;                                                              // increment position between q0 to q1

    m_ctl->x_v0                         =   0;                                                              // initialize velocity | unit[pulse/s]
    m_ctl->x_v1                         =   0;                                                              // the max velocity can be reached | unit[pulse/s]
    m_ctl->x_vpeak                      =   0;                                                              // the peak velocity for tajectory produce | unit[pulse/s]
    m_ctl->x_vpabs                      =   0;                                                              // the absolute peak velocity for tajectory produce | unit[pulse/s]
    m_ctl->xv_real                      =   0;                                                              // real velocity command

    m_ctl->acc_max_real                 =   0;                                                              // absolute maximum accelerate of trajectory | unit[pulse/s/s]

    m_ctl->t0                           =   0;                                                              // initialize time | unit[s]
    m_ctl->treal                        =   0;                                                              // current time | unit[s]
    m_ctl->x_tacc                       =   0;                                                              // total accrate time | unit[s]
    m_ctl->x_tdec                       =   0;                                                              // total decelerate time | unit[s]
    m_ctl->x_ttotal                     =   0;                                                              // total time | unit[s]
    m_ctl->xacc_real                    =   0;                                                              // real accelerate  command | unit[pulse/s/s]

    m_ctl->flag.all                     =   0;

    m_ctl->pcmd_in                      =   0;
    m_ctl->pcmd_out                     =   0;

    m_ctl->spd_cmd_in                   =   0;                                                              // input of speed command
    m_ctl->spd_cmd_out                  =   0;                                                              // output o speed command

    m_ctl->recip_cnt                    =   0;                                                              // reciprocating motion count value
    m_ctl->motion_cnt                   =   0;                                                              // motion times count value
    m_ctl->recip_state                  =   INIT_MOTION_STAGE_RMS;                                          // reciprocating motion state
//**************************************************************************************************************************
    return  TRUE;
}



int16	KpiInitPosTrajProdVar(POS_TRAJ * m_ctl)
{
 //  variable initialization
    m_ctl->ptraj_set                    =   0;                                                              // position command set value
    m_ctl->ptraj_in                     =   0;                                                              // position command input value
    m_ctl->ptraj_out                    =   0;                                                              // position command output value

    m_ctl->xq0                          =   0;                                                              // initialize position | unit[pulse]
    m_ctl->xq1                          =   0;                                                              // finish position | unit [pulse]
    m_ctl->xq_real                      =   0;                                                              // real position | unit [pulse]
    m_ctl->xqh                          =   0;                                                              // increment position between q0 to q1

    m_ctl->x_v0                         =   0;                                                              // initialize velocity | unit[pulse/s]
    m_ctl->x_v1                         =   0;                                                              // the max velocity can be reached | unit[pulse/s]
    m_ctl->x_vpeak                      =   0;                                                              // the peak velocity for tajectory produce | unit[pulse/s]
    m_ctl->x_vpabs                      =   0;                                                              // the absolute peak velocity for tajectory produce | unit[pulse/s]
    m_ctl->xv_real                      =   0;                                                              // real velocity command

    m_ctl->acc_max_real                 =   0;                                                              // absolute maximum accelerate of trajectory | unit[pulse/s/s]

    m_ctl->t0                           =   0;                                                              // initialize time | unit[s]
    m_ctl->treal                        =   0;                                                              // current time | unit[s]
    m_ctl->x_tacc                       =   0;                                                              // total accrate time | unit[s]
    m_ctl->x_tdec                       =   0;                                                              // total decelerate time | unit[s]
    m_ctl->x_ttotal                     =   0;                                                              // total time | unit[s]
    m_ctl->xacc_real                    =   0;                                                              // real accelerate  command | unit[pulse/s/s]

    m_ctl->flag.all                     =   0;

    m_ctl->pcmd_in                      =   0;
    m_ctl->pcmd_out                     =   0;

    m_ctl->spd_cmd_in                   =   0;                                                              // input of speed command
    m_ctl->spd_cmd_out                  =   0;                                                              // output o speed command

    m_ctl->recip_cnt                    =   0;                                                              // reciprocating motion count value
    m_ctl->motion_cnt                   =   0;                                                              // motion times count value
    m_ctl->recip_state                  =   INIT_MOTION_STAGE_RMS;                                          // reciprocating motion state
//**************************************************************************************************************************
    return  TRUE;
}




int16	KpiPosTrajProd(POS_TRAJ * m_ctl, int64 * pset_in, int64 * pcmd_out)
{
    double dtmp, dtmp2;
//**************************************************************************************************************************
    m_ctl->ptraj_set                    =   *pset_in;

    if (m_ctl->ptraj_in != m_ctl->ptraj_set)
    {
        m_ctl->ptraj_in                     =   m_ctl->ptraj_set;
        m_ctl->xq0                          =   m_ctl->xq_real;
        m_ctl->xq1                          =   m_ctl->ptraj_in;
        m_ctl->t0                           =   0;
        m_ctl->treal                        =   0;

        m_ctl->x_v0                         =   m_ctl->xv_real;
        m_ctl->x_v1                         =   0;

        m_ctl->flag.bit.ENDF                =   FALSE;
//**************************************************************************************************************************
        m_ctl->xqh                          =   IQAbsCal(m_ctl->xq1 - m_ctl->xq0);

        dtmp                                =   m_ctl->xqh * m_ctl->acc_max;
        dtmp2                               =   (m_ctl->vel_max * m_ctl->vel_max) - \
                                                (m_ctl->x_v0 * m_ctl->x_v0 + m_ctl->x_v1 * m_ctl->x_v1)/2;
        if (dtmp > dtmp2)
        {
            m_ctl->x_vpabs                  =   m_ctl->vel_max;
        }
        else
        {
            m_ctl->x_vpabs                  =   sqrt(dtmp + (m_ctl->x_v0 * m_ctl->x_v0 + m_ctl->x_v1 * m_ctl->x_v1)/2);
        }

        if (m_ctl->xq0 > m_ctl->xq1)
        {
            m_ctl->x_vpeak                  =   -m_ctl->x_vpabs;
            m_ctl->acc_max_real             =   -m_ctl->acc_max;
        }
        else
        {
            m_ctl->x_vpeak                  =   m_ctl->x_vpabs;
            m_ctl->acc_max_real             =   m_ctl->acc_max;
        }

        if (m_ctl->x_vpabs == m_ctl->vel_max)
        {
            m_ctl->x_tacc                   =   IQAbsCal((m_ctl->x_vpeak - m_ctl->x_v0)/m_ctl->acc_max_real);
            m_ctl->x_tdec                   =   IQAbsCal((m_ctl->x_vpeak - m_ctl->x_v1)/m_ctl->acc_max_real);
            m_ctl->x_ttotal                 =   IQAbsCal(m_ctl->xqh/m_ctl->x_vpeak) + \
                                                (m_ctl->x_vpabs/(2.0*m_ctl->acc_max))*((1 - m_ctl->x_v0/m_ctl->x_vpeak)*(1 - m_ctl->x_v0/m_ctl->x_vpeak)) +\
                                                (m_ctl->x_vpabs/(2.0*m_ctl->acc_max))*((1 - m_ctl->x_v1/m_ctl->x_vpeak)*(1 - m_ctl->x_v1/m_ctl->x_vpeak));
        }
        else
        {
            m_ctl->x_tacc                   =   IQAbsCal((m_ctl->x_vpeak - m_ctl->x_v0)/m_ctl->acc_max_real);
            m_ctl->x_tdec                   =   IQAbsCal((m_ctl->x_vpeak - m_ctl->x_v1)/m_ctl->acc_max_real);
            m_ctl->x_ttotal                 =   m_ctl->x_tacc + m_ctl->x_tdec;
        }
//**************************************************************************************************************************
    }
//**************************************************************************************************************************
    if (m_ctl->treal < m_ctl->x_ttotal)
    {
        if (m_ctl->x_vpabs != m_ctl->vel_max)
        {
            if (m_ctl->treal < m_ctl->x_tacc)
            {
                m_ctl->xq_real          =   m_ctl->xq0  + m_ctl->x_v0*(m_ctl->treal - m_ctl->t0) + \
                                            ((m_ctl->x_vpeak-m_ctl->x_v0)/(2.0*m_ctl->x_tacc))*((m_ctl->treal - m_ctl->t0)*(m_ctl->treal - m_ctl->t0));

                m_ctl->xv_real          =   m_ctl->x_v0 + ((m_ctl->x_vpeak-m_ctl->x_v0)/(m_ctl->x_tacc)) * (m_ctl->treal - m_ctl->t0);

                m_ctl->xacc_real        =   m_ctl->acc_max_real;
            }
            else
            {
                m_ctl->xq_real          =   m_ctl->xq1  - m_ctl->x_v1*(m_ctl->x_ttotal - m_ctl->treal) - \
                                            ((m_ctl->x_vpeak-m_ctl->x_v1)/(2.0*m_ctl->x_tdec))*((m_ctl->x_ttotal - m_ctl->treal)*(m_ctl->x_ttotal - m_ctl->treal));

                m_ctl->xv_real          =   m_ctl->x_v1 + ((m_ctl->x_vpeak-m_ctl->x_v1)/(m_ctl->x_tdec)) * (m_ctl->x_ttotal - m_ctl->treal);

                m_ctl->xacc_real        =   -m_ctl->acc_max_real;
            }
        }
        else
        {
            if (m_ctl->treal < m_ctl->x_tacc)
            {
                m_ctl->xq_real          =   m_ctl->xq0  + m_ctl->x_v0*(m_ctl->treal - m_ctl->t0) + \
                                            ((m_ctl->x_vpeak-m_ctl->x_v0)/(2.0*m_ctl->x_tacc))*((m_ctl->treal - m_ctl->t0)*(m_ctl->treal - m_ctl->t0));

                m_ctl->xv_real          =   m_ctl->x_v0 + ((m_ctl->x_vpeak-m_ctl->x_v0)/(m_ctl->x_tacc)) * (m_ctl->treal - m_ctl->t0);

                m_ctl->xacc_real        =   m_ctl->acc_max_real;
            }
            else if (m_ctl->treal < (m_ctl->x_ttotal - m_ctl->x_tdec))
            {
                m_ctl->xq_real          =   m_ctl->xq0 + m_ctl->x_v0 *(m_ctl->x_tacc/2.0) + m_ctl->x_vpeak * (m_ctl->treal - m_ctl->t0 - (m_ctl->x_tacc/2.0));

                m_ctl->xv_real          =   m_ctl->x_vpeak;

                m_ctl->xacc_real        =   0;
            }
            else
            {
                m_ctl->xq_real          =   m_ctl->xq1  - m_ctl->x_v1*(m_ctl->x_ttotal - m_ctl->treal) - \
                                            ((m_ctl->x_vpeak-m_ctl->x_v1)/(2.0*m_ctl->x_tdec))*((m_ctl->x_ttotal - m_ctl->treal)*(m_ctl->x_ttotal - m_ctl->treal));

                m_ctl->xv_real          =   m_ctl->x_v1 + ((m_ctl->x_vpeak-m_ctl->x_v1)/(m_ctl->x_tdec)) * (m_ctl->x_ttotal - m_ctl->treal);

                m_ctl->xacc_real        =   -m_ctl->acc_max_real;
            }
        }

        m_ctl->treal                        =   m_ctl->treal + (double)(m_ctl->prm.ts)/1000000000.0;
    }
    else
    {
        m_ctl->xq_real                  =   m_ctl->xq1;
        m_ctl->xv_real                  =   0;
        m_ctl->xacc_real                =   0;
        m_ctl->flag.bit.ENDF            =   TRUE;
    }

//**************************************************************************************************************************
    m_ctl->ptraj_out                    =   m_ctl->xq_real;
    *pcmd_out                           =   m_ctl->ptraj_out;
//**************************************************************************************************************************
    return  TRUE;
}



int16   KpiRecipMotionTrajProd(POS_TRAJ * m_ctl, int16 * en_opra, int64 * pset_in, int64 * pcmd_out)
{
    m_ctl->pcmd_in                  =   *pset_in;
//**************************************************************************************************************************
    if ((*en_opra) == TRUE)
    {
        switch (m_ctl->recip_state)
        {
            case    INIT_MOTION_STAGE_RMS:
            {
                m_ctl->recip_cnt++;
                if (m_ctl->recip_cnt >= m_ctl->prm.interv_tim)
                {
                    m_ctl->recip_cnt            =   0;
                    m_ctl->motion_cnt           =   0;
                    m_ctl->recip_state          =   POS_MOTION_STAGE_RMS;
                }
                m_ctl->pcmd_out             =   0;
                break;
            }
            case    POS_MOTION_STAGE_RMS:
            {
                m_ctl->pcmd_out                 =   m_ctl->pcmd_in;
                m_ctl->recip_state              =   WAITN_MOTION_STAGE_RMS;
                break;
            }
            case    WAITN_MOTION_STAGE_RMS:
            {
                if (m_ctl->flag.bit.ENDF == TRUE)
                {
                    m_ctl->recip_cnt++;
                    if (m_ctl->recip_cnt >= m_ctl->prm.interv_tim)
                    {
                        m_ctl->recip_state          =   NEG_MOTION_STATE_RMS;
                        m_ctl->recip_cnt            =   0;
                    }
                }
                m_ctl->pcmd_out                 =   m_ctl->pcmd_in;
                break;
            }
            case    NEG_MOTION_STATE_RMS:
            {
                m_ctl->pcmd_out                 =   0;
                m_ctl->recip_state              =   WAITP_MOTION_STAGE_RMS;
                break;
            }
            case    WAITP_MOTION_STAGE_RMS:
            {
                if (m_ctl->flag.bit.ENDF == TRUE)
                {
                    m_ctl->recip_cnt++;

                    if (m_ctl->recip_cnt >= m_ctl->prm.interv_tim)
                    {
                        m_ctl->motion_cnt++;

                        if (m_ctl->motion_cnt >= m_ctl->prm.recip_num)
                        {
                            m_ctl->motion_cnt           =   0;
                            m_ctl->recip_state          =   END_MOTION_STAGE_RMS;
                        }
                        else
                        {
                            m_ctl->recip_state          =   POS_MOTION_STAGE_RMS;
                        }
                        m_ctl->recip_cnt            =   0;
                    }
                }
                m_ctl->pcmd_out                 =   0;
                break;
            }
            case    END_MOTION_STAGE_RMS:
            {
                m_ctl->pcmd_out                 =   0;
                break;
            }
            default:
            {
                m_ctl->recip_state              =   INIT_MOTION_STAGE_RMS;
                m_ctl->pcmd_out                 =   0;
                break;
            }
        }
    }
    else
    {
        m_ctl->pcmd_out             =   0;
        m_ctl->recip_state          =   INIT_MOTION_STAGE_RMS;
        m_ctl->recip_cnt            =   0;
    }
//**************************************************************************************************************************
    KpiPosTrajProd(m_ctl, &m_ctl->pcmd_out, pcmd_out);
//**************************************************************************************************************************
    return  TRUE;
}



int16   KpiStepCmdRecipMotion(POS_TRAJ * m_ctl, int16 * en_opra, double * cmd_in, double * cmd_out)
{
//**************************************************************************************************************************
    m_ctl->spd_cmd_in           =   *cmd_in;

    if (*en_opra == TRUE)
    {
        switch (m_ctl->recip_state)
        {
            case    INIT_MOTION_STAGE_RMS:
            {
                m_ctl->recip_cnt++;
                if (m_ctl->recip_cnt >= m_ctl->prm.interv_tim)
                {
                    m_ctl->recip_cnt            =   0;
                    m_ctl->motion_cnt           =   0;
                    m_ctl->recip_state          =   POS_MOTION_STAGE_RMS;
                }
                m_ctl->spd_cmd_out              =   0;
                break;
            }
            case    POS_MOTION_STAGE_RMS:
            {
                m_ctl->recip_cnt++;
                if (m_ctl->recip_cnt >= m_ctl->prm.spdr_hold_tim)
                {
                    m_ctl->recip_cnt            =   0;
                    m_ctl->spd_cmd_out          =   0;
                    m_ctl->recip_state          =   WAITN_MOTION_STAGE_RMS;
                }
                else
                {
                    m_ctl->spd_cmd_out          =   m_ctl->spd_cmd_in;
                }

                break;
            }
            case    WAITN_MOTION_STAGE_RMS:
            {
                m_ctl->recip_cnt++;
                if (m_ctl->recip_cnt >= m_ctl->prm.interv_tim)
                {
                    m_ctl->recip_state          =   NEG_MOTION_STATE_RMS;
                    m_ctl->recip_cnt            =   0;
                    m_ctl->spd_cmd_out          =   -m_ctl->spd_cmd_in;
                }
                else
                {
                    m_ctl->spd_cmd_out          =   0;
                }

                break;
            }
            case    NEG_MOTION_STATE_RMS:
            {
                m_ctl->recip_cnt++;
                if (m_ctl->recip_cnt >= m_ctl->prm.spdr_hold_tim)
                {
                    m_ctl->recip_cnt            =   0;
                    m_ctl->spd_cmd_out          =   0;
                    m_ctl->recip_state          =   WAITP_MOTION_STAGE_RMS;
                }
                else
                {
                    m_ctl->spd_cmd_out          =   -m_ctl->spd_cmd_in;
                }
                break;
            }
            case    WAITP_MOTION_STAGE_RMS:
            {
                m_ctl->recip_cnt++;

                if (m_ctl->recip_cnt >= m_ctl->prm.interv_tim)
                {
                    m_ctl->motion_cnt++;

                    if (m_ctl->motion_cnt >= m_ctl->prm.recip_num)
                    {
                        m_ctl->motion_cnt           =   0;
                        m_ctl->recip_state          =   END_MOTION_STAGE_RMS;
                    }
                    else
                    {
                        m_ctl->recip_state          =   POS_MOTION_STAGE_RMS;
                    }

                    m_ctl->recip_cnt            =   0;
                }
                else
                {
                    m_ctl->spd_cmd_out          =   0;
                }
                break;
            }
            case    END_MOTION_STAGE_RMS:
            {
                m_ctl->spd_cmd_out          =   0;
                break;
            }
            default:
            {
                m_ctl->recip_state              =   INIT_MOTION_STAGE_RMS;
                m_ctl->spd_cmd_out              =   0;
                m_ctl->recip_cnt                =   0;
                break;
            }
        }
    }
    else
    {
        m_ctl->spd_cmd_out          =   0;
        m_ctl->recip_state          =   INIT_MOTION_STAGE_RMS;
        m_ctl->recip_cnt            =   0;
        m_ctl->motion_cnt           =   0;
    }

    *cmd_out                   =   m_ctl->spd_cmd_out;
//**************************************************************************************************************************
    return  TRUE;
}

