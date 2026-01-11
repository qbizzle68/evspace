#ifndef _EVS_COMMON_H_
#define _EVS_COMMON_H_

// define to keep constructors that allocate memory from throwing std::bad_alloc
#ifdef EVSPACE_CONSTRUCTOR_NOTHROW
#include <new>
#define EVSPACE_NOTHROW     (std::nothrow)
#define EVSPACE_NOEXCEPT    noexcept
#else
#define EVSPACE_NOTHROW
#define EVSPACE_NOEXCEPT
#endif

// Can only safely use constexpr in our cases on C++20 and up
#if __cplusplus >= 202002L
#   define EVSPACE_CONSTEXPR constexpr
#else
#   define EVSPACE_CONSTEXPR
#endif

#if __cplusplus > 202302L
#   define EVSPACE_CONSTEXPR26 constexpr
#else
#   define EVSPACE_CONSTEXPR26
#endif

#endif // _EVS_COMMON_H_