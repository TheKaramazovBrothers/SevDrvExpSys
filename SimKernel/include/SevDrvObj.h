//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	Servo system object define                      			//
//	file				:	SevDrvObj.h                                                 //
//	Description			:	use for SERVO system tasks Task allocation					//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:           |	Corporation:	|		copyright(C):	//
//--------------------------------------------------------------------------------------//
//		liu.g(1487)		|	2022/7/14       |	liu.g           |		2022 - 2032		//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SEVDRVOBJ_H__
#define __SEVDRVOBJ_H__

#include "DspCpu.h"
#include "CurrCtlLoop.h"
#include "VelCtlLoop.h"
#include "PosCtlLoop.h"
#include "SevDrvMeas.h"
#include "SeqCtlFunc.h"
#include "PosTrajProd.h"

typedef		struct	servo_obj
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// servo object variable define
    CURR_CTL        cur;                                                        // current layer control object
    SENS_MEAS       sens;                                                       // sensor module
    SEQ_CTL         seq;                                                        // sequence control
    VEL_CTL         vel;                                                        // velocity control module
    POS_CTL         pos;                                                        // position control module
    POS_TRAJ        ptrj;                                                       // position trajectory maker
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}SERVO_OBJ;


int16   TpiInitServoObjModule(SERVO_OBJ * m_obj);


#endif


///////////////////////////////////////////////// no more /////////////////////////////////////////////
