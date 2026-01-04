#ifndef _EVS_COMMON_H_
#define _EVS_COMMON_H_

#if defined(_WIN32) && defined(EVSPACE_SHARED_LIB)
#    ifdef EVSPACE_BUILD
//       Compiling a Windows DLL
#        define EVSPACE_API __declspec(dllexport)
#    else
//       Using a Windows DLL
#        define EVSPACE_API __declspec(dllimport)
#    endif
// Windows or Linux static library, or Linux so
#else
#    define EVSPACE_API
#endif

// define to keep constructors that allocate memory from throwing std::bad_alloc
#ifdef EVSPACE_CONSTRUCTOR_NOTHROW
#include <new>
#define EVSPACE_NOTHROW     (std::nothrow)
#define EVSPACE_NOEXCEPT    noexcept
#else
#define EVSPACE_NOTHROW
#define EVSPACE_NOEXCEPT
#endif

#if defined(__GNUC__) || defined(__clang__)
#   define EVSPACE_RESTRICT __restrict__
#elif defined(_MSC_VER)
#   define EVSPACE_RESTRICT __restrict
#else
#   define EVSPACE_RESTRUCT
#endif


#endif // _EVS_COMMON_H_