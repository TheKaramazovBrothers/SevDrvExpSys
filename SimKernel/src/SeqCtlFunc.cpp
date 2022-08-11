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
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_ctl->act_on_tmp                       =   0;
    m_ctl->act_on_out                       =   0;
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
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_ctl->act_on_tmp                       =   0;
    m_ctl->act_on_out                       =   0;
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
    m_ctl->act_on_out                       =   m_ctl->act_on_tmp;

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
        default:
        {
            p_drv->task.cmd_id                      =   IDLE;
            break;
        }
    }

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return  TRUE;
}
