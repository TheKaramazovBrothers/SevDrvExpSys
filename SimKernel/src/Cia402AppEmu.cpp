//=========================================================================================================
// project		:	servo system object dword table define
// File			:	SevCtlPrmTblDef.cpp
// discription	:	use in servo system parameter table define
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g
// date			:	2022/07/12
// copyright(C)	:	liu.g	(2022-2032)
//=========================================================================================================
#include    "BackGroundTask.h"
#include    "SevCtlPrmTblDef.h"
#include    "Cia402AppEmu.h"


//#############################################################################################################################
TOBJ_ENTRY  DefCiA402PrmObjDic[PRM_SERVO_OBJW_INX_MAX_NUM] =
{   /*0x2000*/
   {0x2000, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2000, aName0x2000, NULL, NULL, NULL, SRAT_MOT_PRM_ID16_ADR},
   /*2001*/
   {0x2001, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2001, aName0x2001, NULL, NULL, NULL, PPN_MOT_PRM_ID16_ADR},
   /* Object 0x2002 */
   {0x2002, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2002, aName0x2002, NULL, NULL, NULL, JRAT_MOT_PRM_ID16_ADR},
   /* Object 0x2003 */
   {0x2003, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2003, aName0x2003, NULL, NULL, NULL, VMAX_MOT_PRM_ID16_ADR},
   /*2004*/
   {0x2004, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2004, aName0x2004, NULL, NULL, NULL, FND_CCLD_PRM_ID16_ADR},
    /* Object 0x2005 */
   {0x2005, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2005, aName0x2005, NULL, NULL, NULL, FNQ_CCLD_PRM_ID16_ADR},
   /*0x2006*/
   {0x2006, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2006, aName0x2006, NULL, NULL, NULL, IRATE_MOT_PRM_ID32_ADR},
   /* Object 0x2007 */
   {0x2007, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2007, aName0x2007, NULL, NULL, NULL, IMAX_MOT_PRM_ID32_ADR},
   /* Object 0x2008 */
   {0x2008, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2008, aName0x2008, NULL, NULL, NULL, SCT_MOT_PRM_ID32_ADR},
   /* Object 0x2009 */
   {0x2009, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2009, aName0x2009, NULL, NULL, NULL, NOS_MOT_PRM_ID32_ADR},
   /* Object 0x200A */
   {0x200A, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x200A, aName0x200A, NULL, NULL, NULL, TQR_MOT_PRM_ID32_ADR},
   /* Object 0x200B */
   {0x200B, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x200B, aName0x200B, NULL, NULL, NULL, PHIM_MOT_PRM_ID32_ADR},
   /* Object 0x200C */
   {0x200C, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x200C, aName0x200C, NULL, NULL, NULL, LDM_MOT_PRM_ID32_ADR},
   /* Object 0x200D */
   {0x200D, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x200D, aName0x200D, NULL, NULL, NULL, LQM_MOT_PRM_ID32_ADR},
   /* Object 0x200E */
   {0x200E, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x200E, aName0x200E, NULL, NULL, NULL, RM_MOT_PRM_ID32_ADR},
   /* Object 0x200F */
   {0x200F, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x200F, aName0x200F, NULL, NULL, NULL, JM_MOT_PRM_ID32_ADR},
   /* Object 0x2010 */
   {0x2010, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2010, aName0x2010, NULL, NULL, NULL, TS_ISR_PRM_ID32_ADR},
   /* Object 0x2011 */
   {0x2011, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2011, aName0x2011, NULL, NULL, NULL, TID_CCTL_PRM_ID32_ADR},
    /* Object 0x2012 */
   {0x2012, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2012, aName0x2012, NULL, NULL, NULL, TIQ_CCTL_PRM_ID32_ADR}
};
/*ECATCHANGE_END(V5.11) COE1*/
//#############################################################################################################################
TOBJ_ENTRY  DefCiA402VarObjDic[VAR_SERVO_OBJW_INX_MAX_NUM]  =
{   /*0x3000*/
    {0x3000, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3000, aName0x3000, NULL, NULL, NULL, NULL},
    /*3001*/
    {0x3001, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3001, aName0x3001, NULL, NULL, NULL, NULL},
    /* Object 0x3002 */
    {0x3002, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3002, aName0x3002, NULL, NULL, NULL, NULL},
    /* Object 0x3003 */
    {0x3003, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3003, aName0x3003, NULL, NULL, NULL, NULL},
    /*3004*/
    {0x3004, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3004, aName0x3004, NULL, NULL, NULL, NULL},
     /* Object 0x3005 */
    {0x3005, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3005, aName0x3005, NULL, NULL, NULL, NULL},
    /*0x3006*/
    {0x3006, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3006, aName0x3006, NULL, NULL, NULL, NULL},
    /* Object 0x3007 */
    {0x3007, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3007, aName0x3007, NULL, NULL, NULL, NULL},
    /* Object 0x3008 */
    {0x3008, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3008, aName0x3008, NULL, NULL, NULL, NULL},
    /* Object 0x3009 */
    {0x3009, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3009, aName0x3009, NULL, NULL, NULL, NULL},
    /* Object 0x300A */
    {0x300A, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x300A, aName0x300A, NULL, NULL, NULL, NULL},
    /* Object 0x300B */
    {0x300B, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x300B, aName0x300B, NULL, NULL, NULL, NULL},
    /* Object 0x300C */
    {0x300C, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x300C, aName0x300C, NULL, NULL, NULL, NULL},
    /* Object 0x300D */
    {0x300D, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x300D, aName0x300D, NULL, NULL, NULL, NULL},
    /* Object 0x300E */
    {0x300E, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x300E, aName0x300E, NULL, NULL, NULL, NULL},
    /* Object 0x300F */
    {0x300F, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x300F, aName0x300F, NULL, NULL, NULL, NULL},
    /* Object 0x3010 */
    {0x3010, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3010, aName0x3010, NULL, NULL, NULL, NULL},
    /* Object 0x3011 */
    {0x3011, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3011, aName0x3011, NULL, NULL, NULL, NULL},
     /* Object 0x3012 */
    {0x3012, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3012, aName0x3012, NULL, NULL, NULL, NULL},
    /* Object 0x3013 */
    {0x3013, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3013, aName0x3013, NULL, NULL, NULL, NULL},
    /* Object 0x3014 */
    {0x3014, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3014, aName0x3014, NULL, NULL, NULL, NULL},
    /* Object 0x3015 */
    {0x3015, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3015, aName0x3015, NULL, NULL, NULL, NULL}
};


void    CpiInitCiA402PrmObjPtr(void)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    DefCiA402PrmObjDic[SRAT_MOT_PRM_ID16_OBJW_2000H].pVarPtr                =   ((void *)(&gSevDrv.obj.cur.prm.mot_Srat));
    DefCiA402PrmObjDic[PPN_MOT_PRM_ID16_OBJW_2001H].pVarPtr                 =   ((void *)(&gSevDrv.obj.cur.prm.mot_PPN));
    DefCiA402PrmObjDic[JRAT_MOT_PRM_ID16_OBJW_2002H].pVarPtr                =   ((void *)(&gSevDrv.obj.cur.prm.mot_Jrat));
    DefCiA402PrmObjDic[VMAX_MOT_PRM_ID16_OBJW_2003H].pVarPtr                =   ((void *)(&gSevDrv.obj.cur.prm.mot_Vmax));
    DefCiA402PrmObjDic[FND_CCLD_PRM_ID16_OBJW_2004H].pVarPtr                =   ((void *)(&gSevDrv.obj.cur.prm.curr_ctl_fnd));
    DefCiA402PrmObjDic[FNQ_CCLD_PRM_ID16_OBJW_2005H].pVarPtr                =   ((void *)(&gSevDrv.obj.cur.prm.curr_ctl_fnq));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    DefCiA402PrmObjDic[IRATE_MOT_PRM_ID32_OBJW_2006H].pVarPtr               =   ((void *)(&gSevDrv.obj.cur.prm.mot_Irat));
    DefCiA402PrmObjDic[IMAX_MOT_PRM_ID32_OBJW_2007H].pVarPtr                =   ((void *)(&gSevDrv.obj.cur.prm.mot_Imax));
    DefCiA402PrmObjDic[SCT_MOT_PRM_ID32_OBJW_2008H].pVarPtr                 =   ((void *)(&gSevDrv.obj.cur.prm.mot_Sct));
    DefCiA402PrmObjDic[NOS_MOT_PRM_ID32_OBJW_2009H].pVarPtr                 =   ((void *)(&gSevDrv.obj.cur.prm.mot_Nos));
    DefCiA402PrmObjDic[TQR_MOT_PRM_ID32_OBJW_200AH].pVarPtr                 =   ((void *)(&gSevDrv.obj.cur.prm.mot_Tqr));
    DefCiA402PrmObjDic[PHIM_MOT_PRM_ID32_OBJW_200BH].pVarPtr                =   ((void *)(&gSevDrv.obj.cur.prm.mot_PHIm));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    DefCiA402PrmObjDic[LDM_MOT_PRM_ID32_OBJW_200CH].pVarPtr                 =   ((void *)(&gSevDrv.obj.cur.prm.mot_Ldm));
    DefCiA402PrmObjDic[LQM_MOT_PRM_ID32_OBJW_200DH].pVarPtr                 =   ((void *)(&gSevDrv.obj.cur.prm.mot_Lqm));
    DefCiA402PrmObjDic[RM_MOT_PRM_ID32_OBJW_200EH].pVarPtr                  =   ((void *)(&gSevDrv.obj.cur.prm.mot_Rm));
    DefCiA402PrmObjDic[JM_MOT_PRM_ID32_OBJW_200FH].pVarPtr                  =   ((void *)(&gSevDrv.obj.cur.prm.mot_Jm));
    DefCiA402PrmObjDic[TS_ISR_PRM_ID32_OBJW_2010H].pVarPtr                  =   ((void *)(&gSevDrv.obj.cur.prm.curr_TS)) ;
    DefCiA402PrmObjDic[TID_CCTL_PRM_ID32_OBJW_2011H].pVarPtr                =   ((void *)(&gSevDrv.obj.cur.prm.curr_ctl_Tid));
    DefCiA402PrmObjDic[TIQ_CCTL_PRM_ID32_OBJW_2012H].pVarPtr                =   ((void *)(&gSevDrv.obj.cur.prm.curr_ctl_Tiq));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

void    CpiInitCiA402VarObjPtr(void)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    DefCiA402VarObjDic[ID_CCTL_VAR_OBJW_3000H].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.id));        // d axis current feedback
    DefCiA402VarObjDic[IQ_CCTL_VAR_OBJW_3001H].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.iq));                                      // q axis current feedback
    DefCiA402VarObjDic[ID_REF_CCTL_VAR_OBJW_3002H].pVarPtr                  =   ((void *)(&gSevDrv.obj.cur.id_ref));                                      // d axis current reference
    DefCiA402VarObjDic[IQ_REF_CCTL_VAR_OBJW_3003H].pVarPtr                  =   ((void *)(&gSevDrv.obj.cur.iq_ref));                                      // q axis current reference

    DefCiA402VarObjDic[ID_ERR_CCTL_VAR_OBJW_3004H].pVarPtr                  =   ((void *)(&gSevDrv.obj.cur.id_err));                                      // d axis current control error
    DefCiA402VarObjDic[IQ_ERR_CCTL_VAR_OBJW_3005H].pVarPtr                  =   ((void *)(&gSevDrv.obj.cur.iq_err));                                      // q axis current control error
    DefCiA402VarObjDic[UD_CCTL_VAR_OBJW_3006H].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.ud));                                      // d axis voltage output
    DefCiA402VarObjDic[UQ_CCTL_VAR_OBJW_3007H].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.uq));                                      // q axis voltage output

    DefCiA402VarObjDic[ID_S_CCTL_VAR_OBJW_3008H].pVarPtr                    =   ((void *)(&gSevDrv.obj.cur.id_s));                                      // sum of d axis control output
    DefCiA402VarObjDic[IQ_S_CCTL_VAR_OBJW_3009H].pVarPtr                    =   ((void *)(&gSevDrv.obj.cur.iq_s));                                      // sum of q axis control output
    DefCiA402VarObjDic[IDI_S_CCTL_VAR_OBJW_300AH].pVarPtr                   =   ((void *)(&gSevDrv.obj.cur.idi_s));                                     // sum of d axis error integral
    DefCiA402VarObjDic[IQI_S_CCTL_VAR_OBJW_300BH].pVarPtr                   =   ((void *)(&gSevDrv.obj.cur.iqi_s));                                     // sum of q axis error integral

    DefCiA402VarObjDic[PHIM_CCTL_VAR_OBJW_300CH].pVarPtr                    =   ((void *)(&gSevDrv.obj.cur.phim));                                     // mechancal angel rad
    DefCiA402VarObjDic[PHIE_CCTL_VAR_OBJW_300DH].pVarPtr                    =   ((void *)(&gSevDrv.obj.cur.phie));                                     // electrical angel rad
    DefCiA402VarObjDic[IA_CCTL_VAR_OBJW_300EH].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.ia));                                     // a phase current input
    DefCiA402VarObjDic[IB_CCTL_VAR_OBJW_300FH].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.ib));                                     // b phase current input
    DefCiA402VarObjDic[IC_CCTL_VAR_OBJW_3010H].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.ic));                                     // c phase current input

    DefCiA402VarObjDic[UA_CCTL_VAR_OBJW_3011H].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.ua));                                     // a phase voltage output
    DefCiA402VarObjDic[UB_CCTL_VAR_OBJW_3012H].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.ub));                                     // b phase voltage output
    DefCiA402VarObjDic[UC_CCTL_VAR_OBJW_3013H].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.uc));                                     // c phase voltage output
    DefCiA402VarObjDic[UD_REF_CCTL_VAR_OBJW_3014H].pVarPtr                  =   ((void *)(&gSevDrv.obj.cur.ud_ref));                                     // d axis voltage reference
    DefCiA402VarObjDic[UQ_REF_CCTL_VAR_OBJW_3015H].pVarPtr                  =   ((void *)(&gSevDrv.obj.cur.uq_ref));                                     // q axis voltage reference
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


int16   CpiReadRamPrmByDicInx(Uint16 inx, double * m_data)
{
    TSDOINFOENTRYDESC   sdo_inf;
    Uint32  lutmp;
    Uint16  utmp;
    double  dtmp;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (inx < PRM_SERVO_OBJW_INX_MAX_NUM)
    {
        sdo_inf                     =   *DefCiA402PrmObjDic[inx].pEntryDesc;
        if (sdo_inf.BitLength == 0x20)
        {
            lutmp                   =   *((Uint32 *)(DefCiA402PrmObjDic[inx].pVarPtr));
            dtmp                    =   lutmp;
        }
        else
        {
            utmp                    =   *((Uint16 *)(DefCiA402PrmObjDic[inx].pVarPtr));
            dtmp                    =   utmp;
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        *m_data                     =   dtmp;
        return  TRUE;
    }
    else
    {
        return  FALSE;
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}



int16   CpiReadRamVarByDicInx(Uint16 inx, double * m_data)
{
   double  dtmp;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
   if (inx  < VAR_SERVO_OBJW_INX_MAX_NUM)
   {
       dtmp                         =   *((double *)(DefCiA402VarObjDic[inx].pVarPtr));
       *m_data                      =   dtmp;
       return  TRUE;
   }
   else
   {
       return  FALSE;
   }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


//#############################################################################################################################
