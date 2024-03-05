#include "../chunk.hpp"

#ifndef _WorldGen
#define _WorldGen

class Generator {

    public:
        void generateChunk(Chunk* chunk);

        Generator();
        ~Generator();
};

#endif
