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

//-------------------------------------------------------------------------------------
//						VELOCITY CONTROL PARAMETER STRUCT
//-------------------------------------------------------------------------------------
typedef		struct	sens_meas_prm
{
//#############################################################################################################################
// velocity control module parameter define
    Uint32          enc_line_num;                                                       // line number of encoder in one circle
}SENS_MEAS_PRM;



typedef		struct	sens_meas
{
// parameter define
    SENS_MEAS_PRM   prm;                                                                // parameter define
// parameter define
    double          kspd;                                                               // transform coefficient from delta position to speed
// variable define
    double          ia;																	// current a phase current
    double          ib;																	// current b phase current
    double          ic;																	// current c phase current
// rotate encoder feedback variable define
    double          mot_spd;                                                            //
    double          phim;                                                               // meachnical position /rad
    double          phil;                                                               // load position

    int64           pos_cnt;                                                            // position count variable
    int64           pos_cnt_lst;                                                        // the last position count variable
    Uint32          pos_in;                                                             // enccoder position feedback
    int32           dpos;                                                               // delta position feeedback
}SENS_MEAS;



int16   KpiInitSensMeasModule(SENS_MEAS * m_sens);
int16   KpiGetCurrSensorValue(SENS_MEAS * m_sens);
int16   KpiGetEncValue(SENS_MEAS * m_sens);

int16   KpiThreeVoltageOutput(double * ua, double * ub, double * uc);


#endif
///////////////////////////////////////////////// no more /////////////////////////////////////////////
