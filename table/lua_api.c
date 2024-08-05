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

// image related functions

static Texture2D load_image(const char* filename) {
    return LoadTexture(filename);
}

static void draw_image(Texture2D *tex, const int x, const int y) {
    DrawTexture(*tex, x, y, WHITE);
}

static void unload_image(Texture2D *tex) {
    UnloadTexture(*tex);       
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

// image related functions

static int l_load_image(lua_State *L) {
    const char* filename = luaL_checkstring(L, 1);
    Texture2D *tex = (Texture2D*)lua_newuserdata(L, sizeof(Texture2D));
    *tex = load_image(filename);
    luaL_getmetatable(L, "Texture2D");
    lua_setmetatable(L, -2);
    return 1;
}

static int l_draw_image(lua_State *L) {
    Texture2D *tex = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3);
    draw_image(tex, x, y);
    return 0; 
}

static int l_unload_image(lua_State *L) {
    Texture2D *tex = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    unload_image(tex);
    return 0;
}

static int l_unload_image_gc(lua_State *L) {
    Texture2D *tex = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    if (tex->id != 0) {
        unload_image(tex);
    }
    return 0;
}

// Register Lua functions
//--------------------------------------------------------------

void register_lua_api(lua_State *L) {
    lua_register(L, "draw_text", l_draw_text);
    
    luaL_newmetatable(L, "Texture2D");
    lua_pushcfunction(L, l_draw_image);
    lua_setfield(L, -2, "draw");
    lua_pushcfunction(L, l_unload_image);
    lua_setfield(L, -2, "unload");
    lua_pushcfunction(L, l_unload_image_gc);
    lua_setfield(L, -2, "__gc");
    lua_pushvalue(L, -1);  // Duplicate the metatable
    lua_setfield(L, -2, "__index");    
    lua_pop(L, 1);

    lua_register(L, "load_image", l_load_image);
}