//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	Servo system virtual tuning command define					//
//	file				:	TuningCmd.h													//
//	Description			:	use for servo system virtual hardware tuning Interface		//
//							realization													//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g(1487)		|	2022/08/10	|	googoltech		|		2022 - 2032			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef _TUNINGCMD_H_
#define	_TUNINGCMD_H_

#include    "DspCpu.h"
#include	"SevDrvTask.h"

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
int16	VpiServoEnable(bool m_en);                                              // servo enable function declare | true/enable, false/disable
int16	VpiEnableOperate(bool m_en);                                            // enable operate function delcare | true/enable, false/disable

int16	VpiSetServoWorkMode(tSeqWorkMode m_mod);                                // set servo work mode

// servo reference interface function define
int16	VpiSetIdRef(double id_ref);
int16	VpiSetIqRef(double iq_ref);


int16	VpiSetUdRef(double ud_ref);
int16	VpiSetUqRef(double uq_ref);
int16	VpiSetUaRef(double ua_ref);
int16	VpiSetUbRef(double ub_ref);
int16	VpiSetUcRef(double uc_ref);

int16	VpiSetSpdRef(double spd_ref);
int16	VpiSetPosRef(double pos_ref);
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// servo reference interface function define
double	VpiGetIdRef(void);
double	VpiGetIqRef(void);

double	VpiGetUdRef(void);
double	VpiGetUqRef(void);
double	VpiGetUaRef(void);
double	VpiGetUbRef(void);
double	VpiGetUcRef(void);

double	VpiGetSpdRef(void);
double	VpiGetPosRef(void);
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=






#endif 
