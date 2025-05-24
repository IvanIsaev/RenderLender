
#ifndef RLMATHLIB_EXPORT_H
#define RLMATHLIB_EXPORT_H

#ifdef RLMATHLIB_STATIC_DEFINE
#  define RLMATHLIB_EXPORT
#  define RLMATHLIB_NO_EXPORT
#else
#  ifndef RLMATHLIB_EXPORT
#    ifdef RLMathLib_EXPORTS
        /* We are building this library */
#      define RLMATHLIB_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define RLMATHLIB_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef RLMATHLIB_NO_EXPORT
#    define RLMATHLIB_NO_EXPORT 
#  endif
#endif

#ifndef RLMATHLIB_DEPRECATED
#  define RLMATHLIB_DEPRECATED __declspec(deprecated)
#endif

#ifndef RLMATHLIB_DEPRECATED_EXPORT
#  define RLMATHLIB_DEPRECATED_EXPORT RLMATHLIB_EXPORT RLMATHLIB_DEPRECATED
#endif

#ifndef RLMATHLIB_DEPRECATED_NO_EXPORT
#  define RLMATHLIB_DEPRECATED_NO_EXPORT RLMATHLIB_NO_EXPORT RLMATHLIB_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef RLMATHLIB_NO_DEPRECATED
#    define RLMATHLIB_NO_DEPRECATED
#  endif
#endif

#endif /* RLMATHLIB_EXPORT_H */
