#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>
#include <stdio.h>

#include "../include/globals.h"
#include "../include/components.h"
// #include "../include/utils.h"
// #include "../include/update.h"

int instantiate(int *state);

void test1() 
{
  printf("Testing!");
}

typedef struct {
  void (*funciones[2])();
} KeyA;

void invoke(KeyA* keyA) {
  for (int i = 0; i < 2; i++) {
    keyA->funciones[i]();
  }
}

bool fadeStarted = false;
bool mustFade = false;

typedef struct {
  float lifeTime;
} Timer;

void startTimer(Timer* timer, float lifetime)
{
  mustFade = true;
  fadeStarted = true;
}

void updateTimer(Timer* timer)
{
  if (fadeStarted == false) return;
  if (mustFade == true) {
    timer->lifeTime += GetFrameTime();
    if (timer->lifeTime >= 3.0f) {
      mustFade = false;
    }
  }
  else {
    timer->lifeTime -= GetFrameTime();
    if (timer->lifeTime <= 0.0f) {
      fadeStarted = false;
    }
  }
}

float timerState(Timer* timer) {
  if (fadeStarted == false) return 255;
  return timer->lifeTime >= 2.0f ? 2.0f : timer->lifeTime;
}

bool TimerDone(Timer* timer)
{
  if (timer != NULL)
    return timer->lifeTime <= 0;
  return false;
}

Texture2D sprite;
Texture2D fade;
Camera2D cam;
int e;
Timer fadeTimer;
KeyA keyA;

void drawTiles(Texture2D sprite, int x[MAP_HEIGHT][MAP_WIDTH][2])
{
  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      if (x[i][j][0] == -1) continue;
      DrawTextureRec(
        sprite,
        (Rectangle) {
        x[i][j][0] * TILE_SIZE,
          x[i][j][1] * TILE_SIZE,
          TILE_SIZE,
          TILE_SIZE
      },
        (Vector2) {
        j* TILE_SIZE, i* TILE_SIZE
      }, WHITE);
    }
  }
}

void drawTiles2(Texture2D sprite, int x[2][2][2])
{
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (x[i][j][0] == -1) continue;
      DrawTextureRec(
        sprite,
        (Rectangle) {
        x[i][j][0] * TILE_SIZE,
          x[i][j][1] * TILE_SIZE,
          TILE_SIZE,
          TILE_SIZE
      },
        (Vector2) {
        j* TILE_SIZE, i* TILE_SIZE
      }, WHITE);
    }
  }
}

void start() 
{
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Wenas");
  // SetTargetFPS(1);

  sprite = LoadTexture("assets/tiles_packed.png");
  fade = LoadTexture("assets/black-pixel.png");
  cam.zoom = 4;
  
  e = instantiate(_state);
  _color[e] = RED;

  e = instantiate(_state);
  _x[e] = 30.0f;

  e = instantiate(_state);
  _color[e] = YELLOW;
  _x[e] = 60.0f;
}

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


int main() 
{
  keyA.funciones[0] = test1;
  keyA.funciones[1] = test1;

  start();

  while (!WindowShouldClose()) 
    update();

  CloseWindow();
  return 0;
}