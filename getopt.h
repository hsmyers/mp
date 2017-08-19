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
#ifndef _GETOPT_H   // Include guard
#define _GETOPT_H
#include <stdbool.h>
#include <complex.h>
#include <quadmath.h>

/** Defines the size of the -k stack */
#define NAMES_SIZE 16

/**
 * @brief Variable gathered for image calculation.
 *
 * There are three sources for this data. The first is command line processing.
 * This is by way of short/long options via getopt_long(). The command line may
 * also be processed without options in fixed order. The second is the use of a
 * configuration file that essentially sets the default values for the necessary
 * parameters. The third method is parsing a JSON file which contains the
 * values for a particular fractal image.
 */
typedef struct  {
    __float128    centerX; /**< -x ℜ REAL part of complex center */
    __float128    centerY; /**< -y ℑ IMAG part of complex center */
    __float128    magnify; /**< -m image magnification */
    __float128    diameter; /**< -d diameter of image */
    __float128    radius; /**< -s radius of image length from 0.0 to end of upper axis */
    __complex128  center; /**< centerX + centerY * I */
    float         escape; /**< -e value to compare against for escape decision */
    int           maxiter; /**< -i ƒ(Z) iteration cap */
    int           nMax; /**< actual iteration count at escape */
    int           width; /**< -w image width in pixels */
    __float128    width2; /**< width / 2.0 */
    int           height; /**< -l image height in pixels */
    __float128    height2; /**< height / 2.0 */
    char         *filename; /**< -f image file name */
    char         *palname; /**< -p image palette filename */
    char         *config; /**< -c configuration filename */
    char         *aa; /**< -a anti-aliasing flag */
    char         *json; /**< =j JSON filename */
    char         *names[NAMES_SIZE]; /**< -k Rgb/color name list */
    char         *ultra; /**< -u takes Ultra Fractal formula in quotes */
    int           next; /**< -n seed for next mechanism */
    int           color; /**< -r key for -r; determines coloring */
    int           tweak; /**< -t limit for post iteration of ƒ(Z) */
    int           nargc; /**< count of number of -k entries */
    int           bourke; /**< -b flag for bourke interpolation */
    int           old; /**< key for -o; determines calculation method */
    int           writeJSON; /**< flag for JSON file output */
} Parameters;

/**
 * @brief Choice values for inner loop calculation.
 *
 * Currently 4 values in this list. COMPLEX is the default method. ZX uses all
 * real values, no complex variables. DEMM is the Distance Estimator Method for
 * the Mandelbrot set. MSETPOT is the Mandelbrot set via Continuous Potential
 * Method.
 */
enum innerLoop {
    COMPLEX, /**< ƒ(Z) = Z^2 + C where Z,C are complex */
    ZX, /**< ƒ(Z) =  as above using real ZX, ZY, CX, CY */
    DEMM, /**< Uses Distance estimation method */
    MSETCPM /**< Uses Continuous Potential method */
};

char *getstr( char *arg );
int getNext( char *path );
Parameters fromJSON( Parameters p );
Parameters getParameters( int argc, char *argv[], char *Version, char *Date );
Parameters rawCl( int argc, char *argv[], Parameters p );
Parameters parse_ini_file( char * ini_name, Parameters p );
Parameters zeroP( void );
void help( char c, char *Program, char *Version, char *Date );
void showParameters( Parameters p, char *s );
void toJSON( Parameters g );

#endif // _GETOPT_H