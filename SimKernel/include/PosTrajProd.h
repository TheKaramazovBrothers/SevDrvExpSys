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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EXCITATION STATE STRUCT DEFINE
typedef	enum
{
    INIT_MOTION_STAGE_RMS			=	0,                                                          // initialization stage of reciprocating motion trajectory produce function
    POS_MOTION_STAGE_RMS			=	1,                                                          // position direction motion stage of reciprocating motion trajectory produce function
    WAITN_MOTION_STAGE_RMS          =   2,                                                          // wait for negative motion stage of reciprocating motion trajectory produce function
    NEG_MOTION_STATE_RMS            =   3,                                                          // negative direction motion stage of reciprocating motion trajectory produce function
    WAITP_MOTION_STAGE_RMS          =   4,                                                          // wait for positive motion stage of reciprocating motion trajectory produce function
    END_MOTION_STAGE_RMS            =   5,                                                          // end state of reciprocating motion trajectory produce function
    REV_MOTION_STAGE_RMS            =	0x8000
}tRecipMotionState;


//#############################################################################################################################
typedef struct	pos_traj_cfg_opt_bits
{
    Uint32		NEST            : 1;                                                                // point position trajectory nest mask bit | 1/mask
    Uint32		rsvd            : 31;                                                               // reserved
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

    Uint32              recip_num;                                                          // reciprocating motion times
    Uint32              interv_tim;                                                         // interval time between motion | unit[scan]
    Uint32              spdr_hold_tim;                                                      // speed command hold time in reciprocate motion | unit[scan]
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
    int64               pcmd_in;                                                            // position command input for reciprocating motion trajectory produce
    int64               pcmd_out;                                                           // position command output for reciprocating motion trajectory produce

    double              spd_cmd_in;                                                         // input of speed command
    double              spd_cmd_out;                                                        // output o speed command

    int32               recip_cnt;                                                          // reciprocating motion count value
    int32               motion_cnt;                                                         // motion times count value
    tRecipMotionState   recip_state;                                                        // reciprocating motion state
//#############################################################################################################################
}POS_TRAJ;


//#############################################################################################################################
// function declare
int16	KpiInitPosTrajProdModule(POS_TRAJ * m_ctl);                                          // Initialize the position trajectory produce module
int16	KpiInitPosTrajProdVar(POS_TRAJ * m_ctl);                                             // initialize the position trajectory produce variable
int16	KpiPosTrajProd(POS_TRAJ * m_ctl, int64 * pset_in, int64 * pcmd_out);                 // position trajectory produce function

int16   KpiRecipMotionTrajProd(POS_TRAJ * m_ctl, int16 * en_opra, \
                               int64 * pset_in, int64 * pcmd_out);                           // reciprocating motion trajectory produce function

int16   KpiStepCmdRecipMotion(POS_TRAJ * m_ctl, int16 * en_opra, \
                          double * cmd_in, double * cmd_out);                               // reciprocating motion in velocity mode




#endif


///////////////////////////////////////////////////////// no more ////////////////////////////////////////////////////////////
