#pragma once
#include "vec3.h"

class ray {
   public:
    ray() = default;
    ray(point3d ori, vec3 dir) : origin(ori), direction(dir) {};

    point3d origin;
    vec3 direction;

    point3d at(double t) const {
        return origin + t * direction;
    }
};