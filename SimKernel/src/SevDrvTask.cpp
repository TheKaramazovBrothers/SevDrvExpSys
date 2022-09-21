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
#include    "Cia402AppEmu.h"
#include    "SevHardRes.h"
#include	"SevDrvTask.h"

//*********************************************************************************************************
//*                                             INITIALIZATION
//*
//* Description: This function is used to initialize the multiple axis servo system
//*              
//*
//* Arguments  : m_drv		is a pointer to servo system driver system
//*
//* Returns    : -1/initialize Failure, else/success
//*********************************************************************************************************
int16		KpiInitServoDriverSys(SERVO_DRV * m_drv)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    TpiInitServoTask(&m_drv->task);
    TpiInitServoObjModule(&m_drv->obj);

    CpiInitCiA402PrmObjPtr();
    CpiInitCiA402VarObjPtr();
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	return	TRUE;
}


//*********************************************************************************************************
//*                                           SERVO SYSTEM TASK CALL
//*
//* Description: This function is used to do acceleration control interrupt task call in the multiple axis
//*				 servo system
//*
//*
//* Arguments  : m_drv		is a pointer to servo system driver system
//*
//* Returns    : -1/call Failure, else/success
//*********************************************************************************************************
void		KpiServoTaskCallOne(SERVO_DRV * m_drv)
{
    m_drv->task.TaskLut[1][(int16)(m_drv->task.curr_id)](m_drv);
}

//*********************************************************************************************************
//*                                           SERVO SYSTEM TASK CALL
//*
//* Description: This function is used to do position and velocity control interrupt task call in the
//*				 multiple axis servo system
//*
//*
//* Arguments  : m_drv		is a pointer to servo system driver system
//*
//* Returns    : -1/call Failure, else/success
//*********************************************************************************************************
void		KpiServoTaskCallTwo(SERVO_DRV * m_drv)
{
    m_drv->task.TaskLut[2][(int16)(m_drv->task.curr_id)](m_drv);
}

//*********************************************************************************************************
//*                                           SERVO SYSTEM TASK CALL
//*
//* Description: This function is used to do servo system sensor signal process in the multiple axis servo 
//*              system
//*              
//*
//* Arguments  : m_drv		is a pointer to servo system driver system
//*
//* Returns    : -1/call Failure, else/success
//*********************************************************************************************************
int16	KpiServoSensorSignalPro(SERVO_DRV * m_drv)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    KpiGetCurrSensorValue(&m_drv->obj.sens);
    KpiGetEncValue(&m_drv->obj.sens);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	return	TRUE;
}

//*********************************************************************************************************
//*                                           SERVO SYSTEM TASK CALL
//*
//* Description: This function is used to do servo system sensor signal process in the multiple axis servo 
//*              system
//*              
//*
//* Arguments  : m_drv		is a pointer to servo system driver system
//*
//* Returns    : -1/call Failure, else/success
//*********************************************************************************************************
int16	KpiServoAlarmPowerManage(SERVO_DRV * m_drv)
{
    return  TRUE;
}

//*********************************************************************************************************
//*                                     SERVO SYSTEM BACK GROUND TASK CALL
//*
//* Description: This function is used to do servo system back ground task in the multiple axis servo 
//*              system
//*              
//*
//* Arguments  : m_drv		is a pointer to servo system driver system
//*
//* Returns    : -1/call Failure, else/success
//*********************************************************************************************************
int16	KpiServoBackGroundTask(SERVO_DRV * m_drv)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    KpiSeqBackGroundRout(&m_drv->obj.seq, m_drv);

    TpiServoModeSwitch(m_drv);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}

//*********************************************************************************************************
//*                                          Servo system task manage
//*
//* Description: This function is used to  initialize the servo task.
//*
//* Arguments  : m_task     is a pointer to the servo task object
//*
//*
//* Returns    : -1/initialize failure, else/success
//*******************************************************************************************************
int16	TpiInitServoTask(SERVO_TASK * m_task)
{
    m_task->act_on                      =   FALSE;                                              // TRUE/active command on, FALSE/active command off
    m_task->sec_on                      =   FALSE;                                              // TRUE/Drive no alarm, FALSE/Drive have alarm
    m_task->sof_st_on                   =   FALSE;                                              // TRUE/power soft start ok, FALSE/no
    m_task->serv_ready                  =   FALSE;                                              // TRUE/Servo ready to run ,serv_ready = (act_on && sec_on && sof_st_on)

    m_task->curr_id                     =   IDLE;                                               // The ID of the currently running task
    m_task->cmd_id                      =   COLD;                                               // The ID of the Target running task
    m_task->curr_state                  =   OFF;                                                // current state of servo system
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_task->TaskLut[0][IDLE_TASK_ID]	=	(tpfOneVoidPt)TpiInitIdleRoutine;
    m_task->TaskLut[1][IDLE_TASK_ID]	=	(tpfOneVoidPt)TpiIdleRoutine;
    m_task->TaskLut[2][IDLE_TASK_ID]	=	(tpfOneVoidPt)TpiIdleRoutineIsr2;

    m_task->TaskLut[0][AOA_TASK_ID]		=	(tpfOneVoidPt)TpiInitAdcOfstAdj;
    m_task->TaskLut[1][AOA_TASK_ID]		=	(tpfOneVoidPt)TpiAdcOfstAdj;
    m_task->TaskLut[2][AOA_TASK_ID]		=	(tpfOneVoidPt)TpiIdleRoutineIsr2;

    m_task->TaskLut[0][MIPA_TASK_ID]	=	(tpfOneVoidPt)TpiInitMotorInitPosAdj;
    m_task->TaskLut[1][MIPA_TASK_ID]	=	(tpfOneVoidPt)TpiMotorInitPosAdj;
    m_task->TaskLut[2][MIPA_TASK_ID]	=	(tpfOneVoidPt)TpiIdleRoutineIsr2;

    m_task->TaskLut[0][MPSA_TASK_ID]	=	(tpfOneVoidPt)TpiInitMotorParaSelfAcq;
    m_task->TaskLut[1][MPSA_TASK_ID]	=	(tpfOneVoidPt)TpiMotorParaSelfAcq;
    m_task->TaskLut[2][MPSA_TASK_ID]	=	(tpfOneVoidPt)TpiMotorParaSelfAcqIsr2;

    m_task->TaskLut[0][COLD_TASK_ID]	=	(tpfOneVoidPt)TpiInitCurrOpenLoopDrv;
    m_task->TaskLut[1][COLD_TASK_ID]	=	(tpfOneVoidPt)TpiCurrOpenLoopDrv;
    m_task->TaskLut[2][COLD_TASK_ID]	=	(tpfOneVoidPt)TpiIdleRoutineIsr2;

    m_task->TaskLut[0][CCLD_TASK_ID]	=	(tpfOneVoidPt)TpiInitCurrCloseLoopDrv;
    m_task->TaskLut[1][CCLD_TASK_ID]	=	(tpfOneVoidPt)TpiCurrCloseLoopDrv;
    m_task->TaskLut[2][CCLD_TASK_ID]	=	(tpfOneVoidPt)TpiCurrCloseLoopDrvIsr2;

    m_task->TaskLut[0][VCLD_TASK_ID]	=	(tpfOneVoidPt)TpiInitVelCloseLoopDrv;
    m_task->TaskLut[1][VCLD_TASK_ID]	=	(tpfOneVoidPt)TpiVelCloseLoopDrv;
    m_task->TaskLut[2][VCLD_TASK_ID]	=	(tpfOneVoidPt)TpiVelCloseLoopDrvIsr2;

    m_task->TaskLut[0][POSCLD_TASK_ID]	=	(tpfOneVoidPt)TpiInitPosCloseLoopDrv;
    m_task->TaskLut[1][POSCLD_TASK_ID]	=	(tpfOneVoidPt)TpiPosCloseLoopDrv;
    m_task->TaskLut[2][POSCLD_TASK_ID]	=	(tpfOneVoidPt)TpiPosCloseLoopDrvIsr2;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return	TRUE;
}


//*********************************************************************************************************
//*                                          Servo system mode switch
//*
//* Description: This function is used to  manage the execution of a servo task. 
//*
//* Arguments  : m_drv     is a pointer to the servo manage object
//*
//*
//* Returns    : -1/switch failure, else/success       
//*******************************************************************************************************
int16 TpiServoModeSwitch(SERVO_DRV * m_drv)
{
    tTaskId curr_id_tmp;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_drv->task.serv_ready          =	m_drv->task.sof_st_on && m_drv->task.sec_on && m_drv->task.act_on;

    m_drv->task.serv_ready          =   m_drv->task.act_on;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    switch	(m_drv->task.curr_state)
	{
	case	OFF:
		{
            if ((m_drv->task.cmd_id != IDLE) && (m_drv->task.serv_ready == TRUE))
			{
                m_drv->task.curr_state	=	INIT;
			}

			break;
		}
	case	INIT:
		{
            if (m_drv->task.serv_ready == TRUE)
            {
                m_drv->task.TaskLut[0][(int16)(m_drv->task.cmd_id)](m_drv);                         // target ID task variable initialization

                m_drv->task.curr_id		=	m_drv->task.cmd_id;
                m_drv->task.curr_state	=	ON;
                HalEnableThreePwmOutput();
			}
			else
			{
                m_drv->task.curr_state	=	OFF;
			}

			break;
		}
	case	ON:
		{
            if (m_drv->task.serv_ready != TRUE || (m_drv->task.cmd_id != m_drv->task.curr_id))
			{				
                curr_id_tmp             =   m_drv->task.curr_id;
                m_drv->task.curr_id		=	IDLE;

                if (curr_id_tmp != MIPA)
				{
                     m_drv->task.TaskLut[0][(int16)(curr_id_tmp)](m_drv);
				}
                                                                                            // current ID variable reset when stop
                m_drv->task.curr_state	=	OFF;
                HalDisableThreePwmOutput();
			}
			break;
		}
	default:	
		{
            m_drv->task.curr_state	=	OFF;
            m_drv->task.curr_id		=	IDLE;

			break;
		}
	}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	return	TRUE;
}




//*********************************************************************************************************
//*                                 Servo system idle task Routine
//*
//* Description: This function is used to  manage the execution of a servo task. 
//*
//* Arguments  : m_drv     is a pointer to the servo task manage object
//*
//*
//* Returns    : none      
//********************************************************************************************************
void	TpiIdleRoutine(SERVO_DRV * m_drv)                                                   // idle task routine
{        
    m_drv->task.idle_cnt++;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

}
void	TpiIdleRoutineIsr2(SERVO_DRV * m_drv)                                               // idle task routine task 2
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

}

void	TpiInitIdleRoutine(SERVO_DRV * m_drv)                                               // initialize idle task routine
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_drv->task.idle_cnt	=	0;
}


//*********************************************************************************************************
//*                                 Servo system AOA task Routine
//*
//* Description: This function is used to  manage the execution of a servo task. 
//*
//* Arguments  : m_drv     is a pointer to the servo task manage object
//*
//*
//* Returns    : none      
//********************************************************************************************************
void	TpiAdcOfstAdj(SERVO_DRV * m_drv)                                                    // AOA task routine
{	
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

void	TpiInitAdcOfstAdj(SERVO_DRV * m_drv)                                                // initialize AOS task
{	
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


//*********************************************************************************************************
//*                                 Servo system MIPA task Routine
//*
//* Description: This function is used to  motor initialize position adjust
//*
//* Arguments  : m_drv     is a pointer to the servo task manage object
//*
//*
//* Returns    : none      
//********************************************************************************************************
void	TpiMotorInitPosAdj(SERVO_DRV * m_drv)                                               // MIPA task routine
{	
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

}
void	TpiInitMotorInitPosAdj(SERVO_DRV * m_drv)                                           // initialize MIPA task
{	
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


//********************************************************************************************************
//*                                 Servo system MPSA task Routine
//*
//* Description: This function is used to  motor phase sequence adjust
//*
//* Arguments  : m_drv     is a pointer to the servo task manage object
//*
//*
//* Returns    : none      
//********************************************************************************************************
void	TpiMotorParaSelfAcq(SERVO_DRV * m_drv)                                              // MPSA task routine
{	
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

void	TpiMotorParaSelfAcqIsr2(SERVO_DRV * m_drv)                                          // MPSA task routine 2
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

void	TpiInitMotorParaSelfAcq(SERVO_DRV * m_drv)                                          // initialize MPSA task routine
{	
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


//********************************************************************************************************
//*                                 Servo system COLD task Routine
//*
//* Description: This function is used to  motor open loop drive
//*
//* Arguments  : m_drv     is a pointer to the servo system task manage object
//*
//*
//* Returns    : none      
//********************************************************************************************************
void	TpiCurrOpenLoopDrv(SERVO_DRV * m_drv)                                               // COLD task routine
{
    double  udr_tmp, uqr_tmp;
    double  ua_tmp, ub_tmp, uc_tmp;

    udr_tmp     =   m_drv->obj.seq.udr_out;
    uqr_tmp     =   m_drv->obj.seq.uqr_out;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    KpiGetCurrLoopFb(&m_drv->obj.cur, &m_drv->obj.sens.ia, &m_drv->obj.sens.ib, &m_drv->obj.sens.ic, &m_drv->obj.sens.phim);

    KpiGetUdUqVoltageRef(&m_drv->obj.cur, &udr_tmp, &uqr_tmp);

    KpiCurrOpenLoopUpdate(&m_drv->obj.cur);

    KpiSetCurrLoopOut(&m_drv->obj.cur, &ua_tmp, &ub_tmp, &uc_tmp);

    KpiThreeVoltageOutput(&ua_tmp, &ub_tmp, &uc_tmp);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

void	TpiInitCurrOpenLoopDrv(SERVO_DRV * m_drv)                                           // initialize COLD task routine
{
    KpiInitCurrCtlVar(&m_drv->obj.cur);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

//********************************************************************************************************
//*                                 Servo system CCLD task Routine
//*
//* Description: This function is used to  motor current close loop drive
//*
//* Arguments  : m_drv     is a pointer to the servo system task manage object
//*
//*
//* Returns    : none      
//********************************************************************************************************
void	TpiCurrCloseLoopDrv(SERVO_DRV * m_drv)                                              // CCLD task routine
{
    double  idr_tmp, iqr_tmp;
    double  ua_tmp, ub_tmp, uc_tmp;

    idr_tmp     =   m_drv->obj.seq.idr_out;
    iqr_tmp     =   m_drv->obj.seq.iqr_out;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    KpiGetCurrLoopFb(&m_drv->obj.cur, &m_drv->obj.sens.ia, &m_drv->obj.sens.ib, &m_drv->obj.sens.ic, &m_drv->obj.sens.phim);

    KpiGetCurrLootRef(&m_drv->obj.cur, &idr_tmp, &iqr_tmp);

    KpiCurrCtlLoopUpdate(&m_drv->obj.cur);

    KpiSetCurrLoopOut(&m_drv->obj.cur, &ua_tmp, &ub_tmp, &uc_tmp);

    KpiThreeVoltageOutput(&ua_tmp, &ub_tmp, &uc_tmp);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void	TpiCurrCloseLoopDrvIsr2(SERVO_DRV * m_drv)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void	TpiInitCurrCloseLoopDrv(SERVO_DRV * m_drv)                                          // initialize CCLD task routine
{	
    KpiInitCurrCtlVar(&m_drv->obj.cur);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


//********************************************************************************************************
//*                                 Servo system VCLD task Routine
//*
//* Description: This function is used to  motor Velocity close loop drive
//*
//* Arguments  : m_drv     is a pointer to the servo system task manage object
//*
//*
//* Returns    : none      
//********************************************************************************************************
void	TpiVelCloseLoopDrv(SERVO_DRV * m_drv)                                               // VCLD task routine
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    double  idr_tmp, iqr_tmp;
    double  ua_tmp, ub_tmp, uc_tmp;

    idr_tmp     =   0;
    iqr_tmp     =   m_drv->obj.vel.iqr;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    KpiGetCurrLoopFb(&m_drv->obj.cur, &m_drv->obj.sens.ia, &m_drv->obj.sens.ib, &m_drv->obj.sens.ic, &m_drv->obj.sens.phim);

    KpiGetCurrLootRef(&m_drv->obj.cur, &idr_tmp, &iqr_tmp);

    KpiCurrCtlLoopUpdate(&m_drv->obj.cur);

    KpiSetCurrLoopOut(&m_drv->obj.cur, &ua_tmp, &ub_tmp, &uc_tmp);

    KpiThreeVoltageOutput(&ua_tmp, &ub_tmp, &uc_tmp);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

void	TpiVelCloseLoopDrvIsr2(SERVO_DRV * m_drv)                                           // VCLD task routine 2
{
    double  spdr_tmp, spdf_tmp, tqrp_tmp;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    spdr_tmp            =   m_drv->obj.seq.spdr_out;
    spdf_tmp            =   m_drv->obj.sens.mot_spd;
    tqrp_tmp            =   0;

    m_drv->obj.vel.prm.cfg_opt.bit.RAMP = FALSE;
    KpiVelCloseLoopCtrl(&m_drv->obj.vel, &spdr_tmp, &spdf_tmp, &tqrp_tmp);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

void	TpiInitVelCloseLoopDrv(SERVO_DRV * m_drv)                                           // initialize VCLD task routine
{
    KpiInitCurrCtlVar(&m_drv->obj.cur);
    KpiInitVelLoopVar(&m_drv->obj.vel);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}



//********************************************************************************************************
//*                                 Servo system POSCLD task Routine
//*
//* Description: This function is used to  motor position close loop drive
//*
//* Arguments  : m_drv     is a pointer to the servo system task manage object
//*
//*
//* Returns    : none      
//********************************************************************************************************
void	TpiPosCloseLoopDrv(SERVO_DRV * m_drv)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    double  idr_tmp, iqr_tmp;
    double  ua_tmp, ub_tmp, uc_tmp;

    idr_tmp     =   0;
    iqr_tmp     =   m_drv->obj.seq.iqr_out;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    KpiGetCurrLoopFb(&m_drv->obj.cur, &m_drv->obj.sens.ia, &m_drv->obj.sens.ib, &m_drv->obj.sens.ic, &m_drv->obj.sens.phim);

    KpiGetCurrLootRef(&m_drv->obj.cur, &idr_tmp, &iqr_tmp);

    KpiCurrCtlLoopUpdate(&m_drv->obj.cur);

    KpiSetCurrLoopOut(&m_drv->obj.cur, &ua_tmp, &ub_tmp, &uc_tmp);

    KpiThreeVoltageOutput(&ua_tmp, &ub_tmp, &uc_tmp);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}	

void	TpiPosCloseLoopDrvIsr2(SERVO_DRV * m_drv)                                           // POSCLD task routine 2
{
    double  spdr_tmp, spdf_tmp, tqrp_tmp;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    KpiSeqServoCtlIsr(&m_drv->obj.seq, m_drv);

    switch (m_drv->obj.seq.prm.pov_mode)
    {
    case    POS_CTL_POSCLD:
        {
            KpiPosCloseLoopCtl(&m_drv->obj.pos, &m_drv->obj.seq.dpcmd_out);

            spdr_tmp                    =   m_drv->obj.pos.spdr;
            spdf_tmp                    =   m_drv->obj.sens.mot_spd;

            tqrp_tmp                    =   m_drv->obj.pos.tqrp;

            m_drv->obj.vel.prm.cfg_opt.bit.RAMP         = TRUE;
            KpiVelCloseLoopCtrl(&m_drv->obj.vel, &spdr_tmp, &spdf_tmp, &tqrp_tmp);
            m_drv->obj.seq.iqr_out                      =   m_drv->obj.vel.iqr;
            break;
        }
    case    VEL_CTL_POSCLD:
        {
            spdr_tmp                        =   m_drv->obj.seq.spdr_out;
            spdf_tmp                        =   m_drv->obj.sens.mot_spd;
            tqrp_tmp                        =   0;

            m_drv->obj.vel.prm.cfg_opt.bit.RAMP         = m_drv->obj.seq.prm.cfg_opt.bit.VRAMP;
            KpiVelCloseLoopCtrl(&m_drv->obj.vel, &spdr_tmp, &spdf_tmp, &tqrp_tmp);
            m_drv->obj.seq.iqr_out                      =   m_drv->obj.vel.iqr;
            break;
        }
    case    CURR_CTL_POSCLD:
        {
            break;
        }
    default:
        {
            m_drv->obj.seq.iqr_out          =   0;
            m_drv->obj.seq.idr_out          =   0;
            break;
        }
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

}

void	TpiInitPosCloseLoopDrv(SERVO_DRV * m_drv)
{
    KpiInitCurrCtlVar(&m_drv->obj.cur);
    KpiInitVelLoopVar(&m_drv->obj.vel);
    KpiInitPosLoopVar(&m_drv->obj.pos);
    KpiInitExciSigProdVar(&m_drv->obj.excs);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

}




////////////////////////////////////////////// no more //////////////////////////////////////////////////
