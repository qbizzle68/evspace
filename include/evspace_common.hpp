// This file includes gsl::span from Microsoft GSL
// License: MIT, https://github.com/microsoft/GSL

#ifndef _EVSPACE_COMMON_H_
#define _EVSPACE_COMMON_H_

#if __cplusplus >= 202002L
#include <span>
#else
#include <gsl/span>
#endif

namespace evspace {
    
#if __cplusplus >= 202002L
template<typename T>
using span_t = std::span<T>;
#define EVSPACE_USING_STD_SPAN
#else
template<typename T>
using span_t = gsl::span<T>;
#define EVSPACE_USING_GSL_SPAN
#endif // _EVSPACE_COMMON_H_

#define _EVSPACE_DEFAULT_ULP_MAXIMUM 10

}

#endif // _EVSPACE_COMMON_H_