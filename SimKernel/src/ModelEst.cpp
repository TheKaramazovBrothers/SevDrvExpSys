//=========================================================================================================
// project		:	servo system model estimate
// File			:	ModelEst.cpp
// discription	:	use in servo system mechanical model estimate
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g
// date			:	2022/11/10
// copyright(C)	:	liu.g	(2022-2032)
//=========================================================================================================
#include "Cia402AppEmu.h"
#include "SevCtlPrmTblDef.h"
#include "ModelEst.h"


//*********************************************************************************************************
//*                                   MODEL ESTIMATE MODULE INITIALIZATION
//*
//* Description: This function is used to initialize model estimate module in servo system
//*
//*
//* Arguments  : m_ctl		is a pointer to servo system mechanical model estimate object
//*
//* Returns    : -1/initialize Failure, else/success
//*********************************************************************************************************
int16	KpiInitModIdfModule(MOD_IDF * m_idf)
{
//**************************************************************************************************************************
    if (SEV_PRM_FROM_EX_MEM_EN == DISABLE)
    {
        m_idf->prm.cfg_opt.all                  =   0;
        m_idf->prm.ts                           =   62500;

        m_idf->prm.j0                           =   28;
        m_idf->prm.p0                           =   1000;
        m_idf->prm.lamt                         =   32767;
    }
//**************************************************************************************************************************
    m_idf->prm.a0                       =   -4096.0;
    m_idf->prm.b0                       =   (((double)(m_idf->prm.ts)/(double)(m_idf->prm.j0))*4096.0)/1000.0;
//**************************************************************************************************************************
    m_idf->lambda                       =   m_idf->prm.lamt/16777216.0;
//**************************************************************************************************************************
    m_idf->c0x[0]                       =   m_idf->prm.a0/4096.0;
    m_idf->c0x[1]                       =   m_idf->prm.b0/4096.0;

    m_idf->c1x[0]                       =   m_idf->c0x[0];
    m_idf->c1x[1]                       =   m_idf->c0x[1];

    m_idf->p0x[0][0]                    =   m_idf->prm.p0;
    m_idf->p0x[1][1]                    =   m_idf->prm.p0;
    m_idf->p0x[0][1]                    =   0;
    m_idf->p0x[1][0]                    =   0;

    m_idf->p1x[0][0]                    =   m_idf->p0x[0][0];
    m_idf->p1x[0][1]                    =   m_idf->p0x[0][1];
    m_idf->p1x[1][0]                    =   m_idf->p0x[1][0];
    m_idf->p1x[1][1]                    =   m_idf->p0x[1][1];

    m_idf->phi0x[0]                     =   0;
    m_idf->phi0x[1]                     =   0;
    m_idf->phi1x[0]                     =   0;
    m_idf->phi1x[1]                     =   0;

    m_idf->Gamma[0]                     =   0;
    m_idf->Gamma[1]                     =   0;

    m_idf->err_est                      =   0;

    m_idf->wm                           =   0;
    m_idf->tqr                          =   0;
    m_idf->Jest                         =   0;
    m_idf->Dest                         =   0;

    m_idf->Junit                        =   0;
//**************************************************************************************************************************
    return  TRUE;
}



//*********************************************************************************************************
//*                                   MODEL ESTIMATE MODULE INITIALIZATION
//*
//* Description: This function is used to initialize model estimate variable in servo system
//*
//*
//* Arguments  : m_ctl		is a pointer to servo system mechanical model estimate variable
//*
//* Returns    : -1/initialize Failure, else/success
//*********************************************************************************************************
int16	KpiInitModeIdfVar(MOD_IDF * m_idf)
{
//**************************************************************************************************************************
    m_idf->c0x[0]                       =   m_idf->prm.a0/4096.0;
    m_idf->c0x[1]                       =   m_idf->prm.b0/4096.0;

    m_idf->c1x[0]                       =   m_idf->c0x[0];
    m_idf->c1x[1]                       =   m_idf->c0x[1];

    m_idf->p0x[0][0]                    =   m_idf->prm.p0;
    m_idf->p0x[1][1]                    =   m_idf->prm.p0;
    m_idf->p0x[0][1]                    =   0;
    m_idf->p0x[1][0]                    =   0;

    m_idf->p1x[0][0]                    =   m_idf->p0x[0][0];
    m_idf->p1x[0][1]                    =   m_idf->p0x[0][1];
    m_idf->p1x[1][0]                    =   m_idf->p0x[1][0];
    m_idf->p1x[1][1]                    =   m_idf->p0x[1][1];

    m_idf->phi0x[0]                     =   0;
    m_idf->phi0x[1]                     =   0;
    m_idf->phi1x[0]                     =   0;
    m_idf->phi1x[1]                     =   0;

    m_idf->err_est                      =   0;

    m_idf->Gamma[0]                     =   0;
    m_idf->Gamma[1]                     =   0;

    m_idf->wm                           =   0;
    m_idf->tqr                          =   0;
    m_idf->Jest                         =   0;
    m_idf->Dest                         =   0;

    m_idf->Junit                        =   0;
//**************************************************************************************************************************
    return  TRUE;
}



//*********************************************************************************************************
//*                                   MODEL ESTIMATE USE RLS ALGORITHM
//*
//* Description: This function is used to do model estimate algorithm in servo system
//*
//*
//* Arguments  : m_idf		is a pointer to servo system mechanical model estimate algorithm
//*              m_spdf     is a pointer to servo system speed feedback
//*              m_tqr      is a pointer to servo system torque output
//*
//* Returns    : -1/call Failure, else/success
//*********************************************************************************************************
int16	KpiRLSMotJmDmEst(MOD_IDF * m_idf,  double * m_spdf, double * m_tqr)
{
    double  dtmp, i1, i2, j;
//**************************************************************************************************************************
    m_idf->phi0x[0]                     =   -m_idf->wm;
    m_idf->phi0x[1]                     =   m_idf->tqr;

    m_idf->wm                           =   *m_spdf;
    m_idf->tqr                          =   *m_tqr;

    dtmp                                =   (m_idf->phi0x[0] * m_idf->c0x[0] + m_idf->phi0x[1] * m_idf->c0x[1]);
    m_idf->err_est                      =   m_idf->wm - dtmp;
    m_idf->c1x[0]                       =   m_idf->c0x[0] + m_idf->Gamma[0] * m_idf->err_est;
    m_idf->c1x[1]                       =   m_idf->c0x[1] + m_idf->Gamma[1] * m_idf->err_est;

    m_idf->phi1x[0]                     =   -m_idf->wm;
    m_idf->phi1x[1]                     =   m_idf->tqr;

    i1                                  =   m_idf->p0x[0][0] * m_idf->phi1x[0] + m_idf->p0x[0][1] * m_idf->phi1x[1];
    i2                                  =   m_idf->p0x[1][0] * m_idf->phi1x[0] + m_idf->p0x[1][1] * m_idf->phi1x[1];

    j                                   =   m_idf->phi1x[0] * i1 + m_idf->phi1x[1] * i2;

    m_idf->Gamma[0]                     =   i1/(j+m_idf->lambda);
    m_idf->Gamma[1]                     =   i2/(j+m_idf->lambda);

    m_idf->p1x[0][0]                    =   (m_idf->p0x[0][0] - m_idf->Gamma[0]*i1)/m_idf->lambda;
    m_idf->p1x[0][1]                    =   (m_idf->p0x[0][1] - m_idf->Gamma[0]*i2)/m_idf->lambda;
    m_idf->p1x[1][0]                    =   (m_idf->p0x[1][0] - m_idf->Gamma[1]*i1)/m_idf->lambda;
    m_idf->p1x[1][1]                    =   (m_idf->p0x[1][1] - m_idf->Gamma[1]*i2)/m_idf->lambda;

    m_idf->p0x[0][0]                    =   m_idf->p1x[0][0];
    m_idf->p0x[0][1]                    =   m_idf->p1x[0][1];
    m_idf->p0x[1][0]                    =   m_idf->p1x[1][0];
    m_idf->p0x[1][1]                    =   m_idf->p1x[1][1];

    m_idf->c0x[0]                       =   m_idf->c1x[0];
    m_idf->c0x[1]                       =   m_idf->c1x[1];
//**************************************************************************************************************************
    m_idf->Jest                         =   -(m_idf->c0x[0]/m_idf->c0x[1])*(m_idf->prm.ts/1000000000.0);
    m_idf->Junit                        =   m_idf->Jest * 1000000.0;
    m_idf->Dest                         =   (m_idf->c0x[0] + 1.0)/m_idf->c0x[1];
//**************************************************************************************************************************
    return  TRUE;

}




///////////////////////////////////////////////////////// no more ////////////////////////////////////////////////////////////
