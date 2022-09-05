//=========================================================================================================
// project		:	servo system measure
// File			:	SevDrvMeas.C
// discription	:	use in servo system task scheduling
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g
// date			:	2022/07/14
// copyright(C)	:	googoltech	(2022-2032)
//=========================================================================================================
#include    "SeqCtlFunc.h"
#include    "SevDrvObj.h"



int16   TpiInitServoObjModule(SERVO_OBJ * m_obj)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    KpiInitCurrCtlModule(&m_obj->cur);
    KpiInitSensMeasModule(&m_obj->sens);
    KpiInitSeqCtlModule(&m_obj->seq);
    KpiInitVelLoopModule(&m_obj->vel);
    KpiInitPosLoopModule(&m_obj->pos);
    KpiInitPosTrajProdModule(&m_obj->ptrj);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}












/////////////////////////////////////////////////// no more //////////////////////////////////////////////
