// Copyright (c) 2025 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <locale.h>
#include "main.h"

ScreenClass::ScreenClass( void ) {
    setlocale( LC_ALL, "en_US.UTF-8" );

    memset( colorPairTable, 0, sizeof( colorPairTable ) );

    initscr( );
    noecho( );
    curs_set( 0 );

    width = COLS;
    height = LINES;
    colorCnt = 1;

    setupColor( );
}

ScreenClass::~ScreenClass( void ) {
    endwin( );
}

void ScreenClass::setupColor( void ) {
    int fg = 0;
    int bg = 0;
    int i = 1;

    if ( ( hasColor = has_colors( ) ) ) {
        start_color( );

        for ( bg = 0; bg < 8; bg++ ) {
            for ( fg = 0; fg < 8; fg++ ) {
                init_pair( i, fg, bg );
                colorPairTable[ ( bg << 4 ) | fg ] = COLOR_PAIR( i );

                i++;
            }
        }
    }
}

void ScreenClass::update( void ) {
    refresh( );
}

void ScreenClass::moveTo( int x, int y ) {
    move( y, x );
}

void ScreenClass::putChar( int c ) {
    addch( c );
}

void ScreenClass::putChar( int x, int y, int c ) {
    this->moveTo( x, y );
    this->putChar( c );
}

void ScreenClass::putChar( int x, int y, int c, int attrib ) {
    attron( attrib );
        this->putChar( x, y, c );
    attroff( attrib );
}

int ScreenClass::getAttribForColor( int fg, int bg ) {
    int colorIdx = fg | ( bg << 4 );

    return colorPairTable[ colorIdx & 0xFF ];
}

void ScreenClass::putTile( TileClass& tile, int x, int y ) {
    this->putChar( 
        x, 
        y, 
        tile.getCh( ),
        tile.getAttrs( ) | 
        screen.getAttribForColor( 
            tile.getFg( ),
            tile.getBg( )
        )
    );
}

void ScreenClass::putTile( TileClass& tile, Vector2D pos ) {
    this->putTile( tile, pos.x, pos.y );
}

int ScreenClass::getWidth( void ) {
    return this->width;
}

int ScreenClass::getHeight( void ) {
    return this->height;
}

void ScreenClass::drawCellBoard( CellularClass& cellBoard ) {
    int cell = 0;
    int x = 0;
    int y = 0;

    assert( cellBoard.getWidth( ) <= this->getWidth( ) );
    assert( cellBoard.getHeight( ) <= this->getHeight( ) );

    for ( y = 0; y < cellBoard.getHeight( ); y++ ) {
        for ( x = 0; x < cellBoard.getWidth( ); x++ ) {
            cell = cellBoard.getCellAt( x, y );

            this->putChar(
                x, 
                y,
                ( cell == cellBoard.CELL_ALIVE ) ? '@' : ' '
            );
        }
    }
}
