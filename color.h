#pragma once

#include <iostream>

#include "utilities.h"
#include "vec3.h"

void write_color(std::ostream &out, color pixel_color, int sampleNum) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    r /= sampleNum;
    g /= sampleNum;
    b /= sampleNum;

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * limit(r, 0.0, 0.999999)) << ' '
        << static_cast<int>(255.999 * limit(g, 0.0, 0.999999)) << ' '
        << static_cast<int>(255.999 * limit(b, 0.0, 0.999999)) << '\n';
}

void write_color(std::string &s, color pixel_color, int sampleNum) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    r /= sampleNum;
    g /= sampleNum;
    b /= sampleNum;

    s += std::to_string(static_cast<int>(255.999 * limit(r, 0.0, 0.999999))) + " " + 
         std::to_string(static_cast<int>(255.999 * limit(g, 0.0, 0.999999))) + " " + 
         std::to_string(static_cast<int>(255.999 * limit(b, 0.0, 0.999999)));
    s += "\n";
    // Write the translated [0,255] value of each color component.
    // out << static_cast<int>(255.999 * limit(r, 0.0, 0.999999)) << ' '
    //     << static_cast<int>(255.999 * limit(g, 0.0, 0.999999)) << ' '
    //     << static_cast<int>(255.999 * limit(b, 0.0, 0.999999)) << '\n';
}
