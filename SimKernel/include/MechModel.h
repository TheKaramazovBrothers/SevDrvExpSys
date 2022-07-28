//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	Servo system mechanical model								//
//	file				:	MechModel.h													//
//	Description			:	use for SERVO system modeling								//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g(1487)		|	2022/07/01	|	liu.g           |		2022 - 2032			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef		__MECHMODEL_H__
#define		__MECHMODEL_H__


//-------------------------------------------------------------------------------------
//							SERVO SYSTEM MODEL SELECT
//-------------------------------------------------------------------------------------
typedef	enum
{
    PMSM_ONLY		=	1,
    PMSM_LOADER		=	2
}tModelId;

//-------------------------------------------------------------------------------------
//							SERVO SYSTEM PMSM MODEL
//-------------------------------------------------------------------------------------
class PmsmDrvMechModel
{
//--------------------------------------------------------------------------------------------------------
public:
    PmsmDrvMechModel();
    ~PmsmDrvMechModel();
    void InitPmsmDrvMechModelVar();
    void PmsMotorModeling();

    void InputThreePhaVoltage(double * m_ua, double * m_ub, double *m_uc);
    void OutputThreeCurrent(double * m_ia, double * m_ib, double *m_ic);
    void OutputMechPos(double * posm, double * posl);
private:
    tModelId    mode_sel;
// Fixed parameters
    double      PI;																			// pi
    double      PI_2;																		// pi * 2
    double      PI_23D;																		// pi * (2/3)
    double      K_2D3;																		// sqrt(2/3)
    double      K_SQRT2D3;																	// sqrt(2/3)

    double      LD;																			// the reactance of d axis
    double      LQ;																			// the reactance of q axis
    double      RA;																			// the resistor of wire wound

    double      PSI_F;																		// permanent Flux of rotor
    double      PSI_A;																		// PSI_A = PSI_F * sqrt(3/2)
    double      J;																			// moment of inertia
    double      TL;																			// load torque
    double      DM;																			// Velocity coefficient of friction
    double      TS;																			// periods of pmsm calculate (S)

    double      KA_D;																		// ka_d = (2*Ld)/Ts + Ra
    double      KB_D;																		// Kb_d = (2*Ld)/Ts - Ra
    double      KA_Q;																		// ka_q = (2*Lq)/Ts + Ra
    double      KB_Q;																		// Kb_q = (2*Lq)/Ts - Ra

    double      UP_VOL;																		// unit reference Voltage  [V]
    double      UP_CURR;																	// unit reference Current  [A]
    double      UP_VEL;																		// unit reference velocity [RMP]
    double      UP_PRE;																		// UNIT reference Pressure [10^6 pa]

    int         P_NUM;																		// The pole pair numbers of motor

// Fixed parameters
    double      JL;																			// mechanic loader inertia
    double      JM;																			// motor inertia
    double      BS;																			// the coefficient of friction
    double      KS;																			// modulus of elasticity
    double      J_Rat;																		// JL/JM Ratio on resonance and anti-resonanc
//--------------------------------------------------------------------------------------------------------
// variable define
    double      ua;																			// voltage a phase input of motor
    double      ub;																			// voltage b phase input of motor
    double      uc;																			// voltage c phase input of motor

    double      ud;																			// d axis equivalent voltage
    double      uq;																			// q axis equivalent voltage

    double      ia;																			// a phase current of motor
    double      ib;																			// b phase current of motor
    double      ic;																			// c phase current of motor

    double      id;																			// d axis equivalent current
    double      iq;																			// q axis equivalent current
    double      id_last;																	// last current of d axis
    double      iq_last;																	// last current of q axis

    double      ide;																		// d axis Intermediate variables
    double      iqe;																		// q axis Intermediate variables
    double      ide_last;																	// last d axis Intermediate variables
    double      iqe_last;																	// last q axis Intermediate variables

    double      wm;																			// mechanical speed of motor
    double      wm_last;																	// the last mechanical speed of motor
    double      we;																			// electric speed of motor
    double      te;																			// torque of motor
    double      phim;																		// motor mechanic position
    double      phie;																		// motor electric position
//--------------------------------------------------------------------------------------------------------
    double      tem;                                                                        // torque of motor
    double      tel;                                                                        // torque of loader
    double      wl;                                                                         // angular velocity of loader
    double      phil;                                                                       // angular position of loader
//--------------------------------------------------------------------------------------------------------
};


#endif
