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

#include "token.h"
#include "raylib.h"
#include "stdio.h"

#define TOKEN_SIZE 128

/*
====================
new_token

creates and returns 
a token
====================
*/
static token_t new_token(const char *filename, const char *label,
                         bool is_player) {
  token_t token;
  Image token_image = LoadImage(filename);
  token.image = LoadTextureFromImage(token_image);
  UnloadImage(token_image);
  token.position.x = 0;
  token.position.y = 0;
  token.label = label;
  token.is_player = is_player;
  return token;
}

/*
====================
new_player_token

creates and returns
new player token
====================
*/
token_t new_player_token(const char *filename, const char *label) {
  return new_token(filename, label, true);
}

/*
====================
new_enemy_token

creates and returns
new enemy token
====================
*/
token_t new_enemy_token(const char *filename) {
  return new_token(filename, "", false);
}

/*
====================
update_token

updates any changes
in token data between
frames
====================
*/
void update_token(token_t *token, Camera2D camera) {
  static bool is_dragging = false;
  static Vector2 offset;

  Vector2 mouse_pos = GetScreenToWorld2D(GetMousePosition(), camera);
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (mouse_pos.x >= token->position.x &&
        mouse_pos.x <= token->position.x + TOKEN_SIZE &&
        mouse_pos.y >= token->position.y &&
        mouse_pos.y <= token->position.y + TOKEN_SIZE) {
      is_dragging = true;
      offset = (Vector2){mouse_pos.x - token->position.x,
                         mouse_pos.y - token->position.y};
    }
  }

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    is_dragging = false;
  }

  if (is_dragging) {
    token->position.x = mouse_pos.x - offset.x;
    token->position.y = mouse_pos.y - offset.y;

    // Snap to grid
    token->position.x =
        (float)((int)(token->position.x / TOKEN_SIZE) * TOKEN_SIZE);
    token->position.y =
        (float)((int)(token->position.y / TOKEN_SIZE) * TOKEN_SIZE);
  }

  // Debug logs
  char debug_log[64];
  sprintf(debug_log, "Mouse: %f, %f", mouse_pos.x, mouse_pos.y);
  DrawText(debug_log, 20, 20, 20, DARKGRAY);
  sprintf(debug_log, "Token: %f, %f", token->position.x, token->position.y);
  DrawText(debug_log, 20, 40, 20, DARKGRAY);
}

/*
====================
draw_token

updates the visuals
of the token each
frame
====================
*/
void draw_token(token_t *token) {
  DrawTextureV(token->image, token->position, WHITE);

  const int label_width = MeasureText(token->label, 20);
  DrawText(token->label, token->position.x + (TOKEN_SIZE - label_width) / 2.0f,
           token->position.y + TOKEN_SIZE + 10, 20, DARKGRAY);
}

/*
====================
remove_token

frees memory used
by the token
====================
*/
void remove_token(token_t *token) { UnloadTexture(token->image); }
