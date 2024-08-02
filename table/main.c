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

#include "lua_runtime.h"
#include "lua_api.h"
#include "raylib.h"

#include "raymath.h"
#include "rlgl.h"
#include "server.h"
#include "token.h"
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {
  // Start python server thread
  //----------------------------------------------------------------------------------
  start_websocket_server();
  // Create lua state
  //----------------------------------------------------------------------------------
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);
  lua_set_path(L);
  register_lua_api(L);
  lua_load_script(L,"./scripts/world.lua"); 
  lua_call_function(L, "init");

  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 1920;
  const int screenHeight = 1080;

  InitWindow(screenWidth, screenHeight, "LANdelver");
  MaximizeWindow();
  ToggleFullscreen();

  Camera2D camera = {0};
  camera.zoom = 1.0f;

  token_t demo_token =
      new_player_token("resources/player_border.png", "demo_token");

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------

    lua_call_function(L, "update");
    update_token(&demo_token, camera);

    // Translate based on mouse right click
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
      Vector2 delta = GetMouseDelta();
      delta = Vector2Scale(delta, -1.0f / camera.zoom);
      camera.target = Vector2Add(camera.target, delta);
    }

    // Zoom based on mouse wheel
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
      // Get the world point that is under the mouse
      Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

      // Set the offset to where the mouse is
      camera.offset = GetMousePosition();

      // Set the target to match, so that the camera maps the world space
      // point under the cursor to the screen space point under the cursor at
      // any zoom
      camera.target = mouseWorldPos;

      // Zoom increment
      float scaleFactor = 1.0f + (0.25f * fabsf(wheel));
      if (wheel < 0)
        scaleFactor = 1.0f / scaleFactor;
      camera.zoom = Clamp(camera.zoom * scaleFactor, 0.125f, 64.0f);
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    // Draw the 3d grid, rotated 90 degrees and centered around 0,0
    // just so we have something in the XY plane
    rlPushMatrix();
    rlTranslatef(0, 128 * 25, 0);
    rlRotatef(90, 1, 0, 0);
    DrawGrid(100, 128);
    rlPopMatrix();

    lua_call_function(L, "draw");
    draw_token(&demo_token);

    EndMode2D();

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  lua_close(L);
  //--------------------------------------------------------------------------------------
  return 0;
}
