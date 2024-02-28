#include <GL/glew.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "block.hpp"
#include "blocks.hpp"

const float Block::vertices[]{
    0, 0.0, 0.0,    0, 0, // 0 bottom right front
    0, 1.0, 0.0,    0.007, 0, // 1 top right front
    1, 0.0, 0.0,    0, 0.01, // 2 bottom left front
    1, 1.0, 0.0,    0.007, 0.01, // 3 top left front
    0, 0.0, 1,      0, 0.01, // 4 bottom right back
    0, 1.0, 1,      0.007, 0.01, // 5 top right back    
    1, 0.0, 1.0,    0, 0, // 6 bottom left back
    1, 1.0, 1.0,    0.007, 0, // 7 top left back
};
const unsigned int Block::indices[]{
    0,1,2,
    2,1,3,
    4,5,6,
    6,5,7,
    0,1,5,
    0,4,5,
    2,6,7,
    2,3,7,
    1,3,7,
    5,7,1
};


void Block::render(unsigned int program) {
    (void)program;    

}

Block::Block() {
    

}

Block::~Block() {
}
