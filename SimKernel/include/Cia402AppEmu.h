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
    PRM_SERVO_OBJW_INX_MAX_NUM
}TOBJ_WORD_PRM_INDEX;

//#############################################################################################################################
typedef enum
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    ID_CCTL_VAR_OBJW_3000H                      =   0,                                      // d axis current feedback
    IQ_CCTL_VAR_OBJW_3001H                      =   1,                                      // q axis current feedback
    ID_REF_CCTL_VAR_OBJW_3002H                  =   2,                                      // d axis current reference
    IQ_REF_CCTL_VAR_OBJW_3003H                  =   3,                                      // q axis current reference

    ID_ERR_CCTL_VAR_OBJW_3004H                  =   4,                                      // d axis current control error
    IQ_ERR_CCTL_VAR_OBJW_3005H                  =   5,                                      // q axis current control error
    UD_CCTL_VAR_OBJW_3006H                      =   6,                                      // d axis voltage output
    UQ_CCTL_VAR_OBJW_3007H                      =   7,                                      // q axis voltage output

    ID_S_CCTL_VAR_OBJW_3008H                    =   8,                                      // sum of d axis control output
    IQ_S_CCTL_VAR_OBJW_3009H                    =   9,                                      // sum of q axis control output
    IDI_S_CCTL_VAR_OBJW_300AH                   =   10,                                     // sum of d axis error integral
    IQI_S_CCTL_VAR_OBJW_300BH                   =   11,                                     // sum of q axis error integral

    PHIM_CCTL_VAR_OBJW_300CH                    =   12,                                     // mechancal angel rad
    PHIE_CCTL_VAR_OBJW_300DH                    =   13,                                     // electrical angel rad
    IA_CCTL_VAR_OBJW_300EH                      =   14,                                     // a phase current input
    IB_CCTL_VAR_OBJW_300FH                      =   15,                                     // b phase current input
    IC_CCTL_VAR_OBJW_3010H                      =   16,                                     // c phase current input

    UA_CCTL_VAR_OBJW_3011H                      =   17,                                     // a phase voltage output
    UB_CCTL_VAR_OBJW_3012H                      =   18,                                     // b phase voltage output
    UC_CCTL_VAR_OBJW_3013H                      =   19,                                     // c phase voltage output
    UD_REF_CCTL_VAR_OBJW_3014H                  =   20,                                     // d axis voltage reference
    UQ_REF_CCTL_VAR_OBJW_3015H                  =   21,                                     // q axis voltage reference
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
const   TSDOINFOENTRYDESC sEntryDesc0x2009 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};
/** \brief Object 0x2009 */
const   Uint8   aName0x2009[] = "Over speed unit(max speed) | unit[RPM]";

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x200A Motor rated torque entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x200A = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};
/** \brief Object 0x200A */
const   Uint8   aName0x200A[] = "Motor rated torque | unit[0.001 N.m]";

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x200B */
const   Uint8   aName0x200B[] = "EMF constant | unit[0.1mV/r/min]";
/** \brief Object 0x200B EMF constant*/
const   TSDOINFOENTRYDESC sEntryDesc0x200B = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x200C */
const   Uint8   aName0x200C[] = " Motor d axis reactive inductance | unit[0.001mH]";
/** \brief Object 0x200C Motor d axis reactive resistance entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x200C = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x200D */
const   Uint8   aName0x200D[] = "Motor q axis reactive inductance | unit[0.001mH]";
/** \brief Object 0x200D  Motor q axis reactive resistance entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x200D = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x200E */
const   Uint8   aName0x200E[] = "Motor rotate winding resistance | unit[1 m ohm]";
/** \brief Object 0x200E  Motor rotate winding resistance entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x200E = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x200F */
const   Uint8   aName0x200F[] = "Rotary inertia of motor | unit[10^-6 kg.m^2]";
/** \brief Object 0x200F  Rotary inertia of motor entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x200F = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2010 */
const   Uint8   aName0x2010[] = "Digital control sample periods | unit[1ns]";
/** \brief Object 0x2010  Digital control sample periods entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x2010 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2011 */
const   Uint8   aName0x2011[] = "D axis integral time constant | unit[us]";
/** \brief Object 0x2011  D axis integral time constant  entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x2011 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};

//----------------------------------------------------------------------------------------------------------------------------
/** \brief Object 0x2012 */
const   Uint8   aName0x2012[] = "Q axis integral time constant | unit[us]";
/** \brief Object 0x2012  Q axis integral time constant entry description*/
const   TSDOINFOENTRYDESC sEntryDesc0x2012 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};


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











///////////////////////////////////////////////////////// no more ////////////////////////////////////////////////////////////
