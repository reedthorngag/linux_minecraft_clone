
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

// period paramater is named completely inaccurately, smaller numbers produce a larger period
inline double genWaveForm(double x, double y, double period, double scale) {
    return (o1.eval(x*period,y*period)+1) * scale;
}

inline double sigmoid(double x, double y, double period, double scale, double dropOffSteepness) {
    return abs(1/(1+exp((-o1.eval(x*period,y*period))*dropOffSteepness))*scale);
}

inline double ridge(double x, double y) {
    return sigmoid(x,y,0.005,30,40);
}


double genNoise(double x, double y) {
    return sigmoid(x,y,0.03,30,20);
    // return abs((
    //         ((o1.eval(x*0.00025,y*0.00025) + 1) * 150) +
    //         ((o2.eval(x*0.005,y*0.005) + 1) * 50) +
    //         ((o3.eval(x*0.03,y*0.03) + 1) * 20) + 
    //         ((o4.eval(x*0.1,y*0.1) + 1) * 3)
    //         ));
}