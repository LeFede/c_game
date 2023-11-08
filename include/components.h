#include "globals.h"
#include <raylib.h>

extern int _state[MAX_ENTITIES];

// Transform { 1 }
extern unit _x[MAX_ENTITIES];
extern unit _y[MAX_ENTITIES];
extern unit _w[MAX_ENTITIES];
extern unit _h[MAX_ENTITIES];

// Rigidbody { 2 }
extern unit _vx[MAX_ENTITIES];
extern unit _vy[MAX_ENTITIES];

// Sprite { 3 }
extern Color _color[MAX_ENTITIES];