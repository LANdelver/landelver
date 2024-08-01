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

#include "lua_runtime.h"
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>

static void set_lua_path(lua_State *L) {
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "path");
    const char *current_path = lua_tostring(L, -1);
    lua_pop(L, 1);

    const char *new_path = "./scripts/?.lua;";
    lua_pushfstring(L, "%s%s", new_path, current_path);
    lua_setfield(L, -2, "path");
    lua_pop(L, 1); 
}


void lua_init(lua_State *L) {
    // before we can run lua scripts we need to append ./scripts to the path
    set_lua_path(L);

    if (luaL_dofile(L, "./scripts/world.lua") == LUA_OK) {
        lua_getglobal(L, "init"); // get the function on the stack
        if (lua_isfunction(L, -1)) {     

            lua_pcall(L, 0, 0, 0); // now call the function
        
        } else { 
            printf("[C] Error: didn't find a function on top of Lua stack\n");
        }
    } else {
        printf("[C] Error reading script\n");
        luaL_error(L, "Error: %s\n", lua_tostring(L, -1));
    }
}

void lua_update(lua_State *L) {
    if (luaL_dofile(L, "./scripts/world.lua") == LUA_OK) {
        lua_getglobal(L, "update"); // get the function on the stack
        if (lua_isfunction(L, -1)) {     

            lua_pcall(L, 0, 0, 0); // now call the function
        
        } else { 
            printf("[C] Error: didn't find a function on top of Lua stack\n");
        }
    } else {
        printf("[C] Error reading script\n");
        luaL_error(L, "Error: %s\n", lua_tostring(L, -1));
    }
}

void lua_draw(lua_State *L) {
    if (luaL_dofile(L, "./scripts/world.lua") == LUA_OK) {
        lua_getglobal(L, "draw"); // get the function on the stack
        if (lua_isfunction(L, -1)) {     

            lua_pcall(L, 0, 0, 0); // now call the function
        
        } else { 
            printf("[C] Error: didn't find a function on top of Lua stack\n");
        }
    } else {
        printf("[C] Error reading script\n");
        luaL_error(L, "Error: %s\n", lua_tostring(L, -1));
    }
}