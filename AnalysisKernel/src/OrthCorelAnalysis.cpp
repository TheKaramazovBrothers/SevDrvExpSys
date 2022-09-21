//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	Orthogonal correlation analysis  							//
//	file				:	OrthCorelAnalysis.cpp										//
//	Description			:	Orthogonal correlation analysis realization file            //
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g           |	2022/9/19	|	liu.g           |		2022 - 2032			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "SevCtlPrmTblDef.h"
#include "FastFourierTrans.h"

#include "OrthCorelAnalysis.h"


OrthgCorelAnalysis::OrthgCorelAnalysis()
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_sin_hz_start              =   20;                                                                 // HZ
    m_sin_hz_step               =   10;                                                                 // HZ
    m_sin_harm_num              =   100;                                                                // Harmonic number

    m_sin_delay_times           =   800;                                                                // by TS
    m_sin_data_lth              =   8000;                                                               // effective data length
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

void OrthgCorelAnalysis::setAnalySignalComp(double start_hz, double step_hz, double ts, int32 harm_num, int32 delay_tim, int32 data_lth)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_sin_hz_start              =   start_hz;                                                          // HZ
    m_sin_hz_step               =   step_hz;                                                           // HZ
    m_ts                        =   ts;
    m_sin_harm_num              =   harm_num;                                                          // Harmonic number

    m_sin_delay_times           =   delay_tim;                                                         // by TS
    m_sin_data_lth              =   data_lth;                                                          // effective data length
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


void OrthgCorelAnalysis::RespAnalysisInSinSteadyState(QVector<qreal> * in, QVector<qreal> * rout, QVector<qreal> &dbb, QVector<qreal> &phh)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    m_data_ref                  =   in;
    m_data_fb                   =   rout;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    int start_inx = 0;
    int begin;
    while(m_data_ref->at(start_inx) == 0)
    {
        start_inx++;
    }
    for (int i = 0; i < m_sin_harm_num; i ++)
    {
        QVector<qreal>  *vtmp       =   new QVector<qreal>;
        begin                       =    start_inx + i*(m_sin_data_lth + m_sin_delay_times);

        for (int j = 0; j < m_sin_data_lth; j++)
        {
            vtmp->append(m_data_fb->at(begin + j));
        }

        m_data_fb_grp.append(*vtmp);
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    double fn, wn, exci_amp;
    double Ruy0, Ruy90, Ruy0_out, Ruy90_out;
    double real_sig, im_sig, amp_rep, angel_rep, deg_rep;
    int max_inx;

    max_inx         =   ((1.0/m_sin_hz_start)/m_ts)/4.0;
    exci_amp        =   IQAbsCal(m_data_ref->at(start_inx + max_inx));

    for (int i = 0; i < m_sin_harm_num; i++)
    {
        fn      =   m_sin_hz_start + (i * m_sin_hz_step);
        wn      =   PI2_CIRCULAR_CONSTANT * fn;

        Ruy0    =   0;
        Ruy90   =   0;

        for (int j = 0; j < m_sin_data_lth; j++)
        {
            Ruy0        =   Ruy0 + m_data_fb_grp.at(i).at(j)*sin(wn*j*m_ts);
            Ruy90       =   Ruy90 + m_data_fb_grp.at(i).at(j)*cos(wn*j*m_ts);
        }

        Ruy0_out        =   (Ruy0 * exci_amp)/m_sin_data_lth;
        Ruy90_out       =   (Ruy90 * exci_amp)/m_sin_data_lth;

        real_sig        =   (Ruy0_out * 2.0)/(exci_amp * exci_amp);
        im_sig          =   (Ruy90_out * 2.0)/(exci_amp * exci_amp);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        amp_rep         =   sqrt(real_sig*real_sig + im_sig*im_sig);
        amp_rep         =   20 * log10(amp_rep);

        angel_rep       =   IFatanCal(im_sig, real_sig);
        while ((angel_rep < -M_PI) || (angel_rep > M_PI))
        {
            if (angel_rep > M_PI)
            {
                angel_rep = angel_rep - 2 * M_PI;
            }
            else
            {
                angel_rep = angel_rep + 2 * M_PI;
            }
        }
        deg_rep           = (angel_rep / M_PI)*180.0;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        m_dbb.append(amp_rep);
        m_phh.append(deg_rep);

        dbb             =   m_dbb;
        phh             =   m_phh;
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


OrthgCorelAnalysis::~OrthgCorelAnalysis()
{
    m_data_fb_grp.clear();
}

//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
