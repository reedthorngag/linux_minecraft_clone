

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

enum face_offset {
    NORTH = 0,
    EAST = 4,
    SOUTH = 8,
    WEST = 12,
    TOP = 16,
    BOTTOM = 20
};

const int face_vertex_count = 4;


enum blocks {
    AIR = 0,
    GRASS = 1,
    DIRT = 2,
    STONE = 3
};


// texpos,  north, east, south, west, top, bottom
const int texture_map[][6] = {
    {0},
    {0,0,0,0,1,2}, // grass
    {0}, // dirt
    {0}, // stone
};

