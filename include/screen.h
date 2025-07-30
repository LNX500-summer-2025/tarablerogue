#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "main.h"
#include "tile.h"
#include "cellular.h"

class ScreenClass {
private:
    int colorPairTable[ 256 ];

    int width;
    int height;

    int hasColor;

    int colorCnt;

    void setupColor( void );
public:
    ScreenClass( void );
    ~ScreenClass( void );

    void update( void );

    void moveTo( int x, int y );
    
    void putChar( int c );
    void putChar( int x, int y, int c );
    void putChar( int x, int y, int c, int attrib );

    int getAttribForColor( int fg, int bg );

    void putTile( TileClass& tile, int x, int y );
    void putTile( TileClass& tile, Vector2D pos );

    int getWidth( void );
    int getHeight( void );

    void drawCellBoard( CellularClass& cellBoard );
};

#endif
