/*
Copyright (C) 2024 Sariah Echols

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
#include "token.h"

#ifndef STATUS_H
#define STATUS_H

typedef struct {
    token_t *token; 
    Texture2D status;
} status_token;

status_token base_token(token_t *base_token);
void update_status(status_token*layered_token, Camera2D camera);
void draw_status(status_token *layered_token);
void remove_status(status_token *layered_token);

#endif