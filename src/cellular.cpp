// Copyright (c) 2025 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "main.h"

CellularClass::CellularClass( int width, int height ) {
    this->boardWidth = width;
    this->boardHeight = height;

    this->tempBoardState = new uint8_t[ width * height ];
    this->boardState = new uint8_t[ width * height ];

    assert( this->tempBoardState != nullptr );
    assert( this->boardState != nullptr );

    memset( this->boardState, CELL_DEAD, width * height );
}

CellularClass::~CellularClass( void ) {
    if ( this->tempBoardState )
        delete this->tempBoardState;

    if ( this->boardState )
        delete this->boardState;
}

int CellularClass::getCellAt( int x, int y ) {
    if ( x >= 0 && x < boardWidth && y >= 0 && y < boardHeight )
        return this->boardState[ x + ( y * boardWidth ) ];

    // Assume alive cell if reading beyond borders
    return 1;
}

void CellularClass::setCellAt( int x, int y, int state ) {
    // Do not attempt to set a cell beyond the memory bounds
    if ( x >= 0 && x < boardWidth && y >= 0 && y < boardHeight )
        this->boardState[ x + ( y * boardWidth ) ] = state;
}

int CellularClass::countNeighboursAt( int x, int y ) {
    int n, nw, ne = 0;
    int s, sw, se = 0;
    int w, e = 0;

    nw = this->getCellAt( x - 1, y - 1 );
    n = this->getCellAt( x, y - 1 );
    ne = this->getCellAt( x + 1, y - 1 );

    w = this->getCellAt( x - 1, y );
    e = this->getCellAt( x + 1, y );

    sw = this->getCellAt( x - 1, y + 1 );
    s = this->getCellAt( x, y + 1 );
    se = this->getCellAt( x + 1, y + 1 );

    return nw + n + ne + w + e + sw + s + se;
}

void CellularClass::reset( void ) {
    int state = 0;
    int randv = 0;
    int x = 0;
    int y = 0;

    for ( y = 0; y < this->boardHeight; y++ ) {
        for ( x = 0; x < this->boardWidth; x++ ) {
            randv = Random::range( 1, 100 );
            state = ( randv >= 50 ) ? CELL_ALIVE : CELL_DEAD;

            setCellAt( x, y, state );
        }
    }
}

int CellularClass::getWidth( void ) {
    return this->boardWidth;
}

int CellularClass::getHeight( void ) {
    return this->boardHeight;
}

const uint8_t* CellularClass::getBoardState( void ) {
    return this->boardState;
}

void CellularClass::runGeneration( int count ) {
    int state = 0;
    int x = 0;
    int y = 0;

    this->preGeneration( );
        while ( count-- ) {
            memset( this->tempBoardState, CellularClass::CELL_DEAD, this->boardWidth * this->boardHeight );

            for ( y = 0; y < this->boardHeight; y++ ) {
                for ( x = 0; x < this->boardWidth; x++ ) {
                    state = doesCellLiveThisGen( x, y );
                    this->tempBoardState[ x + ( y * this->boardWidth ) ] = state;
                }
            }

            memcpy( this->boardState, this->tempBoardState, this->boardWidth * this->boardHeight );
        }
    this->postGeneration( );
}

int CellularClass::doesCellLiveThisGen( int x, int y ) {
    int count = 0;
    int cell = 0;

    cell = getCellAt( x, y );
    count = countNeighboursAt( x, y );

    assert( cell == CELL_ALIVE || cell == CELL_DEAD );

    if ( cell == CELL_DEAD ) {
        if ( count >= 5 )
            return 1;
    } else {
        if ( count >= 4 )
            return 1;
    }

    return 0;
}

void CellularClass::preGeneration( void ) {
}

void CellularClass::postGeneration( void ) {
}

void CellularClass::drawLineH( int x, int y, int width, int state ) {
    for ( int i = 0; i < width; i++ )
        setCellAt( i + x, y, state );
}

void CellularClass::drawLineV( int x, int y, int height, int state ) {
    for ( int i = 0; i < height; i++ )
        setCellAt( x, i + y, state );
}

void CellularClass::fill( int x, int y, int width, int height, int state ) {
    for ( int i = 0; i < height; i++ )
        this->drawLineH( x, i + y, width, state );
}

void CellularGrass::preGeneration( void ) {
}

void CellularGrass::reset( void ) {
    int state = 0;
    int randv = 0;
    int x = 0;
    int y = 0;

    for ( y = 0; y < this->boardHeight; y++ ) {
        for ( x = 0; x < this->boardWidth; x++ ) {
            randv = Random::range( 1, 100 );
            state = ( randv >= 90 ) ? CELL_ALIVE : CELL_DEAD;

            setCellAt( x, y, state );
        }
    }
}

void CellularGrass::runGeneration( int count ) {
    // Do nothing; only random
}

void CellularBorder::preGeneration( void ) {
    int w = this->boardWidth - 10;
    int h = this->boardHeight - 10;

    // Make a big empty open space
    this->fill( ( this->boardWidth - w ) / 2, ( this->boardHeight - h ) / 2, w, h, CellularClass::CELL_DEAD );
}

void CellularBorder::postGeneration( void ) {
    this->drawLineH( 0, 0, this->boardWidth, CellularClass::CELL_ALIVE );
    this->drawLineH( 0, this->boardHeight - 1, this->boardWidth, CellularClass::CELL_ALIVE );
    
    this->drawLineV( 0, 0, this->boardHeight, CellularClass::CELL_ALIVE );
    this->drawLineV( this->boardWidth - 1, 0, this->boardHeight, CellularClass::CELL_ALIVE );
}

int CellularWater::doesCellLiveThisGen( int x, int y ) {
    int count = 0;
    int cell = 0;

    cell = getCellAt( x, y );
    count = countNeighboursAt( x, y );

    assert( cell == CELL_ALIVE || cell == CELL_DEAD );

    if ( cell == CELL_DEAD ) {
        if ( count >= 6 )
            return 1;
    } else {
        if ( count >= 4 )
            return 1;
    }

    return 0;
}

int CellularWater::getCellAt( int x, int y ) {
    if ( x >= 0 && x < boardWidth && y >= 0 && y < boardHeight )
        return this->boardState[ x + ( y * boardWidth ) ];

    // Assume dead cell if reading beyond borders
    return 0;
}
