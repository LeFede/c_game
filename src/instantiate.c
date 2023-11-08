#include <raylib.h>
#include <stdio.h>
#include "../include/globals.h"
#include "../include/components.h"

int instantiate(int *state) {
  for (int i = 0; i < MAX_ENTITIES; i++) {
    if (state[i] != 0) continue;

    state[i] |= OBJECT;
    state[i] |= TRANSFORM;
    state[i] |= RIGIDBODY;
    state[i] |= SPRITE;

    _x[i]     = 0.0f;
    _y[i]     = 0.0f;
    _w[i]     = 10.0f;
    _h[i]     = 10.0f;
    _vx[i]    = 1.0f;
    _vy[i]    = 1.0f;
    _color[i] = GREEN;

    printf("Entity added succesfully\n");
    return i;
  }

  printf("No room\n");
  return -1;
}