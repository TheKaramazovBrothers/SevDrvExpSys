//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	velocity control loop design                                //
//	file				:	VelCtlLoop.h                                                //
//	Description			:	use for SERVO system velocity control loop realization   	//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g(1487)		|	2022/08/25	|	liu.g           |		2022 - 2032			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef __VELCTLLOOP_H__
#define __VELCTLLOOP_H__

#include "DspCpu.h"


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
typedef struct	vel_cfg_opt_bits
{
    Uint32		RAMP		: 1;                                                        // velocity command ramp mask bit
    Uint32      LPF0_TRF    : 1;                                                        // the first low pass filter for torque reference
    Uint32      LPF1_TRF    : 1;                                                        // the second low pass filter for torque reference
    Uint32      NCH0_TRF    : 1;                                                        // the first nortch filter for torque reference
    Uint32      NCH1_TRF    : 1;                                                        // the second nortch filter for torque reference

    Uint32      OPENLOOP    : 1;                                                        // velocity feedback openloop
    Uint32		res         : 26;                                                       // reserved
}VEL_CFG_OPT_BITS;


typedef	union
{
    Uint32                      all;
    VEL_CFG_OPT_BITS			bit;
}tVelCtlCfgOpt;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


//-------------------------------------------------------------------------------------
//						VELOCITY CONTROL PARAMETER STRUCT
//-------------------------------------------------------------------------------------
typedef		struct	vel_ctl_prm
{
//#############################################################################################################################
// velocity control module parameter define
    Uint32              fnv_fst;														// velocity loop gain band width | unit[0.1Hz]
    Uint32              tiv_fst;														// velocity loop integral time constant | unit[0.01ms]
    Uint32              fnv_sec;														// the second velocity loop gain bandwidth | unit[0.1Hz]
    Uint32              tiv_sec;														// the second velocity loop integral time constant | unit[0.01ms]
//#############################################################################################################################
    Uint32              ts;																// velocity loop sample times | unit[ns]
//#############################################################################################################################
// torque limit parameter define
    Uint16              abs_rat;														// max torque limit rate | unit[Q12]
    Uint16              pos_rat;														// positive limit rate | unit[Q12]
    Uint16              neg_rat;														// negative limit rate | unit[Q12]
//#############################################################################################################################
    Uint32              tf_rmp;                                                         // ramp time constant of velocity command | unit[ms]
    tVelCtlCfgOpt       cfg_opt;                                                        // velocity control config option
//#############################################################################################################################
    Uint16              fn_lpf0_tqr;                                                    // the fn of the first low pass filter for torque filter | unit[0.1hz]
    Uint16              fn_lpf1_tqr;                                                    // the fn of the second low pass filter for torque filter | unit[0.1hz]

    Uint16              fn_nch0_tqr;                                                    // the fn of the first notch filter for torque filter | unit[0.1hz]
    Uint16              qx_nch0_tqr;                                                    // the width of the first notch filter | unit[0.001]
    Uint16              kx_nch0_tqr;                                                    // the depth of the first notch filter | unit[0.001]

    Uint16              fn_nch1_tqr;                                                    // the fn of the second notch filter for torque filter | unit[0.1hz]
    Uint16              qx_nch1_tqr;                                                    // the width of the second notch filter | unit[0.001]
    Uint16              kx_nch1_tqr;                                                    // the depth of the second notch filter | unit[0.001]
//#############################################################################################################################
}VEL_CTL_PRM;


typedef		struct	vel_ctl
{
// velocity control module parameter define
    VEL_CTL_PRM		prm;
//**************************************************************************************************************************
// velocity control kv & ki parameter
    double		kv_fst;                                                                 // the first velocity loop proportional coefficient
    double		ki_fst;                                                                 // the first velocity loop integral coefficient
    double		kv_sec;                                                                 // the second velocity loop proportional coefficient
    double		ki_sec;                                                                 // the second velocity loop integral coefficient

    double      kti;                                                                    // converse coefficient from motor torque to q axis current
// actual limit parameter
    double		vo_ulim;                                                                // velocity control output upper limit
    double		vo_llim;                                                                // velocity control output lower limit
    double		vi_ulim;                                                                // velocity control integral output upper limit
    double		vi_llim;                                                                // velocity control integral output lower limit
//**************************************************************************************************************************
// velocity control module variable define
    double      spd_fb;                                                                 // motor speed feedback | unit[rad/s]
    double      spd_ref;                                                                // motor speed reference | unit[rad/s]
    double      spd_err;                                                                // speed control error | unit[rad/s]

    double      xwkp;                                                                   // proportional accumulation value
    double      xwki;                                                                   // intergral accumulation value
    double      tqr;                                                                    // torque command output | unit[Nm]
    double      iqr;                                                                    // q axis current command output | unit[A]
//**************************************************************************************************************************
// velocity command ramp variable define
    double      delt_rmp;                                                               // delta ramp value of velocity command
    double      velr_ramp_in;                                                           // ramp input variable of velocity reference
    double      velr_ramp_out;                                                          // ramp output variable of velocity reference
// velocity command filter variable define
//**************************************************************************************************************************
// torque command filter parameter define
    double      kf_lpf0_tqr;                                                            // coefficient of the first low pass filter for torque command
    double      kf_lpf1_tqr;                                                            // coefficient of the second low pass filter for torque command

    double      kf_nch0_tqr[3];                                                         // coefficient of the first notch filter for torque command
    double      kf_nch1_tqr[3];                                                         // coefficient of the second notch filter for torque command
// torque command filter variable define
//**************************************************************************************************************************
    double      iqr_lpf0;                                                               // output of the first low pass filter for iq reference
    double      iqr_lpf1;                                                               // output of the second low pass filter for iq reference
    double      iqr_nch0;                                                               // output of the first notch filter for iq reference
    double      iqr_nch1;                                                               // output of the second notch filter for iq reference

    double      x_nch0[3];                                                              // buffer variable for notch filter
    double      x_nch1[3];                                                              // buffer variable for notch filter
//**************************************************************************************************************************
}VEL_CTL;



// function declare
int16	KpiInitVelLoopModule(VEL_CTL * m_ctl);                                          // Initialize the parameter of velocity control module
int16	KpiInitVelLoopVar(VEL_CTL * m_ctl);                                             // initialize the velocity control variable
int16	KpiVelCloseLoopCtrl(VEL_CTL * m_ctl, \
                            double * m_spdr,double * m_spdf, double *m_tqrp);           // velocity close loop control function

int16   KpiVctlOutTqrFit(VEL_CTL * m_ctl, double * iqr_in, double * iqr_our);           // Velocity close loop output torque filter


#endif



///////////////////////////////////////////////////////// no more ////////////////////////////////////////////////////////////
