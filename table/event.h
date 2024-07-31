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

#ifndef EVENT_H
#define EVENT_H

typedef enum {
    EVENT_TYPE_DEMO,
    // etc...
    EVENT_TYPE_COUNT
} event_type_t;

typedef struct {
    event_type_t type;
    void *data;
} event_t;

typedef void (*event_handler_t)(event_t *event);

typedef struct {
    event_handler_t handlers[EVENT_TYPE_COUNT];
} event_system_t;

extern event_system_t g_combat_manager;

void add_event_handler(event_type_t type, event_handler_t handler);
void dispatch_event(event_t *event);

#endif