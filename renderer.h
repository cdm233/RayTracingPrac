#pragma once
#include <omp.h>

#include "camera.h"
// #include "color.h"
#include "hittableList.h"
#include "utilities.h"

class renderer {
   public:
    int imageHeight;
    int imageWidth;
    int antiAliasingConf;
    int threadCount;
    double totalProgress;
    vector<int> progress;
    vector<string> imageBuffer;

    color rayColor(ray r, hittableList &world);
    renderer(int width, int height, int anti);
    void render();
    void write_color(std::string &s, color pixel_color, int sampleNum);
    bool exportImage(int type, string name);
};