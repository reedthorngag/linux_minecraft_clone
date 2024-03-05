
#include "../include/OpenSimplexNoise.h"
#define DB_PERLIN_IMPL
#include "../include/db_perlin.hpp"

OpenSimplexNoise::Noise o1(100);
OpenSimplexNoise::Noise o2(1001);
OpenSimplexNoise::Noise o3(10001);
OpenSimplexNoise::Noise o4(100001);

double genNoise(double x, double y) {
    return (((o1.eval(x,y) * 3)) +
            ((o2.eval(x,y)+1) * 15));
}

