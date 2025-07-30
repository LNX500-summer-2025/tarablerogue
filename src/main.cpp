#include "main.h"

ScreenClass screen;

#if 0
int main( void ) {
    std::vector< AStarNode > openList;
    AStarNode rootNode( Vector2D( 0, 0 ) );

    openList.push_back( rootNode );
    openList.push_back( AStarNode( Vector2D( ), 1 ) );
    openList.push_back( AStarNode( Vector2D( ), 3 ) );
    openList.push_back( AStarNode( Vector2D( ), 2 ) );
    openList.push_back( AStarNode( Vector2D( ), 5 ) );

    std::sort( openList.begin( ), openList.end( ) );

    for ( AStarNode& i : openList ) {
        printw( "f: %d\n", i.f );
    }

    printf( "\n\n\n" );

    AStarNode low = openList.back( );
    openList.pop_back( );

    printw( "low f: %d\n", low.f );

    refresh( );
    getch( );

    endwin( );
    return 0;
}
#endif

#if 1
void test( void ) {
    CellularClass* water = NULL;

    water = new CellularWater( screen.getWidth( ), screen.getHeight( ) );

    if ( water != nullptr ) {
        water->reset( );
        water->runGeneration( 5 );

        screen.drawCellBoard( *water );
        screen.update( );

        getch( );
    }
}

PlayerClass player( Vector2D( 0, 0 ) );

int main( void ) {
    CellularClass* border = NULL;
    CellularClass* grass = NULL;
    CellularClass* water = NULL;

    Random::init( );

    //test( );

    MapClass* map = new MapClass( screen.getWidth( ), screen.getHeight( ) );

    if ( ( border = new CellularBorder( screen.getWidth( ), screen.getHeight( ) ) ) != nullptr ) {
        border->reset( );
        border->runGeneration( 5 );
    }

    water = new CellularWater( screen.getWidth( ), screen.getHeight( ) );

    if ( water != nullptr ) {
        water->reset( );
        water->runGeneration( 5 );
    }

    if ( ( grass = new CellularGrass( screen.getWidth( ), screen.getHeight( ) ) ) != nullptr ) {
        grass->reset( );
        grass->runGeneration( 1 );

        map->copyFromCellular( *grass, &tileGrassA, &tileGrassB );
        map->addFromCellular( *border, &tileMountain );
        map->addFromCellular( *water, &tileWater );
    
        map->draw( );
        getch( );
        
        Vector2D rng;
        Vector2D goal;

        map->getRandomWalkablePoint( goal, 5 );

        if ( map->getRandomWalkablePoint( rng, 5 ) == 0 ) {
            player.setPosition( rng );
        }

        //player.draw( );

        screen.putTile( tilePlayer, rng );
        screen.putTile( tilePlayer, goal );

        screen.update( );

        getch( );

        map->isThereAPathBetween( rng, goal );

        // std::list< Vector2D > n = map->getWalkableNeighboursAt( player.getPosititon( ) );

        // for ( Vector2D i : n ) {
        //     screen.putTile( tileDebug, i );
        // }

        screen.update( );

        getch( );

        delete grass;
        delete border;
    }

    //screen.putTile( tileMountain, 1, 1 );
    screen.update( );

    return 0;
}
#endif
