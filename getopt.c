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
#include "cJSON.h"
#include "util.h"

#ifdef TEST
char *Version = "0.019";
char *Date = "Mon Jul 17 09:05:17 2017";

int main( int argc, char **argv ) {
    Parameters p = getParameters( argc, argv, Version, Date );

    printf("\n  optind='%d', argc='%d'\n\n", optind, argc );
    showParameters( p );
    printf("\n");
    for (int i = optind; i < argc; ++i) {
        printf("  argv[%d]='%s'\n", i, argv[i] );
    }

    return 0;
}
#endif

Parameters getParameters( int argc, char *argv[], char *Version, char *Date ) {
    Parameters p = zeroP();
    p = parse_ini_file( "mandel.cfg", p );
    static char nextname[128];
    const char *options = "a:c:d:f:hi:j:l:m:n::p:r:t:vw:x:y:";
    int c;
#ifdef TEST
    printf( "  getParameters()\n");
#endif

    while ( true ) {
        static struct option long_options[] = {
            {"aa", required_argument, 0, 'a'},
            {"config", required_argument, 0, 'c'},
            {"diameter", required_argument, 0, 'd'},
            {"file", required_argument, 0, 'f'},
            {"height", required_argument, 0, 'l'},
            {"help", no_argument, 0, 'h'},
            {"iteration", required_argument, 0, 'i'},
            {"json", required_argument, 0, 'j'},
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

        c = getopt_long( argc, argv, options, long_options, &option_index );
        if ( optind == 1) {
            p = rawCl( argc, argv, p );
            break;
        }
        if ( c == -1 )
            break;

        switch ( c ) {
            case 0:
                break;
            case 'a':
                p.aa = optarg;
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
                sprintf( nextname, "fractal.%03d.jpg", p.next++ );
                p.filename = nextname;
                break;
            case 'c':
                p.config = optarg;
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
            case 'j':
                p.json = optarg;
                p = fromJSON( p.json, p );
                break;
            case 'l':
                p.height = atoi( optarg );
                break;
            case 'f':
                p.filename = optarg;
                break;
            case 'p':
                p.palname = optarg;
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

Parameters fromJSON( char *jsonfile, Parameters p ) {
    Parameters g = p;
    char buffer[100];
#ifdef TEST
    printf( "  fromJSON()\n" );
#endif
    g.json = jsonfile;
    char *json = ReadFile( g.json );
    if ( json != NULL ) {
        cJSON *root = cJSON_Parse( json );
        cJSON *params = cJSON_GetObjectItemCaseSensitive( root, "params" );
        cJSON *centerX_item = cJSON_GetObjectItemCaseSensitive( params, "centerX" );
        if ( cJSON_IsString( centerX_item ) ) {
            strcpy( buffer, centerX_item->valuestring );
            g.centerX = strtold( buffer, NULL );
        } else if ( cJSON_IsNumber( centerX_item ) ) {
            g.centerX = centerX_item->valuedouble;
        }
        cJSON *centerY_item = cJSON_GetObjectItemCaseSensitive( params, "centerY" );
        if ( cJSON_IsString( centerY_item ) ) {
            strcpy( buffer, centerY_item->valuestring );
            g.centerY = strtold( buffer, NULL );
        } else if ( cJSON_IsNumber( centerY_item ) ) {
            g.centerY = centerY_item->valuedouble;
        }
        cJSON *magnify_item = cJSON_GetObjectItemCaseSensitive( params, "magnify" );
        if ( cJSON_IsString( magnify_item ) ) {
            strcpy( buffer, magnify_item->valuestring );
            g.diameter = strtold( buffer, NULL );
        } else if ( cJSON_IsNumber( magnify_item ) ) {
            g.diameter = magnify_item->valuedouble;
        }
        cJSON *maxIterations_item = cJSON_GetObjectItemCaseSensitive( params, "maxIterations" );
        if ( cJSON_IsNumber( maxIterations_item ) )
            g.maxiter = ( long ) maxIterations_item->valuedouble;
        cJSON *width_item = cJSON_GetObjectItemCaseSensitive( params, "width" );
        if ( cJSON_IsNumber( width_item ) )
            g.width = ( int ) width_item->valuedouble;
        cJSON *height_item = cJSON_GetObjectItemCaseSensitive( params, "height" );
        if ( cJSON_IsNumber( height_item ) )
            g.height = ( int ) height_item->valuedouble;
        cJSON_Delete( root );
        free( json );
    } else {
            printf( "error in JSON parameter file: %s\n", g.json );
            exit(1);
    }
    return g;
}

Parameters rawCl( int argc, char *argv[], Parameters p ) {
    Parameters g = p;
#ifdef TEST
    printf( "  rawCl()\n");
#endif
    if ( argc >= 3 && argc <= 7 ) {
        g.filename = argv[2];
        g = fromJSON( argv[1], g );
        if ( argc >= 4 ) {
            g.color = atoi( argv[3] );
        }
        if ( argc >= 5 ) {
            g.tweak = atoi( argv[4] );
        }
        if ( argc >= 6 ) {
            g.aa = argv[5];
        }
    } else if ( argc >= 8 ) {
        g.centerX  = strtold( argv[1], NULL );
        g.centerY  = strtold( argv[2], NULL );
        g.diameter = strtold( argv[3], NULL );
        g.maxiter  = atol( argv[4] );
        g.width    = atol( argv[5] );
        g.height   = atol( argv[6] );
        g.filename = argv[7];
        if ( argc >= 9 ) {
            g.color = atoi( argv[8] );
        }
        if ( argc >= 10 ) {
            g.tweak = atoi( argv[9] );
        }
        if ( argc >= 11 ) {
            g.aa = argv[10];
        }

    } else {
        printf( "Usage: either a JSON parameter filename and output file,\n" );
        printf( "    or the above with the name of an anti-aliased file,\n" );
        printf( "    or 7 parameters:\n" );
        printf( "\n" );
        printf( "    center X parameter\n" );
        printf( "    center Y parameter\n" );
        printf( "    diameter parameter\n" );
        printf( "    iteration parameter\n" );
        printf( "    width parameter\n" );
        printf( "    height parameter\n" );
        printf( "    output filename\n" );
        exit(1);
    }
    return g;   
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
        printf( "  --json        requires number as an argument -j\n" );
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

Parameters parse_ini_file( char *ini_name, Parameters g ) {
    Parameters p = g;
    dictionary *ini;

#ifdef TEST
    printf( "  parse_ini_file()\n");
#endif    
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
    p.color = iniparser_getint( ini, "color:color", 10 );

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
    printf( "  p.json      = '%s'\n", p.json );
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
    g.aa = NULL;
    g.json = NULL;
    g.next = 0;
    g.color = 0;
    g.tweak = 0;

    return g;
}
