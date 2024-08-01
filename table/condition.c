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

/*#include "component.h"
#include "raylib.h"
#include <stdint.h>

#define CONDITIONS_COUNT 16

#define COND_BLIND 0x8000
#define COND_CHARM 0x4000
#define COND_DEAF 0x2000
#define COND_FRIGHT 0x1000
#define COND_GRAPP 0x0800
#define COND_INCAP 0x0400
#define COND_POISON 0x0200
#define COND_PETR 0x0100
#define COND_PARA 0x0080
#define COND_PRONE 0x0040
#define COND_RESTR 0x0020
#define COND_STUN 0x0010
#define COND_UNCON 0x0008
#define COND_EXHAUST 0x0004
#define COND_FATIG 0x0002
#define COND_INVIS 0x0001

Texture2D condition_texs[CONDITIONS_COUNT];

static void load_condition_texs() {
    for (int i = 0; i < CONDITIONS_COUNT; ++i) {
        // use an fprintf to a string to append the number to condition_
        // fprintf(&str, "condition_%d.png", i);
        Image cond_image = LoadImage("resources/player_border.png");
        condition_texs[i] = LoadTextureFromImage(cond_image);
        UnloadImage(cond_image);
    }
}

static void delete_condition_texs() {
    for (int i = 0; i < CONDITIONS_COUNT; ++i) {
        UnloadTexture(condition_texs[i]);
    }
}

static void init() {
    load_condition_texs();
}

static void update() {

}

static void draw() {

}

static void remove() {
    delete_condition_texs();
}

condition_t new_condition() {
    condition_t condition;
    condition.conds = 0;
    condition.init = init;
    return 0;
}

void add_cond(uint16_t conditions, status_token*layered_token, Camera2D camera) {
if (COND_BLIND | COND_CHARM){

}

// fancy stuff
int msk = 0;
for (int i = 0; i < 16; ++i) {
    if (msk & (1 << i)) {
        // handle the condition at i
    }
}
}*/