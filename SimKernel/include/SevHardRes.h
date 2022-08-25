//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	Servo system hardware resource interface define 			//
//	file				:	SevHardRes.h												//
//	Description			:	use for SERVO system hardware resource interface define 	//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:           |	Corporation:	|		copyright(C):	//
//--------------------------------------------------------------------------------------//
//		liu.g(1487)		|	2022/7/14       |	liu.g           |		2022 - 2032		//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SEVHARDRES_H__
#define __SEVHARDRES_H__

#include "DspCpu.h"
//--------------------------------------------------------------------------------------------------------
int16		HalGetCurrSensorValue(double * m_ia, double * m_ib, double * m_ic);                 // include in BSP application procedure

int16		HalGetAbsPosValue(double * m_posm, double * m_posl);                                // get absolute encoder value

int16       HalSetThreePhaVoltage(double * m_ua, double * m_ub, double * m_uc);

int16       HalEnableThreePwmOutput();
int16       HalDisableThreePwmOutput();


/////////////////////////////////////////////////// no more /////////////////////////////////////////////////
#endif
