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
    bool rendered;
    string imageName;
    vector<int> progress;
    vector<int> progressPi;
    // ppm image buffer
    vector<string> imageBuffer;
    // plain pixel buffer
    vector<vector<unsigned char>> imagePixelBuffer;

    color rayColor(ray r, hittableList &world);
    renderer(int width, int height, int anti);
    bool render();
    bool renderByThread(int threadId);
    void write_color(std::string &s, color pixel_color, int sampleNum, vector<unsigned char> &pixelBuffer);
    bool exportImage(int type, string name);
    bool exportPPM();
    bool exportPNG();

    bool clearImageData();
};
