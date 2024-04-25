#include <random>
#include <math.h>

#include "world_gen.hpp"
#include "noise.hpp"
#include "../chunk.hpp"
#include "../blocks.hpp"


void WorldGenerator::generateChunk(Chunk* chunk) {

    // const int size = 1000;
    // double array[size*size];

    // for (int x=0;x<size;x++) {
    //     for (int y=0;y<size;y++) {
    //         array[x*size+y] = sigmoid(x,y,0.02,1,10);
    //     }
    // }

    // double min = 1000;
    // double max = -1000;

    // for (int n=0;n<size*size;n++) {
    //     if (array[n]<min) min = array[n];
    //     else if (array[n]>max) max = array[n];
    // }

    // printf("\nmin: %lf, max: %lf \n",min,max);
    // exit(1);

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            double input1 = (chunk->pos[0]*CHUNK_SIZE+x);
            double input2 = (chunk->pos[1]*CHUNK_SIZE+z);
            int y =  (int)round((genNoise(input1,input2)) + 4);

            int pos = z*CHUNK_SIZE+x;
            chunk->heightmap[pos] = y;

            if (!chunk->layers[y])
                chunk->layers[y] = new short[CHUNK_SIZE*CHUNK_SIZE]{0};

            chunk->layers[y--][pos] = blocks::GRASS;

            for (int i=0;i<3;i++) {
                if (!chunk->layers[y])
                    chunk->layers[y] = new short[CHUNK_SIZE*CHUNK_SIZE]{0};
                chunk->layers[y--][pos] = blocks::DIRT;
            }

            for (;y >= 0; y--) {
                if (!chunk->layers[y])
                    chunk->layers[y] = new short[CHUNK_SIZE*CHUNK_SIZE]{0};
                chunk->layers[y][pos] = blocks::STONE;
            }
        }
    }
}

WorldGenerator::WorldGenerator() {
}

WorldGenerator::~WorldGenerator() {

}

