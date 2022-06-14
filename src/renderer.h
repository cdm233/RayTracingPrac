#pragma once
#include <omp.h>

#include "camera.h"
// #include "color.h"
#include "hittableList.h"
#include "utilities.h"
#include "lodepng.h"

class renderer {
   public:
    int imageHeight;
    int imageWidth;
    int antiAliasingConf;
    int threadCount;
    double totalProgress;
    string imageName;
    vector<int> progress;
    // ppm image buffer
    vector<string> imageBuffer;
    // plain pixel buffer
    vector<vector<unsigned char>> imagePixelBuffer;

    color rayColor(ray r, hittableList &world);
    renderer(int width, int height, int anti);
    void render();
    void write_color(std::string &s, color pixel_color, int sampleNum, vector<unsigned char> &pixelBuffer);
    bool exportImage(int type, string name);
    bool exportPPM();
    bool exportPNG();
};
