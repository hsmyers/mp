//
// getopt.h
//
#ifndef GETOPT_H_   /* Include guard */
#define GETOPT_H_
#include <stdbool.h>

typedef struct  {
    long double  centerX;
    long double  centerY;
    long double  magnify;
    long double  diameter;
    float        escape;
    int          maxiter;
    int          nMax;
    int          cv;
    int          width;
    int          height;
    char        *filename;
    char        *palname;
    char        *config;
    char        *aa;
    char        *json;
    char        *names[2];
    int          next;
    int          color;
    int          tweak;
    int          nargc;
} Parameters;

char *getstr( char *arg );
int getNext( char *path );
Parameters fromJSON( char *jsonfile, Parameters p );
Parameters getParameters( int argc, char *argv[], char *Version, char *Date );
Parameters rawCl( int argc, char *argv[], Parameters p );
Parameters parse_ini_file( char * ini_name, Parameters p );
Parameters zeroP( void );
void help( char c, char *Program, char *Version, char *Date );
void showParameters( Parameters p );

#endif // GETOPT_H_