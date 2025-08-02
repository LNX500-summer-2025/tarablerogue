// Copyright (c) 2025 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "main.h"

MapClass::MapClass( int width, int height ) {
    this->mapWidth = width;
    this->mapHeight = height;

    this->walkableNeighbours = new std::list< Vector2D >[ width * height ];
    this->tileMap = new TileClass*[ width * height ];

    assert( this->walkableNeighbours );
    assert( this->tileMap != nullptr );

    this->clearNeighbours( );
}

MapClass::~MapClass( void ) {
    if ( this->tileMap )
        delete this->tileMap;
}

void MapClass::clearNeighbours( void ) {
    for ( int i = 0; i < this->mapWidth * this->mapHeight; i++ )
        this->walkableNeighbours[ i ].clear( );
}

void MapClass::updateNeighbours( void ) {
    int x = 0;
    int y = 0;

    this->clearNeighbours( );

    for ( y = 0; y < this->mapHeight; y++ ) {
        for ( x = 0; x < this->mapWidth; x++ ) {
            this->walkableNeighbours[ x + ( y * this->mapWidth ) ] = this->getWalkableNeighboursAt( Vector2D( x, y ) );
        }
    }
}

void MapClass::clear( TileClass* tile ) {
    int x = 0;
    int y = 0;

    assert( tile != nullptr );

    for ( y = 0; y < this->mapHeight; y++ ) {
        for ( x = 0; x < this->mapWidth; x++ ) {
            this->tileMap[ x + ( y * this->mapWidth ) ] = tile;
        }
    }
}

void MapClass::copyFromCellular( CellularClass& cellMap, TileClass* aliveTile, TileClass* deadTile ) {
    int cell = 0;
    int x = 0;
    int y = 0;

    assert( aliveTile != nullptr );
    assert( deadTile != nullptr );

    assert( cellMap.getWidth( ) == screen.getWidth( ) );
    assert( cellMap.getHeight( ) == screen.getHeight( ) );

    for ( y = 0; y < cellMap.getHeight( ); y++ ) {
        for ( x = 0; x < cellMap.getWidth( ); x++ ) {
            cell = cellMap.getCellAt( x, y );
            this->tileMap[ x + ( y * this->mapWidth ) ] = ( cell == CellularClass::CELL_ALIVE ) ? aliveTile : deadTile;
        }
    }
}

void MapClass::addFromCellular( CellularClass& cellMap, TileClass* aliveTile ) {
    TileClass* tile = nullptr;
    int x = 0;
    int y = 0;

    for ( y = 0; y < this->mapHeight; y++ ) {
        for ( x = 0; x < this->mapWidth; x++ ) {
            tile = this->tileMap[ x + ( y * this->mapWidth ) ];

            if ( aliveTile->getPriority( ) < tile->getPriority( ) ) {
                if ( cellMap.getCellAt( x, y ) == CellularClass::CELL_ALIVE )
                    this->tileMap[ x + ( y * this->mapWidth ) ] = aliveTile;
            }
        }
    }

    this->clearNeighbours( );
    this->updateNeighbours( );
}

void MapClass::draw( void ) {
    TileClass* tile = nullptr;
    int x = 0;
    int y = 0;

    for ( y = 0; y < this->mapHeight; y++ ) {
        for ( x = 0; x < this->mapWidth; x++ ) {
            tile = this->tileMap[ x + ( y * this->mapWidth ) ];

            screen.putTile( *tile, x, y );
        }
    }
}

/// @brief Attempts to find a random walkable point on the map
/// @param outPoint Vector to receive point if successfull
/// @param tries How many times to try to find a random walkable point
/// @return 0 If point was found; -1 if number of tries ran out and no point found
int MapClass::getRandomWalkablePoint( Vector2D& outPoint, int tries ) {
    Vector2D test;

    while ( tries-- ) {
        test.x = Random::range( 0, this->mapWidth - 1 );
        test.y = Random::range( 0, this->mapHeight - 1 );

        if ( this->isPointWalkable( test ) == 1 ) {
            outPoint = test;
            return 0;
        }
    }

    return -1;
}

int MapClass::isPointWalkable( Vector2D p ) {
    //assert( this->isPointInMap( p ) == 1 );

    if ( this->isPointInMap( p ) == 1 )
        return this->getTileAt( p )->getWalkable( );

    return 0;
}

int MapClass::isPointInMap( Vector2D p ) {
    return (
        p.x >= 0 &&
        p.x < this->mapWidth &&
        p.y >= 0 &&
        p.y < this->mapHeight
    ) ? 1 : 0;
}

TileClass* MapClass::getTileAt( Vector2D p ) {
    if ( this->isPointInMap( p ) == 1 ) {
        assert( this->tileMap[ p.x + ( p.y * this->mapWidth ) ] != nullptr );
        return this->tileMap[ p.x + ( p.y * this->mapWidth ) ];
    }

    return NULL;
}

bool lowestF( const AStarNode* a, const AStarNode* b ) {
    return a->f < b->f;
}

std::vector< AStarNode* >::iterator findNodeWithin( Vector2D& pos, std::vector< AStarNode* >& vec ) {
    for ( std::vector< AStarNode* >::iterator i = vec.begin( ); i != vec.end( ); i++ ) {
        if ( ( *i )->pos == pos )
            return i;
    }

    return vec.end( );
}

std::vector< AStarNode >::iterator findNodeWithin2( Vector2D& pos, std::vector< AStarNode >& vec ) {
    for ( std::vector< AStarNode >::iterator i = vec.begin( ); i != vec.end( ); i++ ) {
        if ( ( *i ).pos == pos )
            return i;
    }

    return vec.end( );
}

std::vector< Vector2D > MapClass::getAPathBetween( Vector2D a, Vector2D b ) {
    // F is the total cost of the node.
    // G is the distance between the current node and the start node.
    // H is the heuristic — estimated distance from the current node to the end node.
    std::vector< AStarNode* > openList;
    std::vector< AStarNode* > closedList;
    std::vector< Vector2D > returnPath;
    AStarNode* curNode = nullptr;
    AStarNode* childNode = nullptr;
    bool found = false;

    openList.push_back( new AStarNode( a, 0, 0, Vector2D::distanceBetween( a, b ) ) );

    while ( ! openList.empty( ) ) {
        std::sort( openList.begin( ), openList.end( ), lowestF );

        curNode = openList.front( );
        openList.erase( openList.begin( ) );
        closedList.push_back( curNode );

        //screen.putTile( tileDebug, curNode->pos );
        //screen.update( );

        if ( curNode->pos == b ) {
            // for ( AStarNode* n = curNode->parent; n != nullptr; n = n->parent ) {
            //     screen.putTile( tileDebug2, n->pos );
            //     screen.update( );
            // }

            for ( AStarNode* n = curNode->parent; n != nullptr; n = n->parent ) {
                returnPath.push_back( n->pos );
            }

            break;
        }

        for ( Vector2D i : this->walkableNeighbours[ curNode->pos.x + ( curNode->pos.y * this->mapWidth ) ] ) {
            std::vector< AStarNode* >::iterator ol;

            childNode = new AStarNode( i, 0, 0, 0, curNode );
            childNode->h = Vector2D::distanceBetween( i, b );
            childNode->g = curNode->g;
            childNode->f = childNode->g + childNode->h;

            if ( ( ol = findNodeWithin( i, openList ) ) != openList.end( ) ) {
                if ( ( *ol )->f <= childNode->f ) {
                    delete childNode;
                    continue;
                }
            }

            if ( ( ol = findNodeWithin( i, closedList ) ) != closedList.end( ) ) {
                if ( ( *ol )->f <= childNode->f ) {
                    delete childNode;
                    continue;        
                }       
            }

            if ( ( ol = findNodeWithin( i, openList ) ) != openList.end( ) )
                openList.erase( ol );

            if ( ( ol = findNodeWithin( i, closedList ) ) != closedList.end( ) )
                closedList.erase( ol );

            openList.push_back( childNode );
        }
    }

    return returnPath;
}

std::list< Vector2D > MapClass::getWalkableNeighboursAt( Vector2D point ) {
    std::list< Vector2D > neighbours;

    if ( this->isPointWalkable( point + dirNorthwest ) ) neighbours.push_back( point + dirNorthwest );
    if ( this->isPointWalkable( point + dirNorth ) ) neighbours.push_back( point + dirNorth );
    if ( this->isPointWalkable( point + dirNortheast ) ) neighbours.push_back( point + dirNortheast );

    if ( this->isPointWalkable( point + dirWest ) ) neighbours.push_back( point + dirWest );
    if ( this->isPointWalkable( point + dirEast ) ) neighbours.push_back( point + dirEast );

    if ( this->isPointWalkable( point + dirSouthwest ) ) neighbours.push_back( point + dirSouthwest );
    if ( this->isPointWalkable( point + dirSouth ) ) neighbours.push_back( point + dirSouth );
    if ( this->isPointWalkable( point + dirSoutheast ) ) neighbours.push_back( point + dirSoutheast );

    return neighbours;
}

