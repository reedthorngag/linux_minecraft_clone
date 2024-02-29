

#ifndef _BLOCKS
#define _BLOCKS

// north is positive z
// east is positive x

const float CUBE_VERTICES[]{
    0,0,1,  0,1, // north face
    1,0,1,  0,0,
    0,1,1,  1,1,
    1,1,1,  1,0,

    1,0,1,  0,1, // east face
    1,0,0,  0,0,
    1,1,1,  1,1,
    1,1,0,  1,0,

    1,0,0,  0,1, // south face
    0,0,0,  0,0,
    1,1,0,  1,1,
    0,1,0,  1,0,

    0,0,1,  0,1, // west face
    0,0,0,  0,0,
    0,1,1,  1,1,
    0,1,0,  1,0,

    1,1,0,  0,1, // top face
    0,1,0,  0,0,
    1,1,1,  1,1,
    0,1,1,  1,0,

    1,0,0,  0,1, // bottom face
    0,0,0,  0,0,
    1,0,1,  1,1,
    0,0,1,  1,0

};

const unsigned int INDICES[] {
    0,1,2, 1,2,3,
    4,5,6, 5,6,7,
    8,9,10, 9,10,11,
    12,13,14, 13,14,15,
    16,17,18, 17,18,19,
    20,21,22, 21,22,23,
};

const int face_size = sizeof(float) * 5 * 4;


enum faces {
    NORTH  = 0,
    EAST   = 1,
    SOUTH  = 2,
    WEST   = 3,
    TOP    = 4,
    BOTTOM = 5
};

const short face_offset[] {
    face_size*0,
    face_size*1,
    face_size*2,
    face_size*3,
    face_size*4,
    face_size*5
};

enum blocks {
    AIR = 0,
    GRASS = 1,
    DIRT = 2,
    STONE = 3
};


const int texture_map[] = {
    0, // air
    1, // grass
    3, // dirt
    4, // stone
};

// texpos,  north, east, south, west, top, bottom
const int texture_face_map[][6] = {
    {0},
    {0,0,0,0,1,2}, // grass
    {0}, // dirt
    {0}, // stone
};

#endif
