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

bool sphere::hit(const ray &r, double tMin, double tMax, hitRecord &record) const {
    /*
        in 3d, the equation for a sphere is (x-Cx)^2 + (y-Cy)^2 + (z-Cz)^2 = R^2
        for all possible position that the distance between it and the sphere center is less than R
        if we express (x,y,z) to be P and (Cx, Cy, Cz) to be C, we have (P-C) * (P-C) = R^2

        for the ray we have, P can be expressed to be A + B*t where A is the origin and B is the direction
        thus, the direvation is:
            (P-C) * (P-C) = R^2
            (P-C) * (P-C) - R^2 = 0
            (A + Bt - C) * (A + Bt - C) - R^2 = 0
                A - C = D
            (D + Bt) * (D + Bt) - R^2 = 0
            B * B * t^2 + 2 * B * D * t + D * D - R^2 = 0
                for same vector dot product, the result is the square of its magnitude
            B^2 * t^2 + 2 * B * (A - C) * t + (A - C)^2 - R^2 = 0

            from here we can sue quadratic equation to solve
    */

    vec3 oc = r.origin - center;
    auto a = r.direction.length_squared();
    auto hb = dot(oc, r.direction);
    auto c = oc.length_squared() - radius * radius;
    auto determinant = (hb * hb - a * c);

    // no hit
    if (determinant < 0) {
        return false;
    }

    auto root = (-hb + sqrt(determinant)) / (a);

    // check if root t is within bound
    if (root < tMin || root > tMax) {
        // check if the other root is within bound
        root = (-hb - sqrt(determinant)) / (a);
        if (root < tMin || root > tMax) {
            return false;
        }
    }

    record.t = root;
    record.position = r.at(root);
    auto outwardNorm = unit_vector(record.position - center);
    record.setNorm(r, outwardNorm);

    return true;
}