
#ifndef ASSIMPLIB_EXPORT_H
#define ASSIMPLIB_EXPORT_H

#ifdef ASSIMPLIB_STATIC_DEFINE
#  define ASSIMPLIB_EXPORT
#  define ASSIMPLIB_NO_EXPORT
#else
#  ifndef ASSIMPLIB_EXPORT
#    ifdef AssimpLib_EXPORTS
        /* We are building this library */
#      define ASSIMPLIB_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define ASSIMPLIB_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef ASSIMPLIB_NO_EXPORT
#    define ASSIMPLIB_NO_EXPORT 
#  endif
#endif

#ifndef ASSIMPLIB_DEPRECATED
#  define ASSIMPLIB_DEPRECATED __declspec(deprecated)
#endif

#ifndef ASSIMPLIB_DEPRECATED_EXPORT
#  define ASSIMPLIB_DEPRECATED_EXPORT ASSIMPLIB_EXPORT ASSIMPLIB_DEPRECATED
#endif

#ifndef ASSIMPLIB_DEPRECATED_NO_EXPORT
#  define ASSIMPLIB_DEPRECATED_NO_EXPORT ASSIMPLIB_NO_EXPORT ASSIMPLIB_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ASSIMPLIB_NO_DEPRECATED
#    define ASSIMPLIB_NO_DEPRECATED
#  endif
#endif

#endif /* ASSIMPLIB_EXPORT_H */
