
#ifndef GUILIB_EXPORT_H
#define GUILIB_EXPORT_H

#ifdef GUILIB_STATIC_DEFINE
#  define GUILIB_EXPORT
#  define GUILIB_NO_EXPORT
#else
#  ifndef GUILIB_EXPORT
#    ifdef GUILib_EXPORTS
        /* We are building this library */
#      define GUILIB_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define GUILIB_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef GUILIB_NO_EXPORT
#    define GUILIB_NO_EXPORT 
#  endif
#endif

#ifndef GUILIB_DEPRECATED
#  define GUILIB_DEPRECATED __declspec(deprecated)
#endif

#ifndef GUILIB_DEPRECATED_EXPORT
#  define GUILIB_DEPRECATED_EXPORT GUILIB_EXPORT GUILIB_DEPRECATED
#endif

#ifndef GUILIB_DEPRECATED_NO_EXPORT
#  define GUILIB_DEPRECATED_NO_EXPORT GUILIB_NO_EXPORT GUILIB_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef GUILIB_NO_DEPRECATED
#    define GUILIB_NO_DEPRECATED
#  endif
#endif

#endif /* GUILIB_EXPORT_H */
