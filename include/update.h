#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>


#include "globals.h"
#include "utils.h"
#include "components.h"

void update()
{
  updateTimer(&fadeTimer);

  if (IsKeyPressed(KEY_SPACE))
  {
    cam.target = (Vector2){ _x[0] - (GetScreenWidth() / cam.zoom / 2), _y[0] - (GetScreenHeight() / cam.zoom / 2) };
    startTimer(&fadeTimer, 2.0f);
  }

  if (IsKeyPressed(KEY_A))
  {
    invoke(&keyA);
  }


  if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
  {
    Vector2 delta = GetMouseDelta();
    delta = Vector2Scale(delta, -1.0f / cam.zoom);

    cam.target = Vector2Add(cam.target, delta);
  }

  // zoom based on wheel
  float wheel = GetMouseWheelMove();
  if (wheel != 0)
  {
    // get the world point that is under the mouse
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), cam);

    // set the offset to where the mouse is
    cam.offset = GetMousePosition();

    // set the target to match, so that the camera maps the world space point under the cursor to the screen space point under the cursor at any zoom
    cam.target = mouseWorldPos;

    // zoom
    cam.zoom += wheel * 0.125f;
    printf("zoom: %f\n", cam.zoom);
    if (cam.zoom <= 1.125f)
      cam.zoom = 1.125f;
  }

  // check for alt + enter
  if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
  {
    // see what display we are on right now
    int display = GetCurrentMonitor();
    if (IsWindowFullscreen())
    {
      ToggleFullscreen();
      SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
      SetWindowMonitor(MAIN_MONITOR);
    }
    else
    {
      ToggleFullscreen();
      SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
      SetWindowMonitor(MAIN_MONITOR);
    }
  }

  BeginDrawing();
  ClearBackground(BG_COLOR);

  BeginMode2D(cam);

  // draw the 3d grid, rotated 90 degrees and centered around 0,0 just so we have something in the XY plane
  // rlPushMatrix();
  // rlTranslatef(0, 25 * 50, 0);
  // rlRotatef(90, 1, 0, 0);
  // DrawGrid(100, 50);
  // rlPopMatrix();

  int tiles[MAP_HEIGHT][MAP_WIDTH][2] =
  {
    { {0,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {5,0} },
    { {0,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {5,1} },
    { {0,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {5,1} },
    { {0,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {5,1} },
    { {0,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {5,1} },
    { {0,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {5,1} },
    { {0,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {5,1} },
    { {0,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {5,1} },
    { {0,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {4,1}, {5,1} },
    { {0,4}, {1,4}, {1,4}, {1,4}, {1,4}, {1,4}, {1,4}, {1,4}, {1,4}, {5,4} },
  };

  int tiles2[2][2][2] = {
    { {14,6}, {15,6} },
    { {14,7}, {15,7} },
  };

  drawTiles(sprite, tiles);
  drawTiles2(sprite, tiles2);

  // Draw
  for (int i = 0; i < MAX_ENTITIES; i++)
  {
    if (!(_state[i] & OBJECT))
      continue;

    // Move
    if ((_state[i] & RIGIDBODY))
    {
      _x[i] += _vx[i];
      _y[i] += _vy[i];
    }

    // Draw
    if ((_state[i] & SPRITE))
    {
      DrawRectangle(_x[i], _y[i], _w[i], _h[i], _color[i]);
    }

  }

  DrawTextureEx(fade, (Vector2) { cam.target.x, cam.target.y }, 0.0f, 1000.0f, CLITERAL(Color){255, 255, 255, 255 * (timerState(&fadeTimer) / 2.0f)});

  EndMode2D();
  DrawFPS(0, 0);
  EndDrawing();

}
