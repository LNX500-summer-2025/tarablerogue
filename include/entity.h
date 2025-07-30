#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "main.h"

class EntityClass {
protected:
    Vector2D pos;

    TileClass* tile;
public:
    EntityClass( Vector2D _pos, TileClass* entityTile );

    void draw( void );
    void setPosition( Vector2D _pos );

    Vector2D getPosititon( void ) {
        return this->pos;
    }
};

class PlayerClass : public EntityClass {
public:
    PlayerClass( Vector2D _pos ) : EntityClass( _pos, &tilePlayer ) { }
};

#endif
