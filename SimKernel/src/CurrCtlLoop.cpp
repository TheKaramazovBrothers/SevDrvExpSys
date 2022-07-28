//=========================================================================================================
// project		:	servo system current control loop realization
// File			:	CurrCtlLoop.cpp
// discription	:	use in servo system current control loop realization
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g
// date			:	2022/07/01
// copyright(C)	:	liu.g	(2022-2032)
//=========================================================================================================
#include <cmath>
#include "SevCtlPrmTblDef.h"
#include "CurrCtlLoop.h"


int16   KpiInitCurrCtlModule(CURR_CTL * m_ctl)
{
// OBJECT WORD parameter initialization
//*****************************************************************************************************************************
    m_ctl->prm.mot_Irat             =   3500;                                       // continued phase current rated value | unit[0.001A]
    m_ctl->prm.mot_Imax             =   15000;                                      // instantaneous maximum current of driver system | unit[0.001A]

    m_ctl->prm.mot_Sct              =   3000;                                       // continued speed rated value |  unit[RPM]
    m_ctl->prm.mot_Nos              =   6000;                                       // over speed unit(max speed) | unit[RPM]
    m_ctl->prm.mot_Srat             =   250;                                        // over speed detection level |  unit[%]

    m_ctl->prm.mot_Tqr              =   1400;                                       // motor rated torque | unit[0.001 N.m]
    m_ctl->prm.mot_PPN              =   4;                                          // motor pole pair numbers
// pmsm motor driver system unit parameter
    m_ctl->prm.mot_PHIm             =   197;                                        // EMF constant | unit[0.1mV/r/min]
// motor winding parameter
    m_ctl->prm.mot_Ldm              =   3670;                                       // motor d axis reactive resistance [0.001mH]
    m_ctl->prm.mot_Lqm              =   3670;                                       // motor q axis reactive resistance [0.001mH]
    m_ctl->prm.mot_Rm               =   1000;                                       // motor rotate winding resistance [1 m ohm]

    m_ctl->prm.mot_Jm               =   44;                                         // rotary inertia of motor | unit[10^-6 kg.m^2]
    m_ctl->prm.mot_Jrat             =   540;                                        // Inertia ratio 100 * ((Jtotal - Jmot)/Jmot) | unit[%]
    m_ctl->prm.mot_Vmax             =   1550;                                       // maximum voltage of driver system Vmax [0.1V]
//*****************************************************************************************************************************
// current parameter define
    m_ctl->prm.curr_TS              =   31250;                                      // digital control sample periods / unit[1ns]
//*****************************************************************************************************************************
// current control parameter define
    m_ctl->prm.curr_ctl_Tid         =   1000;                                       // d axis integral time constant | unit[us]
    m_ctl->prm.curr_ctl_Tiq         =   1000;                                       // q axis integral time constant | unit [us]
    m_ctl->prm.curr_ctl_fnd         =   1000;                                       // d axis frequent band width | unit[Hz]
    m_ctl->prm.curr_ctl_fnq         =   1000;                                       // q axis frequent band width | unit[Hz]
// parameter initialization
//**************************************************************************************************************************
    m_ctl->kpq                      =   (2*3.1415926) * m_ctl->prm.curr_ctl_fnq * (m_ctl->prm.mot_Lqm/1000000.0);
    m_ctl->kpd                      =   (2*3.1415926) * m_ctl->prm.curr_ctl_fnd * (m_ctl->prm.mot_Ldm/1000000.0);

    m_ctl->kiq                      =   m_ctl->kpq * (m_ctl->prm.curr_TS/(m_ctl->prm.curr_ctl_Tiq * 1000.0));
    m_ctl->kid                      =   m_ctl->kpd * (m_ctl->prm.curr_TS/(m_ctl->prm.curr_ctl_Tid * 1000.0));

    m_ctl->do_ulim                  =   m_ctl->prm.mot_Vmax * 2.0;
    m_ctl->do_llim                  =   -m_ctl->do_ulim;

    m_ctl->di_ulim                  =   m_ctl->prm.mot_Vmax;
    m_ctl->di_llim                  =   -m_ctl->di_ulim;

    m_ctl->qo_ulim                  =   m_ctl->prm.mot_Vmax * 2.0;
    m_ctl->qo_llim                  =   -m_ctl->qo_ulim;

    m_ctl->qi_ulim                  =   m_ctl->prm.mot_Vmax;
    m_ctl->qi_llim                  =   -m_ctl->qi_ulim;
//**************************************************************************************************************************
// variable initialization
    m_ctl->id                       =   0;                                         // d axis current feedback
    m_ctl->iq                       =   0;                                         // q axis current feedback
    m_ctl->id_ref                   =   0;                                         // d axis current reference
    m_ctl->iq_ref                   =   0;                                         // q axis current reference
    m_ctl->ud                       =   0;                                         // d axis voltage output
    m_ctl->uq                       =   0;                                         // q axis voltage output

    m_ctl->id_s                     =   0;                                         // sum of d axis control output
    m_ctl->iq_s                     =   0;                                         // sum of q axis control output
    m_ctl->idi_s                    =   0;                                         // sum of d axis error integral
    m_ctl->iqi_s                    =   0;                                         // sum of q axis error integral
// measure variable define
    m_ctl->phim                     =   0;                                         // mechanical angel
    m_ctl->phie                     =   0;                                         // electrical angel

    m_ctl->ia                       =   0;                                         // a phase current input
    m_ctl->ib                       =   0;                                         // b phase current input
    m_ctl->ic                       =   0;                                         // c phase current input
// output variable define
    m_ctl->ua                       =   0;                                         // a phase voltage output
    m_ctl->ub                       =   0;                                         // b phase voltage output
    m_ctl->uc                       =   0;                                         // c phase voltage output

    m_ctl->ud_ref                   =   0;                                         // d axis voltage reference
    m_ctl->uq_ref                   =   0;                                         // q axis voltage reference
//*****************************************************************************************************************************
    return  TRUE;
}

int16   KpiInitCurrCtlVar(CURR_CTL * m_ctl)
{
//*****************************************************************************************************************************
// variable initialization
    m_ctl->id                       =   0;                                         // d axis current feedback
    m_ctl->iq                       =   0;                                         // q axis current feedback
    m_ctl->id_ref                   =   0;                                         // d axis current reference
    m_ctl->iq_ref                   =   0;                                         // q axis current reference
    m_ctl->ud                       =   0;                                         // d axis voltage output
    m_ctl->uq                       =   0;                                         // q axis voltage output

    m_ctl->id_s                     =   0;                                         // sum of d axis control output
    m_ctl->iq_s                     =   0;                                         // sum of q axis control output
    m_ctl->idi_s                    =   0;                                         // sum of d axis error integral
    m_ctl->iqi_s                    =   0;                                         // sum of q axis error integral
// measure variable define
    m_ctl->phim                     =   0;                                         // mechanical angel
    m_ctl->phie                     =   0;                                         // electrical angel

    m_ctl->ia                       =   0;                                         // a phase current input
    m_ctl->ib                       =   0;                                         // b phase current input
    m_ctl->ic                       =   0;                                         // c phase current input
// output variable define
    m_ctl->ua                       =   0;                                         // a phase voltage output
    m_ctl->ub                       =   0;                                         // b phase voltage output
    m_ctl->uc                       =   0;                                         // c phase voltage output
//*****************************************************************************************************************************
    return  TRUE;
}



int16   KpiGetCurrLootRef(CURR_CTL * m_ctl, double * m_idr, double * m_iqr)
{
//*****************************************************************************************************************************
    m_ctl->id_ref                   =   *m_idr;
    m_ctl->iq_ref                   =   *m_iqr;
//*****************************************************************************************************************************
    return  TRUE;
}

int16   KpiGetCurrLoopFb(CURR_CTL * m_ctl, double * m_ia, double * m_ib, double * m_ic, double * m_phim)
{
//*****************************************************************************************************************************
    m_ctl->ia                       =   *m_ia;
    m_ctl->ib                       =   *m_ib;
    m_ctl->ic                       =   *m_ic;

    m_ctl->phim                     =   *m_phim;
    m_ctl->phie                     =   m_ctl->phim * m_ctl->prm.mot_PPN;
//*****************************************************************************************************************************
    return  TRUE;
}

int16   KpiSetCurrLoopOut(CURR_CTL * m_ctl, double * m_ua, double * m_ub, double * m_uc)
{
//*****************************************************************************************************************************
    *m_ua                           =   m_ctl->ua;
    *m_ub                           =   m_ctl->ub;
    *m_uc                           =   m_ctl->uc;
//*****************************************************************************************************************************
    return  TRUE;
}


int16 KpiCurrCtlLoopUpdate(CURR_CTL * m_ctl)
{
    double dtmp;
//**************************************************************************************************************************
    m_ctl->id                       =   0.66666667*(m_ctl->ia * cos(m_ctl->phie) +\
                                                    m_ctl->ib * cos(m_ctl->phie - 2.094395) +\
                                                    m_ctl->ic * cos(m_ctl->phie + 2.094395));

    m_ctl->iq                       =   -0.66666667*(m_ctl->ia * sin(m_ctl->phie) +\
                                                    m_ctl->ib * sin(m_ctl->phie - 2.094395) +\
                                                    m_ctl->ic * sin(m_ctl->phie + 2.094395));
//**************************************************************************************************************************
    m_ctl->id_err                   =   m_ctl->id_ref    -   m_ctl->id;

    m_ctl->id_s                     =   m_ctl->id_err * m_ctl->kpd;

    dtmp                            =   m_ctl->idi_s     +   m_ctl->id_err * m_ctl->kid;
    m_ctl->idi_s                    =   IQSatLimit(dtmp, m_ctl->di_ulim, m_ctl->di_llim);

    dtmp                            =   m_ctl->id_s + m_ctl->idi_s;
    m_ctl->ud                       =   IQSatLimit(dtmp, m_ctl->do_ulim, m_ctl->do_llim);
//**************************************************************************************************************************
    m_ctl->iq_err                   =   m_ctl->iq_ref    -   m_ctl->iq;

    m_ctl->iq_s                     =   m_ctl->iq_err * m_ctl->kpq;

    dtmp                            =   m_ctl->iqi_s     +   m_ctl->iq_err * m_ctl->kiq;
    m_ctl->iqi_s                    =   IQSatLimit(dtmp, m_ctl->qi_ulim, m_ctl->qi_llim);

    dtmp                            =   m_ctl->iq_s + m_ctl->iqi_s;
    m_ctl->uq                       =   IQSatLimit(dtmp, m_ctl->qo_ulim, m_ctl->qo_llim);
//**************************************************************************************************************************
    m_ctl->ua                       =   m_ctl->ud * cos(m_ctl->phie) - m_ctl->uq * sin(m_ctl->phie);
    m_ctl->ub                       =   m_ctl->ud * cos(m_ctl->phie - 2.094395) - m_ctl->uq * sin(m_ctl->phie - 2.094395);
    m_ctl->uc                       =   -m_ctl->ua - m_ctl->ub;
//**************************************************************************************************************************
    return  TRUE;
}


int16   KpiGetUdUqVoltageRef(CURR_CTL * m_ctl, double * m_udr, double * m_uqr)
{
//**************************************************************************************************************************
    m_ctl->ud_ref                   =   *m_udr;
    m_ctl->uq_ref                   =   *m_uqr;
//**************************************************************************************************************************
    return  TRUE;
}



int16   KpiCurrOpenLoopUpdate(CURR_CTL * m_ctl)
{
//**************************************************************************************************************************
    m_ctl->id                       =   0.66666667*(m_ctl->ia * cos(m_ctl->phie) +\
                                                    m_ctl->ib * cos(m_ctl->phie - 2.094395) +\
                                                    m_ctl->ic * cos(m_ctl->phie + 2.094395));

    m_ctl->iq                       =   -0.66666667*(m_ctl->ia * sin(m_ctl->phie) +\
                                                    m_ctl->ib * sin(m_ctl->phie - 2.094395) +\
                                                    m_ctl->ic * sin(m_ctl->phie + 2.094395));
//**************************************************************************************************************************
    m_ctl->ua                       =   m_ctl->ud_ref * cos(m_ctl->phie) - m_ctl->uq_ref * sin(m_ctl->phie);
    m_ctl->ub                       =   m_ctl->ud_ref * cos(m_ctl->phie - 2.094395) - m_ctl->uq_ref * sin(m_ctl->phie - 2.094395);
    m_ctl->uc                       =   -m_ctl->ua - m_ctl->ub;
//**************************************************************************************************************************
    return  TRUE;
}




////////////////////////////////////////////////////////// no more /////////////////////////////////////////////////////////











