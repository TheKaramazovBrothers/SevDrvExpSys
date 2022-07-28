//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	Servo control paramter table define                         //
//	file				:	MechModel.h													//
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


//#############################################################################################################################
// parameter table enum define
typedef enum
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    SRAT_MOT_PRM_ID16_ADR                =	 0,															// over speed detection level |  unit[%]
    PPN_MOT_PRM_ID16_ADR                 =   1,                  										// motor pole pair numbers
    JRAT_MOT_PRM_ID16_ADR                =   2,                                                         // Inertia ratio 100 * ((Jtotal - Jmot)/Jmot) | unit[%]
    VMAX_MOT_PRM_ID16_ADR                =   3,                                                         // maximum voltage of driver system Vmax [0.1V]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    FND_CCLD_PRM_ID16_ADR                =   4,                                                         // d axis frequent band width | unit[Hz]
    FNQ_CCLD_PRM_ID16_ADR                =   5,      													// q axis frequent band width | unit[Hz]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    PRM_SERVO_CTL_ID_WORD_MAX_NUM
}tPrmCurrCtlId_WORD;

//#############################################################################################################################
typedef enum
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    IRATE_MOT_PRM_ID32_ADR				 =  0,                                                          // continued phase current rated value | unit[0.001A]
    IMAX_MOT_PRM_ID32_ADR				 =	1,															// instantaneous maximum current of driver system | unit[0.001A]
    SCT_MOT_PRM_ID32_ADR                 =	2,															// continued speed rated value |  unit[RPM]
    NOS_MOT_PRM_ID32_ADR                 =  3,                                                          // over speed unit(max speed) | unit[RPM]
    TQR_MOT_PRM_ID32_ADR                 =  4,    														// motor rated torque | unit[0.001 N.m]
    PHIM_MOT_PRM_ID32_ADR                =  5,      													// EMF constant | unit[0.1mV/r/min]
    LDM_MOT_PRM_ID32_ADR                 =  6,                                                          // motor d axis reactive resistance [0.001mH]
    LQM_MOT_PRM_ID32_ADR                 =  7,      													// motor q axis reactive resistance [0.001mH]
    RM_MOT_PRM_ID32_ADR                  =  8,                                                          // motor rotate winding resistance [1 m ohm]
    JM_MOT_PRM_ID32_ADR                  =  9,                                                          // rotary inertia of motor | unit[10^-6 kg.m^2]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    TS_ISR_PRM_ID32_ADR                  =  10,                                                         // digital control sample periods / unit[1ns]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    TID_CCTL_PRM_ID32_ADR                =  11,                                                         // d axis integral time constant | unit[us]
    TIQ_CCTL_PRM_ID32_ADR                =  12,                                                         // q axis integral time constant | unit[us]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    PRM_SERVO_CTL_ID_DWORD_MAX_NUM
}tPrmServoCtlId_DWORD;

//#############################################################################################################################

Uint16  SclReadFramPrmByID16(Uint16 m_id, Uint16 *m_data);
Uint32  SclReadFramPrmByID32(Uint16 m_id, Uint32 *m_data);

int16   SclWriteFramPrmByID16(Uint16 *m_data, Uint16 m_id);
int16   SclWriteFramPrmByID32(Uint32 *m_data, Uint16 m_id);


#endif

//


///////////////////////////////////////////////////////// no more ////////////////////////////////////////////////////////////
