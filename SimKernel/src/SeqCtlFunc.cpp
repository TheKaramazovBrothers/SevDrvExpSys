//=========================================================================================================
// project		:	servo system sequence control modure realization
// File			:	SeqCtlFunc.cpp
// discription	:	use in servo system sequence control
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g
// date			:	2022/08/09
// copyright(C)	:	liu.g	(2022-2032)
//=========================================================================================================
#include    "SeqCtlFunc.h"
#include	"SevDrvTask.h"

// function declare
int16	KpiInitSeqCtlModule(SEQ_CTL * m_ctl)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// fram parameter initialization
    if (SEV_PRM_FROM_EX_MEM_EN == DISABLE)
    {
        m_ctl->prm.psrc_sel                     =   PC_USER_PCMD;
        m_ctl->prm.vsrc_sel                     =   PC_USER_VCMD;
        m_ctl->prm.csrc_sel                     =   PC_USER_CCMD;
        m_ctl->prm.cmd_dir.all                  =   0;
    }

// parameter initialization
    m_ctl->prm.usr_mode_tmp                 =   IDLE_SEQ_WORK;
    m_ctl->prm.usr_mode                     =   IDLE_SEQ_WORK;

    m_ctl->prm.sev_mode_tmp                 =   STOP_VCTL_SERVO;
    m_ctl->prm.sev_mode                     =   STOP_VCTL_SERVO;

    m_ctl->prm.ctl_word_tmp.all             =   0;
    m_ctl->prm.ctl_word.all                 =   0;

    m_ctl->prm.sts_word.all                 =   0;
    m_ctl->prm.pov_mode                     =   VEL_CTL_POSCLD;
// variable initialization
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_ctl->uar_tmp                          =   0;
    m_ctl->ubr_tmp                          =   0;
    m_ctl->ucr_tmp                          =   0;

    m_ctl->udr_tmp                          =   0;
    m_ctl->uqr_tmp                          =   15.0;

    m_ctl->idr_tmp                          =   0;
    m_ctl->iqr_tmp                          =   0;

    m_ctl->spdr_tmp                         =   0;
    m_ctl->posr_tmp                         =   0;

    m_ctl->uar_out                          =   0;
    m_ctl->ubr_out                          =   0;
    m_ctl->ucr_out                          =   0;

    m_ctl->udr_out                          =   0;
    m_ctl->uqr_out                          =   0;
    m_ctl->idr_out                          =   0;
    m_ctl->iqr_out                          =   0;

    m_ctl->spdr_out                         =   0;
    m_ctl->posr_out                         =   0;
    m_ctl->posr_out_lst                     =   0;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_ctl->act_on_tmp                       =   0;
    m_ctl->act_on_out                       =   0;

    m_ctl->en_opera_tmp                     =   0;
    m_ctl->en_opera_out                     =   0;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}

int16	KpiInitSeqCtlVar(SEQ_CTL * m_ctl)
{
// variable initialization
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_ctl->uar_tmp                          =   0;
    m_ctl->ubr_tmp                          =   0;
    m_ctl->ucr_tmp                          =   0;

    m_ctl->udr_tmp                          =   0;
    m_ctl->uqr_tmp                          =   0;

    m_ctl->idr_tmp                          =   0;
    m_ctl->iqr_tmp                          =   0;

    m_ctl->spdr_tmp                         =   0;
    m_ctl->posr_tmp                         =   0;

    m_ctl->uar_out                          =   0;
    m_ctl->ubr_out                          =   0;
    m_ctl->ucr_out                          =   0;

    m_ctl->udr_out                          =   0;
    m_ctl->uqr_out                          =   0;
    m_ctl->idr_out                          =   0;
    m_ctl->iqr_out                          =   0;

    m_ctl->spdr_out                         =   0;
    m_ctl->posr_out                         =   0;
    m_ctl->posr_out_lst                     =   0;

    m_ctl->dpcmd_in                         =   0;
    m_ctl->dpcmd_out                        =   0;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_ctl->act_on_tmp                       =   0;
    m_ctl->act_on_out                       =   0;

    m_ctl->en_opera_tmp                     =   0;
    m_ctl->en_opera_out                     =   0;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}


int16	KpiSeqBackGroundRout(SEQ_CTL * m_ctl, void * m_drv)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    SERVO_DRV * p_drv                       =   (SERVO_DRV *)(m_drv);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_ctl->prm.usr_mode                     =   m_ctl->prm.usr_mode_tmp;
    m_ctl->prm.ctl_word.all                 =   m_ctl->prm.ctl_word_tmp.all;

    if (m_ctl->prm.ctl_word.bit.SO == TRUE)
    {
        m_ctl->act_on_tmp                   =   TRUE;
    }
    else
    {
        m_ctl->act_on_tmp                   =   FALSE;
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (m_ctl->prm.ctl_word.bit.EO == TRUE)
    {
        m_ctl->en_opera_tmp                 =   TRUE;
    }
    else
    {
        m_ctl->en_opera_tmp                 =   FALSE;
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_ctl->act_on_out                       =   m_ctl->act_on_tmp;
    m_ctl->en_opera_out                     =   m_ctl->en_opera_tmp;

    p_drv->task.act_on                      =   m_ctl->act_on_out;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    switch (m_ctl->prm.usr_mode)
    {
        case    COLD_SEQ_WORK:
        {
            m_ctl->uar_out                          =   m_ctl->uar_tmp;
            m_ctl->ubr_out                          =   m_ctl->ubr_tmp;
            m_ctl->ucr_out                          =   m_ctl->ucr_tmp;

            m_ctl->udr_out                          =   m_ctl->udr_tmp;
            m_ctl->uqr_out                          =   m_ctl->uqr_tmp;

            p_drv->task.cmd_id                      =   COLD;
            break;
        }
        case    CCLD_SEQ_WORK:
        {

            m_ctl->idr_out                          =   m_ctl->idr_tmp;
            m_ctl->iqr_out                          =   m_ctl->iqr_tmp;
            p_drv->task.cmd_id                      =   CCLD;
            break;
        }
        case    VCLD_SEQ_WORK:
        {
            m_ctl->spdr_out                         =   m_ctl->spdr_tmp;
            m_ctl->idr_out                          =   0;
            p_drv->task.cmd_id                      =   VCLD;
            break;
        }
        case    PROF_VELC_SEQ_WORK:
        {
            m_ctl->prm.sev_mode_tmp                 =   SPD_TRA_VCTL_SERVO;
            p_drv->task.cmd_id                      =   POSCLD;
            break;
        }
        case    PROF_POSC_SEQ_WORK:
        {
            m_ctl->prm.sev_mode_tmp                 =   POS_TRA_PCTL_SERVO;
            p_drv->task.cmd_id                      =   POSCLD;
            break;
        }
        case    PROF_CURC_SEQ_WORK:
        {
            m_ctl->prm.sev_mode_tmp                 =   TQR_TRA_CCTL_SERVO;
            p_drv->task.cmd_id                      =   POSCLD;
            break;
        }
        case    CS_VELC_SEQ_WORK:
        {
            m_ctl->prm.sev_mode_tmp                 =   SPD_TRA_VCTL_SERVO;
            p_drv->task.cmd_id                      =   POSCLD;
            break;
        }
        case    CS_POSC_SEQ_WORK:
        {
            m_ctl->prm.sev_mode_tmp                 =   POS_TRA_PCTL_SERVO;
            p_drv->task.cmd_id                      =   POSCLD;
            break;
        }
        case    CS_CURC_SEQ_WORK:
        {
            m_ctl->prm.sev_mode_tmp                 =   TQR_TRA_CCTL_SERVO;
            p_drv->task.cmd_id                      =   POSCLD;
            break;
        }
        default:
        {
            p_drv->task.cmd_id                      =   IDLE;
            break;
        }
    }

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}


int16	KpiSeqServoCtlIsr(SEQ_CTL * m_ctl, void * m_drv)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    int64   lltmp;
    SERVO_DRV * p_drv                       =   (SERVO_DRV *)(m_drv);
    double  spd_ref_tmp, pos_ref_tmp;
//--------------------------------------------------------------------------------------------------------
    switch (m_ctl->prm.sev_mode)
    {
    case	STOP_VCTL_SERVO:
        {
            m_ctl->prm.pov_mode                 =   VEL_CTL_POSCLD;
            m_ctl->spdr_out                     =   0;
            m_ctl->prm.cfg_opt.bit.VRAMP        =   FALSE;


            if ((m_ctl->prm.sev_mode != m_ctl->prm.sev_mode_tmp))
            {
                switch (m_ctl->prm.sev_mode_tmp)
                {
                case    SPD_TRA_VCTL_SERVO:
                    {
                        m_ctl->prm.sev_mode         =   SPD_TRA_VCTL_SERVO;
                        break;
                    }
                case    POS_TRA_PCTL_SERVO:
                    {
                        m_ctl->prm.sev_mode         =   POS_TRA_PCTL_SERVO;
                        break;
                    }
                case    TQR_TRA_CCTL_SERVO:
                    {
                        m_ctl->prm.sev_mode         =   TQR_TRA_CCTL_SERVO;
                        break;
                    }
                default:
                    {
                        break;
                    }
                }
            }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            break;
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    case	SPD_TRA_VCTL_SERVO:
        {
            m_ctl->prm.pov_mode                 =   VEL_CTL_POSCLD;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            switch (m_ctl->prm.vsrc_sel)
            {
                case    PC_USER_VCMD:
                {
                    spd_ref_tmp                     =   m_ctl->spdr_tmp;
                    break;
                }
                case    EXCI_SIG_VCMD:
                {
                    KpiExciSigProd(&p_drv->obj.excs, &spd_ref_tmp);
                    break;
                }
                case    RECIP_STEP_VCMD:
                {
                    KpiStepCmdRecipMotion(&p_drv->obj.ptrj, &m_ctl->en_opera_out, &m_ctl->spdr_tmp, &spd_ref_tmp);
                    break;
                }
                default:
                {
                    spd_ref_tmp                     =   0;
                    break;
                }
            }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            if (m_ctl->prm.cmd_dir.bit.VELC_DIR == 1)
            {
                m_ctl->spdr_out                     =   -spd_ref_tmp;
            }
            else
            {
                m_ctl->spdr_out                     =   spd_ref_tmp;
            }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            if (m_ctl->prm.usr_mode == CS_VELC_SEQ_WORK)
            {
                m_ctl->prm.cfg_opt.bit.VRAMP        =   TRUE;
            }
            else
            {
                m_ctl->prm.cfg_opt.bit.VRAMP        =   FALSE;
            }

            if (m_ctl->prm.sev_mode != m_ctl->prm.sev_mode_tmp)
            {
                m_ctl->prm.sev_mode                 =   STOP_VCTL_SERVO;
            }
            break;
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    case	FIX_PCTL_SERVO:
        {
            m_ctl->prm.pov_mode                 =   POS_CTL_POSCLD;

            m_ctl->posr_out                     =   0;

            if (m_ctl->prm.sev_mode != m_ctl->prm.sev_mode_tmp)
            {
                m_ctl->prm.sev_mode                 =   STOP_VCTL_SERVO;
            }
            break;
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    case	POS_TRA_PCTL_SERVO:
        {
            m_ctl->prm.pov_mode                 =   POS_CTL_POSCLD;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            switch (m_ctl->prm.psrc_sel)
            {
                case    PC_USER_PCMD:
                {
                    KpiPosTrajProd(&p_drv->obj.ptrj, &m_ctl->posr_tmp, &m_ctl->posr_out);
                    break;
                }
                case    EXCI_SIG_PCMD:
                {
                    KpiExciSigProd(&p_drv->obj.excs, &pos_ref_tmp);
                    m_ctl->posr_out        =         pos_ref_tmp*1024.0;
                    break;
                }
                case    RECIP_STEP_PCMD:
                {
                    KpiRecipMotionTrajProd(&p_drv->obj.ptrj, &m_ctl->en_opera_out, &m_ctl->posr_tmp, &m_ctl->posr_out);
                    break;
                }
                default:
                {
                    m_ctl->posr_out         =   0;
                    break;
                }
            }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            lltmp                               =   m_ctl->posr_out - m_ctl->posr_out_lst;

            m_ctl->dpcmd_in                     =   lltmp;
            m_ctl->dpcmd_out                    =   lltmp;
            m_ctl->posr_out_lst                 =   m_ctl->posr_out;

            if (m_ctl->prm.sev_mode != m_ctl->prm.sev_mode_tmp)
            {
                m_ctl->prm.sev_mode                 =   STOP_VCTL_SERVO;
            }
            break;
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    case	TQR_TRA_CCTL_SERVO:
        {
            m_ctl->prm.pov_mode                 =   CURR_CTL_POSCLD;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            switch (m_ctl->prm.csrc_sel)
            {
                case    PC_USER_CCMD:
                {
                    m_ctl->iqr_out              =   m_ctl->iqr_tmp;
                    break;
                }
                case    EXCI_SIG_CCMD:
                {
                    KpiExciSigProd(&p_drv->obj.excs, &m_ctl->iqr_out);
                    break;
                }
                case    RECIP_STEP_CCMD:
                {
                    KpiStepCmdRecipMotion(&p_drv->obj.ptrj, &m_ctl->en_opera_out, &m_ctl->iqr_tmp, &m_ctl->iqr_out);
                    break;
                }
                default:
                {
                    m_ctl->iqr_out              =   0;
                    break;
                }
            }

            if (m_ctl->prm.sev_mode != m_ctl->prm.sev_mode_tmp)
            {
                m_ctl->prm.sev_mode                 =   STOP_VCTL_SERVO;
            }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
            break;
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    case    HOME_VCTL_SERVO:
        {
            m_ctl->prm.pov_mode                 =   VEL_CTL_POSCLD;
            m_ctl->spdr_out                     =   0;

            if (m_ctl->prm.sev_mode != m_ctl->prm.sev_mode_tmp)
            {
                m_ctl->prm.sev_mode                 =   STOP_VCTL_SERVO;
            }
            break;
        }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    default:
        {
            m_ctl->prm.sev_mode		=	STOP_VCTL_SERVO;
            break;
        }
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return	TRUE;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}
