#ifndef _CELLULAR_H_
#define _CELLULAR_H_

#include "main.h"

class CellularClass {
protected:
    int boardWidth;
    int boardHeight;

    uint8_t* tempBoardState;
    uint8_t* boardState;

    virtual int doesCellLiveThisGen( int x, int y );

public:
    static const int CELL_ALIVE = 1;
    static const int CELL_DEAD = 0;

    CellularClass( int width, int height );
    ~CellularClass( void );

    virtual int getCellAt( int x, int y );
    virtual void setCellAt( int x, int y, int state );
    
    virtual int countNeighboursAt( int x, int y );

    virtual void reset( void );

    virtual void preGeneration( void );
    virtual void runGeneration( int count );
    virtual void postGeneration( void );

    int getWidth( void );
    int getHeight( void );

    const uint8_t* getBoardState( void );

    void drawLineH( int x, int y, int width, int state );
    void drawLineV( int x, int y, int height, int state );
    void fill( int x, int y, int width, int height, int state );
};

class CellularGrass : public CellularClass {
public:
    void preGeneration( void );
    void reset( void );
    void runGeneration( int count );

    CellularGrass( int width, int height ) : CellularClass( width, height ) { }
};

class CellularBorder : public CellularClass {
public:
    void preGeneration( void );
    void postGeneration( void );

    CellularBorder( int width, int height ) : CellularClass( width, height ) { }
};

class CellularWater : public CellularClass {
private:
    virtual int doesCellLiveThisGen( int x, int y );
public:
    CellularWater( int width, int height ) : CellularClass( width, height ) { }

    int getCellAt( int x, int y );
};

#endif
