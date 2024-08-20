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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "character.h"

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

// character json handling

static char* json_file_to_string(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("File opening failed");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(length + 1);
    if (content) {
        fread(content, 1, length, file);
        content[length] = '\0';  // Null-terminate the string
    }

    fclose(file);
    return content;
}

static character_t get_character_from_json(const char* filename) {
    char *content = json_file_to_string(filename);
    character_t character = {0};  // Initialize the struct to avoid garbage values
    if (content == NULL) {
        return character;
    }

    cJSON *json = cJSON_Parse(content);
    if (json == NULL) {
        printf("Error parsing JSON\n");
        free(content);
        return character;
    }

    // read the data from the file into json field structs
    cJSON *name = cJSON_GetObjectItemCaseSensitive(json, "name");
    cJSON *race = cJSON_GetObjectItemCaseSensitive(json, "race");
    cJSON *classname = cJSON_GetObjectItemCaseSensitive(json, "class");
    cJSON *level = cJSON_GetObjectItemCaseSensitive(json, "level");

    cJSON *ability_scores = cJSON_GetObjectItemCaseSensitive(json, "ability_scores");
    cJSON *str_score = cJSON_GetObjectItemCaseSensitive(ability_scores, "strength");
    cJSON *dex_score = cJSON_GetObjectItemCaseSensitive(ability_scores, "dexterity");
    cJSON *con_score = cJSON_GetObjectItemCaseSensitive(ability_scores, "constitution");
    cJSON *int_score = cJSON_GetObjectItemCaseSensitive(ability_scores, "intelligence");
    cJSON *wis_score = cJSON_GetObjectItemCaseSensitive(ability_scores, "wisdom");
    cJSON *cha_score = cJSON_GetObjectItemCaseSensitive(ability_scores, "charisma");

    cJSON *saving_throws = cJSON_GetObjectItemCaseSensitive(json, "saving_throws");
    cJSON *str_save = cJSON_GetObjectItemCaseSensitive(saving_throws, "strength");
    cJSON *dex_save = cJSON_GetObjectItemCaseSensitive(saving_throws, "dexterity");
    cJSON *con_save = cJSON_GetObjectItemCaseSensitive(saving_throws, "constitution");
    cJSON *int_save = cJSON_GetObjectItemCaseSensitive(saving_throws, "intelligence");
    cJSON *wis_save = cJSON_GetObjectItemCaseSensitive(saving_throws, "wisdom");
    cJSON *cha_save = cJSON_GetObjectItemCaseSensitive(saving_throws, "charisma");

    cJSON *stats = cJSON_GetObjectItemCaseSensitive(json, "stats");
    cJSON *speed = cJSON_GetObjectItemCaseSensitive(stats, "speed");
    cJSON *ac = cJSON_GetObjectItemCaseSensitive(stats, "ac");
    cJSON *hp = cJSON_GetObjectItemCaseSensitive(stats, "hp");

    cJSON *weapons = cJSON_GetObjectItemCaseSensitive(json, "weapons");
    cJSON *spells = cJSON_GetObjectItemCaseSensitive(json, "spells");
    cJSON *proficiencies = cJSON_GetObjectItemCaseSensitive(json, "proficiencies");

    // Add the fields into the struct (copy strings)
    character.name = name && cJSON_IsString(name) ? strdup(name->valuestring) : NULL;
    character.race = race && cJSON_IsString(race) ? strdup(race->valuestring) : NULL;
    character.classname = classname && cJSON_IsString(classname) ? strdup(classname->valuestring) : NULL;
    character.level = level ? level->valueint : 0;
    
    character.ability_scores.strength = str_score ? str_score->valueint : 0;
    character.ability_scores.dexterity = dex_score ? dex_score->valueint : 0;
    character.ability_scores.constitution = con_score ? con_score->valueint : 0;
    character.ability_scores.intelligence = int_score ? int_score->valueint : 0;
    character.ability_scores.wisdom = wis_score ? wis_score->valueint : 0;
    character.ability_scores.charisma = cha_score ? cha_score->valueint : 0;

    character.saving_throws.strength = str_save ? str_save->valueint : 0;
    character.saving_throws.dexterity = dex_save ? dex_save->valueint : 0;
    character.saving_throws.constitution = con_save ? con_save->valueint : 0;
    character.saving_throws.intelligence = int_save ? int_save->valueint : 0;
    character.saving_throws.wisdom = wis_save ? wis_save->valueint : 0;
    character.saving_throws.charisma = cha_save ? cha_save->valueint : 0;

    character.speed = speed ? speed->valueint : 0;
    character.ac = ac ? ac->valueint : 0;
    character.hp = hp ? hp->valueint : 0;

    character.weapons = new_vector();
    character.spells = new_vector();
    character.proficiencies = new_vector();

    int weapon_count = cJSON_GetArraySize(weapons);
    for (int i = 0; i < weapon_count; i++) {
        cJSON *weapon = cJSON_GetArrayItem(weapons, i);
        push_back(&character.weapons, weapon->valuestring ? strdup(weapon->valuestring) : NULL);
    }
    
    int spell_count = cJSON_GetArraySize(spells);
    for (int i = 0; i < spell_count; i++) {
        cJSON *spell = cJSON_GetArrayItem(spells, i);
        push_back(&character.spells, spell->valuestring ? strdup(spell->valuestring) : NULL);
    }
    
    int proficiencies_count = cJSON_GetArraySize(proficiencies);
    for (int i = 0; i < proficiencies_count; i++) {
        cJSON *proficiency = cJSON_GetArrayItem(proficiencies, i);
        push_back(&character.proficiencies, proficiency->valuestring ? strdup(proficiency->valuestring) : NULL);
    }

    cJSON_Delete(json);
    free(content);
    return character;
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

// character json handling

static int l_get_character_from_json(lua_State *L) {
    const char* filename = luaL_checkstring(L, 1);
    character_t character = get_character_from_json(filename);

    lua_newtable(L);

    lua_pushstring(L, "name");
    lua_pushstring(L, character.name ? character.name : "Unknown");
    lua_settable(L, -3);

    lua_pushstring(L, "race");
    lua_pushstring(L, character.race ? character.race : "Unknown");
    lua_settable(L, -3);

    lua_pushstring(L, "class");
    lua_pushstring(L, character.classname ? character.classname : "Unknown");
    lua_settable(L, -3);

    lua_pushstring(L, "level");
    lua_pushnumber(L, character.level);
    lua_settable(L, -3);

    // Nested tables for stats and arrays
    lua_pushstring(L, "ability_scores");
    lua_newtable(L);

    lua_pushstring(L, "strength");
    lua_pushnumber(L, character.ability_scores.strength);
    lua_settable(L, -3);

    lua_pushstring(L, "dexterity");
    lua_pushnumber(L, character.ability_scores.dexterity);
    lua_settable(L, -3);

    lua_pushstring(L, "constitution");
    lua_pushnumber(L, character.ability_scores.constitution);
    lua_settable(L, -3);
    
    lua_pushstring(L, "intelligence");
    lua_pushnumber(L, character.ability_scores.intelligence);
    lua_settable(L, -3);

    lua_pushstring(L, "wisdom");
    lua_pushnumber(L, character.ability_scores.wisdom);
    lua_settable(L, -3);

    lua_pushstring(L, "charisma");
    lua_pushnumber(L, character.ability_scores.charisma);
    lua_settable(L, -3);

    lua_settable(L, -3);

    lua_pushstring(L, "saving_throws");
    lua_newtable(L);

    lua_pushstring(L, "strength");
    lua_pushnumber(L, character.saving_throws.strength);
    lua_settable(L, -3);

    lua_pushstring(L, "dexterity");
    lua_pushnumber(L, character.saving_throws.dexterity);
    lua_settable(L, -3);

    lua_pushstring(L, "constitution");
    lua_pushnumber(L, character.saving_throws.constitution);
    lua_settable(L, -3);
    
    lua_pushstring(L, "intelligence");
    lua_pushnumber(L, character.saving_throws.intelligence);
    lua_settable(L, -3);

    lua_pushstring(L, "wisdom");
    lua_pushnumber(L, character.saving_throws.wisdom);
    lua_settable(L, -3);

    lua_pushstring(L, "charisma");
    lua_pushnumber(L, character.saving_throws.charisma);
    lua_settable(L, -3);

    lua_settable(L, -3);

    lua_pushstring(L, "stats");
    lua_newtable(L);

    lua_pushstring(L, "speed");
    lua_pushnumber(L, character.speed);
    lua_settable(L, -3);

    lua_pushstring(L, "ac");
    lua_pushnumber(L, character.ac);
    lua_settable(L, -3);

    lua_pushstring(L, "hp");
    lua_pushnumber(L, character.hp);
    lua_settable(L, -3);

    lua_settable(L, -3);

    lua_pushstring(L, "weapons");
    lua_newtable(L);
    
    for (int i = 0; i < character.weapons.size; i++) {
        lua_pushnumber(L, i);
        lua_pushstring(L, get_item(&character.weapons, i) ? get_item(&character.weapons, i) : "Unknown");
        lua_settable(L, -3);
    }
    lua_settable(L, -3);

    lua_pushstring(L, "spells");
    lua_newtable(L);
    
    for (int i = 0; i < character.spells.size; i++) {
        lua_pushnumber(L, i);
        lua_pushstring(L, get_item(&character.spells, i) ? get_item(&character.spells, i) : "Unknown");
        lua_settable(L, -3);
    }
    lua_settable(L, -3);
    
    lua_pushstring(L, "proficiencies");
    lua_newtable(L);
    
    for (int i = 0; i < character.proficiencies.size; i++) {
        lua_pushnumber(L, i);
        lua_pushstring(L, get_item(&character.proficiencies, i) ? get_item(&character.proficiencies, i) : "Unknown");
        lua_settable(L, -3);
    }
    lua_settable(L, -3);

    return 1;
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
    lua_register(L, "get_character", l_get_character_from_json);
}
