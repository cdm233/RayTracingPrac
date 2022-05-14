#pragma once
#include <cstdlib>
#include <vector>
#include <memory>
#include <limits>
#include <cmath>
#include <random>


#include "ray.h"
#include "vec3.h"
#include "hittableObj.h"

using std::make_shared;
using std::shared_ptr;
using std::vector;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double limit(double val, double min, double max){
    if(val < min){
        return min;
    }
    if(val > max){
        return max;
    }

    return val;
}