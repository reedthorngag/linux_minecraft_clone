#include <chrono>

#ifndef _GLOBALS
#define _GLOBALS

const float base_gravity = 1;

const int width = 800;
const int height = 600;
const int halfWidth = width/2;
const int halfHeight = height/2;

typedef std::chrono::high_resolution_clock Clock;
const int tickTime = 50;

const float speed = 0.1;
const float speed_scale = 5;

const int RENDER_DISTANCE = 8;
const int CHUNK_SIZE = 32;
const int CHUNK_HEIGHT = 256;

#endif


