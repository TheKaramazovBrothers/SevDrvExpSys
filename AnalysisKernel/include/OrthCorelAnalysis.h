//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	Orthogonal correlation analysis   							//
//	file				:	OrthCorelAnalysis.h											//
//	Description			:	use for Orthogonal correlation analysis realization 		//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g           |	2022/9/19	|	liu.g           |		2022 - 2032			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ORTHCORELANALYSIS_H__
#define __ORTHCORELANALYSIS_H__

#include <QWidget>
#include <QStringList>

#include "DspCpu.h"


class OrthgCorelAnalysis
{
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
public:
    OrthgCorelAnalysis();
    ~OrthgCorelAnalysis();

    void setAnalySignalComp(double start_hz, double step_hz, double ts, int32 harm_num, int32 delay_tim, int32 data_lth);
    void RespAnalysisInSinSteadyState(QVector<qreal> * in, QVector<qreal> * rout, QVector<qreal> &dbb, QVector<qreal> &phh);
private:
    QList<QVector<qreal>>   m_data_fb_grp;                                                              // data feedback group in signal sinusoidal frequency

    QVector<qreal>			*m_data_ref;                                                                // data reference source
    QVector<qreal>          *m_data_fb;                                                                 // data feedback source

    QVector<qreal>			m_dbb;                                                                      // data reference source
    QVector<qreal>          m_phh;                                                                      // data feedback source
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    double                  m_sin_hz_start;                                                             // HZ
    double                  m_sin_hz_step;                                                              // HZ
    double                  m_ts;                                                                       // sample time | unit[s]

    int32                   m_sin_harm_num;                                                             // Harmonic number

    int32                   m_sin_delay_times;                                                          // by TS
    int32                   m_sin_data_lth;                                                             // effective data length
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
};












#endif


//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
