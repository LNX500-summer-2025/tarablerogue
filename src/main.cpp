#include "main.h"

int generateLevel( void );
bool endScreen( void );

MapClass* level = NULL;
ScreenClass screen;

int generateLevel( void ) {
    CellularClass* border = NULL;
    CellularClass* grass = NULL;
    CellularClass* water = NULL;

    if ( ( level = new MapClass( screen.getWidth( ), screen.getHeight( ) ) ) == nullptr )
        return -1;

    border = new CellularBorder( screen.getWidth( ), screen.getHeight( ) );
    water = new CellularWater( screen.getWidth( ), screen.getHeight( ) );
    grass = new CellularGrass( screen.getWidth( ), screen.getHeight( ) );

    if ( ! border || ! water || ! grass ) {
        if ( border )
            delete border;

        if ( water )
            delete water;

        if ( grass )
            delete grass;

        return -1;
    }

    border->reset( );
    border->runGeneration( 5 );

    water->reset( );
    water->runGeneration( 5 );

    grass->reset( );
    grass->runGeneration( 1 );

    level->copyFromCellular( *grass, &tileGrassA, &tileGrassB );
    level->addFromCellular( *border, &tileMountain );
    level->addFromCellular( *water, &tileWater );

    delete border;
    delete water;
    delete grass;

    return 0;
}

bool endScreen( void ) {
    int yellow = screen.getAttribForColor( COLOR_YELLOW, COLOR_BLACK ) | A_BOLD;

    clear( );

    attron( yellow );
        mvprintw( ( LINES / 2 ) - 1, ( COLS / 2 ) - 22, "YOU'RE ARE AN WINNER!" );
    attroff( yellow );

    mvprintw( ( LINES / 2 ), ( COLS / 2 ) - 33, "PRESS START TO PLAY AGAIN OR SELECT TO EXIT" );

    return ( getch( ) == 'q' ) ? false : true;
}

int main( void ) {
    Vector2D newPlayerPos;
    Vector2D playerPos;
    Vector2D goalPos;
    bool run = true;
    bool goodMap = false;
    bool gameLoop = true;
    int c = 0;

    Random::init( );

    endScreen( );

    while ( run ) {
        do {
            if ( generateLevel( ) == 0 ) {
                level->getRandomWalkablePoint( playerPos, 10 );
                level->getRandomWalkablePoint( goalPos, 10 );

                goodMap = ( level->getAPathBetween( playerPos, goalPos ) ).empty( ) ? false : true;

                level->draw( );
                screen.update( );
            }
        } while ( goodMap == false );

        gameLoop = true;

        while ( gameLoop ) {
            level->draw( );

            screen.putTile( tilePlayer, playerPos );
            screen.putTile( tileGoal, goalPos );

            screen.update( );

            c = getch( );

            switch ( c ) {
                case 'w':
                case 'W': {
                    newPlayerPos = playerPos + Vector2D( 0, -1 );
                    break;
                }
                case 'a':
                case 'A': {
                    newPlayerPos = playerPos + Vector2D( -1, 0 );
                    break;
                }
                case 's':
                case 'S': {
                    newPlayerPos = playerPos + Vector2D( 0, 1 );
                    break;
                }
                case 'd':
                case 'D': {
                    newPlayerPos = playerPos + Vector2D( 1, 0 );
                    break;
                }
                case 'q':
                case 'Q': {
                    gameLoop = false;
                    run = false;

                    break;
                }
            };

            if ( level->isPointWalkable( newPlayerPos ) )
                playerPos = newPlayerPos;

            if ( playerPos == goalPos ) {
                if ( endScreen( ) == false )
                    run = false;

                gameLoop = false;
            }
        }
    }

    return 0;
}
