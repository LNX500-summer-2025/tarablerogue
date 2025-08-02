#ifndef _MAP_H_
#define _MAP_H_

#include "main.h"
#include "tile.h"

#include <list>
#include <vector>

#include <queue>
#include <set>

#include <set>
#include <unordered_set>
#include <unordered_map>
#include <queue>

class BFSNode {
private:

public:
    BFSNode* parent;
    Vector2D pos;

    BFSNode( Vector2D _pos, BFSNode* _parent = nullptr ) {
        this->parent = _parent;
        this->pos = _pos;
    }

    BFSNode( void ) : BFSNode( Vector2D( ) ) { }

    Vector2D getPosition( void ) {
        return this->pos;
    }

    operator Vector2D( void ) {
        return this->pos;
    }

    bool operator ==( const BFSNode& other ) const {
        return this->pos == other.pos;
    }
};

class AStarNode {
public:
    int f;
    int g;
    int h;

    AStarNode* parent;
    Vector2D pos;

    AStarNode( Vector2D _pos, int _f = 0, int _g = 0, int _h = 0, AStarNode* _parent = nullptr ) {
        this->parent = _parent;
        this->pos = _pos;

        this->f = _f;
        this->g = _g;
        this->h = _h;
    }

    AStarNode( void ) : AStarNode( Vector2D( 0, 0 ) ) { }

    const int operator <( const AStarNode& other ) const {
        return this->f < other.f;
    }

    const bool operator ==( const AStarNode& other ) const {
        return this->pos == other.pos;
    }
};

class MapClass {
private:
    std::list< Vector2D >* walkableNeighbours;

    int mapWidth;
    int mapHeight;

    TileClass** tileMap;

    void clearNeighbours( void );
    void updateNeighbours( void );
public:
    MapClass( int width, int height );
    ~MapClass( void );

    void clear( TileClass* tile = &tileEmpty );

    void copyFromCellular( CellularClass& cellMap, TileClass* aliveTile, TileClass* deadTile );
    void addFromCellular( CellularClass& cellMap, TileClass* aliveTile );

    void draw( void );

    //int getRandomWalkableXY( int* outX, int* outY, int tries );

    int getRandomWalkablePoint( Vector2D& outPoint, int tries );

    int isPointWalkable( Vector2D p );
    int isPointInMap( Vector2D p );

    TileClass* getTileAt( Vector2D p );

    std::vector< Vector2D > getAPathBetween( Vector2D a, Vector2D B );

    std::list< Vector2D > getWalkableNeighboursAt( Vector2D point );
    //std::list< BFSNode > getWalkableNodesAt( BFSNode& parent );
};

#endif
