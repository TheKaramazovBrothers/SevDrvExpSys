//=========================================================================================================
// project		:	servo system excitation signal generate module realization
// File			:	PosTrajProd.cpp
// discription	:	use in servo system excitation signal generate module realization
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g
// date			:	2022/09/14
// copyright(C)	:	liu.g	(2022-2032)
//=========================================================================================================
#include <cmath>
#include "Cia402AppEmu.h"
#include "SevCtlPrmTblDef.h"
#include "ExciSigProd.h"


//*********************************************************************************************************
//*                             EXCITATION SIGNAL MODULE INITIALIZATION
//*
//* Description: This function is used to initialize excitation signal module in servo system
//*
//*
//* Arguments  : m_ctl		is a pointer to servo system excitation signal object
//*
//* Returns    : -1/initialize Failure, else/success
//*********************************************************************************************************
int16	KpiInitExciSigProdModule(EXCI_SIG * m_ctl)
{
//**************************************************************************************************************************
// parameter initialization
    if (SEV_PRM_FROM_EX_MEM_EN == DISABLE)
    {
        m_ctl->prm.cfg_opt.all                  =   0;
        m_ctl->prm.ts                           =   62500;

        m_ctl->prm.delay_tim                    =   1600;
        m_ctl->prm.steady_tim                   =   16000;
        m_ctl->prm.exci_amp                     =   1024;

        m_ctl->prm.sin_hz_start                 =   20;
        m_ctl->prm.sin_hz_step                  =   10;
        m_ctl->prm.sin_harm_num                 =   100;

        m_ctl->prm.prbs_div_num                 =   8;
        m_ctl->prm.prbs_durat_tim               =   160000;

        m_ctl->prm.chirp_hz_start               =   5;
        m_ctl->prm.chirp_hz_end                 =   2000;
        m_ctl->prm.chirp_durat_tim              =   10000;

    }
//**************************************************************************************************************************
    m_ctl->delt_ts                              =   m_ctl->prm.ts/1000000000.0;
//**************************************************************************************************************************
    m_ctl->period_cnt                           =   0;
    m_ctl->harm_cnt                             =   0;
    m_ctl->status_flag.all                      =   0;
    m_ctl->exci_sig_out                         =   0;

    m_ctl->real_f                               =   m_ctl->prm.sin_hz_start;
    m_ctl->real_w                               =   0;
    m_ctl->real_t                               =   0;
    m_ctl->state                                =   INIT_STAGE_ESPS;

    m_ctl->prbs_flag.all                        =   0x97c62ad5;
//**************************************************************************************************************************
    return  TRUE;
}


//*********************************************************************************************************
//*                             EXCITATION SIGNAL MODULE INITIALIZATION
//*
//* Description: This function is used to initialize excitation signal module in servo system
//*
//*
//* Arguments  : m_ctl		is a pointer to servo system excitation signal object
//*
//* Returns    : -1/initialize Failure, else/success
//*********************************************************************************************************
int16	KpiInitExciSigProdVar(EXCI_SIG * m_ctl)
{
//**************************************************************************************************************************
    m_ctl->period_cnt                           =   0;
    m_ctl->harm_cnt                             =   0;
    m_ctl->status_flag.all                      =   0;

    m_ctl->real_f                               =   m_ctl->prm.sin_hz_start;
    m_ctl->real_w                               =   0;
    m_ctl->real_t                               =   0;
    m_ctl->exci_sig_out                         =   0;
    m_ctl->state                                =   INIT_STAGE_ESPS;

    m_ctl->prbs_flag.all                        =   0x97c62ad5;
//**************************************************************************************************************************
    return  TRUE;
}




int16	KpiExciSigProd(EXCI_SIG * m_ctl, double * exci_out)
{
    Uint16 utmp;
    double dtmp;

    switch (m_ctl->state)
    {
        case    INIT_STAGE_ESPS:
        {
            m_ctl->period_cnt++;
            if (m_ctl->period_cnt >= m_ctl->prm.delay_tim)
            {
                m_ctl->state            =   WORK_STAGE_ESPS;
                m_ctl->period_cnt       =   0;
            }
            m_ctl->exci_sig_out         =   0;
            break;
        }
        case    WORK_STAGE_ESPS:
        {
//**************************************************************************************************************************
            switch  (m_ctl->prm.cfg_opt.bit.TYPE)
            {
                case    0:
                {
//**************************************************************************************************************************
                    m_ctl->period_cnt++;

                    if (m_ctl->status_flag.bit.FISH == FALSE)
                    {
                        m_ctl->real_w                   =   PI2_CIRCULAR_CONSTANT*m_ctl->real_f;

                        m_ctl->exci_sig_out             =   ((double)(m_ctl->prm.exci_amp)/1024.0) * sin(m_ctl->real_w * m_ctl->real_t);
                        m_ctl->real_t                   =   m_ctl->real_t + m_ctl->delt_ts;

                        if (m_ctl->period_cnt >= m_ctl->prm.steady_tim)
                        {
                            m_ctl->status_flag.bit.FISH     =   TRUE;
                            m_ctl->period_cnt               =   0;
                            m_ctl->real_t                   =   0;
                        }
                    }
                    else
                    {
                        if (m_ctl->period_cnt >= m_ctl->prm.delay_tim)
                        {
                            m_ctl->harm_cnt++;

                            if (m_ctl->harm_cnt >= m_ctl->prm.sin_harm_num)
                            {
                                m_ctl->state            =   END_STAGE_ESPS;
                                m_ctl->harm_cnt         =   0;
                            }

                            m_ctl->real_f                   =   m_ctl->real_f + m_ctl->prm.sin_hz_step;
                            m_ctl->status_flag.bit.FISH     =   FALSE;
                            m_ctl->period_cnt               =   0;
                        }

                        m_ctl->exci_sig_out             =   0;
                    }

//**************************************************************************************************************************
                    break;
                }
                case    1:
                {
//**************************************************************************************************************************
                    m_ctl->period_cnt++;
                    m_ctl->harm_cnt++;

                    if (m_ctl->harm_cnt >= m_ctl->prm.prbs_div_num)
                    {
                        utmp = m_ctl->prbs_flag.bit.PB_X31 ^ m_ctl->prbs_flag.bit.PB_X28;

                        m_ctl->prbs_flag.all        =   m_ctl->prbs_flag.all << 1;
                        m_ctl->prbs_flag.bit.PB_X1  =   utmp;
                        m_ctl->harm_cnt             =   0;

                        dtmp                        =   (int32)(m_ctl->prm.exci_amp)/1024.0;
                        m_ctl->exci_sig_out         =   (m_ctl->prbs_flag.bit.PB_X32 == 1) ? dtmp : -dtmp;

                    }

                    if (m_ctl->period_cnt >= m_ctl->prm.prbs_durat_tim)
                    {
                        m_ctl->state            =   END_STAGE_ESPS;
                        m_ctl->harm_cnt         =   0;
                        m_ctl->period_cnt       =   0;
                    }
//**************************************************************************************************************************
                    break;
                }
                case 2:
                {
//**************************************************************************************************************************
                    m_ctl->period_cnt++;

                    if (m_ctl->prm.chirp_durat_tim == 0)
                    {
                        m_ctl->prm.chirp_durat_tim  =   1000;
                    }
                    dtmp                            =   ((m_ctl->prm.chirp_hz_end - m_ctl->prm.chirp_hz_start)*m_ctl->period_cnt) / (double)(m_ctl->prm.chirp_durat_tim);
                    m_ctl->real_f                   =   m_ctl->prm.chirp_hz_start + dtmp/2.0;

                    m_ctl->real_w                   =   PI2_CIRCULAR_CONSTANT*m_ctl->real_f;
                    m_ctl->real_t                   =   m_ctl->real_t + m_ctl->delt_ts;
                    m_ctl->exci_sig_out             =   ((double)(m_ctl->prm.exci_amp)/1024.0) * sin(m_ctl->real_w * m_ctl->real_t);

                    if (m_ctl->period_cnt > (m_ctl->prm.chirp_durat_tim+2))
                    {
                        m_ctl->state            =   END_STAGE_ESPS;
                        m_ctl->period_cnt       =   0;
                    }
//**************************************************************************************************************************
                    break;
                }
                default:
                {
                    m_ctl->exci_sig_out             =   0;
                    break;
                }
            }
//**************************************************************************************************************************
            break;
        }
        case    END_STAGE_ESPS:
        {
            m_ctl->exci_sig_out             =   0;
            break;
        }
        default:
        {
            m_ctl->state                    =   END_STAGE_ESPS;
            m_ctl->exci_sig_out             =   0;
            break;
        }
    }
//**************************************************************************************************************************
    *exci_out                               =   m_ctl->exci_sig_out;

    return  TRUE;
//**************************************************************************************************************************
}














////////////////////////////////////////////////// no more ///////////////////////////////////////////////////
