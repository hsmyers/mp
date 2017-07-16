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
    int          maxiter;
    int          cv;
    int          width;
    int          height;
    char        *filename;
    char        *palname;
    char        *config;
    char        *aa;
    int          next;
    int          color;
    int          tweak;
} Parameters;

char *getstr( char *arg );
int getNext( char *path );
Parameters getParameters( int argc, char *argv[], char *Version, char *Date );
Parameters parse_ini_file( char * ini_name );
Parameters zeroP( void );
void freeParameters( Parameters p );
void help( char c, char *Program, char *Version, char *Date );
void showParameters( Parameters p );

#endif // GETOPT_H_