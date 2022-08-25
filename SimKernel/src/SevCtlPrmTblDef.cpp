//=========================================================================================================
// project		:	servo system parameter table define
// File			:	SevCtlPrmTblDef.cpp
// discription	:	use in servo system parameter table define
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g
// date			:	2022/07/01
// copyright(C)	:	liu.g	(2022-2032)
//=========================================================================================================

#include "SevCtlPrmTblDef.h"

Uint16	gVirFlashStorage[VIR_FLASH_WORD_SIZE];
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=




Uint16  SclReadFramPrmByID16(Uint16 m_id, Uint16 *m_data)
{
    Uint16  adr_inx;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (m_id <= ID16_MAX_ADR_LENGTH)
    {
        adr_inx                                         =   ID16_START_ADR_FALSH + m_id;
        *m_data                                         =   gVirFlashStorage[adr_inx];
        return  TRUE;
    }
    else
    {
        return  FALSE;
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

Uint32  SclReadFramPrmByID32(Uint16 m_id, Uint32 *m_data)
{
    Uint16  adr_inx;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (m_id <= ID32_MAX_ADR_LENGTH)
    {
        adr_inx                                         =   ID32_START_ADR_FLASH + (m_id << 1);
        *m_data                                         =   *((Uint32 *)(&gVirFlashStorage[adr_inx]));

        return  TRUE;
    }
    else
    {
        *m_data                                         =   0;
        return  FALSE;
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}



int16   SclWriteFramPrmByID16(Uint16 *m_data, Uint16 m_id)
{
    Uint16  adr_inx;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (m_id <= ID16_MAX_ADR_LENGTH)
    {
        adr_inx                                         =   ID16_START_ADR_FALSH + m_id;
        gVirFlashStorage[adr_inx]                       =   *m_data;
        return  TRUE;
    }
    else
    {
        *m_data                                         =   0;
        return  FALSE;
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

int16   SclWriteFramPrmByID32(Uint32 *m_data, Uint16 m_id)
{
    Uint16  adr_inx;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (m_id <= ID32_MAX_ADR_LENGTH)
    {
        adr_inx                                         =   ID32_START_ADR_FLASH + (m_id << 1);
        *((Uint32 *)(&gVirFlashStorage[adr_inx]))       =   *m_data;

        return  TRUE;
    }
    else
    {
        return  FALSE;
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}









////////////////////////////////////////////////// no more ///////////////////////////////////////////////////
