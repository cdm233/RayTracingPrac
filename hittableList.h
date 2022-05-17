#pragma once
#include <memory>
#include <vector>

#include "utilities.h"

class hittableList : public hittable {
   public:
    hittableList(){};
    hittableList(shared_ptr<hittable> object) { add(object); };

    void clear() { objs.clear(); };
    void add(shared_ptr<hittable> object) { objs.push_back(object); };

    virtual bool hit(const ray &r, double tMin, double tMax, hitRecord &rec) const override;

    vector<shared_ptr<hittable>> objs;
};