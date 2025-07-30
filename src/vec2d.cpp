// Copyright (c) 2025 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <math.h>
#include "main.h"

const Vector2D dirNorthwest( -1, -1 );
const Vector2D dirNorth( 0, -1 );
const Vector2D dirNortheast( 1, -1 );

const Vector2D dirWest( -1, 0 );
const Vector2D dirEast( 1, 0 );

const Vector2D dirSouthwest( -1, 1 );
const Vector2D dirSouth( 0, 1 );
const Vector2D dirSoutheast( 1, 1 );

int Vector2D::distance( Vector2D a ) {
    return sqrt(
        ( ( this->x * a.x ) * ( this->x * a.x ) ) + 
        ( ( this->y * a.y ) * ( this->y * a.y ) )
    );
}

int Vector2D::distanceBetween( Vector2D& a, Vector2D& b ) {
    return std::max( abs( a.x - b.x ), abs( a.y - b.y ) );
    //return abs( a.x - b.x ) + abs( a.y - b.y );
    //return a.distance( b );
}
