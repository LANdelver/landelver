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

#include "vector.h"

typedef struct {
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;
} ability_scores_t;


typedef struct {
    const char* name;
    const char* race;
    const char* classname;
    int level;
    ability_scores_t ability_scores;
    ability_scores_t saving_throws;
    int profifiency;
    int initiative;
    int walk_speed;
    int armor_class;
    int hit_points;
    vector_t weapons;
    vector_t spells;
    vector_t proficiencies;
} character_t;
