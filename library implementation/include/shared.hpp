#ifndef LIBRARY_SYMBOL_VISIBILITY
#define LIBRARY_SYMBOL_VISIBILITY

    #ifdef IS_SHARED
        /* these macros are required for controlling symbol visibility for
        shared libraries. are otherwise ignored when compiling a static library */
        #if defined(_WIN32) || defined(__CYGWIN__)
            #ifdef USE_BUILD_SYMBOLS
                #define EXPORT __declspec(dllexport)
            #else
                #define EXPORT __declspec(dllimport)
            #endif
        #else
            #ifdef USE_BUILD_SYMBOLS
                #define EXPORT __attribute__((visibility("default")))
            #else
                #define EXPORT
            #endif
        #endif
    #else
        #define EXPORT
    #endif

#endif