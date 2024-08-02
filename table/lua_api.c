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

#include "raylib.h"
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

// C functions
//--------------------------------------------------------------

static void draw_text(const char* text, int x, int y) {
    DrawText(text, x, y, 20, DARKGRAY);
}

// Lua wrappers
//--------------------------------------------------------------

static int l_draw_text(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3);

    draw_text(text, x, y);

    return 0;
}

// Register Lua functions
//--------------------------------------------------------------

void register_lua_api(lua_State *L) {
    lua_register(L, "draw_text", l_draw_text);
}