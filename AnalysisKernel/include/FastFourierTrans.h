//////////////////////////////////////////////////////////////////////////////////////////
//	summary				:	fast fourier transform design   							//
//	file				:	FastFourierTrans.h											//
//	Description			:	use for system signal analysis      						//
//	lib					:	none														//
//																						//
//======================================================================================//
//		programmer:		|	date:		|	Corporation:	|		copyright(C):		//
//--------------------------------------------------------------------------------------//
//		liu.g           |	2022/9/8	|	liu.g           |		2022 - 2032			//
//--------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef		__FASTFOURIERTRANS_H__
#define		__FASTFOURIERTRANS_H__

#ifndef     M_PI
#define     M_PI				3.14159265358979323846
#endif

#include "DspCpu.h"


typedef struct complex
{
	double real;
	double imag;
}COMPLEX;

///////////////////////////////////////////////////////////////////////////////////////////
//function  declaration

int transform(double real[], double imag[], Uint32 n);

int inverse_transform(double real[], double imag[], Uint32 n);

int transform_radix2(double real[], double imag[], Uint32 n);

int transform_bluestein(double real[], double imag[], Uint32 n);

int convolve_real(double x[], double y[], double out[], Uint32 n);

int convolve_complex(double xreal[], double ximag[], double yreal[], double yimag[], double outreal[], double outimag[], Uint32 n);

double	IFatanCal(double xq, double xd);

// Private function prototypes
static int32	reverse_bits(int32 x, Uint32 n);
static void		*memdup(void *src, Uint32 n);
static int32	reverse_bits1(int32 x, Uint32 levels);

///////////////////////////////////////////////////////////////////////////////////////////
//new function 

int transform_x(COMPLEX* x, Uint32 n);

int inverse_transform_x(COMPLEX* x, Uint32 n);

int transform_radix2_x(COMPLEX* x, Uint32 n);

int transform_bluestein_x(COMPLEX* x, Uint32 n);

int transform2D(COMPLEX* X1, COMPLEX* X2, Uint32 N);

int inverse_transform2D(COMPLEX* X1, COMPLEX* X2, Uint32 N);

int transform1(COMPLEX* X, Uint32 N);

int inverse_transform1(COMPLEX* X, Uint32 N);




#endif


//////////////////////////////////////////////// NO MORE /////////////////////////////////////////////////
