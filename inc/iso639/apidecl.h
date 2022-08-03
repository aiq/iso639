#ifndef ISO639_APIDECL_H
#define ISO639_APIDECL_H

#ifdef ISO639_STATIC_DEFINE
#  define ISO639_API
#  define ISO639_NO_EXPORT
#else
#  ifdef _WIN32
#    ifndef ISO639_API
#      ifdef iso639_EXPORTS
#        define ISO639_API __declspec(dllexport)
#      else
#        define ISO639_API __declspec(dllimport)
#      endif
#    endif
#  else
#    define ISO639_API
#    define ISO639_NO_EXPORT
#  endif
#
#  ifndef ISO639_NO_EXPORT
#    define ISO639_NO_EXPORT 
#  endif
#endif

#endif