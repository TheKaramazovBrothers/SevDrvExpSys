//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	curr control loop design                                    //
//	file				:	CurrCtlLoop.h       										//
//	Description			:	use for SERVO system current control loop realization   	//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g(1487)		|	2022/07/01	|	liu.g           |		2022 - 2032			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __CURRCTLLOOP_H__
#define __CURRCTLLOOP_H__

#include "DspCpu.h"
#include "SevCtlPrmTblDef.h"

typedef struct curr_ctl_prm
{
// serialize parameter define
    Uint32	mot_Irat;                                                       // continued phase current rated value | unit[0.001A]
    Uint32	mot_Imax;														// instantaneous maximum current of driver system | unit[0.001A]

    Uint32	mot_Sct;														// continued speed rated value |  unit[RPM]
    Uint32	mot_Nos;														// over speed unit(max speed) | unit[RPM]
    Uint16	mot_Srat;														// over speed detection level |  unit[%]

    Uint32	mot_Tqr;														// motor rated torque | unit[0.001 N.m]
    Uint16	mot_PPN;														// motor pole pair numbers
// pmsm motor driver system unit parameter
    Uint32	mot_PHIm;														// EMF constant | unit[0.1mV/r/min]
// motor winding parameter
    Uint32	mot_Ldm;														// motor d axis reactive resistance [0.001mH]
    Uint32	mot_Lqm;														// motor q axis reactive resistance [0.001mH]
    Uint32	mot_Rm;                                                         // motor rotate winding resistance [1 m ohm]

    Uint32	mot_Jm;                                                         // rotary inertia of motor | unit[10^-6 kg.m^2]
    Uint16	mot_Jrat;														// Inertia ratio 100 * ((Jtotal - Jmot)/Jmot) | unit[%]
    Uint16  mot_Vmax;                                                       // maximum voltage of driver system Vmax [0.1V]
//#############################################################################################################################
// current parameter define
    Uint32	curr_TS;                                                        // digital control sample periods / unit[1ns]
//#############################################################################################################################
// current control parameter define
    Uint32	curr_ctl_Tid;                                                   // d axis integral time constant | unit[us]
    Uint32	curr_ctl_Tiq;													// q axis integral time constant | unit[us]
    Uint16	curr_ctl_fnd;													// d axis frequent band width | unit[Hz]
    Uint16	curr_ctl_fnq;													// q axis frequent band width | unit[Hz]
//#############################################################################################################################
}CURR_CTL_PRM;



typedef struct curr_ctl
{
//tbl parameter define
    CURR_CTL_PRM    prm;                                                    // table parameter define
//**************************************************************************************************************************
// current control paramter define
    double	kpd;                                                            // proportional coefficient of d axis
    double	kpq;                                                            // proportional coefficient of q axis
    double	kid;                                                            // intergral coefficient of d axis
    double	kiq;                                                            // intergral coefficient of q axis

    double	do_ulim;														// d axis control output upper limit
    double	do_llim;														// d axis control output lower limit
    double	qo_ulim;														// q axis control output upper limit
    double	qo_llim;														// q axis control output lower limit

    double	di_ulim;														// d axis integral upper limit
    double	di_llim;														// d axis integral lower limit
    double	qi_ulim;														// q axis integral upper limit
    double	qi_llim;														// q axis integral lower limit
//**************************************************************************************************************************
// control variable define
    double	id;																// d axis current feedback
    double	iq;																// q axis current feedback
    double	id_ref;															// d axis current reference
    double	iq_ref;															// q axis current reference
    double  id_err;                                                         // d axis current control error
    double  iq_err;                                                         // q axis current control error

    double	ud;																// d axis voltage output
    double	uq;																// q axis voltage output

    double	id_s;															// sum of d axis control output
    double	iq_s;															// sum of q axis control output
    double	idi_s;															// sum of d axis error integral
    double	iqi_s;															// sum of q axis error integral
// measure variable define
    double  phim;                                                           // mechancal angel rad
    double  phie;                                                           // electrical angel rad

    double  ia;                                                             // a phase current input
    double  ib;                                                             // b phase current input
    double  ic;                                                             // c phase current input
// output variable define
    double  ua;                                                             // a phase voltage output
    double  ub;                                                             // b phase voltage output
    double  uc;                                                             // c phase voltage output
// ud & uq reference
    double  ud_ref;                                                         // d axis voltage reference
    double  uq_ref;                                                         // q axis voltage reference
//**************************************************************************************************************************
}CURR_CTL;


int16   KpiInitCurrCtlPrm(CURR_CTL_PRM * m_prm);
int16   KpiInitCurrCtlModule(CURR_CTL * m_ctl);
int16   KpiInitCurrCtlVar(CURR_CTL * m_ctl);


int16   KpiGetCurrLootRef(CURR_CTL * m_ctl, double * m_idr, double * m_iqr);
int16   KpiGetCurrLoopFb(CURR_CTL * m_ctl, double * m_ia, double * m_ib, double * m_ic, double * m_phie);
int16   KpiSetCurrLoopOut(CURR_CTL * m_ctl, double * m_ua, double * m_ub, double * m_uc);
int16   KpiCurrCtlLoopUpdate(CURR_CTL * m_ctl);
int16   KpiCurrOpenLoopUpdate(CURR_CTL * m_ctl);


int16   KpiGetUdUqVoltageRef(CURR_CTL * m_ctl, double * m_udr, double * m_uqr);



#endif




///////////////////////////////////////////////////////// no more ////////////////////////////////////////////////////////////
