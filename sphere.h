#pragma once
#include "utilities.h"

class sphere : public hittable {
   public:
    sphere() = default;
    sphere(point3d cen, double r) : center(cen), radius(r){};
    virtual bool hit(const ray &r, double tMin, double tMax, hitRecord &record) const override;

    point3d center;
    double radius;
};