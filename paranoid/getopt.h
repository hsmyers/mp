/**
 **  @file getopt.h
 **  @author Hugh S. Myers
 **  @brief A collection of functions in aid of creating a parameter object to
 **  carry around.
 **
 **  @date Tue Jul 25 11:49:07 2017
 **
 **  @section DESCRIPTION
 **
 **  Function declarations. More importantly the typedef for Parameters.
 **
 **  @bug No known bugs.
 **/
#ifndef GETOPT_H_   /* Include guard */
#define GETOPT_H_
#include <stdbool.h>
#include <complex.h>

#define NAMES_SIZE 16

typedef struct  {
    __float128  centerX;
    __float128  centerY;
    __float128  magnify;
    __float128  diameter;
    __float128  radius;
    __float128  center;
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
    char        *names[NAMES_SIZE];
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