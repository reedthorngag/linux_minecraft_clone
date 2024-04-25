#ifndef _WorldGen
#define _WorldGen

struct Chunk;

class WorldGenerator {

    public:
        void generateChunk(Chunk* chunk);

        WorldGenerator();
        ~WorldGenerator();
};

#endif
