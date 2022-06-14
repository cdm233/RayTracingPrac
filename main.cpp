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
#include "sphere.h"

// image
int imageWidth;
int imageHeight;
double aspectRatio = 16.0 / 9.0;
int antiAliasingConf = 10;
string imageName = "out";

// Camera
camera *cam = nullptr;

// World
hittableList world;


// Renderer
renderer *g = nullptr;

int main(int argc, char *argv[]) {
    /**
     * argument list:
     *      NULL ImageHeight
     *      NULL ImageHeight AntiAliasingConf
     *      NULL ImageHeight ImageWidth AntiAliasingConf
     *      NULL ImageHeight ImageWidth AntiAliasingConf ImageName
     *
     */
    // argument list: NULL ImageHeight AntiAliasingConf

    if (argc == 2) {
        imageHeight = atoi(argv[1]);
        imageWidth = imageHeight * aspectRatio;
    } else if (argc == 3) {
        imageHeight = atoi(argv[1]);
        imageWidth = imageHeight * aspectRatio;
        antiAliasingConf = atoi(argv[2]);
        antiAliasingConf = antiAliasingConf == 0 ? 1 : antiAliasingConf;
    } else if (argc == 4) {
        imageHeight = atoi(argv[1]);
        imageWidth = atoi(argv[2]);
        antiAliasingConf = atoi(argv[3]);
        antiAliasingConf = antiAliasingConf == 0 ? 1 : antiAliasingConf;
        aspectRatio = imageWidth / imageHeight;
    } else if (argc == 5) {
        imageHeight = atoi(argv[1]);
        imageWidth = atoi(argv[2]);
        antiAliasingConf = atoi(argv[3]);
        imageName = argv[4];
        antiAliasingConf = antiAliasingConf == 0 ? 1 : antiAliasingConf;
        aspectRatio = imageWidth / imageHeight;
    } else {
        imageHeight = 540;
        imageWidth = imageHeight * aspectRatio;
    }
    cout << imageWidth << " " << imageHeight << " " << antiAliasingConf << endl;

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
    cerr << "Render begins, using " << g->threadCount << " threads...\n" << std::endl;

    g->render();

    cerr << "\nRender finished, writing image..." << std::endl;

    g->exportImage(1, imageName);

    auto end = std::chrono::high_resolution_clock::now();
    auto wall = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    cerr << "Program Finished. Run time: " << wall.count() << "s\n";

    return 0;
}