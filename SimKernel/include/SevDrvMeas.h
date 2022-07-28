//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	Servo system feedback value measure	& drive output			//
//	file				:	SevDrvMeas.h												//
//	Description			:	use for SERVO system measurement processing	& drvie output	//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:           |	Corporation:	|		copyright(C):	//
//--------------------------------------------------------------------------------------//
//		liu.g(1487)		|	2022/7/14       |	liu.g           |		2022 - 2032		//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef		__SEVDRVMEAS_H__
#define		__SEVDRVMEAS_H__

#include "DspCpu.h"


typedef		struct	sens_meas
{
// variable define
    double          ia;																	// current a phase current
    double          ib;																	// current b phase current
    double          ic;																	// current c phase current
// rotate encoder feedback variable define
    double          mot_spd;                                                            //
    double          phim;                                                               // meachnical position /rad
    double          phil;                                                               // load position
}SENS_MEAS;



int16   KpiInitSensMeasModule(SENS_MEAS * m_sens);

int16   KpiGetCurrSensorValue(SENS_MEAS * m_sens);
int16   KpiGetEncValue(SENS_MEAS * m_sens);

int16   KpiThreeVoltageOutput(double * ua, double * ub, double * uc);


#endif
///////////////////////////////////////////////// no more /////////////////////////////////////////////
