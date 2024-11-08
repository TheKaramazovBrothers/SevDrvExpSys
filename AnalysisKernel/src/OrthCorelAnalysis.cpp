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
    m_win_num                   =   128;                                                                // the default window numbers
    m_fft_num                   =   16000;
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
    start_inx--;

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



void OrthgCorelAnalysis::TfEstimateByPeriodogramMethod(QVector<qreal> * in, QVector<qreal> * rout, QVector<qreal> &dbb, QVector<qreal> &phh)
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    int32 lth, n, win_ofst, col, row, inx;
    COMPLEX ctmp;

    double ** pAu;
    double ** pAy;
    double * pWinw;

    COMPLEX ** pAuc;
    COMPLEX ** pAyc;

    COMPLEX *  pAuco;
    COMPLEX *  pAyco;

    double    gin, gout, angin, angout, dtmp, ptmp, temp;

    lth = in->count();
    n = (lth/m_win_num);
    n = (n >> 1) << 1;
    win_ofst = n/2;

    col = m_fft_num;
    row = (m_win_num * 2)-1;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    pAu = new double*[row];
    pAy = new double*[row];

    for (int i = 0; i < row; i++)
    {
        pAu[i] = new double[col];
        pAy[i] = new double[col];
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            pAu[i][j]       =   0;
            pAy[i][j]       =   0;
        }
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    pAuc = new COMPLEX*[row];
    pAyc = new COMPLEX*[row];

    pAuco   =   new COMPLEX[col];
    pAyco   =   new COMPLEX[col];

    for (int i = 0; i < row; i++)
    {
        pAuc[i] = new COMPLEX[col];
        pAyc[i] = new COMPLEX[col];
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            pAuc[i][j].real       =   0;
            pAuc[i][j].imag       =   0;

            pAyc[i][j].real       =   0;
            pAyc[i][j].imag       =   0;
        }
    }

    for (int i = 0; i < col; i++)
    {
        pAuco[i].real         =   0;
        pAuco[i].imag         =   0;
        pAyco[i].real         =   0;
        pAyco[i].imag         =   0;
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < n; j++)
        {
            inx = win_ofst*i + j;
            if (inx < lth)
            {
                pAu[i][j]   =   in->at(inx);
                pAy[i][j]   =   rout->at(inx);
            }
        }
    }

    pWinw = new double[n];
    for (int i = 0; i < n; i++)
    {
        double theta    =   PI2_CIRCULAR_CONSTANT * (double)(i) / (double)(n);
        pWinw[i]        =   0.54 - 0.46*cos(theta);
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < n; j++)
        {
            pAu[i][j]               =   pAu[i][j] * pWinw[j];
            pAy[i][j]               =   pAy[i][j] * pWinw[j];
        }
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            pAuc[i][j].real         =   pAu[i][j];
            pAyc[i][j].real         =   pAy[i][j];
        }

        transform_x(pAuc[i], col);
        transform_x(pAyc[i], col);


        for (int j = 0; j < col; j++)
        {
            ctmp.real               =   pAuc[i][j].real * pAyc[i][j].real   +  pAuc[i][j].imag * pAyc[i][j].imag;
            ctmp.imag               =   pAuc[i][j].imag * pAyc[i][j].real   -  pAuc[i][j].real * pAyc[i][j].imag;

            pAuc[i][j].real         =   pAuc[i][j].real * pAuc[i][j].real   + pAuc[i][j].imag * pAuc[i][j].imag;
            pAuc[i][j].imag         =   0;

            pAyc[i][j].real         =   ctmp.real;
            pAyc[i][j].imag         =   ctmp.imag;
        }
    }


    for (int j = 0; j < col; j++)
    {
        for (int i = 0; i < row; i++)
        {
            pAuco[j].real           =   pAuco[j].real + pAuc[i][j].real;
            pAuco[j].imag           =   pAuco[j].imag + pAuc[i][j].imag;

            pAyco[j].real           =   pAyco[j].real + pAyc[i][j].real;
            pAyco[j].imag           =   pAyco[j].imag + pAyc[i][j].imag;
        }
    }

    for (int i = 0; i < col/2; i++)
    {
        gin     =   sqrt(pAuco[i].real * pAuco[i].real + pAuco[i].imag * pAuco[i].imag);
        gout    =   sqrt(pAyco[i].real * pAyco[i].real + pAyco[i].imag * pAyco[i].imag);

        dtmp    =   20 * log10(gout/gin);

        angin   =   IFatanCal(pAuco[i].imag, pAuco[i].real);
        angout  =   IFatanCal(pAyco[i].imag, pAyco[i].real);

        temp    =   angin - angout;

        while ((temp < -M_PI) || (temp > M_PI))
        {
            if (temp > M_PI)
            {
                temp = temp - 2 * M_PI;
            }
            else
            {
                temp = temp + 2 * M_PI;
            }
        }

        ptmp    =   (temp/M_PI)*180.0;                                                          // unit deg

        dbb.append(dtmp);
        phh.append(ptmp);
    }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    for (int i = 0; i < row; i++)
    {
        delete [] pAu[i];
        delete [] pAy[i];
    }

    delete [] pAu;
    delete [] pAy;

    delete [] pWinw;

    for (int i = 0; i < row; i++)
    {
        delete [] pAuc[i];
        delete [] pAyc[i];
    }

    delete [] pAuc;
    delete [] pAyc;

    delete [] pAuco;
    delete [] pAyco;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    return;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


OrthgCorelAnalysis::~OrthgCorelAnalysis()
{
    m_data_fb_grp.clear();
}

//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
