/**
 **  @file getopt.c
 **  @author Hugh S. Myers
 **  @brief Implementation of getopt_long for mp
 **  @date Mon Jul 24 15:05:30 2017
 **
 **  These functions allow mp to garner information from a variety of sources.
 **  From the command line, both with and without the traditional dashes, as well
 **  as from an 'ini' or configuration file. Sufficient information can be
 **  gathered from .JSON files as well,
 **
 **  @note gcc -Wall -DGETOPT_TEST cnames.c cJSON.c getopt.c dictionary.c iniparser.c util.c -o getopt -lquadmath<br>
 **        gcc -ggdb -Wall -DGETOPT_TEST cnames.c cJSON.c getopt.c dictionary.c iniparser.c util.c -o getopt -lquadmath<br>
 **
 **  @bug No known bugs.
 **/
#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>
#include <quadmath.h>
#include "iniparser.h"
#include "getopt.h"
#include "cJSON.h"
#include "util.h"
#include "cnames.h"

#ifdef GETOPT_TEST
char *Version = "0.022";
char *Date = "Sat Aug 05 21:36:43 2017";

int main( int argc, char **argv ) {

    signon( argv[0], Version );
    printf("\n");
    Parameters g = getParameters( argc, argv, Version, Date );
    printf("\n  optind='%d', argc='%d'\n\n", optind, argc );
    showParameters( g, "post GetParameters call…\n" );
    printf("\n");
    if ( g.nargc ) {
        Rgb r;
        for (int i = 0; i < g.nargc; ++i) {
            if ( str2Rgb( g.names[i], &r) ) {
                printf("  names[%d] = '%s' Rgb = { %d, %d, %d }\n", i, g.names[i], r.r, r.g, r.b  );
            }
        }
    }
    printf("\n");
    for (int i = optind; i < argc; ++i) {
        printf("  argv[%d]='%s'\n", i, argv[i] );
    }
    printf( " mp should display:\n\n" );
    printf( "%s-diameter:%.17Lg, dims: %dx%d %s color=%d, tweak=%d aa=%s\n", "???",
            ( long double ) g.diameter, g.width, g.height, g.filename, g.color, g.tweak, g.aa );

    return 0;
}
#endif

Parameters getParameters( int argc, char *argv[], char *Version, char *Date ) {
    Parameters p = parse_ini_file( "mandel.cfg", zeroP() );
    static char nextname[128];
    static char centerx[128];
    static char centery[128];
    static char magn[128];
// Not yet used:
//                                    g                 q
//                                    |                 |
    const char *options = "a:b:c:d:e:f:hi:j:k:l:m:o:n::p:r:s:t:u:vw:x:y:";
    int c;
#ifdef GETOPT_TEST
    printf( "  getParameters()\n");
#endif

    while ( true ) {
        static struct option long_options[] = {
            {"aa", required_argument, 0, 'a'},
            {"bourke", required_argument, 0, 'b'},
            {"color", required_argument, 0, 'r'},
            {"config", required_argument, 0, 'c'},
            {"diameter", required_argument, 0, 'd'},
            {"escape", required_argument, 0, 'e'},
            {"file", required_argument, 0, 'f'},
            {"height", required_argument, 0, 'l'},
            {"help", no_argument, 0, 'h'},
            {"iteration", required_argument, 0, 'i'},
            {"json", required_argument, 0, 'j'},
            {"kolor", required_argument, 0, 'k'},
            {"magnify", required_argument, 0, 'm'},
            {"next", optional_argument, 0, 'n'},
            {"old", required_argument, 0, 'o'},
            {"palette", required_argument, 0, 'p'},
            {"semidiameter", required_argument, 0, 's'},
            {"tweak", required_argument, 0, 't'},
            {"ultra", required_argument, 0, 'u'},
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
            case 'u':
                sscanf( optarg, "BackgroundLocation { location:   center=%[^/]/%s magn=%s }", centerx, centery, magn );
                p.centerX = strtoflt128( centerx, NULL );
                p.centerY = strtoflt128( centery, NULL );
                p.magnify = strtoflt128( magn, NULL );
                p.diameter = 1.0 / ( p.magnify / 3.0 );
                p.radius = p.diameter / 2.0;
#ifdef GETOPT_TEST
    printf( "\n  -u\n" );
    printf( "  centerx='%s'\n", centerx );
    printf( "  centery='%s'\n", centery );
    printf( "  magn='%s'\n", magn );
    printf( "  optarg='%s'\n\n", optarg );
#endif
                break;
            case 'k':
                if ( p.nargc < NAMES_SIZE) {
                    p.names[p.nargc++] = optarg;
                }
                break;
            case 'o':
                if ( stricmp(optarg, "COMPLEX" ) == 0 ) {
                    p.old = COMPLEX;
                } else if ( stricmp(optarg, "ZX" ) == 0 ) {
                    p.old = ZX;
                } else if ( stricmp(optarg, "DEMM" ) == 0 ) {
                    p.old = DEMM;
                } else if ( stricmp(optarg, "MSETCPM" ) == 0 ) {
                    p.old = MSETCPM;
                } else {
                    p.old = atoi( optarg );
                }
                break;
            case 'a':
                p.aa = optarg;
                break;
            case 'x':
                p.centerX = strtoflt128( optarg, NULL );
                break;
            case 'y':
                p.centerY = strtoflt128( optarg, NULL );
                break;
            case 'm':
                p.magnify = strtoflt128( optarg, NULL );
                p.diameter = 1.0 / p.magnify;
                p.radius = p.diameter / 2.0;
                break;
            case 'd':
                p.diameter = strtoflt128( optarg, NULL );
                p.radius = p.diameter / 2.0;
                break;
            case 's':
                p.radius = strtoflt128( optarg, NULL );
                p.diameter = p.radius * 2.0;
                break;
            case 'e':
                sscanf( optarg, "%f", &p.escape );
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
            case 'b':
                p.bourke = atoi( optarg );
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
                if (strnicmp( optarg, "W:", 2 ) == 0 ) {
                    p.json = optarg + 2;
                    p.writeJSON = 1;
                } else {
                    p.json = optarg;
                    p = fromJSON( p );
                }
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
    p.center = p.centerX + p.centerY * I;
    p.width2 = p.width;
    p.width2 /= 2.0;
    p.height2 = p.height;
    p.height2 /= 2.0;
    if (p.writeJSON) {
        toJSON( p );
    }
    return p;
}

Parameters fromJSON( Parameters p ) {
    Parameters g = p;
    char buffer[100];

#ifdef GETOPT_TEST
    printf( "  fromJSON()\n" );
#endif
    char *json = ReadFile( g.json );
    if ( json != NULL ) {
        cJSON *root = cJSON_Parse( json );
        cJSON *params = cJSON_GetObjectItemCaseSensitive( root, "params" );
        cJSON *centerX_item = cJSON_GetObjectItemCaseSensitive( params, "centerX" );
        if ( cJSON_IsString( centerX_item ) ) {
            strcpy( buffer, centerX_item->valuestring );
            g.centerX = strtoflt128( buffer, NULL );
        } else if ( cJSON_IsNumber( centerX_item ) ) {
            g.centerX = centerX_item->valuedouble;
        }
        cJSON *centerY_item = cJSON_GetObjectItemCaseSensitive( params, "centerY" );
        if ( cJSON_IsString( centerY_item ) ) {
            strcpy( buffer, centerY_item->valuestring );
            g.centerY = strtoflt128( buffer, NULL );
        } else if ( cJSON_IsNumber( centerY_item ) ) {
            g.centerY = centerY_item->valuedouble;
        }
        cJSON *magnify_item = cJSON_GetObjectItemCaseSensitive( params, "magnify" );
        if ( cJSON_IsString( magnify_item ) ) {
            strcpy( buffer, magnify_item->valuestring );
            g.diameter = strtoflt128( buffer, NULL );
            g.radius = g.diameter / 2.0;
        } else if ( cJSON_IsNumber( magnify_item ) ) {
            g.diameter = magnify_item->valuedouble;
            g.radius = g.diameter / 2.0;
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
#ifdef GETOPT_TEST
    showParameters( g, "post fromJSON\n" );
#endif
    return g;
}

void toJSON( Parameters g ) {
    cJSON *root = NULL;
    cJSON *params = NULL;
    cJSON *bounds = NULL;
    char *out;

    root = cJSON_CreateObject();

    cJSON_AddStringToObject( root, "name", "Mandelbrot" );
    cJSON_AddItemToObject( root, "params", params = cJSON_CreateObject() );
    cJSON_AddNumberToObject( params, "width", g.width );
    cJSON_AddNumberToObject( params, "height", g.height );
    cJSON_AddNumberToObject( params, "centerX", g.centerX );
    cJSON_AddNumberToObject( params, "centerY", g.centerY );
    cJSON_AddNumberToObject( params, "magnify", g.magnify );
    cJSON_AddItemToObject( params, "bounds", bounds = cJSON_CreateObject() );
    cJSON_AddNumberToObject( bounds, "top", -1.0 );
    cJSON_AddNumberToObject( bounds, "right", 1.0 );
    cJSON_AddNumberToObject( bounds, "bottom", 1.0 );
    cJSON_AddNumberToObject( bounds, "left", -2.0 );
    cJSON_AddNumberToObject( params, "maxIterations", g.maxiter );
    cJSON_AddNumberToObject( params, "version", 1.0 );

    out = cJSON_Print( root );
#ifdef GETOPT_TEST
    printf( "\n  Proposed %s…\n\n", g.json );
    printf( "%s\n", out );
#endif
    FILE *fp = fopen( g.json, "w+");
    if ( fp != NULL ) {
        fputs( out, fp );
        fclose( fp );
    }
    free( out );
    cJSON_Delete( root );
}

Parameters rawCl( int argc, char *argv[], Parameters p ) {
    Parameters g = p;
#ifdef GETOPT_TEST
    printf( "  rawCl()\n");
#endif
    if ( argc >= 3 && argc <= 7 ) {
        g.filename = argv[2];
        g = fromJSON( g );
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
        printf( "    or 7(..10) parameters:\n" );
        printf( "\n" );
        printf( "    center X parameter\n" );
        printf( "    center Y parameter\n" );
        printf( "    diameter parameter\n" );
        printf( "    iteration parameter\n" );
        printf( "    width parameter\n" );
        printf( "    height parameter\n" );
        printf( "    output filename\n" );
        printf( "\n" );
        printf( "    Additionally:\n" );
        printf( "\n" );
        printf( "    color parameter\n" );
        printf( "    tweak parameter\n" );
        printf( "    aa parameter\n" );
        exit(1);
    }
    return g;
}

void help( char c, char *Program, char *Version, char *Date ) {
    printf( "%s v%s dated %s\n", Program, Version, Date );
    if ( c == 'h' || c == '?' ) {
        printf( "\n  Options:\n\n" );
        printf( "  --aa           requires filename as an argument -a\n" );
        printf( "  --bourke       requires number as an argument -b\n" );
        printf( "  --color        requires number as an argument -r\n" );
        printf( "  --config       requires filename as an argument -c\n" );
        printf( "  --diameter     requires real as an argument   -d\n" );
        printf( "  --escape       requires real as an argument   -e\n" );
        printf( "  --file         requires filename as an argument -f\n" );
        printf( "  --height       requires number as an argument -l\n" );
        printf( "  --help         no argument                    -h\n" );
        printf( "  --iteration    requires number as an argument -i\n" );
        printf( "  --json         requires filename as an argument -j\n" );
        printf( "      may be prefixed with W: to write parameters\n" );
        printf( "  --kolor        requires RGB spec as an argument -k\n" );
        printf( "      allows up to %d RGB color specifications\n", NAMES_SIZE );
        printf( "      which may be 'named' colors or braced {..}\n" );
        printf( "  --magnify      requires real as an argument   -m\n" );
        printf( "  --next         argument is optional number    -n\n" );
        printf( "  --old          requires number as argument    -o\n" );
        printf( "  --palette      requires filename as an argument -p\n" );
        printf( "  --semidiameter requires number as an argument -s\n" );
        printf( "      this is an alias for radius\n" );
        printf( "  --tweak        requires number as an argument -t\n" );
        printf( "  --ultra        requires string in quotes as an argument -u\n");
        printf( "  --version      no argument                    -v\n" );
        printf( "  --width        requires number as an argument -w\n" );
        printf( "  --x_center     requires real as an argument   -x\n" );
        printf( "  --y_center     requires real as an argument   -y\n" );
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

#ifdef GETOPT_TEST
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
    p.escape = iniparser_getlongdouble( ini, "image:escape", 4.0);

    p.tweak = iniparser_getint( ini, "color:tweak", 0 );
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

void showParameters( Parameters p, char *s ) {
    int width = 46;
    char buf[128];
    int n;

    if ( s ) {
        printf( "\n  %s\n", s );
    }
    n = quadmath_snprintf (buf, sizeof buf, "%+-#*.20Qe", width, p.centerX );
    if ((size_t) n < sizeof buf)
        printf( "  p.centerX   = '%s'\n", buf );
    n = quadmath_snprintf (buf, sizeof buf, "%+-#*.20Qe", width, p.centerY );
    if ((size_t) n < sizeof buf)
        printf( "  p.centerY   = '%s'\n", buf );
    n = quadmath_snprintf (buf, sizeof buf, "%+-#*.20Qe", width, p.magnify );
    if ((size_t) n < sizeof buf)
        printf( "  p.magnify   = '%s'\n", buf );
    n = quadmath_snprintf (buf, sizeof buf, "%+-#*.20Qe", width, p.diameter );
    if ((size_t) n < sizeof buf)
        printf( "  p.diameter  = '%s'\n", buf );
    n = quadmath_snprintf (buf, sizeof buf, "%+-#*.20Qe", width, p.radius );
    if ((size_t) n < sizeof buf)
        printf( "  p.radius    = '%s'\n", buf );
    printf( "  p.escape    = '%.f'\n", p.escape );
    printf( "  p.maxiter   = '%d'\n", p.maxiter );
    printf( "  p.nMax      = '%d'\n", p.nMax );
    printf( "  p.width     = '%d'\n", p.width );
    printf( "  p.height    = '%d'\n", p.height );
    printf( "  p.filename  = '%s'\n", p.filename );
    printf( "  p.palname   = '%s'\n", p.palname );
    printf( "  p.config    = '%s'\n", p.config );
    printf( "  p.aa        = '%s'\n", p.aa );
    printf( "  p.json      = '%s'\n", p.json );
    printf( "  p.writeJSON = '%d'\n", p.writeJSON );
    for (int i = 0; i < p.nargc; ++i) {
        printf("  p.names[%d]  = '%s'\n", i, p.names[i] );
    }
    printf( "  p.next      = '%d'\n", p.next );
    printf( "  p.color     = '%d'\n", p.color );
    printf( "  p.tweak     = '%d'\n", p.tweak );
    printf( "  p.nargc     = '%d'\n", p.nargc );
    printf( "  p.bourke    = '%d'\n", p.bourke );
    printf( "  p.old       = '%d'\n", p.old );
}

Parameters zeroP( void ) {
    Parameters g;

    g.centerX = 0;
    g.centerY = 0;
    g.magnify = 0;
    g.diameter = 0;
    g.radius = 0;
    g.escape = 0;
    g.maxiter = 0;
    g.nMax = 0;
    g.width = 0;
    g.height = 0;
    g.filename = NULL;
    g.palname = NULL;
    g.config = NULL;
    g.aa = NULL;
    g.json = NULL;
    g.ultra = NULL;
    g.writeJSON = 0;
    for (int i = 0;i < NAMES_SIZE ;i++ ) {
        g.names[i] = NULL;
    }
    g.next = 0;
    g.color = 0;
    g.tweak = 0;
    g.nargc = 0;
    g.bourke = 0;
    g.old = 0;

    return g;
}
