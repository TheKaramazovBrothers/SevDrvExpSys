//
// MATLAB Compiler: 8.0 (R2020a)
// Date: Thu Oct 20 15:48:59 2022
// Arguments:
// "-B""macro_default""-W""cpplib:my_prbs_idf_n4sid""-T""link:lib""my_prbs_idf_n
// 4sid.m"
//

#ifndef my_prbs_idf_n4sid_h
#define my_prbs_idf_n4sid_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" { // sbcheck:ok:extern_c
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_my_prbs_idf_n4sid_C_API 
#define LIB_my_prbs_idf_n4sid_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_my_prbs_idf_n4sid_C_API 
bool MW_CALL_CONV my_prbs_idf_n4sidInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_my_prbs_idf_n4sid_C_API 
bool MW_CALL_CONV my_prbs_idf_n4sidInitialize(void);

extern LIB_my_prbs_idf_n4sid_C_API 
void MW_CALL_CONV my_prbs_idf_n4sidTerminate(void);

extern LIB_my_prbs_idf_n4sid_C_API 
void MW_CALL_CONV my_prbs_idf_n4sidPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_my_prbs_idf_n4sid_C_API 
bool MW_CALL_CONV mlxMy_prbs_idf_n4sid(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                       *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_my_prbs_idf_n4sid
#define PUBLIC_my_prbs_idf_n4sid_CPP_API __declspec(dllexport)
#else
#define PUBLIC_my_prbs_idf_n4sid_CPP_API __declspec(dllimport)
#endif

#define LIB_my_prbs_idf_n4sid_CPP_API PUBLIC_my_prbs_idf_n4sid_CPP_API

#else

#if !defined(LIB_my_prbs_idf_n4sid_CPP_API)
#if defined(LIB_my_prbs_idf_n4sid_C_API)
#define LIB_my_prbs_idf_n4sid_CPP_API LIB_my_prbs_idf_n4sid_C_API
#else
#define LIB_my_prbs_idf_n4sid_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_my_prbs_idf_n4sid_CPP_API void MW_CALL_CONV my_prbs_idf_n4sid(int nargout, mwArray& dbb, mwArray& phh, const mwArray& u0, const mwArray& y0, const mwArray& ts);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
