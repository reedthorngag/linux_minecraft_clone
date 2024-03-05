#include <random>
#include <math.h>

#include "../include/OpenSimplexNoise.h"

#include "world_gen.hpp"
#include "../chunk.hpp"
#include "../blocks.hpp"


void Generator::generateChunk(Chunk* chunk) {
    OpenSimplexNoise::Noise noise;

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            int y =  (int)round(
                (noise.eval(chunk->pos[0]*CHUNK_SIZE+x,chunk->pos[1]*CHUNK_SIZE+z) + 0.5) * 
                (CHUNK_HEIGHT-2) + 
                4); 

            int pos = z*CHUNK_SIZE+x;
            chunk->heightmap[pos] = y;

            if (!chunk->layers[y])
                chunk->layers[y] = new short[CHUNK_SIZE*CHUNK_SIZE];

            chunk->layers[y--][pos] = blocks::GRASS;

            for (int i=0;i<3;i++) {
                if (!chunk->layers[y])
                    chunk->layers[y] = new short[CHUNK_SIZE*CHUNK_SIZE];
                chunk->layers[y--][pos] = blocks::DIRT;
            }

            for (;y >= 0; y--) {
                if (!chunk->layers[y])
                    chunk->layers[y] = new short[CHUNK_SIZE*CHUNK_SIZE];
                chunk->layers[y][pos] = blocks::STONE;
            }
        }
    }
}

Generator::Generator() {
}

Generator::~Generator() {

}

