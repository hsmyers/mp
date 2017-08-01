/**
 **  @file elapsed.c
 **  @author Hugh S. Myers
 **  @brief Routines to provide time information as mp executes.
 **  @date Mon Jul 24 16:09:35 2017
 **
 **  Description
 **
 **  @bug No known bugs.
 **/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include "elapsed.h"
#include "util.h"

void elapsed( int elapsedSeconds, long milleseconds ) {
    int totalSeconds = ( int ) elapsedSeconds;
    int seconds = ( totalSeconds % 60 );
    int minutes = ( totalSeconds % 3600 ) / 60;
    int hours = ( totalSeconds % 86400 ) / 3600;
    int days = ( totalSeconds % ( 86400 * 30 ) ) / 86400;
    printf( "elapsed time %d:%d:%d:%d:%06ld\n", days, hours, minutes, seconds, milleseconds );
}

int timeval_subtract( struct timeval *result, struct timeval *x, struct timeval *y ) {
    struct timeval xx = *x;
    struct timeval yy = *y;
    x = &xx;
    y = &yy;

    if ( x->tv_usec > 999999 ) {
        x->tv_sec += x->tv_usec / 1000000;
        x->tv_usec %= 1000000;
    }

    if ( y->tv_usec > 999999 ) {
        y->tv_sec += y->tv_usec / 1000000;
        y->tv_usec %= 1000000;
    }

    result->tv_sec = x->tv_sec - y->tv_sec;

    if ( ( result->tv_usec = x->tv_usec - y->tv_usec ) < 0 ) {
        result->tv_usec += 1000000;
        result->tv_sec--;       // borrow
    }

    return result->tv_sec < 0;
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
    char tzn[128];

    sprintf( buffer, "TZ=%s", tz );
    putenv( "TZ=" );
    tzset(  );
    if ( tzname[1] ) {
        str2abbr( tzn, sizeof(tzn), tzname[1] );
    } else {
        str2abbr( tzn, sizeof(tzn), tzname[0] );
    }
    nowtime = tv->tv_sec;
    nowtm = localtime( &nowtime );
    written = ( ssize_t ) strftime( buf, sz, "%d:%m:%Y %H:%M:%S", nowtm );
    int w = snprintf( buf, sz, "%s.%06ld %s", buf, tv->tv_usec, tzn );
    written = ( w > 0 ) ? written + w : -1;
    putenv( buffer );
    return written;
}
