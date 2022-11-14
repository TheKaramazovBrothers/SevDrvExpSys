//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	model estimate for servo system parameter identification    //
//	file				:	ModelEst.h                                                  //
//	Description			:	use for SERVO system mechanical model estimate              //
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g(1487)		|	2022/11/10	|	   liu.g        |		2022 - 2032			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////


#ifndef     __MODELEST_H__
#define     __MODELEST_H__


#include "DspCpu.h"


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
typedef struct	idf_cfg_opt_bits
{
    Uint32      RLS_EN      : 1;                                                        // RLS algorithm enable bit
    Uint32		res         : 31;                                                       // reserved
}IDF_CFG_OPT_BITS;


typedef	union
{
    Uint32                      all;
    IDF_CFG_OPT_BITS			bit;
}tModIdfCfgOpt;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


//-------------------------------------------------------------------------------------
//                          MODEL ESTIMATE PARAMETER STRUCT
//-------------------------------------------------------------------------------------
typedef		struct	mod_idf_prm
{
//#############################################################################################################################
    tModIdfCfgOpt       cfg_opt;                                                        // config option
    Uint32              ts;																// model estimate sample times | unit[ns]
//#############################################################################################################################
// recursive least squares parameter declare
    Uint32              j0;                                                             // initialize value of inertia for rls algorithm | unit[10^-6 kg.m^2]
    Uint32              p0;                                                             // initialize gain of p1 coefficient for rls algorithm
    Uint32              lamt;                                                           // the lamt coefficient for rsl algorithm realization | unit[Q24]
//-------------------------------------------------------------------------------------
//  a0 = Jm/(d*Ts+Jm)
//-------------------------------------------------------------------------------------
    double              a0;                                                             // initialize value of a1 coefficient for rls algorithm | unit[Q12]
//-------------------------------------------------------------------------------------
//  b0 = Ts/(d*Ts+Jm)
//-------------------------------------------------------------------------------------
    double              b0;                                                             // initialize value of b1 coefficient for rls algorithm | unit[Q12
//#############################################################################################################################
}MOD_IDF_PRM;


typedef		struct	mod_idf
{
// velocity control module parameter define
    MOD_IDF_PRM		prm;
//**************************************************************************************************************************
    double          lambda;                                                              // the constant coefficient for rls algorithm

    double          c0x[2];                                                             // parameter coefficient array 0
    double          c1x[2];                                                             // parameter coefficient array 1
    double          p0x[2][2];                                                          // covariance matrix 0
    double          p1x[2][2];                                                          // covariance matrix 1
    double          Gamma[2];                                                           // update gain for rls algorithm
    double          phi0x[2];                                                           // input variable array 0 for rls algorithm
    double          phi1x[2];                                                           // input variable array 1 for rls algorithm

    double          err_est;                                                            // the est error variable

    double          wm;                                                                 // input velocity of motor for rls algorithm | unit[rad/s]
    double          tqr;                                                                // input torque of motor for rls algorithm | unit[Nm]
//-------------------------------------------------------------------------------------
//  Jm = -(a1/b1)*Ts
//-------------------------------------------------------------------------------------
    double          Jest;                                                               // the estimate Moment of inertia for rls algorithm | unit[kg.m^2]
//-------------------------------------------------------------------------------------
//  Dm = (a1 + 1)/b1
//-------------------------------------------------------------------------------------
    double          Dest;                                                               // the estimate viscous friciton for rls algorithm| unit[Nm/rad]
    double          Junit;                                                              // Moment of inertia for rls algorithm| unit[10^-6 kg.m^2]
//**************************************************************************************************************************
}MOD_IDF;



// function declare
int16	KpiInitModIdfModule(MOD_IDF * m_idf);                                           // Initialize the parameter of model identification module
int16	KpiInitModeIdfVar(MOD_IDF * m_idf);                                             // initialize the model identification variable
int16	KpiRLSMotJmDmEst(MOD_IDF * m_idf,  double * m_spdf, double * m_tqr);            // model parameter identification use least square method












#endif



///////////////////////////////////////////////////////// no more ////////////////////////////////////////////////////////////
