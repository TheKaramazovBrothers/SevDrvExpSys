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
   {0x2012, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2012, aName0x2012, NULL, NULL, NULL, TIQ_CCTL_PRM_ID32_ADR},
    /* Object 0x2013 */
   {0x2013, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2013, aName0x2013, NULL, NULL, NULL, LINE_NUM_ENC_PRM_ID32_ADR},
    /* Object 0x2014 */
   {0x2014, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2014, aName0x2014, NULL, NULL, NULL, FNV_FST_VCTL_PRM_ID32_ADR},
    /* Object 0x2015 */
   {0x2015, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2015, aName0x2015, NULL, NULL, NULL, TIV_FST_VCTL_PRM_ID32_ADR},
    /* Object 0x2016 */
   {0x2016, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2016, aName0x2016, NULL, NULL, NULL, FNV_SEC_VCTL_PRM_ID32_ADR},
    /* Object 0x2017 */
   {0x2017, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2017, aName0x2017, NULL, NULL, NULL, TIV_SEC_VCTL_PRM_ID32_ADR},
    /* Object 0x2018 */
   {0x2018, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2018, aName0x2018, NULL, NULL, NULL, TS_VCTL_PRM_ID32_ADR},
    /* Object 0x2019 */
   {0x2019, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2019, aName0x2019, NULL, NULL, NULL, TF_RMP_VCTL_PRM_ID32_ADR},
    /* Object 0x201a */
   {0x201a, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x201A, aName0x201A, NULL, NULL, NULL, CFG_OPT_ALL_PRM_ID32_ADR},
    /* Object 0x201b */
   {0x201b, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x201B, aName0x201B, NULL, NULL, NULL, ABS_RAT_TQR_LIM_VCTL_PRM_ID16_ADR},
    /* Object 0x201c */
   {0x201c, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x201C, aName0x201D, NULL, NULL, NULL, POS_RAT_TQR_LIM_VCTL_PRM_ID16_ADR},
    /* Object 0x201d */
   {0x201d, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x201D, aName0x201D, NULL, NULL, NULL, NEG_RAT_TQR_LIM_VCTL_PRM_ID16_ADR},
    /* Object 0x201E */
   {0x201E, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x201E, aName0x201E, NULL, NULL, NULL, TS_POS_CTL_PRM_ID32_ADR},
    /* Object 0x201F */
   {0x201F, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x201F, aName0x201F, NULL, NULL, NULL, CFG_OPT_ALL_PCTL_PRM_ID32_ADR},
    /* Object 0x2020 */
   {0x2020, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2020, aName0x2020, NULL, NULL, NULL, FNP_FST_PCTL_PRM_ID16_ADR},
    /* Object 0x2021 */
   {0x2021, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2021, aName0x2021, NULL, NULL, NULL, FNP_SEC_PCTL_PRM_ID16_ADR},
    /* Object 0x2022 */
   {0x2022, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2022, aName0x2022, NULL, NULL, NULL, ABS_RAT_SPD_LIM_PCTL_PRM_ID16_ADR},
    /* Object 0x2023 */
   {0x2023, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2023, aName0x2023, NULL, NULL, NULL, POS_RAT_SPD_LIM_PCTL_PRM_ID16_ADR},
    /* Object 0x2024 */
   {0x2024, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2024, aName0x2024, NULL, NULL, NULL, NEG_RAT_SPD_LIM_PCTL_PRM_ID16_ADR},
    /* Object 0x2025 */
   {0x2025, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2025, aName0x2025, NULL, NULL, NULL, MAF_NUM_PCTL_PRM_ID16_ADR},
    /* Object 0x2026 */
   {0x2026, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2026, aName0x2026, NULL, NULL, NULL, PSRC_SEL_SEQ_CTL_PRM_ID16_ADR},
    /* Object 0x2027 */
   {0x2027, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2027, aName0x2027, NULL, NULL, NULL, VSRC_SEL_SEQ_CTL_PRM_ID16_ADR},
    /* Object 0x2028 */
   {0x2028, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2028, aName0x2028, NULL, NULL, NULL, CSRC_SEL_SEQ_CTL_PRM_ID16_ADR},
    /* Object 0x2029 */
   {0x2029, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2029, aName0x2029, NULL, NULL, NULL, CMD_DIR_SEQ_CTL_PRM_ID16_ADR},
    /* Object 0x202A */
   {0x202A, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x202A, aName0x202A, NULL, NULL, NULL, CFG_OPT_ALL_SEQ_CTL_PRM_ID32_ADR},
    /* Object 0x202B */
   {0x202B, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x202B, aName0x202B, NULL, NULL, NULL, ROT_RES_POS_TRAJ_PRM_ID32_ADR},
    /* Object 0x202C */
   {0x202C, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x202C, aName0x202C, NULL, NULL, NULL, TS_POS_TRAJ_PRM_ID32_ADR},
    /* Object 0x202D */
   {0x202D, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x202D, aName0x202D, NULL, NULL, NULL, ACCRATE_POS_TRAJ_PRM_ID32_ADR},
    /* Object 0x202E */
   {0x202E, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x202E, aName0x202E, NULL, NULL, NULL, DECRATE_POS_TRAJ_PRM_ID32_ADR},
    /* Object 0x202F */
   {0x202F, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x202F, aName0x202F, NULL, NULL, NULL, MAXSPD_POS_TRAJ_PRM_ID32_ADR},
    /* Object 0x2030 */
   {0x2030, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2030, aName0x2030, NULL, NULL, NULL, CFG_OPT_ALL_POS_TRAJ_PRM_ID32_ADR},
    /* Object 0x2031 */
   {0x2031, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2031, aName0x2031, NULL, NULL, NULL, FFV_RATE_PCTL_PRM_ID16_ADR},
    /* Object 0x2032 */
   {0x2032, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2032, aName0x2032, NULL, NULL, NULL, FFT_RATE_PCTL_PRM_ID16_ADR},
    /* Object 0x2033 */
   {0x2033, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2033, aName0x2033, NULL, NULL, NULL, FFJ_RATE_PCTL_PRM_ID32_ADR},
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
    {0x3015, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3015, aName0x3015, NULL, NULL, NULL, NULL},
    /* Object 0x3016 */
    {0x3016, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3016, aName0x3016, NULL, NULL, NULL, NULL},
    /* Object 0x3017 */
    {0x3017, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3017, aName0x3017, NULL, NULL, NULL, NULL},
    /* Object 0x3018 */
    {0x3018, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3018, aName0x3018, NULL, NULL, NULL, NULL},
    /* Object 0x3019 */
    {0x3019, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3019, aName0x3019, NULL, NULL, NULL, NULL},
    /* Object 0x301a */
    {0x301a, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x301A, aName0x301A, NULL, NULL, NULL, NULL},
    /* Object 0x301b */
    {0x301b, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x301B, aName0x301B, NULL, NULL, NULL, NULL},
    /* Object 0x301c */
    {0x301c, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x301C, aName0x301C, NULL, NULL, NULL, NULL},
    /* Object 0x301d */
    {0x301d, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x301D, aName0x301D, NULL, NULL, NULL, NULL},
    /* Object 0x301e */
    {0x301e, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x301E, aName0x301E, NULL, NULL, NULL, NULL},
    /* Object 0x301f */
    {0x301f, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x301F, aName0x301F, NULL, NULL, NULL, NULL},
    /* Object 0x3020 */
    {0x3020, {DEFTYPE_INTEGER64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3020, aName0x3020, NULL, NULL, NULL, NULL},
    /* Object 0x3021 */
    {0x3021, {DEFTYPE_INTEGER64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3021, aName0x3021, NULL, NULL, NULL, NULL},
    /* Object 0x3022 */
    {0x3022, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3022, aName0x3022, NULL, NULL, NULL, NULL},
    /* Object 0x3023 */
    {0x3023, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3023, aName0x3023, NULL, NULL, NULL, NULL},
    /* Object 0x3024 */
    {0x3024, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3024, aName0x3024, NULL, NULL, NULL, NULL},
    /* Object 0x3025 */
    {0x3025, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3025, aName0x3025, NULL, NULL, NULL, NULL},
    /* Object 0x3026 */
    {0x3026, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3026, aName0x3026, NULL, NULL, NULL, NULL},
    /* Object 0x3027 */
    {0x3027, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3027, aName0x3027, NULL, NULL, NULL, NULL},
    /* Object 0x3028 */
    {0x3028, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3028, aName0x3028, NULL, NULL, NULL, NULL},
    /* Object 0x3029 */
    {0x3029, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3029, aName0x3029, NULL, NULL, NULL, NULL},
    /* Object 0x302A */
    {0x302A, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x302A, aName0x302A, NULL, NULL, NULL, NULL},
    /* Object 0x302B */
    {0x302B, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x302B, aName0x302B, NULL, NULL, NULL, NULL},
    /* Object 0x302C */
    {0x302C, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x302C, aName0x302C, NULL, NULL, NULL, NULL},
    /* Object 0x302D */
    {0x302D, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x302D, aName0x302D, NULL, NULL, NULL, NULL},
    /* Object 0x302E */
    {0x302E, {DEFTYPE_INTEGER64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x302E, aName0x302E, NULL, NULL, NULL, NULL},
    /* Object 0x302F */
    {0x302F, {DEFTYPE_INTEGER64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x302F, aName0x302F, NULL, NULL, NULL, NULL},
    /* Object 0x3030 */
    {0x3030, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3030, aName0x3030, NULL, NULL, NULL, NULL},
    /* Object 0x3031 */
    {0x3031, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3031, aName0x3031, NULL, NULL, NULL, NULL},
    /* Object 0x3032 */
    {0x3032, {DEFTYPE_INTEGER64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3032, aName0x3032, NULL, NULL, NULL, NULL},
    /* Object 0x3033 */
    {0x3033, {DEFTYPE_INTEGER64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3033, aName0x3033, NULL, NULL, NULL, NULL},
    /* Object 0x3034 */
    {0x3034, {DEFTYPE_INTEGER64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3034, aName0x3034, NULL, NULL, NULL, NULL},
    /* Object 0x3035 */
    {0x3035, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3035, aName0x3035, NULL, NULL, NULL, NULL},
    /* Object 0x3036 */
    {0x3036, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3036, aName0x3036, NULL, NULL, NULL, NULL},
    /* Object 0x3037 */
    {0x3037, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3037, aName0x3037, NULL, NULL, NULL, NULL},
    /* Object 0x3038 */
    {0x3038, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3038, aName0x3038, NULL, NULL, NULL, NULL},
    /* Object 0x3039 */
    {0x3039, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3039, aName0x3039, NULL, NULL, NULL, NULL},
    /* Object 0x303A */
    {0x303A, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x303A, aName0x303A, NULL, NULL, NULL, NULL},
    /* Object 0x303B */
    {0x303B, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x303B, aName0x303B, NULL, NULL, NULL, NULL},
    /* Object 0x303C */
    {0x303C, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x303C, aName0x303C, NULL, NULL, NULL, NULL},
    /* Object 0x303D */
    {0x303D, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x303D, aName0x303D, NULL, NULL, NULL, NULL},
    /* Object 0x303E */
    {0x303E, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x303E, aName0x303E, NULL, NULL, NULL, NULL},    
    /* Object 0x303F */
    {0x303F, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x303F, aName0x303F, NULL, NULL, NULL, NULL},
    /* Object 0x3040 */
    {0x3040, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3040, aName0x3040, NULL, NULL, NULL, NULL},
    /* Object 0x3041 */
    {0x3041, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3041, aName0x3041, NULL, NULL, NULL, NULL},
    /* Object 0x3042 */
    {0x3042, {DEFTYPE_REAL64 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x3042, aName0x3042, NULL, NULL, NULL, NULL},
};

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

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
    DefCiA402PrmObjDic[LINE_NUM_ENC_PRM_ID32_OBJW_2013H].pVarPtr            =   ((void *)(&gSevDrv.obj.sens.prm.enc_line_num));                                 // line number of encoder in one circle | unit[pulse]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    DefCiA402PrmObjDic[FNV_FST_VCTL_PRM_ID32_OBJW_2014H].pVarPtr            =   ((void *)(&gSevDrv.obj.vel.prm.fnv_fst));                                       // velocity loop gain band width | unit[0.1Hz]
    DefCiA402PrmObjDic[TIV_FST_VCTL_PRM_ID32_OBJW_2015H].pVarPtr            =   ((void *)(&gSevDrv.obj.vel.prm.tiv_fst));                                       // velocity loop integral time constant | unit[0.01ms]
    DefCiA402PrmObjDic[FNV_SEC_VCTL_PRM_ID32_OBJW_2016H].pVarPtr            =   ((void *)(&gSevDrv.obj.vel.prm.fnv_sec));                                       // the second velocity loop gain bandwidth | unit[0.1Hz]
    DefCiA402PrmObjDic[TIV_SEC_VCTL_PRM_ID32_OBJW_2017H].pVarPtr            =   ((void *)(&gSevDrv.obj.vel.prm.tiv_sec));                                 // the second velocity loop integral time constant | unit[0.01ms]
    DefCiA402PrmObjDic[TS_VCTL_PRM_ID32_OBJW_2018H].pVarPtr                 =   ((void *)(&gSevDrv.obj.vel.prm.ts));                                            // velocity loop sample times | unit[ns]

    DefCiA402PrmObjDic[TF_RMP_VCTL_PRM_ID32_OBJW_2019H].pVarPtr             =   ((void *)(&gSevDrv.obj.vel.prm.tf_rmp));                                        // ramp time constant of velocity command | unit[ms]
    DefCiA402PrmObjDic[CFG_OPT_ALL_PRM_ID32_OBJW_201AH].pVarPtr             =   ((void *)(&gSevDrv.obj.vel.prm.cfg_opt.all));                                   // velocity control config option

    DefCiA402PrmObjDic[ABS_RAT_TQR_LIM_VCTL_PRM_ID16_OBJW_201BH].pVarPtr    =   ((void *)(&gSevDrv.obj.vel.prm.abs_rat));                                       // max torque limit rate | unit[Q12]
    DefCiA402PrmObjDic[POS_RAT_TQR_LIM_VCTL_PRM_ID16_OBJW_201CH].pVarPtr    =   ((void *)(&gSevDrv.obj.vel.prm.pos_rat));                                       // positive tqrque limit rate | unit[Q12]
    DefCiA402PrmObjDic[NEG_RAT_TQR_LIM_VCTL_PRM_ID16_OBJW_201DH].pVarPtr    =   ((void *)(&gSevDrv.obj.vel.prm.neg_rat));                                       // negative tqrque limit rate | unit[Q12]
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    DefCiA402PrmObjDic[TS_POS_CTL_PRM_ID32_OBJW_201EH].pVarPtr              =   ((void *)(&gSevDrv.obj.pos.prm.ts));
    DefCiA402PrmObjDic[CFG_OPT_ALL_PCTL_PRM_ID32_OBJW_201FH].pVarPtr        =   ((void *)(&gSevDrv.obj.pos.prm.cfg_opt.all));
    DefCiA402PrmObjDic[FNP_FST_PCTL_PRM_ID16_OBJW_2020H].pVarPtr            =   ((void *)(&gSevDrv.obj.pos.prm.fnp_fst));
    DefCiA402PrmObjDic[FNP_SEC_PCTL_PRM_ID16_OBJW_2021H].pVarPtr            =   ((void *)(&gSevDrv.obj.pos.prm.fnp_sec));

    DefCiA402PrmObjDic[ABS_RAT_SPD_LIM_PCTL_PRM_ID16_OBJW_2022H].pVarPtr    =   ((void *)(&gSevDrv.obj.pos.prm.abs_rat));
    DefCiA402PrmObjDic[POS_RAT_SPD_LIM_PCTL_PRM_ID16_OBJW_2023H].pVarPtr    =   ((void *)(&gSevDrv.obj.pos.prm.pos_rat));
    DefCiA402PrmObjDic[NEG_RAT_SPD_LIM_PCTL_PRM_ID16_OBJW_2024H].pVarPtr    =   ((void *)(&gSevDrv.obj.pos.prm.neg_rat));
    DefCiA402PrmObjDic[MAF_NUM_PCTL_PRM_ID16_OBJW_2025H].pVarPtr            =   ((void *)(&gSevDrv.obj.pos.prm.maf_num));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    DefCiA402PrmObjDic[PSRC_SEL_SEQ_CTL_PRM_ID16_OBJW_2026H].pVarPtr        =   ((void *)(&gSevDrv.obj.seq.prm.psrc_sel));
    DefCiA402PrmObjDic[VSRC_SEL_SEQ_CTL_PRM_ID16_OBJW_2027H].pVarPtr        =   ((void *)(&gSevDrv.obj.seq.prm.vsrc_sel));
    DefCiA402PrmObjDic[CSRC_SEL_SEQ_CTL_PRM_ID16_OBJW_2028H].pVarPtr        =   ((void *)(&gSevDrv.obj.seq.prm.csrc_sel));
    DefCiA402PrmObjDic[CMD_DIR_SEQ_CTL_PRM_ID16_OBJW_2029H].pVarPtr         =   ((void *)(&gSevDrv.obj.seq.prm.cmd_dir.all));
    DefCiA402PrmObjDic[CFG_OPT_ALL_SEQ_CTL_PRM_ID32_OBJW_202AH].pVarPtr     =   ((void *)(&gSevDrv.obj.seq.prm.cfg_opt.all));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    DefCiA402PrmObjDic[ROT_RES_POS_TRAJ_PRM_ID32_OBJW_202BH].pVarPtr        =   ((void *)(&gSevDrv.obj.ptrj.prm.rot_res));
    DefCiA402PrmObjDic[TS_POS_TRAJ_PRM_ID32_OBJW_202CH].pVarPtr             =   ((void *)(&gSevDrv.obj.ptrj.prm.ts));
    DefCiA402PrmObjDic[ACCRATE_POS_TRAJ_PRM_ID32_OBJW_202DH].pVarPtr        =   ((void *)(&gSevDrv.obj.ptrj.prm.accrate));
    DefCiA402PrmObjDic[DECRATE_POS_TRAJ_PRM_ID32_OBJW_202EH].pVarPtr        =   ((void *)(&gSevDrv.obj.ptrj.prm.decrate));
    DefCiA402PrmObjDic[MAXSPD_POS_TRAJ_PRM_ID32_OBJW_202FH].pVarPtr         =   ((void *)(&gSevDrv.obj.ptrj.prm.maxspd));
    DefCiA402PrmObjDic[CFG_OPT_ALL_POS_TRAJ_PRM_ID32_OBJW_2030H].pVarPtr    =   ((void *)(&gSevDrv.obj.ptrj.prm.cfg_opt.all));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    DefCiA402PrmObjDic[FFV_RATE_PCTL_PRM_ID16_OBJW_2031H].pVarPtr           =   ((void *)(&gSevDrv.obj.pos.prm.ffv_rat));
    DefCiA402PrmObjDic[FFT_RATE_PCTL_PRM_ID16_OBJW_2032H].pVarPtr           =   ((void *)(&gSevDrv.obj.pos.prm.fft_rat));
    DefCiA402PrmObjDic[FFJ_RATE_PCTL_PRM_ID32_OBJW_2033H].pVarPtr           =   ((void *)(&gSevDrv.obj.pos.prm.ffj_kg));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=



void    CpiInitCiA402VarObjPtr(void)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    DefCiA402VarObjDic[ID_CCTL_VAR_OBJW_3000H].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.id));                                                // d axis current feedback
    DefCiA402VarObjDic[IQ_CCTL_VAR_OBJW_3001H].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.iq));                                                // q axis current feedback
    DefCiA402VarObjDic[ID_REF_CCTL_VAR_OBJW_3002H].pVarPtr                  =   ((void *)(&gSevDrv.obj.cur.id_ref));                                            // d axis current reference
    DefCiA402VarObjDic[IQ_REF_CCTL_VAR_OBJW_3003H].pVarPtr                  =   ((void *)(&gSevDrv.obj.cur.iq_ref));                                            // q axis current reference

    DefCiA402VarObjDic[ID_ERR_CCTL_VAR_OBJW_3004H].pVarPtr                  =   ((void *)(&gSevDrv.obj.cur.id_err));                                            // d axis current control error
    DefCiA402VarObjDic[IQ_ERR_CCTL_VAR_OBJW_3005H].pVarPtr                  =   ((void *)(&gSevDrv.obj.cur.iq_err));                                            // q axis current control error
    DefCiA402VarObjDic[UD_CCTL_VAR_OBJW_3006H].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.ud));                                                // d axis voltage output
    DefCiA402VarObjDic[UQ_CCTL_VAR_OBJW_3007H].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.uq));                                                // q axis voltage output

    DefCiA402VarObjDic[ID_S_CCTL_VAR_OBJW_3008H].pVarPtr                    =   ((void *)(&gSevDrv.obj.cur.id_s));                                              // sum of d axis control output
    DefCiA402VarObjDic[IQ_S_CCTL_VAR_OBJW_3009H].pVarPtr                    =   ((void *)(&gSevDrv.obj.cur.iq_s));                                              // sum of q axis control output
    DefCiA402VarObjDic[IDI_S_CCTL_VAR_OBJW_300AH].pVarPtr                   =   ((void *)(&gSevDrv.obj.cur.idi_s));                                             // sum of d axis error integral
    DefCiA402VarObjDic[IQI_S_CCTL_VAR_OBJW_300BH].pVarPtr                   =   ((void *)(&gSevDrv.obj.cur.iqi_s));                                             // sum of q axis error integral

    DefCiA402VarObjDic[PHIM_CCTL_VAR_OBJW_300CH].pVarPtr                    =   ((void *)(&gSevDrv.obj.cur.phim));                                              // mechancal angel rad
    DefCiA402VarObjDic[PHIE_CCTL_VAR_OBJW_300DH].pVarPtr                    =   ((void *)(&gSevDrv.obj.cur.phie));                                              // electrical angel rad
    DefCiA402VarObjDic[IA_CCTL_VAR_OBJW_300EH].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.ia));                                                // a phase current input
    DefCiA402VarObjDic[IB_CCTL_VAR_OBJW_300FH].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.ib));                                                // b phase current input
    DefCiA402VarObjDic[IC_CCTL_VAR_OBJW_3010H].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.ic));                                                // c phase current input

    DefCiA402VarObjDic[UA_CCTL_VAR_OBJW_3011H].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.ua));                                                // a phase voltage output
    DefCiA402VarObjDic[UB_CCTL_VAR_OBJW_3012H].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.ub));                                                // b phase voltage output
    DefCiA402VarObjDic[UC_CCTL_VAR_OBJW_3013H].pVarPtr                      =   ((void *)(&gSevDrv.obj.cur.uc));                                                // c phase voltage output
    DefCiA402VarObjDic[UD_REF_CCTL_VAR_OBJW_3014H].pVarPtr                  =   ((void *)(&gSevDrv.obj.cur.ud_ref));                                            // d axis voltage reference
    DefCiA402VarObjDic[UQ_REF_CCTL_VAR_OBJW_3015H].pVarPtr                  =   ((void *)(&gSevDrv.obj.cur.uq_ref));                                            // q axis voltage reference
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    DefCiA402VarObjDic[MOT_SPD_SENS_VAR_OBJW_3016H].pVarPtr                 =   ((void *)(&gSevDrv.obj.sens.mot_spd));
    DefCiA402VarObjDic[POS_IN_SENS_VAR_OBJW_3017H].pVarPtr                  =   ((void *)(&gSevDrv.obj.sens.pos_in));

    DefCiA402VarObjDic[SPD_FB_VCTL_VAR_OBJW_3018H].pVarPtr                  =   ((void *)(&gSevDrv.obj.vel.spd_fb));
    DefCiA402VarObjDic[SPD_REF_VCTL_VAR_OBJW_3019H].pVarPtr                 =   ((void *)(&gSevDrv.obj.vel.spd_ref));
    DefCiA402VarObjDic[SPD_ERR_VCTL_VAR_OBJW_301AH].pVarPtr                 =   ((void *)(&gSevDrv.obj.vel.spd_err));

    DefCiA402VarObjDic[XWKP_VCTL_VAR_OBJW_301BH].pVarPtr                    =   ((void *)(&gSevDrv.obj.vel.xwkp));
    DefCiA402VarObjDic[XWKI_VCTL_VAR_OBJW_301CH].pVarPtr                    =   ((void *)(&gSevDrv.obj.vel.xwki));
    DefCiA402VarObjDic[TQR_VCTL_VAR_OBJW_301DH].pVarPtr                     =   ((void *)(&gSevDrv.obj.vel.tqr));
    DefCiA402VarObjDic[IQR_VCTL_VAR_OBJW_301EH].pVarPtr                     =   ((void *)(&gSevDrv.obj.vel.iqr));
    DefCiA402VarObjDic[VELR_RAMP_IN_OBJW_301FH].pVarPtr                     =   ((void *)(&gSevDrv.obj.vel.velr_ramp_in));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    DefCiA402VarObjDic[ACC_POS_REF_PCTL_VAR_OBJW_3020H].pVarPtr             =   ((void *)(&gSevDrv.obj.pos.acc_pos_ref));
    DefCiA402VarObjDic[ACC_POS_FB_PCTL_VAR_OBJW_3021H].pVarPtr              =   ((void *)(&gSevDrv.obj.pos.acc_pos_fb));
    DefCiA402VarObjDic[POS_ERR_PCTL_VAR_OBJW_3022H].pVarPtr                 =   ((void *)(&gSevDrv.obj.pos.pos_err));

    DefCiA402VarObjDic[XWKP_PCTL_VAR_OBJW_3023H].pVarPtr                    =   ((void *)(&gSevDrv.obj.pos.xwkp));
    DefCiA402VarObjDic[SPDR_PCTL_VAR_OBJW_3024H].pVarPtr                    =   ((void *)(&gSevDrv.obj.pos.spdr));
    DefCiA402VarObjDic[TQRP_PCTL_VAR_OBJW_3025H].pVarPtr                    =   ((void *)(&gSevDrv.obj.pos.tqrp));

    DefCiA402VarObjDic[MAF_IN_PCTL_VAR_OBJW_3026H].pVarPtr                  =   ((void *)(&gSevDrv.obj.pos.maf_in));
    DefCiA402VarObjDic[MAF_OUT_PCTL_VAR_OBJW_3027H].pVarPtr                 =   ((void *)(&gSevDrv.obj.pos.maf_out));
    DefCiA402VarObjDic[DPCMD_PCTL_VAR_OBJW_3028H].pVarPtr                   =   ((void *)(&gSevDrv.obj.pos.dpcmd));
    DefCiA402VarObjDic[DPFB_PCTL_VAR_OBJW_3029H].pVarPtr                    =   ((void *)(&gSevDrv.obj.pos.dpfb));

    DefCiA402VarObjDic[SIG_POS_PCTL_VAR_OBJW_302AH].pVarPtr                 =   ((void *)(&gSevDrv.obj.pos.sig_pos));
    DefCiA402VarObjDic[SIG_POS_LST_PCTL_VAR_OBJW_302BH].pVarPtr             =   ((void *)(&gSevDrv.obj.pos.sig_pos_lst));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    DefCiA402VarObjDic[IQR_OUT_SEQ_CTL_VAR_OBJW_302CH].pVarPtr              =   ((void *)(&gSevDrv.obj.seq.iqr_out));
    DefCiA402VarObjDic[SPDR_OUT_SEQ_CTL_VAR_OBJW_302DH].pVarPtr             =   ((void *)(&gSevDrv.obj.seq.spdr_out));
    DefCiA402VarObjDic[POSR_OUT_SEQ_CTL_VAR_OBJW_302EH].pVarPtr             =   ((void *)(&gSevDrv.obj.seq.posr_out));
    DefCiA402VarObjDic[POSR_OUT_LST_SEQ_CTL_VAR_OBJW_302FH].pVarPtr         =   ((void *)(&gSevDrv.obj.seq.posr_out_lst));
    DefCiA402VarObjDic[DPCMP_IN_SEQ_CTL_VAR_OBJW_3030H].pVarPtr             =   ((void *)(&gSevDrv.obj.seq.dpcmd_in));
    DefCiA402VarObjDic[DPCMP_OUT_SEQ_CTL_VAR_OBJW_3031H].pVarPtr            =   ((void *)(&gSevDrv.obj.seq.dpcmd_out));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    DefCiA402VarObjDic[PTRAJ_SET_POS_TRAJ_VAR_OBJW_3032H].pVarPtr           =   ((void *)(&gSevDrv.obj.ptrj.ptraj_set));
    DefCiA402VarObjDic[PTRAJ_IN_POS_TRAJ_VAR_OBJW_3033H].pVarPtr            =   ((void *)(&gSevDrv.obj.ptrj.ptraj_in));
    DefCiA402VarObjDic[PTRAJ_OUT_POS_TRAJ_VAR_OBJW_3034H].pVarPtr           =   ((void *)(&gSevDrv.obj.ptrj.ptraj_out));
    DefCiA402VarObjDic[XQ0_POS_TRAJ_VAR_OBJW_3035H].pVarPtr                 =   ((void *)(&gSevDrv.obj.ptrj.xq0));
    DefCiA402VarObjDic[XQ1_POS_TRAJ_VAR_OBJW_3036H].pVarPtr                 =   ((void *)(&gSevDrv.obj.ptrj.xq1));

    DefCiA402VarObjDic[XQ_REAL_POS_TRAJ_VAR_OBJW_3037H].pVarPtr             =   ((void *)(&gSevDrv.obj.ptrj.xq_real));
    DefCiA402VarObjDic[XQH_POS_TRAJ_VAR_OBJW_3038H].pVarPtr                 =   ((void *)(&gSevDrv.obj.ptrj.xqh));
    DefCiA402VarObjDic[XV0_POS_TRAJ_VAR_OBJW_3039H].pVarPtr                 =   ((void *)(&gSevDrv.obj.ptrj.x_v0));
    DefCiA402VarObjDic[XV1_POS_TRAJ_VAR_OBJW_303AH].pVarPtr                 =   ((void *)(&gSevDrv.obj.ptrj.x_v1));
    DefCiA402VarObjDic[XV_REAL_POS_TRAJ_VAR_OBJW_303BH].pVarPtr             =   ((void *)(&gSevDrv.obj.ptrj.xv_real));

    DefCiA402VarObjDic[TREAL_POS_TRAJ_VAR_OBJW_303CH].pVarPtr               =   ((void *)(&gSevDrv.obj.ptrj.treal));
    DefCiA402VarObjDic[XACC_REAL_POS_TRAJ_VAR_OBJW_303DH].pVarPtr           =   ((void *)(&gSevDrv.obj.ptrj.xacc_real));
    DefCiA402VarObjDic[FLAG_ALL_POS_TRAJ_VAR_OBJW_303EH].pVarPtr            =   ((void *)(&gSevDrv.obj.ptrj.flag.all));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    DefCiA402VarObjDic[SPD_FFD_PCTL_VAR_OBJW_303FH].pVarPtr                 =   ((void *)(&gSevDrv.obj.pos.spd_ffd));
    DefCiA402VarObjDic[SPD_FFD_OUT_PCTL_VAR_OBJW_3040H].pVarPtr             =   ((void *)(&gSevDrv.obj.pos.spd_ffd_out));
    DefCiA402VarObjDic[TQR_FFD_PCTL_VAR_OBJW_3041H].pVarPtr                 =   ((void *)(&gSevDrv.obj.pos.tqr_ffd));
    DefCiA402VarObjDic[TQR_FFD_OUT_PCTL_VAR_OBJW_3042H].pVarPtr             =   ((void *)(&gSevDrv.obj.pos.tqr_ffd_out));
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
   Uint32  lutmp;
   int32   ltmp;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
   if (inx  < VAR_SERVO_OBJW_INX_MAX_NUM)
   {
       if (DefCiA402VarObjDic[inx].ObjDesc.DataType == DEFTYPE_UNSIGNED32)
       {
            lutmp                   =   *((Uint32 *)(DefCiA402VarObjDic[inx].pVarPtr));
            dtmp                    =   lutmp;
       }
       else if (DefCiA402VarObjDic[inx].ObjDesc.DataType == DEFTYPE_INTEGER32)
       {
           ltmp                     =   *((int32 *)(DefCiA402VarObjDic[inx].pVarPtr));
           dtmp                     =   ltmp;
       }
       else if (DefCiA402VarObjDic[inx].ObjDesc.DataType == DEFTYPE_INTEGER64)
       {
           dtmp                    =   *((int64 *)(DefCiA402VarObjDic[inx].pVarPtr));
       }
       else
       {
            dtmp                   =   *((double *)(DefCiA402VarObjDic[inx].pVarPtr));
       }

       *m_data                     =   dtmp;
       return  TRUE;
   }
   else
   {
       return  FALSE;
   }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


//#############################################################################################################################
