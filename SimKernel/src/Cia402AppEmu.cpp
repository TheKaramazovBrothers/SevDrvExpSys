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
#include "SevCtlPrmTblDef.h"
#include "Cia402AppEmu.h"


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
