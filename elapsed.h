#ifndef ELAPSED_H_   /* Include guard */
#define ELAPSED_H_

void elapsed( int elapsedSeconds, long milleseconds );
int timeval_subtract( struct timeval *result, struct timeval *t2, struct timeval *t1 );
void timeval_print( struct timeval *tv );
ssize_t format_timeval( struct timeval *tv, char *buf, size_t sz );

#endif // ELAPSED_H_