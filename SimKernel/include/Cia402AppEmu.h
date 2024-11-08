//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	cia402 application emulate                                  //
//	file				:	Cia402AppEmu.h       										//
//	Description			:	use for SERVO system cia402 application procedure emulate   //
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g(1487)		|	2022/07/08	|	liu.g           |		2022 - 2032			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __CIA402APPEMU_H__
#define __CIA402APPEMU_H__

#include "DspCpu.h"

//#############################################################################################################################
// CIA402 DataTypes define
#define     DEFTYPE_NULL                0x0000                                              /**< \brief Null*/
#define     DEFTYPE_BOOLEAN             0x0001                                              /**< \brief BOOLEAN*/
#define     DEFTYPE_INTEGER8            0x0002                                              /**< \brief INTEGER8*/
#define     DEFTYPE_INTEGER16           0x0003                                              /**< \brief INTEGER16*/
#define     DEFTYPE_INTEGER32           0x0004                                              /**< \brief INTEGER32*/
#define     DEFTYPE_UNSIGNED8           0x0005                                              /**< \brief UNSIGNED8*/
#define     DEFTYPE_UNSIGNED16          0x0006                                              /**< \brief UNSIGNED16*/
#define     DEFTYPE_UNSIGNED32          0x0007                                              /**< \brief UNSIGNED32*/
#define     DEFTYPE_REAL32              0x0008                                              /**< \brief REAL32*/
#define     DEFTYPE_VISIBLESTRING       0x0009                                              /**< \brief VISIBLE_STRING*/
#define     DEFTYPE_OCTETSTRING         0x000A                                              /**< \brief OCTET_STRING*/
#define     DEFTYPE_UNICODE_STRING      0x000B                                              /**< \brief UNICODE_STRING*/
#define     DEFTYPE_TIME_OF_DAY         0x000C                                              /**< \brief TIME_OF_DAY*/
#define     DEFTYPE_TIME_DIFFERENCE     0x000D                                              /**< \brief TIME_DIFFERENCE*/
#define     DEFTYPE_INTEGER24           0x0010                                              /**< \brief INTEGER24*/
#define     DEFTYPE_REAL64              0x0011                                              /**< \brief REAL64*/
#define     DEFTYPE_INTEGER40           0x0012                                              /**< \brief INTEGER40*/
#define     DEFTYPE_INTEGER48           0x0013                                              /**< \brief INTEGER48*/
#define     DEFTYPE_INTEGER56           0x0014                                              /**< \brief INTEGER56*/
#define     DEFTYPE_INTEGER64           0x0015                                              /**< \brief INTEGER64*/
#define     DEFTYPE_UNSIGNED24          0x0016                                              /**< \brief UNSIGNED24*/
#define     DEFTYPE_UNSIGNED40          0x0018                                              /**< \brief UNSIGNED40*/
#define     DEFTYPE_UNSIGNED48          0x0019                                              /**< \brief UNSIGNED48*/
#define     DEFTYPE_UNSIGNED56          0x001A                                              /**< \brief UNSIGNED56*/
#define     DEFTYPE_UNSIGNED64          0x001B                                              /**< \brief UNSIGNED64*/
#define     DEFTYPE_GUID                0x001D                                              /**< \brief DEFTYPE_GUID*/
#define     DEFTYPE_BYTE                0x001E                                              /**< \brief DEFTYPE_BYTE*/
#define     DEFTYPE_WORD                0x001F                                              /**< \brief DEFTYPE_WORD*/
#define     DEFTYPE_DWORD               0x0020                                              /**< \brief DEFTYPE_DWORD*/
#define     DEFTYPE_PDOMAPPING          0x0021                                              /**< \brief PDO_MAPPING*/
#define     DEFTYPE_IDENTITY            0x0023                                              /**< \brief IDENTITY*/
#define     DEFTYPE_COMMAND             0x0025                                              /**< \brief COMMAND_PAR*/
#define     DEFTYPE_PDOCOMPAR           0x0027                                              /**< \brief PDO_PARAMETER*/
#define     DEFTYPE_ENUM                0x0028                                              /**< \brief DEFTYPE_ENUM */
#define     DEFTYPE_SMPAR               0x0029                                              /**< \brief SM_SYNCHRONISATION*/
#define     DEFTYPE_RECORD              0x002A                                              /**< \brief DEFTYPE_RECORD */
#define     DEFTYPE_BACKUP              0x002B                                              /**< \brief BACKUP_PARAMETER*/
#define     DEFTYPE_MDP                 0x002C                                              /**< \brief MODULAR_DEVICE_PROFILE*/
#define     DEFTYPE_BITARR8             0x002D                                              /**< \brief BITARR8*/
#define     DEFTYPE_BITARR16            0x002E                                              /**< \brief BITARR16*/
#define     DEFTYPE_BITARR32            0x002F                                              /**< \brief BITARR32*/
#define     DEFTYPE_BIT1                0x0030                                              /**< \brief BIT1*/
#define     DEFTYPE_BIT2                0x0031                                              /**< \brief BIT2*/
#define     DEFTYPE_BIT3                0x0032                                              /**< \brief BIT3*/
#define     DEFTYPE_BIT4                0x0033                                              /**< \brief BIT4*/
#define     DEFTYPE_BIT5                0x0034                                              /**< \brief BIT5*/
#define     DEFTYPE_BIT6                0x0035                                              /**< \brief BIT6*/
#define     DEFTYPE_BIT7                0x0036                                              /**< \brief BIT7*/
#define     DEFTYPE_BIT8                0x0037                                              /**< \brief BIT8*/
#define     DEFTYPE_ARRAY_OF_INT        0x0260                                              /**< \brief DEFTYPE_ARRAY_OF_INT*/
#define     DEFTYPE_ARRAY_OF_SINT       0x0261                                              /**< \brief DEFTYPE_ARRAY_OF_SINT*/
#define     DEFTYPE_ARRAY_OF_DINT       0x0262                                              /**< \brief DEFTYPE_ARRAY_OF_DINT*/
#define     DEFTYPE_ARRAY_OF_UDINT      0x0263                                              /**< \brief DEFTYPE_ARRAY_OF_UDINT*/
#define     DEFTYPE_ERRORHANDLING       0x0281                                              /**< \brief DEFTYPE_ERRORHANDLING*/
#define     DEFTYPE_DIAGHISTORY         0x0282                                              /**< \brief DEFTYPE_DIAGHISTORY*/
#define     DEFTYPE_SYNCSTATUS          0x0283                                              /**< \brief DEFTYPE_SYNCSTATUS*/
#define     DEFTYPE_SYNCSETTINGS        0x0284                                              /**< \brief DEFTYPE_SYNCSETTINGS*/
#define     DEFTYPE_FSOEFRAME           0x0285                                              /**< \brief DEFTYPE_FSOEFRAME*/
#define     DEFTYPE_FSOECOMMPAR         0x0286                                              /**< \brief DEFTYPE_FSOECOMMPAR*/

//#############################################################################################################################
// REL_CiA402_140617
typedef struct  tsdoinfoobjdec
{
    Uint16            DataType;                                                             /**< \brief Object data type*/
    Uint16            ObjFlags;                                                             /**< \brief Object flags (including object code and max subindex)*/

    /*Object Code and MaxSubindex will be set manually in the object dictionary. The value is always created in little endian format*/
    #define    OBJFLAGS_MAXSUBINDEXMASK    0x00FF                                           /**< \brief Max subindex mask*/
    #define    OBJFLAGS_MAXSUBINDEXSHIFT   0                                                /**< \brief Max subindex shift*/
    #define    OBJFLAGS_OBJCODEMASK        0x0F00                                           /**< \brief Mask Object code mask*/
    #define    OBJFLAGS_OBJCODESHIFT       8                                                /**< \brief Object code shift*/

    #define    OBJCODE_VAR                 0x07                                             /**< \brief Object code VARIABLE*/
    #define    OBJCODE_ARR                 0x08                                             /**< \brief Object code ARRAY*/
    #define    OBJCODE_REC                 0x09                                             /**< \brief Object code RECORD*/

}TSDOINFOOBJDESC;



/**
 * SDO Info entry description
 */
typedef struct tsdoinfoentrydesc
{
    Uint16                DataType; /**< \brief Entry data type*/
    Uint16                BitLength; /**< \brief Entry bit size*/
    Uint16                ObjAccess; /**< \brief Entry access rights*/
                                     /**<
                                     Bit 0: Read Access in Pre-Op
                                     <br>Bit 1: Read Access in Safe-Op
                                     <br>Bit 2: Read Access in Op
                                     <br>Bit 3: Write Access in Pre-Op
                                     <br>Bit 4: Write Access in Safe-Op
                                     <br>Bit 5: Write Access in Op
                                     <br>Bit 6: mappable in RxPDO
                                     <br>Bit 7: mappable in TxPDO
                                     <br>Bit 8: entry will be included in backup
                                     <br>Bit 9: entry will be included in settings*/

        #define    ACCESS_READWRITE             0x003F /**< \brief Read/write in all states*/
        #define    ACCESS_READ                  0x0007 /**< \brief Read only in all states*/
        #define    ACCESS_READ_PREOP            0x0001 /**< \brief Read only in PreOP*/
        #define    ACCESS_READ_SAFEOP           0x0002 /**< \brief Read only in SafeOP*/
        #define    ACCESS_READ_OP               0x0004 /**< \brief Read only in OP*/
        #define    ACCESS_WRITE                 0x0038 /**< \brief Write only in all states*/
        #define    ACCESS_WRITE_PREOP           0x0008 /**< \brief Write only in PreOP*/
        #define    ACCESS_WRITE_SAFEOP          0x0010 /**< \brief Write only in SafeOP*/
        #define    ACCESS_WRITE_OP              0x0020 /**< \brief Write only in OP*/
        #define    OBJACCESS_NOPDOMAPPING       0x0000 /**< \brief Not PDO mappable*/
        #define    OBJACCESS_RXPDOMAPPING       0x0040 /**< \brief Mappable in RxPDOs*/
        #define    OBJACCESS_TXPDOMAPPING       0x0080 /**< \brief Mappable in TxPDOs*/
        #define    OBJACCESS_BACKUP             0x0100 /**< \brief Backup entry*/
        #define    OBJACCESS_SETTINGS           0x0200 /**< \brief Setting Entry*/
        #define    OBJACCESS_SAFEINPUTS         0x0400 /**< \brief Safe input*/
        #define    OBJACCESS_SAFEOUTPUTS        0x0800 /**< \brief Safe output*/
        #define    OBJACCESS_SAFEPARAMETER      0x1000 /**< \brief Safe parameter*/
}TSDOINFOENTRYDESC;

//#############################################################################################################################

typedef struct obj_entry
{
    Uint16                      Index;                                                      /**< \brief Object index*/
    TSDOINFOOBJDESC             ObjDesc;                                                    /**< \brief Object access, type and code*/
    const TSDOINFOENTRYDESC     *pEntryDesc;                                                /**< \brief pointer to object entry descriptions*/
    const Uint8                 *pName;                                                     /**< \brief Pointer to object and entry names*/
    volatile void               *pVarPtr;                                                   /**< \brief Pointer to object buffer*/
    int16                       (* Read)(Uint16 Index, Uint16 Subindex, Uint32 Size, \
                                         Uint16 * pData, Uint16 bCompleteAccess );          /**< \brief Function pointer to read function (if NULL default read function will be used)*/
    int16                       (* Write)(Uint16 Index, Uint16 Subindex, Uint32 Size, \
                                         Uint16 * pData, Uint16 bCompleteAccess );          /**< \brief Function pointer to write function (if NULL default write function will be used)*/
    Uint16                      NonVolatileOffset;                                          /**< \brief Offset within the non volatile memory (need to be defined for backup objects)*/
}TOBJ_ENTRY;

//#############################################################################################################################

typedef enum
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    SRAT_MOT_PRM_ID16_OBJW_2000H                =   0,                                      // over speed detection level |  unit[%]
    PPN_MOT_PRM_ID16_OBJW_2001H                 =   1,                                      // motor pole pair numbers
    JRAT_MOT_PRM_ID16_OBJW_2002H                =   2,                                      // Inertia ratio 100 * ((Jtotal - Jmot)/Jmot) | unit[%]
    VMAX_MOT_PRM_ID16_OBJW_2003H                =   3,                                      // maximum voltage of driver system Vmax [0.1V]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    FND_CCLD_PRM_ID16_OBJW_2004H                =   4,                                      // d axis frequent band width | unit[Hz]
    FNQ_CCLD_PRM_ID16_OBJW_2005H                =   5,      								// q axis frequent band width | unit[Hz]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    IRATE_MOT_PRM_ID32_OBJW_2006H               =   6,                                      // continued phase current rated value | unit[0.001A]
    IMAX_MOT_PRM_ID32_OBJW_2007H				=	7,                                      // instantaneous maximum current of driver system | unit[0.001A]
    SCT_MOT_PRM_ID32_OBJW_2008H                 =	8,										// continued speed rated value |  unit[RPM]
    NOS_MOT_PRM_ID32_OBJW_2009H                 =   9,                                      // over speed unit(max speed) | unit[RPM]
    TQR_MOT_PRM_ID32_OBJW_200AH                 =   10,    									// motor rated torque | unit[0.001 N.m]
    PHIM_MOT_PRM_ID32_OBJW_200BH                =   11,                                     // EMF constant | unit[0.1mV/r/min]
    LDM_MOT_PRM_ID32_OBJW_200CH                 =   12,                                     // motor d axis reactive resistance [0.001mH]
    LQM_MOT_PRM_ID32_OBJW_200DH                 =   13,      								// motor q axis reactive resistance [0.001mH]
    RM_MOT_PRM_ID32_OBJW_200EH                  =   14,                                     // motor rotate winding resistance [1 m ohm]
    JM_MOT_PRM_ID32_OBJW_200FH                  =   15,                                     // rotary inertia of motor | unit[10^-6 kg.m^2]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    TS_ISR_PRM_ID32_OBJW_2010H                  =   16,                                     // digital control sample periods / unit[1ns]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    TID_CCTL_PRM_ID32_OBJW_2011H                =   17,                                     // d axis integral time constant | unit[us]
    TIQ_CCTL_PRM_ID32_OBJW_2012H                =   18,                                     // q axis integral time constant | unit[us]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    LINE_NUM_ENC_PRM_ID32_OBJW_2013H            =   19,                                     // line number of encoder in one circle | unit[pulse]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    FNV_FST_VCTL_PRM_ID32_OBJW_2014H            =   20,                                     // velocity loop gain band width | unit[0.1Hz]
    TIV_FST_VCTL_PRM_ID32_OBJW_2015H            =   21,                                     // velocity loop integral time constant | unit[0.01ms]
    FNV_SEC_VCTL_PRM_ID32_OBJW_2016H            =   22,                                     // the second velocity loop gain bandwidth | unit[0.1Hz]
    TIV_SEC_VCTL_PRM_ID32_OBJW_2017H            =   23,                                     // the second velocity loop integral time constant | unit[0.01ms]
    TS_VCTL_PRM_ID32_OBJW_2018H                 =   24,                                     // velocity loop sample times | unit[ns]

    TF_RMP_VCTL_PRM_ID32_OBJW_2019H             =   25,                                     // ramp time constant of velocity command | unit[ms]
    CFG_OPT_ALL_PRM_ID32_OBJW_201AH             =   26,                                     // velocity control config option

    ABS_RAT_TQR_LIM_VCTL_PRM_ID16_OBJW_201BH    =   27,                                     // max torque limit rate | unit[Q12]
    POS_RAT_TQR_LIM_VCTL_PRM_ID16_OBJW_201CH    =   28,                                     // positive tqrque limit rate | unit[Q12]
    NEG_RAT_TQR_LIM_VCTL_PRM_ID16_OBJW_201DH    =   29,                                     // negative tqrque limit rate | unit[Q12]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    TS_POS_CTL_PRM_ID32_OBJW_201EH              =   30,                                     // position loop sample times | unit[ns]
    CFG_OPT_ALL_PCTL_PRM_ID32_OBJW_201FH        =   31,                                     // position control config option

    FNP_FST_PCTL_PRM_ID16_OBJW_2020H            =   32,                                     // position loop gain band width | unit[0.1Hz]
    FNP_SEC_PCTL_PRM_ID16_OBJW_2021H            =   33,                                     // the second position loop gain bandwidth | unit[0.1Hz]

    ABS_RAT_SPD_LIM_PCTL_PRM_ID16_OBJW_2022H    =   34,                                     // max velocity limit rate | unit[Q12]
    POS_RAT_SPD_LIM_PCTL_PRM_ID16_OBJW_2023H    =   35,                                     // positive velocity limit rate | unit[Q12]
    NEG_RAT_SPD_LIM_PCTL_PRM_ID16_OBJW_2024H    =   36,                                     // negative velocity limit rate | unit[Q12]
    MAF_NUM_PCTL_PRM_ID16_OBJW_2025H            =   37,                                     // moving average filtering times | unit[scan]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    PSRC_SEL_SEQ_CTL_PRM_ID16_OBJW_2026H        =   38,                                     // position command source select
    VSRC_SEL_SEQ_CTL_PRM_ID16_OBJW_2027H        =   39,                                     // velocity command source select
    CSRC_SEL_SEQ_CTL_PRM_ID16_OBJW_2028H        =   40,                                     // current command source select
    CMD_DIR_SEQ_CTL_PRM_ID16_OBJW_2029H         =   41,                                     // command direction of sequence control
    CFG_OPT_ALL_SEQ_CTL_PRM_ID32_OBJW_202AH     =   42,                                     // config option of sequence control
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    ROT_RES_POS_TRAJ_PRM_ID32_OBJW_202BH        =   43,                                     // rotation resolution | unit[pulse number/circle]
    TS_POS_TRAJ_PRM_ID32_OBJW_202CH             =   44,                                     // position command maker sample times | unit[ns]

    ACCRATE_POS_TRAJ_PRM_ID32_OBJW_202DH        =   45,                                     // acceleration of position command maker | unit[10000pulse/s/s]
    DECRATE_POS_TRAJ_PRM_ID32_OBJW_202EH        =   46,                                     // deceleration of position command maker | unit[10000pulse/s/s]
    MAXSPD_POS_TRAJ_PRM_ID32_OBJW_202FH         =   47,                                     // maximum velocity set for position trajectory maker | unit[RPM]
    CFG_OPT_ALL_POS_TRAJ_PRM_ID32_OBJW_2030H    =   48,                                     // point position trajectory nest mask bit | 1/mask
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    FFV_RATE_PCTL_PRM_ID16_OBJW_2031H           =   49,                                     // velocity feedforward rate | unit[Q12]
    FFT_RATE_PCTL_PRM_ID16_OBJW_2032H           =   50,                                     // torque feedforward rate | unit[Q12]
    FFJ_RATE_PCTL_PRM_ID32_OBJW_2033H           =   51,                                     // jerk feedforward gain coefficient | unit[Q16]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    CFG_OPT_ALL_CCTL_PRM_ID32_OBJW_2034H        =   52,                                     // config option for current loop control
    TF_LPF_CCTL_PRM_ID16_OBJW_2035H             =   53,                                     // low pass filter time constant | uni[us]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    TS_EXCI_SIG_PRM_ID32_OBJW_2036H             =   54,                                     // excitation signal produce module sample times | unit[ns]
    CFG_OPT_ALL_EXCI_SIG_PRM_ID32_OBJW_2037H    =   55,                                     // config option of excitation signal module
    STEADY_TIM_EXCI_SIG_PRM_ID32_OBJW_2038H     =   56,                                     // Steady state time of sinusoidal excitation | unit[scan]
    DELAY_TIM_EXCI_SIG_PRM_ID32_OBJW_2039H      =   57,                                     // delay time between harmonic component | unit[scan]

    SIN_HZ_START_EXCI_SIG_PRM_ID16_OBJW_203AH   =   58,                                     // start frequency of sinusoidal excitation | unit[HZ]
    SIN_HZ_STEP_EXCI_SIG_PRM_ID16_OBJW_203BH    =   59,                                     // step of sinusoidal excitation | unit[HZ]
    SIN_HARM_NUM_EXCI_SIG_PRM_ID16_OBJW_203CH   =   60,                                     // sinusoidal excitation numbers (numbers of sine waves)

    EXCI_AMP_EXCI_SIG_PRM_ID32_OBJW_203DH       =   61,                                     // amplitude of excitation signal | unit[Q10]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    RECIP_NUM_TRAJ_PRM_ID32_OBJW_203EH          =   62,                                     // reciprocating motion times
    INTERV_TIM_TRAJ_PRM_ID32_OBJW_203FH         =   63,                                     // interval time between motion | unit[scan]
    SPDR_HOLD_TIM_TRAJ_PRM_ID32_OBJW_2040H      =   64,                                     // speed command hold time in reciprocate motion | unit[scan]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    PRBS_DIV_NUM_EXCI_SIG_PRM_ID16_OBJW_2041H   =   65,                                     // prbs diivision times | unit[ts]
    PRBS_DURAT_TIM_EXCI_SIG_PRM_ID32_OBJW_2042H =   66,                                     // prbs durate time | unit[ts]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    FN_LPF0_TQR_VCTL_PRM_ID16_OBJW_2043H        =   67,                                     // fn of the first low pass filter for torque filter | unit[0.1hz]
    FN_LPF1_TQR_VCTL_PRM_ID16_OBJW_2044H        =   68,                                     // fn of the second low pass filter for torque filter | unit[0.1hz]

    FN_NCH0_TQR_VCTL_PRM_ID16_OBJW_2045H        =   69,                                     // fn of the first notch filter for torque filter | unit[0.1hz]
    QX_NCH0_TQR_VCTL_PRM_ID16_OBJW_2046H        =   70,                                     // width of the first notch filter | unit[0.001]
    KX_NCH0_TQR_VCTL_PRM_ID16_OBJW_2047H        =   71,                                     // depth of the first notch filter | unit[0.001]

    FN_NCH1_TQR_VCTL_PRM_ID16_OBJW_2048H        =   72,                                     // fn of the second notch filter for torque filter | unit[0.1hz]
    QX_NCH1_TQR_VCTL_PRM_ID16_OBJW_2049H        =   73,                                     // width of the second notch filter | unit[0.001]
    KX_NCH1_TQR_VCTL_PRM_ID16_OBJW_204AH        =   74,                                     // depth of the second notch filter | unit[0.001]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    CFG_OPT_ALL_MOD_IDF_PRM_ID32_OBJW_204BH     =   75,                                     // config option of model identification module
    TS_MOD_IDF_PRM_ID32_OBJW_204CH              =   76,                                     // model estimate sample times | unit[ns]
    J0_RLS_MOD_IDF_PRM_ID32_OBJW_204DH          =   77,                                     // Initialize inertia for rls algorithm | unit[10^-6 kg.m^2]
    P0_RLS_MOD_IDF_PRM_ID32_OBJW_204EH          =   78,                                     // initialize gain of p1 coefficient for rls algorithm
    LAMT_RLS_MOD_IDF_PRM_ID32_OBJW_204FH        =   79,                                     // the lamt coefficient for rsl algorithm realization | unit[Q24]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    CHIRP_HZ_START_EXCI_SIG_PRM_ID16_OBJW_2050H =   80,                                     // start frequency of chirp excitation signal | unit[HZ]
    CHIRP_HZ_END_EXCI_SIG_PRM_ID16_OBJW_2051H   =   81,                                     // end frequency of chirp excitation signal | unit[HZ]
    CHIRP_DURAT_TIM_EXCI_SIG_PRM_ID32_OBJW_2052H=   82,                                     // duration time of chirp excitation signal | unit[ts]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    PRM_SERVO_OBJW_INX_MAX_NUM
}TOBJ_WORD_PRM_INDEX;


//#############################################################################################################################
typedef enum
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    ID_CCTL_VAR_OBJW_3000H                      =   0,                                      // d axis current feedback | unit[A]
    IQ_CCTL_VAR_OBJW_3001H                      =   1,                                      // q axis current feedback | unit[A]
    ID_REF_CCTL_VAR_OBJW_3002H                  =   2,                                      // d axis current reference | unit[A]
    IQ_REF_CCTL_VAR_OBJW_3003H                  =   3,                                      // q axis current reference | unit[A]

    ID_ERR_CCTL_VAR_OBJW_3004H                  =   4,                                      // d axis current control error | unit[A]
    IQ_ERR_CCTL_VAR_OBJW_3005H                  =   5,                                      // q axis current control error | unit[A]
    UD_CCTL_VAR_OBJW_3006H                      =   6,                                      // d axis voltage output | unit[V]
    UQ_CCTL_VAR_OBJW_3007H                      =   7,                                      // q axis voltage output | unit[V]

    ID_S_CCTL_VAR_OBJW_3008H                    =   8,                                      // sum of d axis control output
    IQ_S_CCTL_VAR_OBJW_3009H                    =   9,                                      // sum of q axis control output
    IDI_S_CCTL_VAR_OBJW_300AH                   =   10,                                     // sum of d axis error integral
    IQI_S_CCTL_VAR_OBJW_300BH                   =   11,                                     // sum of q axis error integral

    PHIM_CCTL_VAR_OBJW_300CH                    =   12,                                     // mechancal angel rad
    PHIE_CCTL_VAR_OBJW_300DH                    =   13,                                     // electrical angel rad
    IA_CCTL_VAR_OBJW_300EH                      =   14,                                     // a phase current input | unit[A]
    IB_CCTL_VAR_OBJW_300FH                      =   15,                                     // b phase current input | unit[A]
    IC_CCTL_VAR_OBJW_3010H                      =   16,                                     // c phase current input | unit[A]

    UA_CCTL_VAR_OBJW_3011H                      =   17,                                     // a phase voltage output | unit[V]
    UB_CCTL_VAR_OBJW_3012H                      =   18,                                     // b phase voltage output | unit[V]
    UC_CCTL_VAR_OBJW_3013H                      =   19,                                     // c phase voltage output | unit[V]
    UD_REF_CCTL_VAR_OBJW_3014H                  =   20,                                     // d axis voltage reference | unit[V]
    UQ_REF_CCTL_VAR_OBJW_3015H                  =   21,                                     // q axis voltage reference | unit[V]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    MOT_SPD_SENS_VAR_OBJW_3016H                 =   22,                                     // motor speed | unit[rad/s]
    POS_IN_SENS_VAR_OBJW_3017H                  =   23,                                     // encoder position input | unit[pulse]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    SPD_FB_VCTL_VAR_OBJW_3018H                  =   24,                                     // motor speed feedback | unit[rad/s]
    SPD_REF_VCTL_VAR_OBJW_3019H                 =   25,                                     // motor speed reference | unit[rad/s]
    SPD_ERR_VCTL_VAR_OBJW_301AH                 =   26,                                     // speed control error | unit[rad/s]
    XWKP_VCTL_VAR_OBJW_301BH                    =   27,                                     // proportional accumulation value
    XWKI_VCTL_VAR_OBJW_301CH                    =   28,                                     // intergral accumulation value
    TQR_VCTL_VAR_OBJW_301DH                     =   29,                                     // torque command output | unit[Nm]
    IQR_VCTL_VAR_OBJW_301EH                     =   30,                                     // q axis current command output | unit[A]
    VELR_RAMP_IN_OBJW_301FH                     =   31,                                     // ramp input variable of velocity reference | unit[rad/s]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    ACC_POS_REF_PCTL_VAR_OBJW_3020H             =   32,                                     // accumulate position command | unit[pulse]
    ACC_POS_FB_PCTL_VAR_OBJW_3021H              =   33,                                     // accumulate position feedback | unit[pulse]
    POS_ERR_PCTL_VAR_OBJW_3022H                 =   34,                                     // position control error | unit[pulse]

    XWKP_PCTL_VAR_OBJW_3023H                    =   35,                                     // proportional accumulation value
    SPDR_PCTL_VAR_OBJW_3024H                    =   36,                                     // position loop velocity command output | unit[rad/s]
    TQRP_PCTL_VAR_OBJW_3025H                    =   37,                                     // torque feedforward command
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    MAF_IN_PCTL_VAR_OBJW_3026H                  =   38,                                     // input of moving average filtering
    MAF_OUT_PCTL_VAR_OBJW_3027H                 =   39,                                     // output of moving average filtering
    DPCMD_PCTL_VAR_OBJW_3028H                   =   40,                                     // delta position command
    DPFB_PCTL_VAR_OBJW_3029H                    =   41,                                     // delta position feedback
    SIG_POS_PCTL_VAR_OBJW_302AH                 =   42,                                     // singal circle encoder position
    SIG_POS_LST_PCTL_VAR_OBJW_302BH             =   43,                                     // the last circle encoder position
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    IQR_OUT_SEQ_CTL_VAR_OBJW_302CH              =   44,                                     // q axis current command output of sequece control
    SPDR_OUT_SEQ_CTL_VAR_OBJW_302DH             =   45,                                     // speed command output of sequence control
    POSR_OUT_SEQ_CTL_VAR_OBJW_302EH             =   46,                                     // position command output of sequence control
    POSR_OUT_LST_SEQ_CTL_VAR_OBJW_302FH         =   47,                                     // the last position command output of sequence control

    DPCMP_IN_SEQ_CTL_VAR_OBJW_3030H             =   48,                                     // delta position command input of sequence control
    DPCMP_OUT_SEQ_CTL_VAR_OBJW_3031H            =   49,                                     // delta position command output of sequence control
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    PTRAJ_SET_POS_TRAJ_VAR_OBJW_3032H           =   50,                                     // position command set value
    PTRAJ_IN_POS_TRAJ_VAR_OBJW_3033H            =   51,                                     // position command input value
    PTRAJ_OUT_POS_TRAJ_VAR_OBJW_3034H           =   52,                                     // position command output value
    XQ0_POS_TRAJ_VAR_OBJW_3035H                 =   53,                                     // initialize position | unit[pulse]
    XQ1_POS_TRAJ_VAR_OBJW_3036H                 =   54,                                     // finish position | unit [pulse]

    XQ_REAL_POS_TRAJ_VAR_OBJW_3037H             =   55,                                     // real position | unit [pulse]
    XQH_POS_TRAJ_VAR_OBJW_3038H                 =   56,                                     // increment positon between q0 to q1

    XV0_POS_TRAJ_VAR_OBJW_3039H                 =   57,                                     // initialize velocity | unit[pulse/s]
    XV1_POS_TRAJ_VAR_OBJW_303AH                 =   58,                                     // the max velocity can be reached | unit[pulse/s]
    XV_REAL_POS_TRAJ_VAR_OBJW_303BH             =   59,                                     // real velocity command | unit[pule/s]

    TREAL_POS_TRAJ_VAR_OBJW_303CH               =   60,                                     // current time | unit[s]
    XACC_REAL_POS_TRAJ_VAR_OBJW_303DH           =   61,                                     // the real accelerate | unit[pulse/s/s]
    FLAG_ALL_POS_TRAJ_VAR_OBJW_303EH            =   62,                                     // trajectory produce flag
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    SPD_FFD_PCTL_VAR_OBJW_303FH                 =   63,                                     // speed feedforward value | unit[rad/s]
    SPD_FFD_OUT_PCTL_VAR_OBJW_3040H             =   64,                                     // speed feedforward output value | unit[Nm]
    TQR_FFD_PCTL_VAR_OBJW_3041H                 =   65,                                     // torque feedforward value | unit[Nm]
    TQR_FFD_OUT_PCTL_VAR_OBJW_3042H             =   66,                                     // torque feedforward output value | unit[Nm]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    REAL_T_EXCI_SIG_VAR_OBJW_3043H              =   67,                                     // real time of current harmonic signal
    REAL_F_EXCI_SIG_VAR_OBJW_3044H              =   68,                                     // real frequency of current harmonic signal
    EXCI_SIG_OUT_EXCI_SIG_VAR_OBJW_3045H        =   69,                                     // excition signal output

    PRBS_FLAG_EXCI_SIG_VAR_OBJW_3046H           =   70,                                     // the prbs flag
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    IQR_LPF0_VCTL_VAR_OBJW_3047H                =   71,                                     // output of the first low pass filter for iq reference
    IQR_LPF1_VCTL_VAR_OBJW_3048H                =   72,                                     // output of the second low pass filter for iq reference
    IQR_NCH0_VCTL_VAR_OBJW_3049H                =   73,                                     // output of the first notch filter for iq reference
    IQR_NCH1_VCTL_VAR_OBJW_304AH                =   74,                                     // output of the second notch filter for iq reference
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    ERR_RLS_MOD_IDF_VAR_OBJW_304BH              =   75,                                     // the estimate error variable for rls algorithm design
    CX0_RLS_MOD_IDF_VAR_OBJW_304CH              =   76,                                     // parameter coefficient0 array for rls algorithm
    CX1_RLS_MOD_IDF_VAR_OBJW_304DH              =   77,                                     // parameter coefficient1 array for rls algorithm
    DEST_RLS_MOD_IDF_VAR_OBJW_304EH             =   78,                                     // the estimate viscous friciton for rls algorithm| unit[Nm/rad]
    JUNIT_RLS_MOD_IDF_VAR_OBJ_304FH             =   79,                                     // Moment of inertia for rls algorithm| unit[10^-6 kg.m^2]

    GAMMA0_RLS_MOD_IDF_VAR_OBJ_3050H            =   80,                                     // gamma coefficient 0 for rls algorithm
    GAMMA1_RLS_MOD_IDF_VAR_OBJ_3051H            =   81,                                     // gamma coefficient 1 for rls algorithm
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    VAR_SERVO_OBJW_INX_MAX_NUM
}TOBJ_WORD_VAR_INDEX;




//#############################################################################################################################
// parameter entry discription
//#############################################################################################################################
const   TSDOINFOENTRYDESC sEntryDesc0x2000 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};
/** \brief Object 0x2000 Over speed detection level */
const   Uint8   aName0x2000[] = "Over speed detection level";

//----------------------------------------------------------------------------------------------------------------------------
const   TSDOINFOENTRYDESC sEntryDesc0x2001 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};
/** \brief Object 0x2001 Motor pole pair numbers */
const   Uint8   aName0x2001[] = "Motor pole pair numbers";

//----------------------------------------------------------------------------------------------------------------------------
const   TSDOINFOENTRYDESC sEntryDesc0x2002 = {DEFTYPE_INTEGER16, 0x10, ACCESS_READWRITE};
/** \brief Object 0x2002 Inertia ratio */
const   Uint8   aName0x2002[] = "Inertia ratio 100 * ((Jtotal - Jmot)/Jmot) | unit[%]";

//----------------------------------------------------------------------------------------------------------------------------
const   TSDOINFOENTRYDESC sEntryDesc0x2003 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};
/** \brief Object 0x2003 maximum voltage of driver system */
const   Uint8   aName0x2003[] = "maximum voltage of driver system Vmax | unit[0.1V]";

//----------------------------------------------------------------------------------------------------------------------------
const   TSDOINFOENTRYDESC sEntryDesc0x2004 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};
/** \brief Object 0x2004 D axis frequent band width */
const   Uint8   aName0x2004[] = "D axis frequent band width | unit[Hz]";

//----------------------------------------------------------------------------------------------------------------------------
const   TSDOINFOENTRYDESC sEntryDesc0x2005 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};
/** \brief Object 0x2005 Q axis frequent band width */
const   Uint8   aName0x2005[] = "Q axis frequent band width | unit[Hz]";

//----------------------------------------------------------------------------------------------------------------------------
//0x2006
const   TSDOINFOENTRYDESC sEntryDesc0x2006 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
/** \brief Object 0x2006 Continued phase current rated value */
const   Uint8   aName0x2006[] = "Continued phase current rated value | unit[0.001A]";

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2007 Instantaneous maximum current of driver system entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x2007 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
/** \brief Object 0x2007 */
const   Uint8   aName0x2007[] = "Instantaneous maximum current of driver system | unit[0.001A]";

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2008  Continued speed rated value  entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x2008 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
/** \brief Object 0x2008 */
const   Uint8   aName0x2008[] = "Continued speed rated value |  unit[RPM]";

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2009 Over speed unit(max speed) entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x2009 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
/** \brief Object 0x2009 */
const   Uint8   aName0x2009[] = "Over speed unit(max speed) | unit[RPM]";

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x200A Motor rated torque entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x200A = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
/** \brief Object 0x200A */
const   Uint8   aName0x200A[] = "Motor rated torque | unit[0.001 N.m]";

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x200B */
const   Uint8   aName0x200B[] = "EMF constant | unit[0.1mV/r/min]";
/** \brief Object 0x200B EMF constant*/
const   TSDOINFOENTRYDESC sEntryDesc0x200B = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x200C */
const   Uint8   aName0x200C[] = "Motor d axis reactive inductance | unit[0.001mH]";
/** \brief Object 0x200C Motor d axis reactive resistance entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x200C = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x200D */
const   Uint8   aName0x200D[] = "Motor q axis reactive inductance | unit[0.001mH]";
/** \brief Object 0x200D  Motor q axis reactive resistance entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x200D = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x200E */
const   Uint8   aName0x200E[] = "Motor rotate winding resistance | unit[1 m ohm]";
/** \brief Object 0x200E  Motor rotate winding resistance entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x200E = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x200F */
const   Uint8   aName0x200F[] = "Rotary inertia of motor | unit[10^-6 kg.m^2]";
/** \brief Object 0x200F  Rotary inertia of motor entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x200F = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2010 */
const   Uint8   aName0x2010[] = "Digital control sample periods | unit[1ns]";
/** \brief Object 0x2010  Digital control sample periods entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x2010 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2011 */
const   Uint8   aName0x2011[] = "D axis integral time constant | unit[us]";
/** \brief Object 0x2011  D axis integral time constant  entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x2011 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2012 */
const   Uint8   aName0x2012[] = "Q axis integral time constant | unit[us]";
/** \brief Object 0x2012  Q axis integral time constant entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x2012 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2013 */
const   Uint8   aName0x2013[] = "line number of encoder in one circle | unit[pulse]";
/** \brief Object 0x2013  line number of encoder in one circle | unit[pulse]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2013 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2014 */
const   Uint8   aName0x2014[] = "velocity loop gain band width | unit[0.1Hz]";
/** \brief Object 0x2014  // velocity loop gain band width | unit[0.1Hz]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2014 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2015 */
const   Uint8   aName0x2015[] = "velocity loop integral time constant | unit[0.01ms]";
/** \brief Object 0x2015  velocity loop integral time constant | unit[0.01ms]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2015 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2016 */
const   Uint8   aName0x2016[] = "the second velocity loop gain bandwidth | unit[0.1Hz]";
/** \brief Object 0x2016  the second velocity loop gain bandwidth | unit[0.1Hz]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2016 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2017 */
const   Uint8   aName0x2017[] = "the second velocity loop integral time constant | unit[0.01ms]";
/** \brief Object 0x2017  the second velocity loop integral time constant | unit[0.01ms]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2017 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2018 */
const   Uint8   aName0x2018[] = "velocity loop sample times | unit[ns]";
/** \brief Object 0x2018  velocity loop sample times | unit[ns]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2018 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2019 */
const   Uint8   aName0x2019[] = "ramp time constant of velocity command | unit[ms]";
/** \brief Object 0x2019  ramp time constant of velocity command | unit[ms]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2019 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x201a */
const   Uint8   aName0x201A[] = "velocity control config option";
/** \brief Object 0x201A  velocity control config option*/
const   TSDOINFOENTRYDESC sEntryDesc0x201A = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x201B */
const   Uint8   aName0x201B[] = "max torque limit rate | unit[Q12]";
/** \brief Object 0x201b  max torque limit rate | unit[Q12]*/
const   TSDOINFOENTRYDESC sEntryDesc0x201B = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x201C */
const   Uint8   aName0x201C[] = "positive tqrque limit rate | unit[Q12]";
/** \brief Object 0x201C  positive tqrque limit rate | unit[Q12]*/
const   TSDOINFOENTRYDESC sEntryDesc0x201C = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x201D */
const   Uint8   aName0x201D[] = "negative tqrque limit rate | unit[Q12]";
/** \brief Object 0x201D  positive tqrque limit rate | unit[Q12]*/
const   TSDOINFOENTRYDESC sEntryDesc0x201D = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x201E */
const   Uint8   aName0x201E[] = "position loop sample times | unit[ns]";
/** \brief Object 0x201E  position loop sample times | unit[ns]*/
const   TSDOINFOENTRYDESC sEntryDesc0x201E = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x201F */
const   Uint8   aName0x201F[] = "position control config option";
/** \brief Object 0x201F  position control config option*/
const   TSDOINFOENTRYDESC sEntryDesc0x201F = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2020 */
const   Uint8   aName0x2020[] = "position loop gain band width | unit[0.1Hz]";
/** \brief Object 0x2020  position loop gain band width | unit[0.1Hz]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2020 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2021 */
const   Uint8   aName0x2021[] = "the second position loop gain bandwidth | unit[0.1Hz]";
/** \brief Object 0x2021  the second position loop gain bandwidth | unit[0.1Hz]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2021 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2022 */
const   Uint8   aName0x2022[] = "max velocity limit rate | unit[Q12]";
/** \brief Object 0x2022  max velocity limit rate | unit[Q12]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2022 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2023 */
const   Uint8   aName0x2023[] = "positive velocity limit rate | unit[Q12]";
/** \brief Object 0x2023  positive velocity limit rate | unit[Q12]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2023 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2024 */
const   Uint8   aName0x2024[] = "negative velocity limit rate | unit[Q12]";
/** \brief Object 0x2024  negative velocity limit rate | unit[Q12]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2024 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2025 */
const   Uint8   aName0x2025[] = "moving average filtering times | unit[scan]";
/** \brief Object 0x2025  moving average filtering times | unit[scan]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2025 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2026 */
const   Uint8   aName0x2026[] = "position command source select";
/** \brief Object 0x2026  position command source select*/
const   TSDOINFOENTRYDESC sEntryDesc0x2026 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2027 */
const   Uint8   aName0x2027[] = "velocity command source select";
/** \brief Object 0x2027  velocity command source select*/
const   TSDOINFOENTRYDESC sEntryDesc0x2027 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2028 */
const   Uint8   aName0x2028[] = "current command source select";
/** \brief Object 0x2028  current command source select*/
const   TSDOINFOENTRYDESC sEntryDesc0x2028 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2029 */
const   Uint8   aName0x2029[] = "command direction of sequence control";
/** \brief Object 0x2029  command direction of sequence control*/
const   TSDOINFOENTRYDESC sEntryDesc0x2029 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x202A */
const   Uint8   aName0x202A[] = "config option of sequence control";
/** \brief Object 0x202A  config option of sequence control*/
const   TSDOINFOENTRYDESC sEntryDesc0x202A = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x202B */
const   Uint8   aName0x202B[] = "rotation resolution | unit[pulse number/circle]";
/** \brief Object 0x202B  rotation resolution | unit[pulse number/circle]*/
const   TSDOINFOENTRYDESC sEntryDesc0x202B = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x202C */
const   Uint8   aName0x202C[] = "position command maker sample times | unit[ns]";
/** \brief Object 0x202C  position command maker sample times | unit[ns]*/
const   TSDOINFOENTRYDESC sEntryDesc0x202C = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x202D */
const   Uint8   aName0x202D[] = "acceleration of position command maker | unit[10000pulse/s/s]";
/** \brief Object 0x202D  acceleration of position command maker | unit[10000pulse/s/s]*/
const   TSDOINFOENTRYDESC sEntryDesc0x202D = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x202E */
const   Uint8   aName0x202E[] = "deceleration of position command maker | unit[10000pulse/s/s]";
/** \brief Object 0x202E  deceleration of position command maker | unit[10000pulse/s/s]*/
const   TSDOINFOENTRYDESC sEntryDesc0x202E = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x202F */
const   Uint8   aName0x202F[] = "maximum velocity set for position trajectory maker | unit[RPM]";
/** \brief Object 0x202F  maximum velocity set for position trajectory maker | unit[RPM]*/
const   TSDOINFOENTRYDESC sEntryDesc0x202F = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2030 */
const   Uint8   aName0x2030[] = "point position trajectory nest mask bit | 1/mask";
/** \brief Object 0x2030  point position trajectory nest mask bit | 1/mask*/
const   TSDOINFOENTRYDESC sEntryDesc0x2030 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2031 */
const   Uint8   aName0x2031[] = "velocity feedforward rate | unit[Q12]";
/** \brief Object 0x2031  velocity feedforward rate | unit[Q12]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2031 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2032 */
const   Uint8   aName0x2032[] = "torque feedforward rate | unit[Q12]";
/** \brief Object 0x2032  torque feedforward rate | unit[Q12]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2032 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2033 */
const   Uint8   aName0x2033[] = "jerk feedforward gain coefficient | unit[Q16]";
/** \brief Object 0x2033  jerk feedforward gain coefficient | unit[Q16]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2033 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2034 */
const   Uint8   aName0x2034[] = "config option for current loop control";
/** \brief Object 0x2034  config option for current loop control*/
const   TSDOINFOENTRYDESC sEntryDesc0x2034 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2035 */
const   Uint8   aName0x2035[] = "low pass filter time constant of current command | uni[us]";
/** \brief Object 0x2035  low pass filter time constant | uni[us]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2035 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2036 */
const   Uint8   aName0x2036[] = "excitation signal produce module sample times | unit[ns]";
/** \brief Object 0x2036  excitation signal produce module sample times | unit[ns]]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2036 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2037 */
const   Uint8   aName0x2037[] = "config option of excitation signal module";
/** \brief Object 0x2037  config option of excitation signal module*/
const   TSDOINFOENTRYDESC sEntryDesc0x2037 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2038 */
const   Uint8   aName0x2038[] = "Steady state time of sinusoidal excitation | unit[scan]";
/** \brief Object 0x2038  Steady state time of sinusoidal excitation | unit[scan]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2038 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2039 */
const   Uint8   aName0x2039[] = "delay time between harmonic component | unit[scan]";
/** \brief Object 0x2039  delay time between harmonic component | unit[scan]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2039 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x203A */
const   Uint8   aName0x203A[] = "start frequency of sinusoidal excitation | unit[HZ]";
/** \brief Object 0x203A  start frequency of sinusoidal excitation | unit[HZ]*/
const   TSDOINFOENTRYDESC sEntryDesc0x203A = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x203B */
const   Uint8   aName0x203B[] = "step of sinusoidal excitation | unit[HZ]";
/** \brief Object 0x203B  step of sinusoidal excitation | unit[HZ]*/
const   TSDOINFOENTRYDESC sEntryDesc0x203B = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x203C */
const   Uint8   aName0x203C[] = "sinusoidal excitation numbers (numbers of sine waves)";
/** \brief Object 0x203C  sinusoidal excitation numbers (numbers of sine waves)*/
const   TSDOINFOENTRYDESC sEntryDesc0x203C = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x203D */
const   Uint8   aName0x203D[] = "amplitude of excitation signal | unit[Q10]";
/** \brief Object 0x203D  amplitude of excitation signal | unit[Q10]*/
const   TSDOINFOENTRYDESC sEntryDesc0x203D = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x203E */
const   Uint8   aName0x203E[] = "reciprocating motion times";
/** \brief Object 0x203E  reciprocating motion times*/
const   TSDOINFOENTRYDESC sEntryDesc0x203E = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x203F */
const   Uint8   aName0x203F[] = "interval time between motion | unit[scan]";
/** \brief Object 0x203F  interval time between motion | unit[scan]*/
const   TSDOINFOENTRYDESC sEntryDesc0x203F = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2040 */
const   Uint8   aName0x2040[] = "speed command hold time in reciprocate motion | unit[scan]";
/** \brief Object 0x2040  speed command hold time in reciprocate motion | unit[scan]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2040 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2041 */
const   Uint8   aName0x2041[] = "prbs division times | unit[ts]";
/** \brief Object 0x2041  prbs division times | unit[ts]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2041 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2042 */
const   Uint8   aName0x2042[] = "prbs durate time | unit[ts]";
/** \brief Object 0x2042  prbs durate time | unit[ts]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2042 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2043 */
const   Uint8   aName0x2043[] = "fn of the first low pass filter for torque filter | unit[0.1hz]";
/** \brief Object 0x2043  fn of the first low pass filter for torque filter | unit[0.1hz]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2043 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2044 */
const   Uint8   aName0x2044[] = "fn of the second low pass filter for torque filter | unit[0.1hz]";
/** \brief Object 0x2044  fn of the second low pass filter for torque filter | unit[0.1hz]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2044 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2045 */
const   Uint8   aName0x2045[] = "fn of the first notch filter for torque filter | unit[0.1hz]";
/** \brief Object 0x2045  fn of the first notch filter for torque filter | unit[0.1hz]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2045 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2046 */
const   Uint8   aName0x2046[] = "width of the first notch filter | unit[0.001]";
/** \brief Object 0x2046  width of the first notch filter | unit[0.001]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2046 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2047 */
const   Uint8   aName0x2047[] = "depth of the first notch filter | unit[0.001]";
/** \brief Object 0x2047  depth of the first notch filter | unit[0.001]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2047 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2048 */
const   Uint8   aName0x2048[] = "fn of the second notch filter for torque filter | unit[0.1hz]";
/** \brief Object 0x2048  fn of the second notch filter for torque filter | unit[0.1hz]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2048 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2049 */
const   Uint8   aName0x2049[] = "width of the second notch filter | unit[0.001]";
/** \brief Object 0x2049  width of the second notch filter | unit[0.001]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2049 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x204A */
const   Uint8   aName0x204A[] = "depth of the second notch filter | unit[0.001]";
/** \brief Object 0x204A  depth of the second notch filter | unit[0.001]*/
const   TSDOINFOENTRYDESC sEntryDesc0x204A = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x204B */
const   Uint8   aName0x204B[] = "config option of model identification module";
/** \brief Object 0x204B  config option of model identification module*/
const   TSDOINFOENTRYDESC sEntryDesc0x204B = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x204C */
const   Uint8   aName0x204C[] = "model estimate sample times | unit[ns]";
/** \brief Object 0x204C  model estimate sample times | unit[ns]*/
const   TSDOINFOENTRYDESC sEntryDesc0x204C = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x204D */
const   Uint8   aName0x204D[] = "Initialize inertia for rls algorithm | unit[10^-6 kg.m^2]";
/** \brief Object 0x204D  Initialize inertia for rls algorithm | unit[10^-6 kg.m^2]*/
const   TSDOINFOENTRYDESC sEntryDesc0x204D = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x204E */
const   Uint8   aName0x204E[] = "initialize gain of p1 coefficient for rls algorithm";
/** \brief Object 0x204E  initialize gain of p1 coefficient for rls algorithm*/
const   TSDOINFOENTRYDESC sEntryDesc0x204E = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x204F */
const   Uint8   aName0x204F[] = "the lamt coefficient for rsl algorithm realization | unit[Q24]";
/** \brief Object 0x204F  the lamt coefficient for rsl algorithm realization | unit[Q24]*/
const   TSDOINFOENTRYDESC sEntryDesc0x204F = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2050 */
const   Uint8   aName0x2050[] = "start frequency of chirp excitation | unit[HZ]";
/** \brief Object 0x2050  start frequency of chirp excitation | unit[HZ]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2050 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2051 */
const   Uint8   aName0x2051[] = "end frequency of chirp excitation | unit[HZ]";
/** \brief Object 0x2051  end frequency of chirp excitation | unit[HZ]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2051 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2052 */
const   Uint8   aName0x2052[] = "duration times of chirp signal | unit[ts]";
/** \brief Object 0x2052  the duration times of chirp signal | unit[ts]*/
const   TSDOINFOENTRYDESC sEntryDesc0x2052 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=



//#############################################################################################################################
// variable entry discription
//#############################################################################################################################
const   TSDOINFOENTRYDESC sEntryDesc0x3000 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};
/** \brief Object 0x3000 d axis current feedback */
const   Uint8   aName0x3000[] = "d axis current feedback";

//----------------------------------------------------------------------------------------------------------------------------
const   TSDOINFOENTRYDESC sEntryDesc0x3001 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};
/** \brief Object 0x3001 q axis current feedback */
const   Uint8   aName0x3001[] = "q axis current feedback";

//----------------------------------------------------------------------------------------------------------------------------
const   TSDOINFOENTRYDESC sEntryDesc0x3002 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};
/** \brief Object 0x3002 d axis current reference */
const   Uint8   aName0x3002[] = "d axis current reference";

//----------------------------------------------------------------------------------------------------------------------------
const   TSDOINFOENTRYDESC sEntryDesc0x3003 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};
/** \brief Object 0x3003 q axis current reference */
const   Uint8   aName0x3003[] = "q axis current reference";

//----------------------------------------------------------------------------------------------------------------------------
const   TSDOINFOENTRYDESC sEntryDesc0x3004 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};
/** \brief Object 0x3004 d axis current control error */
const   Uint8   aName0x3004[] = "d axis current control error";

//----------------------------------------------------------------------------------------------------------------------------
const   TSDOINFOENTRYDESC sEntryDesc0x3005 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};
/** \brief Object 0x3005 q axis current control error */
const   Uint8   aName0x3005[] = "q axis current control error";

//----------------------------------------------------------------------------------------------------------------------------
const   TSDOINFOENTRYDESC sEntryDesc0x3006 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};
/** \brief Object 0x3006 d axis voltage output */
const   Uint8   aName0x3006[] = "d axis voltage output";

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x3007 q axis voltage output*/
const   TSDOINFOENTRYDESC sEntryDesc0x3007 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};
const   Uint8   aName0x3007[] = "q axis voltage output";

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x3008  sum of d axis control output*/
const   TSDOINFOENTRYDESC sEntryDesc0x3008 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};
const   Uint8   aName0x3008[] = "sum of d axis control output";

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x3009 sum of q axis control output*/
const   TSDOINFOENTRYDESC sEntryDesc0x3009 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};
const   Uint8   aName0x3009[] = "sum of q axis control output";

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x300A[] = "sum of d axis error integral";
/** \brief Object 0x300A sum of d axis error integral*/
const   TSDOINFOENTRYDESC sEntryDesc0x300A = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x300B[] = "sum of q axis error integral";
/** \brief Object 0x300B sum of q axis error integral*/
const   TSDOINFOENTRYDESC sEntryDesc0x300B = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x300C[] = "mechancal angel rad";
/** \brief Object 0x300C mechancal angel rad*/
const   TSDOINFOENTRYDESC sEntryDesc0x300C = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x300D[] = "electrical angel rad";
/** \brief Object 0x300D  electrical angel rad*/
const   TSDOINFOENTRYDESC sEntryDesc0x300D = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x300E[] = "a phase current input";
/** \brief Object 0x300E  Motor a phase current input*/
const   TSDOINFOENTRYDESC sEntryDesc0x300E = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x300F[] = "b phase current input";
/** \brief Object 0x300F  b phase current input*/
const   TSDOINFOENTRYDESC sEntryDesc0x300F = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3010[] = "c phase current input";
/** \brief Object 0x3010  c phase current input*/
const   TSDOINFOENTRYDESC sEntryDesc0x3010 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3011[] = "a phase voltage output";
/** \brief Object 0x3011  a phase voltage output*/
const   TSDOINFOENTRYDESC sEntryDesc0x3011 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3012[] = "b phase voltage output";
/** \brief Object 0x3012  b phase voltage output*/
const   TSDOINFOENTRYDESC sEntryDesc0x3012 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3013[] = "c phase voltage output";
/** \brief Object 0x3013  c phase voltage output*/
const   TSDOINFOENTRYDESC sEntryDesc0x3013 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3014[] = "d axis voltage reference";
/** \brief Object 0x3014  d axis voltage reference*/
const   TSDOINFOENTRYDESC sEntryDesc0x3014 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3015[] = "q axis voltage reference";
/** \brief Object 0x3015 q axis voltage reference*/
const   TSDOINFOENTRYDESC sEntryDesc0x3015 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3016[] = "motor speed | unit[rad/s]";
/** \brief Object motor speed | unit[rad/s]*/
const   TSDOINFOENTRYDESC sEntryDesc0x3016 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3017[] = "encoder position input | unit[pulse]";
/** \brief Object 0x3017 encoder position input | unit[pulse]*/
const   TSDOINFOENTRYDESC sEntryDesc0x3017 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3018[] = "motor speed feedback | unit[rad/s]";
/** \brief Object 0x3018 motor speed feedback | unit[rad/s]*/
const   TSDOINFOENTRYDESC sEntryDesc0x3018 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3019[] = "motor speed reference | unit[rad/s]";
/** \brief Object 0x3019 motor speed reference | unit[rad/s]*/
const   TSDOINFOENTRYDESC sEntryDesc0x3019 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x301A[] = "speed control error | unit[rad/s]";
/** \brief Object 0x301A speed control error | unit[rad/s]*/
const   TSDOINFOENTRYDESC sEntryDesc0x301A = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x301B[] = "proportional accumulation value";
/** \brief Object 0x301B proportional accumulation value*/
const   TSDOINFOENTRYDESC sEntryDesc0x301B = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x301C[] = "intergral accumulation value";
/** \brief Object 0x301C intergral accumulation value*/
const   TSDOINFOENTRYDESC sEntryDesc0x301C = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x301D[] = "torque command output | unit[Nm]";
/** \brief Object 0x301D torque command output | unit[Nm]*/
const   TSDOINFOENTRYDESC sEntryDesc0x301D = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x301E[] = "q axis current command output | unit[A]";
/** \brief Object 0x301E q axis current command output | unit[A]*/
const   TSDOINFOENTRYDESC sEntryDesc0x301E = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x301F[] = "ramp input variable of velocity reference | unit[rad/s]";
/** \brief Object 0x301F ramp input variable of velocity reference | unit[rad/s]*/
const   TSDOINFOENTRYDESC sEntryDesc0x301F = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3020[] = "accumulate position command | unit[pulse]";
/** \brief Object 0x3020 accumulate position command | unit[pulse]*/
const   TSDOINFOENTRYDESC sEntryDesc0x3020 = {DEFTYPE_INTEGER64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3021[] = "accumulate position feedback | unit[pulse]";
/** \brief Object 0x3021 accumulate position feedback | unit[pulse]*/
const   TSDOINFOENTRYDESC sEntryDesc0x3021 = {DEFTYPE_INTEGER64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3022[] = "position control error | unit[pulse]";
/** \brief Object 0x3022 position control error | unit[pulse]*/
const   TSDOINFOENTRYDESC sEntryDesc0x3022 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3023[] = "proportional accumulation value of position control]";
/** \brief Object 0x3023 proportional accumulation value of position control*/
const   TSDOINFOENTRYDESC sEntryDesc0x3023 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3024[] = "position loop velocity command output | unit[rad/s]]";
/** \brief Object 0x3024 position loop velocity command output | unit[rad/s]*/
const   TSDOINFOENTRYDESC sEntryDesc0x3024 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3025[] = "torque feedforward command";
/** \brief Object 0x3025 torque feedforward command*/
const   TSDOINFOENTRYDESC sEntryDesc0x3025 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3026[] = "input of moving average filtering";
/** \brief Object 0x3026 input of moving average filtering*/
const   TSDOINFOENTRYDESC sEntryDesc0x3026 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3027[] = "output of moving average filtering";
/** \brief Object 0x3027 output of moving average filtering*/
const   TSDOINFOENTRYDESC sEntryDesc0x3027 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3028[] = "delta position command";
/** \brief Object 0x3028 delta position command*/
const   TSDOINFOENTRYDESC sEntryDesc0x3028 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3029[] = "delta position feedback";
/** \brief Object 0x3029 delta position command*/
const   TSDOINFOENTRYDESC sEntryDesc0x3029 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x302A[] = "singal circle encoder position";
/** \brief Object 0x302A singal circle encoder position*/
const   TSDOINFOENTRYDESC sEntryDesc0x302A = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x302B[] = "the last circle encoder position";
/** \brief Object 0x302B the last circle encoder position*/
const   TSDOINFOENTRYDESC sEntryDesc0x302B = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x302C[] = "q axis current command output of sequece control";
/** \brief Object 0x302C q axis current command output of sequece control*/
const   TSDOINFOENTRYDESC sEntryDesc0x302C = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x302D[] = "speed command output of sequence control";
/** \brief Object 0x302D speed command output of sequence control*/
const   TSDOINFOENTRYDESC sEntryDesc0x302D = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x302E[] = "position command output of sequence control";
/** \brief Object 0x302E position command output of sequence control*/
const   TSDOINFOENTRYDESC sEntryDesc0x302E = {DEFTYPE_INTEGER64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x302F[] = "the last position command output of sequence control";
/** \brief Object 0x302F the last position command output of sequence control*/
const   TSDOINFOENTRYDESC sEntryDesc0x302F = {DEFTYPE_INTEGER64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3030[] = "delta position command input of sequence control";
/** \brief Object 0x3030 delta position command input of sequence control*/
const   TSDOINFOENTRYDESC sEntryDesc0x3030 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3031[] = "delta position command output of sequence control";
/** \brief Object 0x3031 delta position command output of sequence control*/
const   TSDOINFOENTRYDESC sEntryDesc0x3031 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3032[] = "position command set value in trajectory produce";
/** \brief Object 0x3032 position command set value*/
const   TSDOINFOENTRYDESC sEntryDesc0x3032 = {DEFTYPE_INTEGER64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3033[] = "position command input value trajectory produce";
/** \brief Object 0x3033 position command input value*/
const   TSDOINFOENTRYDESC sEntryDesc0x3033 = {DEFTYPE_INTEGER64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3034[] = "position command output value trajectory produce";
/** \brief Object 0x3034 position command output value*/
const   TSDOINFOENTRYDESC sEntryDesc0x3034 = {DEFTYPE_INTEGER64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3035[] = "initialize position | unit[pulse] | for trajectory produce";
/** \brief Object 0x3035 position command output value*/
const   TSDOINFOENTRYDESC sEntryDesc0x3035 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3036[] = "finish position | unit [pulse] | for trajectory produce";
/** \brief Object 0x3036 finish position | unit [pulse]*/
const   TSDOINFOENTRYDESC sEntryDesc0x3036 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3037[] = "real position | unit [pulse] | for trajectory produce";
/** \brief Object 0x3037 real position | unit [pulse]*/
const   TSDOINFOENTRYDESC sEntryDesc0x3037 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3038[] = "increment positon between q0 to q1 | for trajectory produce";
/** \brief Object 0x3038 increment positon between q0 to q1*/
const   TSDOINFOENTRYDESC sEntryDesc0x3038 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3039[] = "initialize velocity | unit[pulse/s] | for trajectory produce";
/** \brief Object 0x3039 initialize velocity | unit[pulse/s]*/
const   TSDOINFOENTRYDESC sEntryDesc0x3039 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x303A[] = "the max velocity can be reached | unit[pulse/s] | for trajectory produce";
/** \brief Object 0x303A the max velocity can be reached | unit[pulse/s]*/
const   TSDOINFOENTRYDESC sEntryDesc0x303A = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x303B[] = "real velocity command | unit[pule/s] | for trajectory produce";
/** \brief Object 0x303B real velocity command | unit[pule/s]*/
const   TSDOINFOENTRYDESC sEntryDesc0x303B = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x303C[] = "current time | unit[s] | for trajectory produce";
/** \brief Object 0x303C current time | unit[s]*/
const   TSDOINFOENTRYDESC sEntryDesc0x303C = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x303D[] = "the real accelerate | unit[pulse/s/s] | for trajectory produce";
/** \brief Object 0x303D the real accelerate | unit[pulse/s/s]*/
const   TSDOINFOENTRYDESC sEntryDesc0x303D = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x303E[] = "trajectory produce flag | for trajectory produce";
/** \brief Object 0x303E trajectory produce flag*/
const   TSDOINFOENTRYDESC sEntryDesc0x303E = {DEFTYPE_UNSIGNED32, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x303F[] = "speed feedforward value | unit[rad/s]";
/** \brief Object 0x303F speed feedforward value | unit[rad/s] */
const   TSDOINFOENTRYDESC sEntryDesc0x303F = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3040[] = "speed feedforward output value | unit[rad/s]";
/** \brief Object 0x3040 speed feedforward output value | unit[Nm] */
const   TSDOINFOENTRYDESC sEntryDesc0x3040 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3041[] = "torque feedforward value | unit[Nm]";
/** \brief Object 0x3041 torque feedforward value | unit[Nm] */
const   TSDOINFOENTRYDESC sEntryDesc0x3041 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3042[] = "torque feedforward output value | unit[Nm]";
/** \brief Object 0x3042 torque feedforward output value | unit[Nm] */
const   TSDOINFOENTRYDESC sEntryDesc0x3042 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3043[] = "real time of current harmonic signal | unit[s]";
/** \brief Object 0x3043 real time of current harmonic signal | unit[s] */
const   TSDOINFOENTRYDESC sEntryDesc0x3043 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3044[] = "real frequency of current harmonic signal | unit[hz]";
/** \brief Object 0x3044 real frequency of current harmonic signal | unit[hz] */
const   TSDOINFOENTRYDESC sEntryDesc0x3044 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3045[] = "excition signal output";
/** \brief Object 0x3045 excition signal output */
const   TSDOINFOENTRYDESC sEntryDesc0x3045 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3046[] = "the prbs generate flag";
/** \brief Object 0x3046 the prbs generate flag */
const   TSDOINFOENTRYDESC sEntryDesc0x3046 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3047[] = "output of the first low pass filter for iq reference";
/** \brief Object 0x3047 output of the first low pass filter for iq reference */
const   TSDOINFOENTRYDESC sEntryDesc0x3047 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3048[] = "output of the second low pass filter for iq reference";
/** \brief Object 0x3048 output of the second low pass filter for iq reference */
const   TSDOINFOENTRYDESC sEntryDesc0x3048 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};


//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3049[] = "output of the first notch filter for iq reference";
/** \brief Object 0x3049 output of the first notch filter for iq reference */
const   TSDOINFOENTRYDESC sEntryDesc0x3049 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x304A[] = "output of the second notch filter for iq reference";
/** \brief Object 0x304A output of the second notch filter for iq reference */
const   TSDOINFOENTRYDESC sEntryDesc0x304A = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x304B[] = "the estimate error variable for rls algorithm design";
/** \brief the estimate error variable for rls algorithm design */
const   TSDOINFOENTRYDESC sEntryDesc0x304B = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x304C[] = "parameter coefficient0 array for rls algorithm";
/** \brief parameter coefficient0 array for rls algorithm */
const   TSDOINFOENTRYDESC sEntryDesc0x304C = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x304D[] = "parameter coefficient1 array for rls algorithm";
/** \brief parameter coefficient1 array for rls algorithm */
const   TSDOINFOENTRYDESC sEntryDesc0x304D = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x304E[] = "the estimate viscous friciton for rls algorithm| unit[Nm/rad]";
/** \brief the estimate viscous friciton for rls algorithm| unit[Nm/rad] */
const   TSDOINFOENTRYDESC sEntryDesc0x304E = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x304F[] = "Moment of inertia for rls algorithm| unit[10^-6 kg.m^2]";
/** \brief Moment of inertia for rls algorithm| unit[10^-6 kg.m^2] */
const   TSDOINFOENTRYDESC sEntryDesc0x304F = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3050[] = "gamma coefficient 0 for rls algorithm";
/** \brief gamma coefficient 0 for rls algorithm */
const   TSDOINFOENTRYDESC sEntryDesc0x3050 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
const   Uint8   aName0x3051[] = "gamma coefficient 1 for rls algorithm";
/** \brief gamma coefficient 1 for rls algorithm */
const   TSDOINFOENTRYDESC sEntryDesc0x3051 = {DEFTYPE_REAL64, 0x40, ACCESS_READWRITE};
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=



//#############################################################################################################################
// function interface define
void    CpiInitCiA402PrmObjPtr(void);
void    CpiInitCiA402VarObjPtr(void);

int16   CpiReadRamPrmByDicInx(Uint16 inx, double * m_data);
int16   CpiReadRamVarByDicInx(Uint16 inx, double * m_data);
//#############################################################################################################################
extern TOBJ_ENTRY  DefCiA402PrmObjDic[PRM_SERVO_OBJW_INX_MAX_NUM];
extern TOBJ_ENTRY  DefCiA402VarObjDic[VAR_SERVO_OBJW_INX_MAX_NUM];

//#############################################################################################################################







#endif



///////////////////////////////////////////////////////// no more /////////////////////////////////////////////////////////////

