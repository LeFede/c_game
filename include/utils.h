#include <raylib.h>
#include <stdio.h>
#include "globals.h"

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