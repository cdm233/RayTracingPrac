#pragma once
#include "utilities.h"

class camera {
   public:
    camera(int width, int height) {
        const double aspectRatio = (double) height / (double) width;
        const double viewPortHeight = 2.0;
        const double viewPortWidth = viewPortHeight / aspectRatio;
        const double focalLength = 1.0;

        cameraOrigin = point3d(0, 0, 0);
        cameraHorVec = vec3(viewPortWidth, 0, 0);
        cameraVerVec = vec3(0, viewPortHeight, 0);
        lowerLeftCorner = cameraOrigin - cameraHorVec / 2 - cameraVerVec / 2 - vec3(0, 0, focalLength);
    }

    ray getRay(double horizontalStep, double verticalStep) {
        return ray(cameraOrigin, lowerLeftCorner + horizontalStep * cameraHorVec + verticalStep * cameraVerVec - cameraOrigin);
    }

   public:
    point3d cameraOrigin;
    vec3 cameraHorVec;
    vec3 cameraVerVec;
    vec3 lowerLeftCorner;
};