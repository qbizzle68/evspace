#ifndef _EVS_COMMON_H_
#define _EVS_COMMON_H_

#if defined(_WIN32) && defined(EVSPACE_DLL)
#    ifdef EVSPACE_BUILD
//       Compiling a Windows DLL
#        define EVSPACE_EXPORT __declspec(dllexport)
#    else
//       Using a Windows DLL
#        define EVSPACE_EXPORT __declspec(dllimport)
#    endif
// Windows or Linux static library, or Linux so
#else
#    define EVSPACE_EXPORT
#endif

#endif // _EVS_COMMON_H_