//
// util.h
//
#ifndef UTIL_H_   /* Include guard */
#define UTIL_H_

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

char *getCl( int argc, char *argv[] );
char *ReadFile( char *filename );
char *guessStr( int g );
double scaleWidth( double d, int N, double E );
int bestGuess( double diameter, int W );

#endif // UTIL_H_