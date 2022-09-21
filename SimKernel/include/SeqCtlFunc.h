//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	Servo control sequencec control module define               //
//	file				:	SeqCtlFunc.h                                                //
//	Description			:	use for SERVO system sequence control   					//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g(1487)		|	2022/08/09	|	liu.g           |		2022 - 2032			//
//--------------------------------------------------------------------------------------//

#ifndef __SEQCTLFUNC_H__
#define __SEQCTLFUNC_H__

#include "DspCpu.h"


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
typedef	enum
{
    IDLE_SEQ_WORK			=	0,													// idle work mode in sequence control | IDLE_TASK_ID
    AOA_SEQ_WORK			=	1,													// adc offset adjust work mode in sequence control | AOA_TASK_ID
    MIPA_SEQ_WORK			=	2,													// motor initialize phase adjust work mode in sequence control | MIPA_TASK_ID
    MPSA_SEQ_WORK			=	3,													// motor parameter self acquire in sequence control | MPSA_TASK_ID
    COLD_SEQ_WORK			=	4,													// current open loop control work mode in sequence control | COLD_TASK_ID
    CCLD_SEQ_WORK			=	5,													// current closed loop control work mode in sequence control | CCLD_TASK_ID
    VCLD_SEQ_WORK			=	6,													// velocity closed loop control work mode in sequence control | VCLD_TASK_ID
    PROF_VELC_SEQ_WORK		=	7,													// profile velocity control work mode in sequence control | POSCLD_TASK_ID
    PROF_POSC_SEQ_WORK      =	8,                                                  // profile position control work mode in sequence control	| POSCLD_TASK_ID
    PROF_CURC_SEQ_WORK		=	9,			   										// profile current control work mode in sequence control | POSCLD_TASK_ID
    CS_VELC_SEQ_WORK		=	10,													// periodic synchronization velocity control work mode in sequence control | POSCLD_TASK_ID
    CS_POSC_SEQ_WORK		=	11,													// periodic synchronization position control work mode in sequence control | POSCLD_TASK_ID
    CS_CURC_SEQ_WORK        =	12,                                                 // periodic synchronization torque discharge work mode in sequence control | POSCLD_TASK_ID
    HOME_SEQ_WORK           =   13,                                                 // mechanic home search and fix mode in sequence control | POSCLD_TASK_ID
    STOP_SEQ_WORK           =   14,                                                 // stop mode in sequence control
    REV_SEQ_WORK_MODE		=	0x8000
}tSeqWorkMode;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// position command input source select
typedef	enum
{
    PC_USER_PCMD			=	0,													// position command come from app in PC
    LINK_NET_PCMD			=	1,													// position command come from bus network
    PULSE_DIR_PCMD			=	2,													// position command come from pulse direction
    PT_INTERP_PCMD          =   3,                                                  // position command come from position time interpolate
    EXCI_SIG_PCMD           =   4,                                                  // position command come from exitation signal source module
    RECIP_STEP_PCMD         =   5,                                                  // position command come from reciprocate step motion
    REV_PCMD_SEL			=	0x8000
}tSeqPcmdSel;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// velocity command input source select
typedef	enum
{
    PC_USER_VCMD			=	0,													// velocity command come from app in PC
    LINK_NET_VCMD			=	1,													// velocity command come from bus network
    ANALOG_VCMD				=	2,													// velocity command come from analog signal input
    EXCI_SIG_VCMD           =   3,                                                  // velocity command come from exitation signal source module
    RECIP_STEP_VCMD         =   4,                                                  // velocity command come from reciprocate step motion
    REV_VCMD_SEL			=	0x8000
}tSeqVcmdSel;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// current command input source select
typedef	enum
{
    PC_USER_CCMD			=	0,													// current command come from app in PC
    LINK_NET_CCMD			=	1,													// current command come from bus network
    ANALOG_CCMD				=	2,													// current command come from analog signal input
    EXCI_SIG_CCMD           =   3,                                                  // current command come from exitation signal source module
    RECIP_STEP_CCMD         =   4,                                                  // current command come from reciprocate step motion
    REV_CCMD_SEL			=	0x8000
}tSeqCcmdSel;


// command direction select
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
typedef struct	seq_cmd_dir_bits
{
    Uint16  POSC_DIR    : 1;                                                        // position command direction bit
    Uint16  VELC_DIR    : 1;                                                        // velocity command direction bit
    Uint16  CURC_DIR    : 1;                                                        // current command direction bit

    Uint16  rsvd        : 13;                                                       // reserved
}SEQ_CMD_DIR_BITS;


typedef	union
{
    Uint16					all;
    SEQ_CMD_DIR_BITS		bit;
}tSeqCmdDir;



//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
typedef struct	ins_ctlw_bits
{
    Uint16		SO		: 1;														// servo enable instruction bit
    Uint16		EV		: 1;														// voltage enable instruction bit
    Uint16      QS      : 1;                                                        // quick stop instruction bit
    Uint16		EO		: 1;														// enable operation instruction bit

    Uint16		OMS		: 3;														// servo driver work mode
    Uint16		FR		: 1;														// system reset instruction bit

    Uint16		HALT	: 1;														// halt state
    Uint16		res		: 7;														// reserved
}INS_CTLW_BITS;


typedef	union
{
    Uint16					all;
    INS_CTLW_BITS			bit;
}tDrvInsCtlW;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

typedef struct	ins_stsw_bits
{
    Uint16		RTSO	: 1;														// servo ready state status
    Uint16		SOS		: 1;														// servo on state status
    Uint16		OES		: 1;														// operation enable status
    Uint16      FALTS   : 1;                                                        // fault bit status

    Uint16		VES		: 1;														// voltage enable status
    Uint16      QSS     : 1;                                                        // quick stop status
    Uint16      SOD     : 1;                                                        // switch on disable
    Uint16      WARNS   : 1;                                                        // warning status

    Uint16		RSS		: 1;														// motor running status
    Uint16      RMTS    : 1;                                                        // remote
    Uint16		TRS		: 1;														// target reached status
    Uint16      LIMS    : 1;                                                        // limit status

    Uint16		OMSS	: 2;														// driver work mode status
    Uint16		rsvd	: 2;														// reserved
}INS_STSW_BITS;

typedef	union
{
    Uint16					all;
    INS_STSW_BITS			bit;
}tDrvInsStsW;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


typedef	enum
{
    STOP_VCTL_SERVO			=	0,													// stop in velocity mode
    SPD_TRA_VCTL_SERVO      =	1,													// closed loop velocity control mode (with position control in outside controller)
    FIX_PCTL_SERVO			=	2,													// fixed position control mode
    POS_TRA_PCTL_SERVO      =	3,													// track position control mode
    TQR_TRA_CCTL_SERVO      =	4,													// torque control mode
    HOME_VCTL_SERVO         =   5,                                                  // home velocity control mode
    REV_SERVO_MODE			=	0x8000
}tSeqServoMode;

typedef	enum
{
    POS_CTL_POSCLD			=	0,													// position control mode in POSCLD ID task
    VEL_CTL_POSCLD			=	1,													// velocity control mode in POSCLD ID task
    CURR_CTL_POSCLD			=	2,													// current control mode in POSCLD ID task
    REV_POSCLD_MODE			=	0x8000
}tSeqPoscldMode;


typedef struct	seq_cfg_opt_bits
{
    Uint32		VRAMP	: 1;                                                        // velocity reference ramp mask bit in VEL_CTL_POSCLD mode | 1/mask ramp

    Uint32		rsvd	: 31;	                                                    // rsvd
}SEQ_CFG_OPT_BITS;


typedef	union
{
    Uint32					all;
    SEQ_CFG_OPT_BITS        bit;
}tSeqCfgOpt;


//-------------------------------------------------------------------------------------
//						SEQUENCE CONTROL PARAMETER STRUCT
//-------------------------------------------------------------------------------------
typedef		struct	seq_ctl_prm
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// config parameter
    tSeqPcmdSel             psrc_sel;                                               // position command source select
    tSeqVcmdSel             vsrc_sel;                                               // velocity command source select
    tSeqCcmdSel             csrc_sel;                                               // current command source select
    tSeqCmdDir              cmd_dir;                                                // command direction of sequence control
    tSeqCfgOpt              cfg_opt;                                                // config option of sequence control
// user define work task mode parameter
    tSeqWorkMode			usr_mode_tmp;											// user define work task mode
    tSeqWorkMode			usr_mode;												// user define work task mode
// POSCLD ID task sequence control parameter define
    tSeqServoMode			sev_mode_tmp;											// servo work mode temper in POSCLD task
    tSeqServoMode			sev_mode;												// servo work mode in POSCLD task
    tSeqPoscldMode			pov_mode;												// position or velocity control mode switch in POSCLD task

    tDrvInsCtlW             ctl_word_tmp;
    tDrvInsCtlW             ctl_word;												// control word in servo driver instruction
    tDrvInsStsW             sts_word;												// status word in instruction
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}SEQ_CTL_PRM;



typedef		struct	seq_ctl
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// sequence control parameter define
    SEQ_CTL_PRM			prm;														// parameter object define
// variable define
    double              udr_tmp;
    double              uqr_tmp;

    double              uar_tmp;
    double              ubr_tmp;
    double              ucr_tmp;

    double              idr_tmp;
    double              iqr_tmp;
    double              spdr_tmp;
    int64               posr_tmp;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    double              udr_out;
    double              uqr_out;

    double              uar_out;
    double              ubr_out;
    double              ucr_out;

    double              idr_out;
    double              iqr_out;
    double              spdr_out;
    int64               posr_out;
    int64               posr_out_lst;

    int32               dpcmd_in;
    int32               dpcmd_out;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    int16               act_on_tmp;
    int16               act_on_out;
    int16               en_opera_tmp;
    int16               en_opera_out;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}SEQ_CTL;



// function declare
int16	KpiInitSeqCtlModule(SEQ_CTL * m_ctl);
int16	KpiInitSeqCtlVar(SEQ_CTL * m_ctl);
int16	KpiSeqBackGroundRout(SEQ_CTL * m_ctl, void * m_drv);
int16	KpiSeqServoCtlIsr(SEQ_CTL * m_ctl, void * m_drv);




#endif
