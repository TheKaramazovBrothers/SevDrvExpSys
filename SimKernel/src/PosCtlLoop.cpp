//=========================================================================================================
// project		:	servo system position control loop realization
// File			:	PosCtlLoop.cpp
// discription	:	use in servo system position control loop realization
//
//---------------------------------------------------------------------------------------------------------
// programmer	:	liu.g
// date			:	2022/08/26
// copyright(C)	:	liu.g	(2022-2032)
//=========================================================================================================
#include "Cia402AppEmu.h"
#include "SevCtlPrmTblDef.h"
#include "PosCtlLoop.h"




//*********************************************************************************************************
//*                                   POSITION CONTROL MODULE INITIALIZATION
//*
//* Description: This function is used to initialize position control loop module in servo system
//*
//*
//* Arguments  : m_ctl		is a pointer to servo system position control object
//*
//* Returns    : -1/initialize Failure, else/success
//*********************************************************************************************************
int16	KpiInitPosLoopModule(POS_CTL * m_ctl)
{
    double  line_num_tmp, nos_tmp;
    int32   ltmp, ltmp2;
    int16   i;
//**************************************************************************************************************************
    if (SEV_PRM_FROM_EX_MEM_EN == DISABLE)
    {
        m_ctl->prm.fnp_fst          =   100;
        m_ctl->prm.fnp_sec          =   100;

        m_ctl->prm.abs_rat          =   4096;
        m_ctl->prm.pos_rat          =   4096;
        m_ctl->prm.neg_rat          =   4096;

        m_ctl->prm.ts               =   62500;
        m_ctl->prm.cfg_opt.all      =   0;
        m_ctl->prm.maf_num          =   320;

        line_num_tmp                =   16777216.0;
        nos_tmp                     =   6000;
    }
    else
    {
        CpiReadRamPrmByDicInx(LINE_NUM_ENC_PRM_ID32_OBJW_2013H, &line_num_tmp);
        CpiReadRamPrmByDicInx(NOS_MOT_PRM_ID32_OBJW_2009H, &nos_tmp);
    }
//**************************************************************************************************************************
    m_ctl->kp_fst               =   ((PI2_CIRCULAR_CONSTANT * PI2_CIRCULAR_CONSTANT)*(m_ctl->prm.fnp_fst/10.0))/line_num_tmp;
    m_ctl->kp_sec               =   ((PI2_CIRCULAR_CONSTANT * PI2_CIRCULAR_CONSTANT)*(m_ctl->prm.fnp_sec/10.0))/line_num_tmp;

    ltmp						=	(int32)(m_ctl->prm.abs_rat) * (int32)(m_ctl->prm.pos_rat);				// Q24 = Q12 * Q12
    ltmp2						=	-((int32)(m_ctl->prm.abs_rat) * (int32)(m_ctl->prm.neg_rat));			// Q24 = Q12 * Q12

    m_ctl->po_ulim              =   (((nos_tmp/60.0)*PI2_CIRCULAR_CONSTANT) * (double)(ltmp))/16777216.0;
    m_ctl->po_llim              =   (((nos_tmp/60.0)*PI2_CIRCULAR_CONSTANT) * (double)(ltmp2))/16777216.0;

    m_ctl->line_num_pctl        =   line_num_tmp;
//**************************************************************************************************************************
    m_ctl->acc_pos_ref          =   0;
    m_ctl->acc_pos_fb           =   0;
    m_ctl->pos_err              =   0;

    m_ctl->xwkp                 =   0;
    m_ctl->spdr                 =   0;
    m_ctl->tqrp                 =   0;
//**************************************************************************************************************************
    m_ctl->idx_maf              =   0;
    m_ctl->ksub_maf             =   0;
    m_ctl->remx_maf             =   0;
    m_ctl->sumx_maf             =   0;
    m_ctl->zcntx_maf            =   0;

    for (i = 0; i < PCMD_MAF_BUF_NUM; i++)
    {
        m_ctl->maf_buf[i]		=	0;
    }

    m_ctl->maf_in               =   0;
    m_ctl->maf_out              =   0;
//**************************************************************************************************************************
    m_ctl->dpcmd                =   0;
    m_ctl->dpfb                 =   0;
    m_ctl->sig_pos              =   0;
    m_ctl->sig_pos_lst          =   0;
//**************************************************************************************************************************
    return  TRUE;
}


//*********************************************************************************************************
//*                                POSITION CONTROL VARIABLE INITIALIZATION
//*
//* Description: This function is used to initialize position control loop variable in servo system
//*
//*
//* Arguments  : m_ctl		is a pointer to servo system position control object
//*
//* Returns    : -1/initialize Failure, else/success
//*********************************************************************************************************
int16	KpiInitPosLoopVar(POS_CTL * m_ctl)
{
    double dtmp;
    int16 i;
//**************************************************************************************************************************
    m_ctl->acc_pos_ref          =   0;
    m_ctl->acc_pos_fb           =   0;
    m_ctl->pos_err              =   0;

    m_ctl->xwkp                 =   0;
    m_ctl->spdr                 =   0;
    m_ctl->tqrp                 =   0;
//**************************************************************************************************************************
    m_ctl->idx_maf              =   0;
    m_ctl->ksub_maf             =   0;
    m_ctl->remx_maf             =   0;
    m_ctl->sumx_maf             =   0;
    m_ctl->zcntx_maf            =   0;

    for (i = 0; i < PCMD_MAF_BUF_NUM; i++)
    {
        m_ctl->maf_buf[i]		=	0;
    }

    m_ctl->maf_in               =   0;
    m_ctl->maf_out              =   0;
//**************************************************************************************************************************
    m_ctl->dpcmd                =   0;
    m_ctl->dpfb                 =   0;

    CpiReadRamVarByDicInx(POS_IN_SENS_VAR_OBJW_3017H, &dtmp);
    m_ctl->sig_pos              =   dtmp;
    m_ctl->sig_pos_lst          =   dtmp;
//**************************************************************************************************************************
    return  TRUE;
}


//*********************************************************************************************************
//*                                POSITION PI CONTROLER DESIGN
//*
//* Description: This function is used to do  position loop PI control
//*
//*
//* Arguments  : m_ctl		is a pointer to servo system position loop control object
//*
//* Returns    : -1/Failure, else/success
//*********************************************************************************************************
int16	KpiPosCloseLoopCtl(POS_CTL * m_ctl, int32 * dpcmd)
{
    int32   ltmp ,ltmp2;
    int32	subx;
    int32	outx;
    double  dtmp;
//**************************************************************************************************************************
    if (CpiReadRamVarByDicInx(POS_IN_SENS_VAR_OBJW_3017H, &dtmp) == TRUE)
    {
        m_ctl->sig_pos                      =   dtmp;
    }
    else
    {
        m_ctl->sig_pos                      =   0;
    }


    ltmp2                                   =	m_ctl->sig_pos - m_ctl->sig_pos_lst;
    ltmp                                    =	m_ctl->line_num_pctl >> 1;
    m_ctl->dpfb                             =	(ltmp2 > ltmp)?(ltmp2 - m_ctl->line_num_pctl):((ltmp2 < -ltmp)?(ltmp2 + m_ctl->line_num_pctl):ltmp2);

    m_ctl->sig_pos_lst                      =	m_ctl->sig_pos;
//**************************************************************************************************************************
    m_ctl->maf_in                           =   *dpcmd;

    if ((m_ctl->prm.cfg_opt.bit.MAF  ==  TRUE) || (m_ctl->prm.maf_num == 1))
    {
        m_ctl->zcntx_maf                    =   (m_ctl->maf_in != 0) ? 1:0;
        m_ctl->maf_out                      =   m_ctl->maf_in;
        m_ctl->sumx_maf                     =   m_ctl->maf_out * m_ctl->prm.maf_num;
    }
    else
    {
        subx                                =	m_ctl->ksub_maf * m_ctl->maf_buf[m_ctl->idx_maf];
        m_ctl->maf_buf[m_ctl->idx_maf]		=	m_ctl->maf_in;

        if (++m_ctl->idx_maf >= m_ctl->prm.maf_num)
        {
            m_ctl->idx_maf                  =	0;
            m_ctl->ksub_maf                 =	1;
        }

        m_ctl->sumx_maf                     =	m_ctl->sumx_maf - subx + m_ctl->maf_in;
        outx                                =	(m_ctl->sumx_maf + m_ctl->remx_maf) / m_ctl->prm.maf_num;
        m_ctl->remx_maf                     =	(m_ctl->sumx_maf + m_ctl->remx_maf) - (m_ctl->prm.maf_num * outx);

        if (m_ctl->maf_in != 0)
        {
            m_ctl->zcntx_maf = (Uint16)(m_ctl->prm.maf_num);
        }
        else if( m_ctl->zcntx_maf > 0 )
        {
            --m_ctl->zcntx_maf;
        }
        m_ctl->maf_out                      =   outx;
    }
//**************************************************************************************************************************
    m_ctl->dpcmd                            =   m_ctl->maf_out;

    ltmp                                    =   m_ctl->dpcmd - m_ctl->dpfb;
    m_ctl->acc_pos_ref                      =   m_ctl->acc_pos_ref + m_ctl->dpcmd;
    m_ctl->acc_pos_fb                       =   m_ctl->acc_pos_fb + m_ctl->dpfb;
    m_ctl->pos_err                          =   m_ctl->pos_err + ltmp;

    dtmp                                    =   (double)(m_ctl->pos_err) * m_ctl->kp_fst;
    m_ctl->xwkp                             =   IQSatLimit(dtmp, m_ctl->po_ulim, m_ctl->po_llim);

    m_ctl->spdr                             =   m_ctl->xwkp;
//**************************************************************************************************************************
    m_ctl->tqrp                             =   0;
//**************************************************************************************************************************
    return  TRUE;
}





















///////////////////////////////////////////////////////// no more ////////////////////////////////////////////////////////////
