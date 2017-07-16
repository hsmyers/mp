//
// getopt.c
//
// to compile:  gcc -Wall -DTEST getopt.c dictionary.c iniparser.c -o getopt
//
// dictionary.c
// iniparser.c
//
#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>
#include "iniparser.h"
#include "getopt.h"

#ifdef TEST
char *Version = "0.016";
char *Date = "Sun Jul 16 11:54:11 2017";

int main( int argc, char **argv ) {
    Parameters p = getParameters( argc, argv, Version, Date );

    showParameters( p );
    freeParameters( p );

    return 0;
}
#endif

Parameters getParameters( int argc, char *argv[], char *Version, char *Date ) {
    Parameters p = parse_ini_file( "mandel.cfg" );
    char buffer[256];
    int c;

    while ( true ) {
        static struct option long_options[] = {
            {"aa", required_argument, 0, 'a'},
            {"config", required_argument, 0, 'c'},
            {"diameter", required_argument, 0, 'd'},
            {"file", required_argument, 0, 'f'},
            {"height", required_argument, 0, 'l'},
            {"help", no_argument, 0, 'h'},
            {"iteration", required_argument, 0, 'i'},
            {"magnify", required_argument, 0, 'm'},
            {"next", optional_argument, 0, 'n'},
            {"palette", required_argument, 0, 'p'},
            {"color", required_argument, 0, 'r'},
            {"tweak", required_argument, 0, 't'},
            {"version", no_argument, 0, 'v'},
            {"width", required_argument, 0, 'w'},
            {"x_center", required_argument, 0, 'x'},
            {"y_center", required_argument, 0, 'y'},
            {0, 0, 0, 0}
        };
        int option_index = 0;

        c = getopt_long( argc, argv, "l:a:d:t:r:c:x:y:m:i:w:h::d:f:p:n::vl", long_options, &option_index );
        if ( c == -1 )
            break;

        switch ( c ) {
            case 0:
                break;
            case 'a':
                free( p.aa );
                p.aa = getstr( optarg );
                break;
            case 'x':
                sscanf( optarg, "%Lf", &p.centerX );
                break;
            case 'y':
                sscanf( optarg, "%Lf", &p.centerY );
                break;
            case 'm':
                sscanf( optarg, "%Lf", &p.magnify );
                p.diameter = 1.0 / p.magnify;
                break;
            case 'd':
                sscanf( optarg, "%Lf", &p.diameter );
                break;
            case 'n':
                if ( optarg ) {
                    p.next = atoi( ++optarg );
                } else {
                    p.next = getNext( "jpg" );
                }
                sprintf( buffer, "fractal.%03d.jpg", p.next++ );
                free( p.filename );
                p.filename = getstr( buffer );
                break;
            case 'c':
                free( p.config );
                p.config = getstr( optarg );
                break;
            case 'r':
                p.color = atoi( optarg );
                break;
            case 't':
                p.tweak = atoi( optarg );
                break;
            case 'i':
                p.maxiter = atoi( optarg );
                break;
            case 'w':
                p.width = atoi( optarg );
                break;
            case 'l':
                p.height = atoi( optarg );
                break;
            case 'f':
                free( p.filename );
                p.filename = getstr( optarg );
                break;
            case 'p':
                free( p.palname );
                p.palname = getstr( optarg );
                break;
            case '?':
                help( '?', argv[0], Version, Date );
                break;
            case 'v':
                help( 'v', argv[0], Version, Date );
                break;
            case 'h':
                help( 'h', argv[0], Version, Date );
                break;
            default:
                abort(  );
        }
    }
    return p;
}

void help( char c, char *Program, char *Version, char *Date ) {
    printf( "%s v%s dated %s\n", Program, Version, Date );
    if ( c == 'h' || c == '?' ) {
        printf( "\n  Options:\n\n" );
        printf( "  --x_center    requires real as an argument   -x\n" );
        printf( "  --y_center    requires real as an argument   -y\n" );
        printf( "  --magnify     requires real as an argument   -m\n" );
        printf( "  --diameter    requires real as an argument   -d\n" );
        printf( "  --iteration   requires number as an argument -i\n" );
        printf( "  --width       requires number as an argument -w\n" );
        printf( "  --height      requires number as an argument -l\n" );
        printf( "  --file        requires string as an argument -f\n" );
        printf( "  --palette     requires string as an argument -p\n" );
        printf( "  --next        argument is optional number    -n\n" );
        printf( "  --config      requires string as an argument -c\n" );
        printf( "  --color       requires number as an argument -r\n" );
        printf( "  --aa          requires string as an argument -a\n" );
        printf( "  --tweak       requires number as an argument -t\n" );
        printf( "  --version     no argument                    -v\n" );
        printf( "  --help        no argument                    -h\n" );
        printf( "\n  long options ('--' prefix) are incremental till unambiguous\n" );
        printf( "  short options ('-' prefix) are exact\n" );
        printf( "  Hideously enough, options with optional arguments,\n" );
        printf( "  take the form [-[-]]option=arg, no spaces.\n" );
    }
    exit( 0 );
}

void freeParameters( Parameters p ) {
    free( p.filename );
    free( p.aa );
    free( p.palname );
    free( p.config );
    return;
}

Parameters parse_ini_file( char *ini_name ) {
    Parameters p;
    dictionary *ini;

    ini = iniparser_load( ini_name );
    if ( ini == NULL ) {
        fprintf( stderr, "cannot parse file: %s\n", ini_name );
        return p;
    }

    p.centerX = iniparser_getlongdouble( ini, "image:centerx", -0.65 );
    p.centerY = iniparser_getlongdouble( ini, "image:centery", 0.0 );
    p.magnify = iniparser_getlongdouble( ini, "image:magnify", 2.75 );
    p.maxiter = iniparser_getint( ini, "image:maxiter", 500 );
    p.width = iniparser_getint( ini, "image:width", 3840 );
    p.height = iniparser_getint( ini, "image:height", 2160 );

    p.cv = iniparser_getint( ini, "color:cv", 64 );
    p.tweak = iniparser_getint( ini, "color:tweak", 3 );

    p.filename = getstr( ( char * )
                         iniparser_getstring( ini, "files:filename", "fractal.000.jpg" ) );
    p.config = getstr( ( char * ) iniparser_getstring( ini, "files:config", "mandel.cfg" ) );
    p.palname = getstr( ( char * ) iniparser_getstring( ini, "files:palname", "test.pal" ) );
    p.next = iniparser_getint( ini, "files:next", 0 );

    iniparser_freedict( ini );
    return p;
}

int getNext( char *path ) {
    DIR *dp;
    struct dirent *ep;
    char *ptr;
    char buffer[256];
    int n;
    int max = 0;

    dp = opendir( path );
    if ( dp != NULL ) {
        while ( ( ep = readdir( dp ) ) ) {
            n = -1;
            strcpy( buffer, ep->d_name );
            ptr = strtok( buffer, "." );
            while ( ( ptr = strtok( NULL, "." ) ) ) {
                if ( isdigit( ptr[0] ) ) {
                    n = atoi( ptr );
                }
            }
            if ( max < n ) {
                max = n;
            }
        }
        ++max;
        closedir( dp );
    } else {
        perror( "Couldn't open the directory" );
    }
    return max;
}

char *getstr( char *arg ) {
    char *result = malloc( strlen( arg ) + 1 );
    strcpy( result, arg );
    return result;
}

void showParameters( Parameters p ) {
    printf( "  p.centerX   = '%.17Lg'\n", p.centerX );
    printf( "  p.centerY   = '%.17Lg'\n", p.centerY );
    printf( "  p.magnify   = '%.17Lg'\n", p.magnify );
    printf( "  p.diameter  = '%.17Lg'\n", p.diameter );
    printf( "  p.maxiter   = '%d'\n", p.maxiter );
    printf( "  p.cv        = '%d'\n", p.cv );
    printf( "  p.width     = '%d'\n", p.width );
    printf( "  p.height    = '%d'\n", p.height );
    printf( "  p.filename  = '%s'\n", p.filename );
    printf( "  p.palname   = '%s'\n", p.palname );
    printf( "  p.config    = '%s'\n", p.config );
    printf( "  p.next      = '%d'\n", p.next );
    printf( "  p.color     = '%d'\n", p.color );
    printf( "  p.aa        = '%s'\n", p.aa );
    printf( "  p.tweak     = '%d'\n", p.tweak );
}

Parameters zeroP( void ) {
    Parameters g;

    g.centerX = 0;
    g.centerY = 0;
    g.magnify = 0;
    g.diameter = 0;
    g.maxiter = 0;
    g.cv = 0;
    g.width = 0;
    g.height = 0;
    g.filename = NULL;
    g.palname = NULL;
    g.config = NULL;
    g.next = 0;
    g.color = 0;
    g.aa = NULL;
    g.tweak = 0;

    return g;
}
