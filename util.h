/**
 **  @file util.h
 **  @author Hugh S. Myers
 **  @brief A collection of functions in aid of this and that.
 **  @date Mon Jul 24 19:30:12 2017
 **
 **  @section DESCRIPTION
 **
 **  Convenient parking lot for utility functions used by mp.
 **
 **  @bug No known bugs.
 **/
#ifndef _UTIL_H   /* Include guard */
#define _UTIL_H
#include <math.h>
#include <complex.h>

#define max(x,y) ( \
    { __auto_type __x = (x); __auto_type __y = (y); \
      __x > __y ? __x : __y; })

enum {
    FLT,
    DBL,
    LDBL,
    FLT128,
    FLTMPC,
    NOTYET
};

__float128 fabsq( __float128 x );
char **CommandLineToArgvA( char *lpCmdline, int *numargs );
char *getCl( int argc, char *argv[] );
char *guessStr( int g );
char *ReadFile( char *filename );
char *strgets( char **ptr );
double scaleWidth( double d, int N, double E );
int bestGuess( double diameter, int W );
int countChar( const char *s, const char c );
void signon( const char *prog, const char *Version );
void str2abbr( char *abbr, size_t size, const char *s );

#endif // _UTIL_H