
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

inline double ridge(double x, double y) {
    return 1/(1+exp((-o3.eval(x*0.01,y*0.01)-0.2)*10));
}


double genNoise(double x, double y) {
    return abs(1/(1+exp((-o3.eval(x*0.03,y*0.03))*10))*30);
    // return abs((
    //         ((o1.eval(x*0.00025,y*0.00025) + 1) * 150) +
    //         ((o2.eval(x*0.005,y*0.005) + 1) * 50) +
    //         ((o3.eval(x*0.03,y*0.03) + 1) * 20) + 
    //         ((o4.eval(x*0.1,y*0.1) + 1) * 3)
    //         ));
}