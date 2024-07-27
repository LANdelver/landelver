/*
Copyright (C) 2024 Lance Borden

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

#ifndef TOKEN_H
#define TOKEN_H

typedef struct {
  Image image;
  Vector2 position;
  const char *label;
  bool is_player;
} token_t;

token_t new_player_token(const char *filename, const char *label);
token_t new_enemy_token(const char *filename);
void update_token(token_t *token, Camera2D camera);
void draw_token(token_t *token);
void remove_token(token_t *token);

#endif // TOKEN_H
