
#include <math.h>

#include <OpenSimplexNoise.h>
#define DB_PERLIN_IMPL
#include <db_perlin.hpp>

OpenSimplexNoise::Noise o1(100);
OpenSimplexNoise::Noise o2(1001);
OpenSimplexNoise::Noise o3(10001);
OpenSimplexNoise::Noise o4(100001);
OpenSimplexNoise::Noise o5(1000001);


// double noise1D = db::perlin(0);
// double noise2D = db::perlin(0, 0);
// double noise3D = db::perlin(0, 0, 0);


inline double genWaveForm(double x, double y, double frequency, double scale) {
    return (o1.eval(x*frequency,y*frequency)+1) * scale;
}

inline double sigmoid(double in, double scale, double dropOffSteepness) {
    return abs(1/(1+exp(-in*dropOffSteepness))*scale);
}

inline double sigmoidWave(double x, double y, double frequency, double scale, double dropOffSteepness) {
    return sigmoid(o1.eval(x*frequency,y*frequency),scale,dropOffSteepness);
}

inline double ridge(double x, double y, double frequency, double ) {
    return 1-abs(sigmoidWave(x,y,frequency,2,5)-1);
}

inline double valley(double x, double y, double frequency, double width) {
    double z = o1.eval(x*frequency,y*frequency);
    return abs(sigmoid(z*z*z,2,200)-1);
}


// TODO: make this cos I think it would be cool
inline double ridgeWithValleysOffIt(double x, double y) {
    return 1;
}


double genNoise(double x, double y) {
    return 50+valley(x,y,0.01,10)*20;
}