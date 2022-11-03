//=========================================================================================================
// project		:	servo system velocity control loop realization
// File			:	VelCtlLoop.cpp
// discription	:	use in servo system velocity control loop realization
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g
// date			:	2022/08/26
// copyright(C)	:	liu.g	(2022-2032)
//=========================================================================================================
#include "Cia402AppEmu.h"
#include "SevCtlPrmTblDef.h"
#include <cmath>

#include "VelCtlLoop.h"



//*********************************************************************************************************
//*                                   VELOCITY CONTROL MODULE INITIALIZATION
//*
//* Description: This function is used to initialize velocity control loop module in servo system
//*
//*
//* Arguments  : m_ctl		is a pointer to servo system velocity control object
//*
//* Returns    : -1/initialize Failure, else/success
//*********************************************************************************************************
int16	KpiInitVelLoopModule(VEL_CTL * m_ctl)
{
    double  imax_tmp, phim_tmp, jm_tmp, jrat_tmp, jall_tmp, tmax_tmp;
    double  nos_tmp, dtmp;
    double  zeta1, zeta2, wn, wc, b0, b1, b2, c0, h;
    int32   ltmp, ltmp2;
//**************************************************************************************************************************
    if (SEV_PRM_FROM_EX_MEM_EN == DISABLE)
    {
        imax_tmp                    =   10.0;
        phim_tmp                    =   197.0;
        jm_tmp                      =   44;
        jrat_tmp                    =   540;
        nos_tmp                     =   6000;

        m_ctl->prm.fnv_fst          =   1000;
        m_ctl->prm.tiv_fst          =   1000;
        m_ctl->prm.fnv_sec          =   1000;
        m_ctl->prm.tiv_sec          =   1000;

        m_ctl->prm.abs_rat          =   4096;
        m_ctl->prm.pos_rat          =   4096;
        m_ctl->prm.neg_rat          =   4096;

        m_ctl->prm.ts               =   62500;

        m_ctl->prm.tf_rmp           =   2000;
        m_ctl->prm.cfg_opt.all      =   0;
//**************************************************************************************************************************
        m_ctl->prm.fn_lpf0_tqr      =   4000;
        m_ctl->prm.fn_lpf1_tqr      =   8000;

        m_ctl->prm.fn_nch0_tqr      =   3000;
        m_ctl->prm.qx_nch0_tqr      =   500;
        m_ctl->prm.kx_nch0_tqr      =   500;

        m_ctl->prm.fn_nch1_tqr      =   6000;
        m_ctl->prm.qx_nch1_tqr      =   500;
        m_ctl->prm.kx_nch1_tqr      =   500;
//**************************************************************************************************************************
    }
    else
    {
//**************************************************************************************************************************
        CpiReadRamPrmByDicInx(IMAX_MOT_PRM_ID32_OBJW_2007H, &imax_tmp);
        CpiReadRamPrmByDicInx(PHIM_MOT_PRM_ID32_OBJW_200BH, &phim_tmp);
        CpiReadRamPrmByDicInx(JM_MOT_PRM_ID32_OBJW_200FH, &jm_tmp);
        CpiReadRamPrmByDicInx(JRAT_MOT_PRM_ID16_OBJW_2002H, &jrat_tmp);
        CpiReadRamPrmByDicInx(NOS_MOT_PRM_ID32_OBJW_2009H, &nos_tmp);
//**************************************************************************************************************************
    }
//**************************************************************************************************************************
    m_ctl->kti                  =   phim_tmp/698.129;
    jall_tmp                    =   (jm_tmp + (jm_tmp * (jrat_tmp / 100.0)))/1000000.0;
    tmax_tmp                    =   m_ctl->kti * (imax_tmp/1000.0);
//**************************************************************************************************************************
    m_ctl->kv_fst               =   (PI2_CIRCULAR_CONSTANT * ((double)(m_ctl->prm.fnv_fst)/10.0)) * jall_tmp;
    m_ctl->kv_sec               =   (PI2_CIRCULAR_CONSTANT * ((double)(m_ctl->prm.fnv_sec)/10.0)) * jall_tmp;

    if (m_ctl->prm.tiv_fst == 0)
    {
        m_ctl->ki_fst           =   0;
    }
    else
    {
        m_ctl->ki_fst               =   m_ctl->kv_fst * ((double)(m_ctl->prm.ts)/((double)(10000.0) * (double)(m_ctl->prm.tiv_fst)));
    }

    if (m_ctl->prm.tiv_sec == 0)
    {
        m_ctl->ki_sec           =   0;
    }
    else
    {
        m_ctl->ki_sec               =   m_ctl->kv_sec * ((double)(m_ctl->prm.ts)/((double)(10000.0) * (double)(m_ctl->prm.tiv_sec)));
    }
//**************************************************************************************************************************
    ltmp						=	(int32)(m_ctl->prm.abs_rat) * (int32)(m_ctl->prm.pos_rat);				// Q24 = Q12 * Q12
    ltmp2						=	-((int32)(m_ctl->prm.abs_rat) * (int32)(m_ctl->prm.neg_rat));			// Q24 = Q12 * Q12

    m_ctl->vo_ulim              =	tmax_tmp * ((double)(ltmp)/16777216.0);
    m_ctl->vo_llim              =	tmax_tmp * ((double)(ltmp2)/16777216.0);

    m_ctl->vi_ulim              =	m_ctl->vo_ulim;
    m_ctl->vi_llim              =	m_ctl->vo_llim;
//**************************************************************************************************************************
    m_ctl->delt_rmp             =   ((nos_tmp/60.0)*PI2_CIRCULAR_CONSTANT)/(((double)(m_ctl->prm.tf_rmp) * 1000000.0)/(double)(m_ctl->prm.ts));
//**************************************************************************************************************************
    dtmp                        =   1000000000.0/(PI2_CIRCULAR_CONSTANT*(m_ctl->prm.fn_lpf0_tqr/10.0));
    m_ctl->kf_lpf0_tqr          =   m_ctl->prm.ts/(m_ctl->prm.ts + dtmp);

    dtmp                        =   1000000000.0/(PI2_CIRCULAR_CONSTANT*(m_ctl->prm.fn_lpf1_tqr/10.0));
    m_ctl->kf_lpf1_tqr          =   m_ctl->prm.ts/(m_ctl->prm.ts + dtmp);
//**************************************************************************************************************************
    wn                          =   PI2_CIRCULAR_CONSTANT * (m_ctl->prm.fn_nch0_tqr/10.0);
    dtmp                        =   m_ctl->prm.ts/1000000000.0;

    wc                          =   (2.0/dtmp)*tan((wn*dtmp)/2.0);
    zeta2                       =   m_ctl->prm.qx_nch0_tqr/1000.0;
    zeta1                       =   zeta2 * (m_ctl->prm.kx_nch0_tqr/1000.0);
    h                           =   2.0/dtmp;

    c0                          =   2.0*(zeta2 - zeta1)*wc*h;
    b0                          =   h*h + 2.0*zeta2*wc*h + wc*wc;
    b1                          =   2.0*(h*h-wc*wc);
    b2                          =   h*h - 2.0*zeta2*wc*h + wc*wc;

    m_ctl->kf_nch0_tqr[0]       =   b1/b0;
    m_ctl->kf_nch0_tqr[1]       =   b2/b0;
    m_ctl->kf_nch0_tqr[2]       =   c0/b0;
//**************************************************************************************************************************
    wn                          =   PI2_CIRCULAR_CONSTANT * (m_ctl->prm.fn_nch1_tqr/10.0);
    dtmp                        =   m_ctl->prm.ts/1000000000.0;

    wc                          =   (2.0/dtmp)*tan((wn*dtmp)/2.0);
    zeta2                       =   m_ctl->prm.qx_nch1_tqr/1000.0;
    zeta1                       =   zeta2 * (m_ctl->prm.kx_nch1_tqr/1000.0);
    h                           =   2.0/dtmp;

    c0                          =   2.0*(zeta2 - zeta1)*wc*h;
    b0                          =   h*h + 2.0*zeta2*wc*h + wc*wc;
    b1                          =   2.0*(h*h-wc*wc);
    b2                          =   h*h - 2.0*zeta2*wc*h + wc*wc;

    m_ctl->kf_nch1_tqr[0]       =   b1/b0;
    m_ctl->kf_nch1_tqr[1]       =   b2/b0;
    m_ctl->kf_nch1_tqr[2]       =   c0/b0;
//**************************************************************************************************************************
    m_ctl->spd_fb               =   0;                                                                      // motor speed feedback | unit[rad/s]
    m_ctl->spd_ref              =   0;                                                                      // motor speed reference | unit[rad/s]
    m_ctl->spd_err              =   0;                                                                      // speed control error | unit[rad/s]

    m_ctl->xwkp                 =   0;                                                                      // proportional accumulation value
    m_ctl->xwki                 =   0;                                                                      // intergral accumulation value
    m_ctl->tqr                  =   0;                                                                      // torque command output | unit[Nm]
    m_ctl->iqr                  =   0;                                                                      // q axis current command output | unit[A]
//**************************************************************************************************************************
    m_ctl->velr_ramp_in         =   0;                                                                      // ramp input of velocity command
    m_ctl->velr_ramp_out        =   0;                                                                      // ramp output of velociity command
//**************************************************************************************************************************
    m_ctl->iqr_lpf0             =   0;
    m_ctl->iqr_lpf1             =   0;
    m_ctl->iqr_nch0             =   0;
    m_ctl->iqr_nch1             =   0;

    m_ctl->x_nch0[0]            =   0;
    m_ctl->x_nch0[1]            =   0;
    m_ctl->x_nch0[2]            =   0;

    m_ctl->x_nch1[0]            =   0;
    m_ctl->x_nch1[1]            =   0;
    m_ctl->x_nch1[2]            =   0;
//**************************************************************************************************************************
    return  TRUE;
}


//*********************************************************************************************************
//*                                VELOCITY CONTROL VARIABLE INITIALIZATION
//*
//* Description: This function is used to initialize  velocity control loop variable in servo system
//*
//*
//* Arguments  : m_ctl		is a pointer to servo system velocity control object
//*
//* Returns    : -1/initialize Failure, else/success
//*********************************************************************************************************
int16	KpiInitVelLoopVar(VEL_CTL * m_ctl)
{
//**************************************************************************************************************************
    m_ctl->spd_fb               =   0;                                                                      // motor speed feedback | unit[rad/s]
    m_ctl->spd_ref              =   0;                                                                      // motor speed reference | unit[rad/s]
    m_ctl->spd_err              =   0;                                                                      // speed control error | unit[rad/s]

    m_ctl->xwkp                 =   0;                                                                      // proportional accumulation value
    m_ctl->xwki                 =   0;                                                                      // intergral accumulation value
    m_ctl->tqr                  =   0;                                                                      // torque command output | unit[Nm]
    m_ctl->iqr                  =   0;                                                                      // q axis current command output | unit[A]
//**************************************************************************************************************************
    m_ctl->velr_ramp_in         =   0;                                                                      // ramp input of velocity command
    m_ctl->velr_ramp_out        =   0;                                                                      // ramp output of velociity command
//**************************************************************************************************************************
    m_ctl->iqr_lpf0             =   0;
    m_ctl->iqr_lpf1             =   0;
    m_ctl->iqr_nch0             =   0;
    m_ctl->iqr_nch1             =   0;

    m_ctl->x_nch0[0]            =   0;
    m_ctl->x_nch0[1]            =   0;
    m_ctl->x_nch0[2]            =   0;

    m_ctl->x_nch1[0]            =   0;
    m_ctl->x_nch1[1]            =   0;
    m_ctl->x_nch1[2]            =   0;
//**************************************************************************************************************************
    return  TRUE;
}



//*********************************************************************************************************
//*                                VELOCITY PI CONTROLER DESIGN
//*
//* Description: This function is used to do  velocity PI control
//*
//*
//* Arguments  : m_ctl		is a pointer to servo system velocity control object
//*
//* Returns    : -1/Failure, else/success
//*********************************************************************************************************
int16	KpiVelCloseLoopCtrl(VEL_CTL * m_ctl, double * m_spdr, double * m_spdf, double *m_tqrp)
{
    double  dtmp, ulim, llim;
//**************************************************************************************************************************
    m_ctl->velr_ramp_in             =   *m_spdr;

    if (m_ctl->prm.cfg_opt.bit.RAMP == FALSE)
    {
        ulim                            =   m_ctl->velr_ramp_out + m_ctl->delt_rmp;
        llim                            =   m_ctl->velr_ramp_out - m_ctl->delt_rmp;
        m_ctl->velr_ramp_out            =   IQSatLimit(m_ctl->velr_ramp_in, ulim, llim);
    }
    else
    {
        m_ctl->velr_ramp_out            =   m_ctl->velr_ramp_in;
    }
//**************************************************************************************************************************
    m_ctl->spd_ref              =   m_ctl->velr_ramp_out;

    if (m_ctl->prm.cfg_opt.bit.OPENLOOP == TRUE)
    {
        m_ctl->spd_fb               =   0;
    }
    else
    {
        m_ctl->spd_fb               =   *m_spdf;
    }

    m_ctl->spd_err              =   m_ctl->spd_ref - m_ctl->spd_fb;

    dtmp                        =   m_ctl->xwki + m_ctl->ki_fst * m_ctl->spd_err;
    m_ctl->xwki                 =   IQSatLimit(dtmp, m_ctl->vi_ulim, m_ctl->vi_llim);

    dtmp                        =   m_ctl->kv_fst * m_ctl->spd_err + m_ctl->xwki;
    m_ctl->xwkp                 =   IQSatLimit(dtmp, m_ctl->vo_ulim, m_ctl->vo_llim);

    m_ctl->tqr                  =   m_ctl->xwkp + (*m_tqrp);

    dtmp                        =   m_ctl->tqr/m_ctl->kti;

    KpiVctlOutTqrFit(m_ctl, &dtmp, &m_ctl->iqr);
//**************************************************************************************************************************
    return  TRUE;
}


int16   KpiVctlOutTqrFit(VEL_CTL * m_ctl, double * iqr_in, double * iqr_our)
{
//**************************************************************************************************************************
    if (m_ctl->prm.cfg_opt.bit.LPF0_TRF == TRUE)
    {
        m_ctl->iqr_lpf0                 =   m_ctl->iqr_lpf0 + ((*iqr_in) - m_ctl->iqr_lpf0) * m_ctl->kf_lpf0_tqr;
    }
    else
    {
        m_ctl->iqr_lpf0                 =   *iqr_in;
    }
//**************************************************************************************************************************
    if (m_ctl->prm.cfg_opt.bit.LPF1_TRF == TRUE)
    {
        m_ctl->iqr_lpf1                 =   m_ctl->iqr_lpf1 + (m_ctl->iqr_lpf0 - m_ctl->iqr_lpf1) * m_ctl->kf_lpf1_tqr;
    }
    else
    {
        m_ctl->iqr_lpf1                 =   m_ctl->iqr_lpf0;
    }
//**************************************************************************************************************************
    if (m_ctl->prm.cfg_opt.bit.NCH0_TRF == TRUE)
    {
        m_ctl->x_nch0[0]                =   m_ctl->x_nch0[1] * m_ctl->kf_nch0_tqr[0] - m_ctl->x_nch0[2]*m_ctl->kf_nch0_tqr[1] + m_ctl->iqr_lpf1*m_ctl->kf_nch0_tqr[2];

        m_ctl->iqr_nch0                 =   m_ctl->iqr_lpf1 - m_ctl->x_nch0[0] + m_ctl->x_nch0[2];

        m_ctl->x_nch0[2]                =   m_ctl->x_nch0[1];
        m_ctl->x_nch0[1]                =   m_ctl->x_nch0[0];
    }
    else
    {
        m_ctl->iqr_nch0              =   m_ctl->iqr_lpf1;
    }
//**************************************************************************************************************************
    if (m_ctl->prm.cfg_opt.bit.NCH1_TRF == TRUE)
    {
        m_ctl->x_nch1[0]                =   m_ctl->x_nch1[1] * m_ctl->kf_nch1_tqr[0] - m_ctl->x_nch1[2]*m_ctl->kf_nch1_tqr[1] + m_ctl->iqr_nch0*m_ctl->kf_nch1_tqr[2];

        m_ctl->iqr_nch1                 =   m_ctl->iqr_nch0 - m_ctl->x_nch1[0] + m_ctl->x_nch1[2];

        m_ctl->x_nch1[2]                =   m_ctl->x_nch1[1];
        m_ctl->x_nch1[1]                =   m_ctl->x_nch1[0];
    }
    else
    {
        m_ctl->iqr_nch1                 =   m_ctl->iqr_nch0;
    }
//**************************************************************************************************************************
    *iqr_our                        =   m_ctl->iqr_nch1;
//**************************************************************************************************************************
    return  TRUE;
}
