#include "hittableList.h"

bool hittableList::hit(const ray &r, double tMin, double tMax, hitRecord &rec) const {
    bool hit = false;
    double closest = tMax;
    hitRecord tempRec;

    for (auto &obj : objs) {
        if (obj->hit(r, tMin, closest, tempRec)) {
            hit = true;
            closest = tempRec.t;
            rec = tempRec;
        }
    }

    return hit;
}