//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	Excitation signal generation module design                  //
//	file				:	ExciSigProd.h                                               //
//	Description			:	use for SERVO system excitation signal generate             //
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g(1487)		|	2022/09/14	|	   liu.g        |		2022 - 2032			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef     __EXCISIGPROD_H__
#define     __EXCISIGPROD_H__


#include "DspCpu.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EXCITATION STATE STRUCT DEFINE
typedef	enum
{
    INIT_STAGE_ESPS			=	0,                                                          // initialization stage of excitation signal produce
    WORK_STAGE_ESPS			=	1,                                                          // work stage of excitation signal produce
    END_STAGE_ESPS          =   2,                                                          // end stage of excitation signal produce
    REV_STAGE_ESPS			=	0x8000
}tExciSigProdState;



//#############################################################################################################################
typedef struct	exci_sig_cfg_opt_bits
{
    Uint32		TYPE            : 4;                                                        // excitation signal type select bit | 0/sinusoidal signal, 1/prbs signal, 2/chirp signal
    Uint32		rsvd            : 28;                                                       // reserved
}EXCI_SIG_CFG_OPT_BITS;


typedef	union
{
    Uint32                      all;
    EXCI_SIG_CFG_OPT_BITS       bit;
}tExciSigCfgOpt;
//#############################################################################################################################

//#############################################################################################################################
typedef struct	exci_sig_flag_bits
{
    Uint32		FISH            : 1;                                                        // finished flag |1/finished,0/no
    Uint32		rsvd            : 31;                                                       // reserved
}EXCI_SIG_FLAG_BITS;


typedef	union
{
    Uint32                      all;
    EXCI_SIG_FLAG_BITS          bit;
}tExciSigFlag;
//#############################################################################################################################

typedef struct	prbs_prod_bits
{
    Uint32		PB_X1              : 1;                                                     // BIT 0
    Uint32      PB_X2_X27          : 26;                                                    // BIT 2 ---> 27
    Uint32      PB_X28             : 1;                                                     // BIT 28
    Uint32      PB_X29_X30         : 2;                                                     // BIT 29 ---> 30
    Uint32		PB_X31             : 1;                                                     // BIT 31
    Uint32      PB_X32             : 1;                                                     // BIT 32
}PRBS_PROD_BITS;


typedef	union
{
    Uint32                      all;
    PRBS_PROD_BITS              bit;
}tPrbsProdFlag;

//#############################################################################################################################
//-------------------------------------------------------------------------------------
//					EXCITATION SIGNAL MODULE PARAMETER STRUCT
//-------------------------------------------------------------------------------------
typedef		struct	exci_sig_prm
{
//#############################################################################################################################
// OBJ parameter define
    Uint32              ts;																	// excitation signal produce module sample times | unit[ns]
    tExciSigCfgOpt      cfg_opt;                                                            // config option of excitation signal module

    Uint32              exci_amp;                                                           // amplitude of excitation signal | unit[Q10]
    Uint32              steady_tim;                                                         // Steady state time of sinusoidal excitation | unit[scan]
    Uint32              delay_tim;                                                          // delay time between harmonic component
// parameter define for sinusoidal excitation
    Uint16              sin_hz_start;                                                       // start frequency of sinusoidal excitation | unit[HZ]
    Uint16              sin_hz_step;                                                        // step of sinusoidal excitation | unit[HZ]
    Uint16              sin_harm_num;                                                       // sinusoidal excitation numbers (numbers of sine waves)
// parameter define for prbs signal excitation
    Uint16              prbs_div_num;                                                       // prbs division times | unit[ts]
    Uint32              prbs_durat_tim;                                                     // prbs durate time | unit[ts]
// parameter define for chirp signal excitation
    Uint16              chirp_hz_start;                                                     // start frequency of chirp signal | unit[HZ]
    Uint16              chirp_hz_end;                                                       // end frequency of chirp signal | unit[HZ]
    Uint32              chirp_durat_tim;                                                    // duration times of chirp signal | unit[ts]
//#############################################################################################################################
}EXCI_SIG_PRM;





//-------------------------------------------------------------------------------------
//							POSITION COMMAND MAKER
//-------------------------------------------------------------------------------------
typedef		struct	exci_sig
{
//#############################################################################################################################
// parameter define
    EXCI_SIG_PRM		prm;
//  excitation signal parameter define
    double              delt_ts;                                                            //  sample times in double parameter | unit[s]
//#############################################################################################################################
    double              real_t;                                                             // real time of current harmonic signal | unit[s]
    double              real_f;                                                             // real frequency of current harmonic signal | unit[HZ]
    double              real_w;                                                             // real angular frequency of current harmonic signal |unit[rad/s]
    double              exci_sig_out;                                                       // excition signal output

    int32               period_cnt;                                                         // period count variable
    int32               harm_cnt;                                                           // harmonic times count variable
    tExciSigFlag        status_flag;                                                        // status flag
    tExciSigProdState   state;                                                              // the work state of extition signal produce

    tPrbsProdFlag       prbs_flag;                                                          // the prbs generate flag
//#############################################################################################################################
}EXCI_SIG;


//#############################################################################################################################
// function declare
int16	KpiInitExciSigProdModule(EXCI_SIG * m_ctl);                                          // Initialize the parameter of excitation signal produce module
int16	KpiInitExciSigProdVar(EXCI_SIG * m_ctl);                                             // initialize the excitation signal produce variable
int16	KpiExciSigProd(EXCI_SIG * m_ctl, double * exci_out);                                 // excitation signal produce function






#endif






///////////////////////////////////////////////////////// no more ////////////////////////////////////////////////////////////
