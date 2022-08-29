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


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
typedef struct	vel_cfg_opt_bits
{
    Uint32		RAMP		: 1;                                                        // servo enable instruction bit
    Uint32		res         : 31;                                                       // reserved
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
// velocity command filter parameter define
    double      delt_rmp;                                                               // delta ramp value of velocity command
    double      velr_ramp_in;                                                           // ramp input variable of velocity reference
    double      velr_ramp_out;                                                          // ramp output variable of velocity reference
// velocity command filter variable define
//**************************************************************************************************************************
}VEL_CTL;



// function declare
int16	KpiInitVelLoopModule(VEL_CTL * m_ctl);                                          // Initialize the parameter of velocity control module
int16	KpiInitVelLoopVar(VEL_CTL * m_ctl);                                             // initialize the velocity control variable
int16	KpiVelCloseLoopCtrl(VEL_CTL * m_ctl, \
                            double * m_spdr,double * m_spdf, double *m_tqrp);           // velocity close loop control function



#endif



///////////////////////////////////////////////////////// no more ////////////////////////////////////////////////////////////
