// Copyright (c) 2025 Tara Keeling
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "main.h"

EntityClass::EntityClass( Vector2D _pos, TileClass* entityTile ) {
    assert( entityTile != nullptr );

    this->pos = _pos;
    this->tile = entityTile;
}

void EntityClass::draw( void ) {
    screen.putTile( *this->tile, this->pos.x, this->pos.y );
}

void EntityClass::setPosition( Vector2D _pos ) {
    this->pos = _pos;
}
