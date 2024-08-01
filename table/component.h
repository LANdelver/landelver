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

#ifndef COMPONENT_H
#define COMPONENT_H

typedef enum {
    CONDITION_COMPONENT,
    TOKEN_COMPONENT,
    COMPONENT_COUNT
} component_types_t;

typedef struct {
    void (* init) ();
    void (* update) ();
    void (* draw) ();
    void (* remove) ();
} component_t;

#endif