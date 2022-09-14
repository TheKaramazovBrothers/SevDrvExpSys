//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	algorithm for singal analysis								//
//	file				:	SignalAnalysis.h                                            //
//	Description			:	algorithm realization for signal analysis       			//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g           |	2022/9/08	|	liu.g           |		2022 - 2032			//
//--------------------------------------------------------------------------------------//

#ifndef __SIGNALANALYSIS_H__
#define __SIGNALANALYSIS_H__

#include "DspCpu.h"
#include "FastFourierTrans.h"

int RespAnalysisInFreDomain(double * r_in, double * r_out, double * dbb, double * phh, unsigned int n);

int SignalAnalysisFFT(double * r_in, double * dbb, double * phh, unsigned int n);

//new fft can speed up 

int RespAnalysisInFreDomain_x(COMPLEX* input, COMPLEX* output, double * dbb, double * phh, unsigned int n);

int SignalAnalysisFFT_x(COMPLEX* input, double * dbb, double * phh, unsigned int n);





#endif



//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
