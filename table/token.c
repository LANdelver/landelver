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

#include "token.h"
#include "raylib.h"
#include "stdio.h"

token_t new_token(const char *filename, bool is_player) {
  token_t token;
  token.image = LoadImage(filename);
  token.position.x = 0;
  token.position.y = 0;
  token.is_player = is_player;
  return token;
}

void update_token(token_t *token, Camera2D camera) {
  static bool is_dragging = false;
  static Vector2 offset;

  Vector2 mouse_pos = GetScreenToWorld2D(GetMousePosition(), camera);
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (mouse_pos.x >= token->position.x &&
        mouse_pos.x <= token->position.x + 256 &&
        mouse_pos.y >= token->position.y &&
        mouse_pos.y <= token->position.y + 256) {
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
    token->position.x = (float)((int)(token->position.x / 256) * 256);
    token->position.y = (float)((int)(token->position.y / 256) * 256);
  }

  // Debug logs
  char debug_log[64];
  sprintf(debug_log, "Mouse: %f, %f", mouse_pos.x, mouse_pos.y);
  DrawText(debug_log, 20, 20, 20, DARKGRAY);
  sprintf(debug_log, "Token: %f, %f", token->position.x, token->position.y);
  DrawText(debug_log, 20, 40, 20, DARKGRAY);
}

void draw_token(token_t *token) {
  Texture2D token_tex = LoadTextureFromImage(token->image);
  DrawTextureV(token_tex, token->position, WHITE);
}
