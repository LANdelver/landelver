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

#include "event.h"

// singleton instance of the event system
event_system_t g_combat_manager;

/*
====================
add_event_handler

assign an event type to
a given handler function
====================
*/
void add_event_handler(event_type_t type, event_handler_t handler) {
    g_combat_manager.handlers[type] = handler;
}

/*
====================
dispatch_event

send out an event for
the combat manager to 
handle
====================
*/
void dispatch_event(event_t *event) {
    g_combat_manager.handlers[event->type](event);
}

