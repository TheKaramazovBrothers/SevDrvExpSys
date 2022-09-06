//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	position control loop design                                //
//	file				:	PosCtlLoop.h                                                //
//	Description			:	use for SERVO system position control loop realization   	//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g(1487)		|	2022/08/30	|	   liu.g        |		2022 - 2032			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __POSCTLLOOP_H__
#define __POSCTLLOOP_H__

#include "DspCpu.h"

#define		PCMD_MAF_BUF_NUM				16384										// position command move average filter number

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
typedef struct	pos_cfg_opt_bits
{
    Uint32		MAF         : 1;                                                        // moving average filtering mask bit | 1/mask
    Uint32      FFV         : 1;                                                        // velocity feedforward mask  bit | 1/mask
    Uint32      FFT         : 1;                                                        // torque feedforward mask bit | 1/mask
    Uint32      FFJ         : 1;                                                        // jerk feedforward enable | 1/enable,0/disable

    Uint32      LPFFV       : 1;                                                        // low pass filter of velocity feedforward
    Uint32      LPFFT       : 1;                                                        // low pass filter of torque feedforward
    Uint32      LPFFJ       : 1;                                                        // low pass filter of jerk feedforward

    Uint32		res         : 25;                                                       // reserved
}POS_CFG_OPT_BITS;


typedef	union
{
    Uint32                      all;
    POS_CFG_OPT_BITS			bit;
}tPosCtlCfgOpt;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


//-------------------------------------------------------------------------------------
//						POSITION CONTROL PARAMETER STRUCT
//-------------------------------------------------------------------------------------
typedef		struct	pos_ctl_prm
{
//#############################################################################################################################
    Uint32              ts;																// position loop sample times | unit[ns]
    tPosCtlCfgOpt       cfg_opt;                                                        // position control config option
//#############################################################################################################################
// position control module parameter define
    Uint16              fnp_fst;														// position loop gain band width | unit[0.1Hz]
    Uint16              fnp_sec;														// the second position loop gain bandwidth | unit[0.1Hz]
//#############################################################################################################################
// velocity limit parameter define
    Uint16              abs_rat;														// max velocity limit rate | unit[Q12]
    Uint16              pos_rat;														// positive velocity limit rate | unit[Q12]
    Uint16              neg_rat;														// negative velocity limit rate | unit[Q12]
//#############################################################################################################################
    Uint16              maf_num;                                                        // moving average filtering times | unit[scan]
//#############################################################################################################################
    Uint16              ffv_rat;                                                        // velocity feedforward rate | unit[Q12]
    Uint16              fft_rat;                                                        // torque feedforward rate | unit[Q12]
    Uint32              ffj_kg;                                                         // jerk feedforward rate | unit[Q12]
//#############################################################################################################################
}POS_CTL_PRM;



typedef		struct	pos_ctl
{
// position control module parameter define
    POS_CTL_PRM         prm;
//**************************************************************************************************************************
// position control kv & ki parameter
    double              kp_fst;                                                         // the first position loop proportional coefficient
    double              kp_sec;                                                         // the second position loop proportional coefficient
// actual limit parameter
    double              po_ulim;                                                        // position control output upper limit
    double              po_llim;                                                        // position control output lower limit

    double              kg_ffv;                                                         // gain of velocity feedforward
    double              kg_fft;                                                         // gain of torque feedforward

    Uint32              line_num_pctl;                                                  // line number for position control
//**************************************************************************************************************************
// velocity control module variable define
    int64               acc_pos_ref;                                                    // accumulate position command | unit[pulse]
    int64               acc_pos_fb;                                                     // accumulate position feedback | unit[pulse]
    int32               pos_err;                                                        // position control error | unit[pulse]

    double              xwkp;                                                           // proportional accumulation value
    double              spdr;                                                           // position loop velocity command output | unit[rad/s]
    double              tqrp;                                                           // torque feedforward command

    double              spd_ffd;                                                        // velocity feedforward value | unit[rad/s]
    double              spd_ffd_lst;                                                    // the last velocity feedforward value | unit[rad/s]
    double              spd_ffd_out;                                                    // the output of speed feedforward | unit[rad/s]

    double              tqr_ffd;                                                        // torque feedforward value | unit[Nm]
    double              tqr_ffd_out;                                                    // the output of torque feedforward | unit[Nm]
//**************************************************************************************************************************
// position command filter variable define
// moving average filter variable
    int16				idx_maf;                                                        // index
    int16				ksub_maf;                                                       // subtraction weight gain

    int64				sumx_maf;                                                       // sum variable
    int32				remx_maf;                                                       // remainder variable
    Uint16				zcntx_maf;                                                      // finish flag(0:finished)
    int32               maf_buf[PCMD_MAF_BUF_NUM];                                      // moving average filtering buffer variable

    int32               maf_in;                                                         // input of moving average filtering
    int32               maf_out;                                                        // output of moving average filtering
// delta positon command & feedback variable define
    int32               dpcmd;                                                          // delta position command
    int32               dpfb;                                                           // delta position feedback

    Uint32              sig_pos;                                                        // singal circle encoder position
    Uint32              sig_pos_lst;                                                    // the last circle encoder position
//**************************************************************************************************************************
}POS_CTL;



// function declare
int16	KpiInitPosLoopModule(POS_CTL * m_ctl);                                          // Initialize the parameter of position control module
int16	KpiInitPosLoopVar(POS_CTL * m_ctl);                                             // initialize the position control variable
int16	KpiPosCloseLoopCtl(POS_CTL * m_ctl, int32 * dpcmd);                             // position close loop control function



#endif


///////////////////////////////////////////////////////// no more ////////////////////////////////////////////////////////////
