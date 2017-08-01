//
// elapsed.c
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "elapsed.h"

void elapsed( int elapsedSeconds, long milleseconds ) {
    int totalSeconds = ( int ) elapsedSeconds;
    int seconds = ( totalSeconds % 60 );
    int minutes = ( totalSeconds % 3600 ) / 60;
    int hours = ( totalSeconds % 86400 ) / 3600;
    int days = ( totalSeconds % ( 86400 * 30 ) ) / 86400;
    printf( "elapsed time %d:%d:%d:%d:%06ld\n", days, hours, minutes, seconds, milleseconds );
}

int timeval_subtract( struct timeval *result, struct timeval *t2, struct timeval *t1 ) {
    long int diff = ( t2->tv_usec + 1000000 * t2->tv_sec ) - ( t1->tv_usec + 1000000 * t1->tv_sec );

    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;

    return ( diff < 0 );
}

void timeval_print( struct timeval *tv ) {
    char buffer[128];

    format_timeval( tv, buffer, 128 );
    printf( "%s\n", buffer );
}

ssize_t format_timeval( struct timeval *tv, char *buf, size_t sz ) {
    ssize_t written = -1;
    time_t nowtime;
    struct tm *nowtm;
    char *tz = getenv( "TZ" );
    char buffer[256];

    sprintf( buffer, "TZ=%s", tz );
    putenv( "TZ=MST7MDT" );
    tzset();
    nowtime = tv->tv_sec;
    nowtm = localtime( &nowtime );
    written = ( ssize_t ) strftime( buf, sz, "%d:%m:%Y %H:%M:%S", nowtm );
    int w = snprintf( buf, sz, "%s.%06ld %s", buf, tv->tv_usec, tzname[1] );
    written = ( w > 0 ) ? written + w : -1;
    putenv( buffer );
    return written;
}
