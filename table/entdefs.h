/*
Copyright (C) 2024 Lance Borden, Sariah Echols

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3.0
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.

*/

#include "component.h"

#ifndef ENTDEFS_H
#define ENTDEFS_H

typedef struct {
    component_t components[COMPONENT_COUNT];
} entity_t;

typedef struct {
    entity_t self;
} player_t;

typedef struct {
    entity_t self;
} npc_t;

typedef struct {
    entity_t self;
} spell_t;

typedef struct {
    entity_t self;
} environmental_t;

#endif