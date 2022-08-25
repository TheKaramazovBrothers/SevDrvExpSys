//=========================================================================================================
// project		:	servo system task manage and scheduling
// File			:	SevDrvTask.C
// discription	:	use in servo system task scheduling
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g
// date			:	2022/07/14
// copyright(C)	:	googoltech	(2022-2032)
//=========================================================================================================
#include	"MechModel.h"
#include    "BackGroundTask.h"

#include    "SevHardRes.h"



int16   HalGetCurrSensorValue(double * m_ia, double * m_ib, double * m_ic)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    gMechModel.OutputThreeCurrent(m_ia, m_ib, m_ic);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}

int16   HalGetAbsPosValue(double * m_posm, double * m_posl)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    gMechModel.OutputMechPos(m_posm, m_posl);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}


int16   HalSetThreePhaVoltage(double * m_ua, double * m_ub, double * m_uc)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    gMechModel.InputThreePhaVoltage(m_ua, m_ub, m_uc);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}


int16   HalEnableThreePwmOutput()
{
    double  m_ua  =   0.0;
    double  m_ub  =   0.0;
    double  m_uc  =   0.0;

    gMechModel.InputThreePhaVoltage(&m_ua, &m_ub, &m_uc);

    return  TRUE;
}

int16   HalDisableThreePwmOutput()
{
    double  m_ua  =   0.0;
    double  m_ub  =   0.0;
    double  m_uc  =   0.0;

    gMechModel.InputThreePhaVoltage(&m_ua, &m_ub, &m_uc);

    return  TRUE;
}





///////////////////////////////////////////////// no more //////////////////////////////////////////////
