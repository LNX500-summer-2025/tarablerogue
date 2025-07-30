#ifndef _VEC2D_H_
#define _VEC2D_H_

class Vector2D {
public:
    int x;
    int y;

    Vector2D( void ) : Vector2D( 0, 0 ) { }

    Vector2D( int _x, int _y ) {
        this->x = _x;
        this->y = _y;
    }

    Vector2D operator +( Vector2D a ) {
        return Vector2D( this->x + a.x, this->y + a.y );
    }

    Vector2D operator *( Vector2D a ) {
        return Vector2D( this->x * a.x, this->y * a.y );
    }

    bool operator ==( const Vector2D& point ) const {
        return ( point.x == this->x ) && ( point.y == this->y );
    }

    int distance( Vector2D a );

    static int distanceBetween( Vector2D& a, Vector2D& b );
};

extern const Vector2D dirNorthwest;
extern const Vector2D dirNorth;
extern const Vector2D dirNortheast;

extern const Vector2D dirWest;
extern const Vector2D dirEast;

extern const Vector2D dirSouthwest;
extern const Vector2D dirSouth;
extern const Vector2D dirSoutheast;

#endif
