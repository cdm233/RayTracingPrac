#include <omp.h>

#include <atomic>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <thread>
#include <utility>
#include <vector>

#include "camera.h"
#include "renderer.h"
#include "settingLoader.h"
#include "sphere.h"

// image
int imageWidth;
int imageHeight;
double aspectRatio = 16.0 / 9.0;
int antiAliasingConf = 10;
string imageName = "out";
int outputType = 1;

// Camera
camera *cam = nullptr;

// World
hittableList world;

// Renderer
renderer *g = nullptr;

int main(int argc, char *argv[]) {
    settingLoader sLoader("./setting.ini");

    imageHeight = atoi(sLoader.getSetting("imageHeight").c_str());
    imageWidth = atoi(sLoader.getSetting("imageWidth").c_str());
    cout << sLoader.getSetting("antiAliasingConf") << endl;
    antiAliasingConf = atoi(sLoader.getSetting("AntiAliasingConf").c_str());
    imageName = sLoader.getSetting("outFileName");
    outputType = atoi(sLoader.getSetting("outputType").c_str());
    
    antiAliasingConf = antiAliasingConf == 0 ? 1 : antiAliasingConf;

    g = new renderer(imageWidth, imageHeight, antiAliasingConf);
    cam = new camera(imageWidth, imageHeight);

    // Create world
    world.add(make_shared<sphere>(point3d(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3d(-1, 0, -1), 0.5));

    // world.add(make_shared<sphere>(point3d(0.7, 0.7, -1), 0.3));
    // world.add(make_shared<sphere>(point3d(-0.7, 0.7, -1), 0.3));
    // world.add(make_shared<sphere>(point3d(0, -100.5, -1), 100));

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Render
    cerr << "Render begins, using " << g->threadCount << " threads...\n"
         << std::endl;

    g->render();

    cerr << "\nRender finished, writing image..." << std::endl;

    g->exportImage(outputType, imageName);

    auto end = std::chrono::high_resolution_clock::now();
    auto wall = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    cerr << "Program Finished. Run time: " << wall.count() << "s\n";

    return 0;
}