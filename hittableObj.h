#pragma once
#include "vec3.h"
#include "ray.h"

struct hitRecord {
    double t;
    point3d position;
    vec3 normal;
    bool frontFaceNorm;

    // here we determine this information at geometry time
    inline void setNorm(const ray& r, const vec3& outwardNorm){
        frontFaceNorm = dot(r.direction, outwardNorm) < 0;
        normal = frontFaceNorm ? outwardNorm : -outwardNorm;
    } 
};

// base class
class hittable {
    public:
        virtual bool hit(const ray &r, double tMin, double tMax, hitRecord &rec) const = 0;
        // virtual bool hit(const ray &r, double tMin, double tMax, hitRecord &rec) const;
};