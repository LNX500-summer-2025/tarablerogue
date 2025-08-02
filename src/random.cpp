// Copyright (c) 2025 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <stdlib.h>
#include <time.h>
#include "main.h"

int Random::range( int min, int max ) {
    int range = max - min + 1;
    double r = 0.0;

    r = ( ( double ) rand( ) ) / ( ( double ) ( RAND_MAX ) + 1.0 );

    return min + ( int ) ( r * ( double ) range );
}

void Random::init( void ) {
    //sranddev( );
    srand( time( NULL ) );
}
