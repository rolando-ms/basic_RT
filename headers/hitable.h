//
// Created by rolandoms on 27.09.18.
//

#ifndef SHIRLEY_HITABLE_H
#define SHIRLEY_HITABLE_H

#include "ray.h"

struct hit_record{
    float t;
    vec3 p;
    vec3 normal;
};

class hitable{
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif //SHIRLEY_HITABLE_H
