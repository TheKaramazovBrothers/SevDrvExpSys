//=========================================================================================================
// project		:	servo system mechanic modeling
// File			:	MechModel.c
// discription	:	use in servo system mechanic modeling
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g
// date			:	2022/07/01
// copyright(C)	:	liu.g	(2022-2032)
//=========================================================================================================

#include	<cmath>
#include	"MechModel.h"


//*********************************************************************************************************
//*                                    PMSM MOTOR MODEL INITIALIZATION
//*
//* Description: This function is used to initialize PMSM model in servo system
//*
//*
//* Arguments  : m_pmsm		is a pointer to servo system pmsm model object
//*
//* Returns    : -1/initialize Failure, else/success
//*********************************************************************************************************
PmsmDrvMechModel::PmsmDrvMechModel()
{
    this->mode_sel          =       PMSM_ONLY;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    this->PI				=		3.14159265358979323846;								// pi
    this->PI_2              =		this->PI*2.0;										// pi * 2
    this->PI_23D			=		2.0943951;											// pi * (2/3)
    this->K_2D3             =		0.66667;											// 2/3
    this->K_SQRT2D3         =		0.8165;												// sqrt(2/3)

    this->LD				=		0.00367;                                            // reactance of d axis
    this->LQ				=		0.00367;											// reactance of q axis
    this->RA				=		2.9;												// resistor of wire wound

    this->P_NUM             =		4;													// pole pairs of motor
    this->PSI_F             =		0.18856/this->P_NUM;								// permanent flux of rotor (V/rad.s /PPN) |{[KT / sqrt(2)] === [(3/2) * PPN * psi_F]}
//	this->PSI_F             =		0.4204;												//
//	this->PSI_A             =		0.3432;												// PSI_A = PSI_F * sqrt(3/2) (the right relationship with k equal to sqrt(2/3))
//	this->PSI_A             =		0.4204;												// PSI_A = PSI_F * 3/2
    this->PSI_A             =		this->PSI_F;										// PSI_A = PSI_F (the right relationship with k equal to 2/3)

    this->J                 =		0.000044 * (1.0 + 5.4);                             // inertia of motor
    this->J_Rat             =       5.4;                                                // JL/JM Ratio on resonance and anti-resonance
    this->JM                =       0.000044;

    this->JL                =       this->JM * this->J_Rat;                             // inertia of the loader (kg-m^2)
    this->BS                =       0.0002;												// the viscous friction coefficient (Nm-s/rad)
    this->KS                =       5000.0;                                             //	modulus of elasticity (Nm/rad)
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    this->TL				=		0;													// load torque
    this->DM				=		0.001;												// friction coefficient of velocity Nms/rad
    this->TS				=		0.00000625;											// periods of pmsm model calculate

    this->KA_D              =		(((2*this->LD) / this->TS) + this->RA);             // ka = (2*Ld)/Ts + Ra
    this->KB_D              =		(((2*this->LD) / this->TS) - this->RA);             // Kb = (2*Ld)/Ts - Ra
    this->KA_Q              =		(((2*this->LQ) / this->TS) + this->RA);             // ka = (2*Lq)/Ts + Ra
    this->KB_Q              =		(((2*this->LQ) / this->TS) - this->RA);             // Kb = (2*Lq)/Ts - Ra

    this->UP_CURR			=		150.0;												// Unit per unit reference of current (A)
    this->UP_VOL			=		150.0;												// Unit per unit reference of voltage (V)
    this->UP_VEL			=		3600.0;												// Unit per unit reference of velocity (RPM)
    this->UP_PRE			=		20.0;												// Unit per unit reference of pressure(10^6 ps)
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    this->ua				=		0;
    this->ub				=		0;
    this->uc				=		0;

    this->ud				=		0;
    this->uq				=		0;

    this->ia				=		0;
    this->ib				=		0;
    this->ic				=		0;

    this->id				=		0;
    this->iq				=		0;
    this->id_last			=		0;
    this->iq_last			=		0;

    this->ide				=		0;
    this->iqe				=		0;
    this->ide_last          =		0;
    this->iqe_last          =		0;

    this->we				=		0;
    this->wm				=		0;
    this->wm_last			=		0;
    this->phim              =		0;
    this->phie              =		0;
    this->te				=		0;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}



PmsmDrvMechModel::~PmsmDrvMechModel()
{
}

//*********************************************************************************************************
//*                                    PMSM MOTOR VARIABLE INITIALIZATION
//*
//* Description: This function is used to initialize PMSM model variable in servo system
//*
//*
//* Arguments  : m_pmsm		is a pointer to servo system pmsm model object
//*
//* Returns    : -1/initialize Failure, else/success
//*********************************************************************************************************
void PmsmDrvMechModel::InitPmsmDrvMechModelVar()
{
    this->ua				=		0;
    this->ub				=		0;
    this->uc				=		0;

    this->ud				=		0;
    this->uq				=		0;

    this->ia				=		0;
    this->ib				=		0;
    this->ic				=		0;

    this->id				=		0;
    this->iq				=		0;
    this->id_last			=		0;
    this->iq_last			=		0;

    this->ide				=		0;
    this->iqe				=		0;
    this->ide_last          =		0;
    this->iqe_last          =		0;

    this->we				=		0;
    this->wm				=		0;
    this->wm_last			=		0;
    this->phim              =		0;
    this->phie              =		0;
    this->te				=		0;
}


//*********************************************************************************************************
//*                                    PMSM MOTOR MODELING
//*
//* Description: This function is used to pmsm motor modeling
//*
//*
//* Arguments  : none
//*
//* Returns    : none
//*********************************************************************************************************
void PmsmDrvMechModel::PmsMotorModeling()
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////
    this->we		=	this->wm * this->P_NUM;
    this->phie      =	this->phim * this->P_NUM;

    this->ud		=	this->K_2D3 * (this->ua * cos(this->phie) +\
                        this->ub * cos(this->phie - this->PI_23D) +\
                        this->uc * cos(this->phie + this->PI_23D));

    this->uq		=	-this->K_2D3 * (this->ua * sin(this->phie) +\
                        this->ub * sin(this->phie - this->PI_23D) +\
                        this->uc * sin(this->phie + this->PI_23D));

    this->ide		=	this->ud + this->we * this->LQ * this->iq;
    this->iqe		=	this->uq - this->we * this->LD * this->id - this->we*this->PSI_A;

    this->id		=	(this->ide + this->ide_last + this->KB_D*this->id_last)/this->KA_D;
    this->iq		=	(this->iqe + this->iqe_last + this->KB_Q*this->iq_last)/this->KA_Q;

    this->ide_last	=		this->ide;
    this->iqe_last	=		this->iqe;
    this->id_last	=		this->id;
    this->iq_last	=		this->iq;


    this->ia		=	1.0 * (this->id * cos(this->phie) - this->iq *sin(this->phie));
    this->ib		=	1.0 * (this->id * cos(this->phie - this->PI_23D) -\
                        this->iq * sin(this->phie - this->PI_23D));

    this->ic		=	-(this->ia + this->ib);

    this->te		=	-this->P_NUM * ((this->ia * sin(this->phie) * this->PSI_F) +\
                        (this->ib * sin(this->phie - this->PI_23D) * this->PSI_F) +\
                         (this->ic * sin(this->phie + this->PI_23D) * this->PSI_F));

    if (this->mode_sel == PMSM_ONLY)
    {
        this->wm		=	this->wm + (this->te - this->TL - this->DM * this->wm)*(this->TS/this->J);
        this->phim      =	this->phim + this->TS * (this->wm + this->wm_last)/2.0;

        this->wm_last	=	this->wm;
    }
    else
    {
        this->tem			=	this->te - this->tel;

        this->wm			=	this->wm + (this->tem - this->TL - this->DM * this->wm)*(this->TS/this->JM);
        this->phim          =	this->phim + this->TS * this->wm;

        this->wl			=	this->wl + this->tel * (this->TS/this->JL);
        this->phil          =	this->phil + this->TS * this->wl;

        this->tel			=	(this->wm - this->wl) * this->BS + (this->phim - this->phil) * this->KS;
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void PmsmDrvMechModel::InputThreePhaVoltage(double * m_ua, double * m_ub, double *m_uc)
{
    this->ua                =   *m_ua;
    this->ub                =   *m_ub;
    this->uc                =   *m_uc;
}


void PmsmDrvMechModel::OutputThreeCurrent(double *m_ia, double *m_ib, double *m_ic)
{
    *m_ia                   =   this->ia;
    *m_ib                   =   this->ib;
    *m_ic                   =   this->ic;
}


void PmsmDrvMechModel::OutputMechPos(double *posm, double *posl)
{
    *posm                   =   this->phim;
    *posl                   =   this->phil;
}

////////////////////////////////////////////////// no more ///////////////////////////////////////////////////
