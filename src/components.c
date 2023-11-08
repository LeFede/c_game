#include <raylib.h>
#include "../include/globals.h"

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