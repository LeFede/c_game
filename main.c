#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>
#include <stdio.h>
#include "sock-lib.h"

#define SCREEN_WIDTH 1920 / 1.5
#define SCREEN_HEIGHT 1080 / 1.5
#define MAIN_MONITOR 0

#define MAIN_COLOR GREEN
#define BG_COLOR BLUE

#define MAX_ENTITIES 3

#define OBJECT    1 << 0
#define TRANSFORM 1 << 1
#define RIGIDBODY 1 << 2
#define SPRITE    1 << 3

typedef unsigned short unit;

bool hasComponent(unit state, unit component);
unit instantiate(unit *state);

unit _state[MAX_ENTITIES] = {};

// Transform { 1 }
unit _x[MAX_ENTITIES] = {};      
unit _y[MAX_ENTITIES] = {};      
unit _w[MAX_ENTITIES] = {};    
unit _h[MAX_ENTITIES] = {};    

// Rigidbody { 2 }
unit _vx[MAX_ENTITIES] = {};      
unit _vy[MAX_ENTITIES] = {};      

// Sprite { 3 }
Color _color[MAX_ENTITIES] = {};

#define BUFFER_SIZE 4096

int main() {

  // SetConfigFlags(FLAG_WINDOW_UNDECORATED);

  int sock;
  sock = conectar("localhost", 80000, 1);


  // int sock;
  // char buf[BUFFER_SIZE];
  // int bytes_recibidos;

  // sock = conectar("localhost", 8000, 1);

  // bytes_recibidos = read(sock, buf, BUFFER_SIZE);
  // buf[bytes_recibidos] = 0;
  // fprintf(stderr, "debug :: recibido=%s", buf);
  // close(sock);




  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Wenas");
  // SetWindowMinSize(1920, 1080);
  // SetConfigFlags(FLAG_WINDOW_RESIZABLE);

  // ToggleFullscreen();

  Texture2D sprite = LoadTexture("mi_sprite.png");

  Camera2D cam = { 0 };
  cam.zoom = 1;
  
  unit e;
  e = instantiate(_state);
  _color[e] = RED;
  
  e = instantiate(_state);
  _x[e] = 30;

  e = instantiate(_state);
  _color[e] = YELLOW;
  _x[e] = 60;


  while (!WindowShouldClose()) {

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
			if (cam.zoom < 0.125f)
				cam.zoom = 0.125f;
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
    rlPushMatrix();
    rlTranslatef(0, 25 * 50, 0);
    rlRotatef(90, 1, 0, 0);
    DrawGrid(100, 50);
    rlPopMatrix();

		// draw a thing
		DrawCircle(100, 100, 50, YELLOW);

    DrawTexture(sprite, 10, 10, WHITE);


    // Draw
    for (unit i = 0; i < MAX_ENTITIES; i++)
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

		EndMode2D();

    DrawFPS(0, 0);
    EndDrawing();
  }

  close(sock);

  CloseWindow();
  return 0;
}

unit instantiate(unit *state) {
  for (unit i = 0; i < MAX_ENTITIES; i++) {
    if (state[i] != 0) continue;

    state[i] |= OBJECT;
    state[i] |= TRANSFORM;
    state[i] |= RIGIDBODY;
    state[i] |= SPRITE;

    _x[i]     = 0;
    _y[i]     = 0;
    _w[i]     = 10;
    _h[i]     = 10;
    _vx[i]    = .1;
    _vy[i]    = .1;
    _color[i] = GREEN;

    printf("Entity added succesfully\n");
    return i;
  }

  printf("No room\n");
  return -1;
}
