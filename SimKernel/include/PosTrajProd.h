//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	position trajectory produce module design                   //
//	file				:	PosTrajProd.h                                               //
//	Description			:	use for SERVO system position trajectory  realization       //
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g(1487)		|	2022/08/31	|	   liu.g        |		2022 - 2032			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __POSTRAJPROD_H__
#define __POSTRAJPROD_H__

#include "DspCpu.h"


//#############################################################################################################################
typedef struct	pos_traj_cfg_opt_bits
{
    Uint32		NEST            : 1;                                                        // point position trajectory nest mask bit | 1/mask
    Uint32		rsvd            : 31;                                                       // reserved
}POS_TRAJ_CFG_OPT_BITS;


typedef	union
{
    Uint32                      all;
    POS_TRAJ_CFG_OPT_BITS       bit;
}tPosTrajCfgOpt;
//#############################################################################################################################


//#############################################################################################################################
typedef struct	pos_traj_flag_bits
{
    Uint32		ENDF            : 1;                                                        // finished flag |1/finished,0/no
    Uint32		rsvd            : 31;                                                       // reserved
}POS_TRAJ_FLAG_BITS;


typedef	union
{
    Uint32                      all;
    POS_TRAJ_FLAG_BITS          bit;
}tPosTrajFlag;
//#############################################################################################################################

//-------------------------------------------------------------------------------------
//					POSITION COMMAND TRAJECTORY PARAMETER STRUCT
//-------------------------------------------------------------------------------------
typedef		struct	pos_traj_prm
{
//#############################################################################################################################
// OBJ parameter define
    Uint32              rot_res;                                                            // rotation resolution | unit[pulse number/circle]
    Uint32              ts;																	// position command maker sample times | unit[ns]

    Uint32              accrate;															// acceleration of position command maker | unit[10000pulse/s/s]
    Uint32              decrate;															// deceleration of position command maker | unit[10000pulse/s/s]
    Uint32              maxspd;																// maximum velocity set for position trajectory maker | unit[RPM]
    tPosTrajCfgOpt      cfg_opt;                                                            // point position trajectory nest mask bit | 1/mask
//#############################################################################################################################
}POS_TRAJ_PRM;



//-------------------------------------------------------------------------------------
//							POSITION COMMAND MAKER
//-------------------------------------------------------------------------------------
typedef		struct	pos_traj
{
//#############################################################################################################################
// parameter define
    POS_TRAJ_PRM		prm;
// trajectory parameter define
    double              vel_max;                                                            // maximum velocity of trajectory | unit[pulse/s]
    double              acc_max;                                                            // maximum accelerate of trajectory | unit[pulse/s/s]
// variable define
//#############################################################################################################################
    int64               ptraj_set;                                                          // position command set value
    int64               ptraj_in;                                                           // position command input value
    int64               ptraj_out;                                                          // position command output value

    double              xq0;                                                                // initialize position | unit[pulse]
    double              xq1;                                                                // finish position | unit [pulse]
    double              xq_real;                                                            // real position | unit [pulse]
    double              xqh;                                                                // increment positon between q0 to q1

    double              x_v0;                                                               // initialize velocity | unit[pulse/s]
    double              x_v1;                                                               // the max velocity can be reached | unit[pulse/s]
    double              x_vpeak;                                                            // the peak velocity for position trajectory produce | unit[pulse/s]
    double              x_vpabs;                                                            // the absolute peak velocity for position trajectory produce | unit[pulse/s]
    double              xv_real;                                                            // real velocity command | unit[pule/s]

    double              t0;                                                                 // initialize time | unit[s]
    double              treal;                                                              // current time | unit[s]
    double              x_tacc;                                                             // total accrate time | unit[s]
    double              x_tdec;                                                             // total decelerate time | unit[s]
    double              x_ttotal;                                                           // total time | unit[s]
    double              xacc_real;                                                          // the real accelerate | unit[pulse/s/s]

    double              acc_max_real;                                                       // real value of maximum accelerate | unit[pulse/s/s]

    tPosTrajFlag        flag;                                                               //  trajectory produce flag
//#############################################################################################################################
}POS_TRAJ;


//#############################################################################################################################
// function declare
int16	KpiInitPosTrajProdModule(POS_TRAJ * m_ctl);                                          // Initialize the parameter of position control module
int16	KpiInitPosTrajProdVar(POS_TRAJ * m_ctl);                                             // initialize the position control variable
int16	KpiPosTrajProd(POS_TRAJ * m_ctl, int64 * pset_in, int64 * pcmd_out);                 // position close loop control function




#endif


///////////////////////////////////////////////////////// no more ////////////////////////////////////////////////////////////
