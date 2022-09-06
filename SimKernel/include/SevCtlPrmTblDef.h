//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	Servo control paramter table define                         //
//	file				:	SevCtlPrmTblDef.h											//
//	Description			:	use for SERVO system parameter define   					//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g(1487)		|	2022/07/01	|	liu.g           |		2022 - 2032			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef     __SEVCTLPRMTBLDEF_H__
#define     __SEVCTLPRMTBLDEF_H__

#include "DspCpu.h"


#define     VIR_FLASH_WORD_SIZE             65536

#define     ID16_START_ADR_FALSH            0
#define     ID32_START_ADR_FLASH            2048

#define     ID16_MAX_ADR_LENGTH             2048
#define     ID32_MAX_ADR_LENGTH             2048

#define		SEV_PRM_FROM_EX_MEM_EN			ENABLE

#define     PI_CIRCULAR_CONSTANT            3.1415926535
#define     PI2_CIRCULAR_CONSTANT          (2 * PI_CIRCULAR_CONSTANT)
//#############################################################################################################################
// parameter table enum define
typedef enum
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    SRAT_MOT_PRM_ID16_ADR                   =   0,                                                          // over speed detection level |  unit[%]
    PPN_MOT_PRM_ID16_ADR                    =   1,                                                          // motor pole pair numbers
    JRAT_MOT_PRM_ID16_ADR                   =   2,                                                          // Inertia ratio 100 * ((Jtotal - Jmot)/Jmot) | unit[%]
    VMAX_MOT_PRM_ID16_ADR                   =   3,                                                          // maximum voltage of driver system Vmax [0.1V]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    FND_CCLD_PRM_ID16_ADR                   =   4,                                                          // d axis frequent band width | unit[Hz]
    FNQ_CCLD_PRM_ID16_ADR                   =   5,                                                          // q axis frequent band width | unit[Hz]
    ABS_RAT_TQR_LIM_VCTL_PRM_ID16_ADR       =   6,                                                          // max torque limit rate | unit[Q12]
    POS_RAT_TQR_LIM_VCTL_PRM_ID16_ADR       =   7,                                                          // positive tqrque limit rate | unit[Q12]
    NEG_RAT_TQR_LIM_VCTL_PRM_ID16_ADR       =   8,                                                          // negative tqrque limit rate | unit[Q12]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    FNP_FST_PCTL_PRM_ID16_ADR               =   9,                                                          // position loop gain band width | unit[0.1Hz]
    FNP_SEC_PCTL_PRM_ID16_ADR               =   10,                                                         // the second position loop gain bandwidth | unit[0.1Hz]

    ABS_RAT_SPD_LIM_PCTL_PRM_ID16_ADR       =   11,                                                         // max velocity limit rate | unit[Q12]
    POS_RAT_SPD_LIM_PCTL_PRM_ID16_ADR       =   12,                                                         // positive velocity limit rate | unit[Q12]
    NEG_RAT_SPD_LIM_PCTL_PRM_ID16_ADR       =   13,                                                         // negative velocity limit rate | unit[Q12]
    MAF_NUM_PCTL_PRM_ID16_ADR               =   14,                                                         // moving average filtering times | unit[scan]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    PSRC_SEL_SEQ_CTL_PRM_ID16_ADR           =   15,                                                         // position command source select
    VSRC_SEL_SEQ_CTL_PRM_ID16_ADR           =   16,                                                         // velocity command source select
    CSRC_SEL_SEQ_CTL_PRM_ID16_ADR           =   17,                                                         // current command source select
    CMD_DIR_SEQ_CTL_PRM_ID16_ADR            =   18,                                                         // command direction of sequence control
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    FFV_RATE_PCTL_PRM_ID16_ADR              =   19,                                                         // velocity feedforward rate | unit[Q12]
    FFT_RATE_PCTL_PRM_ID16_ADR              =   20,                                                         // torque feedforward rate | unit[Q12]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    PRM_SERVO_CTL_ID_WORD_MAX_NUM
}tPrmCurrCtlId_WORD;



//#############################################################################################################################
typedef enum
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    IRATE_MOT_PRM_ID32_ADR                  =   0,                                                          // continued phase current rated value | unit[0.001A]
    IMAX_MOT_PRM_ID32_ADR                   =   1,                                                          // instantaneous maximum current of driver system | unit[0.001A]
    SCT_MOT_PRM_ID32_ADR                    =	2,															// continued speed rated value |  unit[RPM]
    NOS_MOT_PRM_ID32_ADR                    =   3,                                                          // over speed unit(max speed) | unit[RPM]
    TQR_MOT_PRM_ID32_ADR                    =   4,    														// motor rated torque | unit[0.001 N.m]
    PHIM_MOT_PRM_ID32_ADR                   =   5,      													// EMF constant | unit[0.1mV/r/min]
    LDM_MOT_PRM_ID32_ADR                    =   6,                                                          // motor d axis reactive resistance [0.001mH]
    LQM_MOT_PRM_ID32_ADR                    =   7,      													// motor q axis reactive resistance [0.001mH]
    RM_MOT_PRM_ID32_ADR                     =   8,                                                          // motor rotate winding resistance [1 m ohm]
    JM_MOT_PRM_ID32_ADR                     =   9,                                                          // rotary inertia of motor | unit[10^-6 kg.m^2]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    TS_ISR_PRM_ID32_ADR                     =   10,                                                         // digital control sample periods / unit[1ns]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    TID_CCTL_PRM_ID32_ADR                   =   11,                                                         // d axis integral time constant | unit[us]
    TIQ_CCTL_PRM_ID32_ADR                   =   12,                                                         // q axis integral time constant | unit[us]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    LINE_NUM_ENC_PRM_ID32_ADR               =   13,                                                         // line number of encoder in one circle | unit[pulse]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    FNV_FST_VCTL_PRM_ID32_ADR               =   14,                                                         // velocity loop gain band width | unit[0.1Hz]
    TIV_FST_VCTL_PRM_ID32_ADR               =   15,                                                         // velocity loop integral time constant | unit[0.01ms]
    FNV_SEC_VCTL_PRM_ID32_ADR               =   16,                                                         // the second velocity loop gain bandwidth | unit[0.1Hz]
    TIV_SEC_VCTL_PRM_ID32_ADR               =   17,                                                         // the second velocity loop integral time constant | unit[0.01ms]
    TS_VCTL_PRM_ID32_ADR                    =   18,                                                         // velocity loop sample times | unit[ns]
    TF_RMP_VCTL_PRM_ID32_ADR                =   19,                                                         // ramp time constant of velocity command | unit[ms]
    CFG_OPT_ALL_PRM_ID32_ADR                =   20,                                                         // velocity control config option
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    TS_POS_CTL_PRM_ID32_ADR                 =   21,                                                         // position loop sample times | unit[ns]
    CFG_OPT_ALL_PCTL_PRM_ID32_ADR           =   22,                                                         // position control config option
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    CFG_OPT_ALL_SEQ_CTL_PRM_ID32_ADR        =   23,                                                         // config option of sequence control

    ROT_RES_POS_TRAJ_PRM_ID32_ADR           =   24,                                                         // rotation resolution | unit[pulse number/circle]
    TS_POS_TRAJ_PRM_ID32_ADR                =   25,                                                         // position command maker sample times | unit[ns]

    ACCRATE_POS_TRAJ_PRM_ID32_ADR           =   26,                                                         // acceleration of position command maker | unit[10000pulse/s/s]
    DECRATE_POS_TRAJ_PRM_ID32_ADR           =   27,                                                         // deceleration of position command maker | unit[10000pulse/s/s]
    MAXSPD_POS_TRAJ_PRM_ID32_ADR            =   28,                                                         // maximum velocity set for position trajectory maker | unit[RPM]
    CFG_OPT_ALL_POS_TRAJ_PRM_ID32_ADR       =   29,                                                         // point position trajectory nest mask bit | 1/mask
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    FFJ_RATE_PCTL_PRM_ID32_ADR              =   30,                                                         // jerk feedforward gain coefficient | unit[Q16]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    PRM_SERVO_CTL_ID_DWORD_MAX_NUM
}tPrmServoCtlId_DWORD;


//#############################################################################################################################

Uint16  SclReadFramPrmByID16(Uint16 m_id, Uint16 *m_data);
Uint32  SclReadFramPrmByID32(Uint16 m_id, Uint32 *m_data);

int16   SclWriteFramPrmByID16(Uint16 *m_data, Uint16 m_id);
int16   SclWriteFramPrmByID32(Uint32 *m_data, Uint16 m_id);



//#############################################################################################################################
extern  Uint16	gVirFlashStorage[VIR_FLASH_WORD_SIZE];




#endif

//


///////////////////////////////////////////////////////// no more ////////////////////////////////////////////////////////////
