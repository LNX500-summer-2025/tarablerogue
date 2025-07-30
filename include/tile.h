#ifndef _TILE_H_
#define _TILE_H_

#include "main.h"

class TileClass {
private:
    int isWalkable;
    int attrs;
    int priority;
    int fg;
    int bg;
    int ch;

public:
    TileClass( int _priority, int character, int _isWalkable, int fgColor, int bgColor, int extraAttrs = 0 );

    int getAttrs( void ) { return attrs; }
    int getPriority( void ) { return priority; }
    int getFg( void ) { return fg; }
    int getBg( void ) { return bg; }
    int getCh( void ) { return ch; }

    int getWalkable( void ) { return isWalkable; }
};

extern TileClass tileMountain;
extern TileClass tileEmpty;
extern TileClass tileGrassA;
extern TileClass tileGrassB;
extern TileClass tileWater;
extern TileClass tilePlayer;
extern TileClass tileDebug;
extern TileClass tileDebug2;
extern TileClass tileDebug3;

#endif
