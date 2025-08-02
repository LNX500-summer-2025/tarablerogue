// Copyright (c) 2025 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "main.h"

TileClass::TileClass( int _priority, int character, int _isWalkable, int fgColor, int bgColor, int extraAttrs ) {
        this->isWalkable = _isWalkable;
        this->priority = _priority;
        
        this->fg = fgColor;
        this->bg = bgColor;
        this->ch = character;
        this->attrs = extraAttrs;
    }

TileClass tileMountain( 0, '^', 0, COLOR_BLACK, COLOR_WHITE );
TileClass tileEmpty( 10, ' ', 1, COLOR_BLACK, COLOR_BLACK );
TileClass tileGrassA( 9, '.', 1, COLOR_YELLOW, COLOR_GREEN, 0 );
TileClass tileGrassB( 9, ',', 1, COLOR_GREEN, COLOR_GREEN, 0 );
TileClass tileWater( 1, '~', 0, COLOR_CYAN, COLOR_BLUE, 0 );
TileClass tilePlayer( 0, '@', 0, COLOR_CYAN, COLOR_BLACK, A_BOLD );
TileClass tileDebug( 10, 'X', 1, COLOR_MAGENTA, COLOR_BLACK, A_BOLD );
TileClass tileDebug2( 10, 'Y', 1, COLOR_YELLOW, COLOR_BLACK, A_BOLD );
TileClass tileDebug3( 10, 'D', 1, COLOR_GREEN, COLOR_BLACK, A_BOLD );
TileClass tileGoal( 8, 'G', 1, COLOR_RED, COLOR_BLACK, A_BOLD | A_BLINK );

