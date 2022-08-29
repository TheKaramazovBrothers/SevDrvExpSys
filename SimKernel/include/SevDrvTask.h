//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	Servo system Tasks Classification and scheduling			//
//	file				:	SevDrvTask.h												//
//	Description			:	use for SERVO system tasks Task allocation					//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g(1487)		|	2022/7/14	|	liu.g           |		2022 - 2032			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef		__SEVDRVTASK_H__
#define		__SEVDRVTASK_H__


#include "DspCpu.h"
#include "SevDrvObj.h"

// servo driver dsp software version
#define		SERVO_DRV_SOFTWARE_VERSION				1								// main version of servo driver software
#define		SERVO_SOFTWARE_MINI_VERSION				0								// mini version of servo driver software
#define		SERVO_SOFTWARE_TINY_VERSION				8								// tiny version of servo driver software
//----------------------------------------------------------------------------------------



#define		SERVO_AXIS_NUM			1												// axis numbers of servo system

#define     EFFEC_SEV_AXIS_NUM      SERVO_AXIS_NUM
//----------------------------------------------------------------------------------------
#define		SERVO_MAX_TASKS			12												// max tasks of servo system

#define		IDLE_TASK_ID			0												// idle task ID
#define		AOA_TASK_ID				1												// adc offset adjust task ID
#define		MIPA_TASK_ID			2												// motor initialize phase adjust task ID
#define		MPSA_TASK_ID			3												// motor parameters self acquisition ID
#define		COLD_TASK_ID			4												// current open loop drive task ID
#define		CCLD_TASK_ID			5												// current closed loop drive task		
#define		VCLD_TASK_ID			6												// Velocity closed loop drive task
#define		POSCLD_TASK_ID			7												// position closed loop drive task

typedef	void (* tpfOneVoidPt)(void *);                                              // 1 pointer parameter function pointer
typedef	void (* tpfTwoVoidPt)(void *, void *);										// 2 pointer parameter function pointer
typedef	void (* tpfThrVoidPt)(void *, void *, void*);								// 3 pointer parameter function pointer


typedef enum
{
	OFF				=	1,
	INIT			=	2,
	ON				=	3,
	RES_SEV_SS		=	0x8000
}tServoState;																		// Servo state type define

typedef enum
{
	IDLE			=	0,															// TpiIdleRoutine()	----------> ID|0
	AOA				=	1,															// TpiAdcOfstAdj() -----------> ID|1
	MIPA			=	2,															// TpiMotorInitPosAdj() ------> ID|2
	MPSA			=	3,															// TpiMotorPhaSeqAdj()--------> ID|3
	COLD			=	4,															// TpiMotorPhaSeqAdj()--------> ID|4
	CCLD			=	5,															// TpiCurrCloseLoopDrv()------> ID|5
	VCLD			=	6,															// TpiVelCloseLoopDrv()-------> ID|6
	POSCLD			=	7,															// TpiPosCloseLoopDrv()-------> ID|7
    TaskIDMaxNum    =   8,                                                          // the max number of servo task
    RES_SEV_TASK	=	0x8000
}tTaskId;		


typedef struct	servo_task
{
// variable define
    int16			act_on;                                                         // TRUE/active command on, FALSE/active command off
    int16			sec_on;                                                         // TRUE/Drive no alarm, FALSE/Drive have alarm
    int16			sof_st_on;                                                      // TRUE/power soft start ok, FALSE/no
    int16			serv_ready;                                                     // TRUE/Servo ready to run ,serv_ready = (act_on && sec_on && sof_st_on)

    tTaskId			curr_id;                                                        // The ID of the currently running task
    tTaskId			cmd_id;                                                         // The ID of the Target running task
    tServoState		curr_state;                                                     // current state of servo system
//--------------------------------------------------------------------------------------
    int32           idle_cnt;                                                       // count variable for idle state
//------------------------------------------------------------------------------------------------------	
    tpfOneVoidPt	TaskLut[3][SERVO_MAX_TASKS];
//-------------------------------------------------------------------------------------------------------
}SERVO_TASK;


//-------------------------------------------------------------------------------------
//									GROBAL SERVO STRUCT
//-------------------------------------------------------------------------------------
typedef struct	servo_drv
{
    SERVO_TASK          task;
    SERVO_OBJ           obj;
}SERVO_DRV;


//-------------------------------------------------------------------------------------
//							 SERVO DRIVER FUNCTION DECLARE
//-------------------------------------------------------------------------------------
int16	KpiInitServoDriverSys(SERVO_DRV * m_drv);
int16	KpiServoMessageProcess(SERVO_DRV * m_drv);
int16	KpiServoSensorSignalPro(SERVO_DRV * m_drv);
int16	KpiServoAlarmPowerManage(SERVO_DRV * m_drv);
int16	KpiServoBackGroundTask(SERVO_DRV * m_drv);


extern  void    KpiServoTaskCallOne(SERVO_DRV * m_drv);
extern  void    KpiServoTaskCallTwo(SERVO_DRV * m_drv);


int16 TpiServoModeSwitch(SERVO_DRV * m_drv);


///////////////////////////////////////////////////////////////////////////////////////////////////////
int16	TpiInitServoTask(SERVO_TASK *m_task);                                       // Servo task object initialization
///////////////////////////////////////////////////////////////////////////////////////////////////////


//								SERVO TASK 0 function declare
//-------------------------------------------------------------------------------------
void	TpiIdleRoutine(SERVO_DRV * m_drv);                                          // idle task routine
void	TpiIdleRoutineIsr2(SERVO_DRV * m_drv);                                      // idle task routine task 2

void	TpiInitIdleRoutine(SERVO_DRV * m_drv);                                      // initialize idle task routine
//-------------------------------------------------------------------------------------
//								SERVO TASK 1 function declare
//-------------------------------------------------------------------------------------
void	TpiAdcOfstAdj(SERVO_DRV * m_drv);                                           // AOA task routine
void	TpiInitAdcOfstAdj(SERVO_DRV * m_drv);                                       // initialize AOS task
//-------------------------------------------------------------------------------------
//								SERVO TASK 2 function declare
//-------------------------------------------------------------------------------------
void	TpiMotorInitPosAdj(SERVO_DRV * m_drv);                                      // MIPA task routine
void	TpiInitMotorInitPosAdj(SERVO_DRV * m_drv);                                  // initialize MIPA task
//-------------------------------------------------------------------------------------
//								SERVO TASK 3 function declare
//-------------------------------------------------------------------------------------
void	TpiMotorParaSelfAcq(SERVO_DRV * m_drv);                                     // MPSA task routine
void	TpiMotorParaSelfAcqIsr2(SERVO_DRV * m_drv);                                 // MPSA task routine 2

void	TpiInitMotorParaSelfAcq(SERVO_DRV * m_drv);                                 // initialize MPSA task routine
//-------------------------------------------------------------------------------------
//								SERVO TASK 4 function declare
//-------------------------------------------------------------------------------------
void	TpiCurrOpenLoopDrv(SERVO_DRV * m_drv);                                      // COLD task routine
void	TpiInitCurrOpenLoopDrv(SERVO_DRV * m_drv);                                  // initialize COLD task routine
//-------------------------------------------------------------------------------------
//								SERVO TASK 5 function declare
//-------------------------------------------------------------------------------------
void	TpiCurrCloseLoopDrv(SERVO_DRV * m_drv);                                     // CCLD task routine
void	TpiCurrCloseLoopDrvIsr2(SERVO_DRV * m_drv);                                 // CCLD task routine

void	TpiInitCurrCloseLoopDrv(SERVO_DRV * m_drv);                                 // initialize CCLD task routine

//-------------------------------------------------------------------------------------
//								SERVO TASK 6 function declare
//-------------------------------------------------------------------------------------
void	TpiVelCloseLoopDrv(SERVO_DRV * m_drv);                                      // VCLD task routine
void	TpiVelCloseLoopDrvIsr2(SERVO_DRV * m_drv);                                  // VCLD task routine 2

void	TpiInitVelCloseLoopDrv(SERVO_DRV * m_drv);                                  // initialize VCLD task routine
	
//-------------------------------------------------------------------------------------
//								SERVO TASK 7 function declare
//-------------------------------------------------------------------------------------
void	TpiPosCloseLoopDrv(SERVO_DRV * m_drv);                                      // POSCLD task routine
void	TpiPosCloseLoopDrvIsr2(SERVO_DRV * m_drv);                                  // POSCLD task routine 2

void	TpiInitPosCloseLoopDrv(SERVO_DRV * m_drv);                                  // initialize POSCLD task routine



//-------------------------------------------------------------------------------------
//								GLOBAL VARIABLE DECLARE
//-------------------------------------------------------------------------------------

#endif

///////////////////////////////////////// no more //////////////////////////////////////

