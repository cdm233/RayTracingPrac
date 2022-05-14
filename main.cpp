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
#include "color.h"
#include "hittableList.h"
#include "sphere.h"
#include "utilities.h"

// image
int imageWidth;
int imageHeight;
double aspectRatio = 16.0 / 9.0;
int antiAliasingConf = 10;

// Camera
camera cam;

// world
hittableList world;

void antiAnliasing(color &color, int num, int i, int j);

color rayColor(ray r, hittableList &world) {
    hitRecord temp;
    if (world.hit(r, 0, infinity, temp)) {
        return 0.5 * color(temp.normal.x() + 1, temp.normal.y() + 1, temp.normal.z() + 1);
    }

    auto unitDir = unit_vector(r.direction);

    // the more tiled up, the more blue it gets
    // y ranges from -1 to 1, thus we offset it by 1.0 and normalize it back by 0.5
    auto modifier = (unitDir.y() + 1.0) * 0.5;

    // linear blend between white and blue
    return (1.0 - modifier) * color(1.0, 1.0, 1.0) + color(0.5, 0.7, 1.0) * modifier;
}

int main(int argc, char *argv[]) {
    // argument list: NULL ImageHeight AntiAliasingConf
    if (argc == 2) {
        imageHeight = atoi(argv[1]);
    } else if (argc == 3) {
        imageHeight = atoi(argv[1]);
        antiAliasingConf = atoi(argv[2]);
    } else {
        imageHeight = 540;
    }

    imageWidth = imageHeight * aspectRatio;

    // Create world
    world.add(make_shared<sphere>(point3d(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3d(0, -100.5, -1), 100));

    // Open image file
    std::ofstream outImage;
    outImage.open("out.ppm");

    outImage << "P3\n"
             << imageWidth << ' ' << imageHeight << "\n255\n";

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Render
    vector<int> progress(omp_get_max_threads(), 0);
    vector<string> parallelS(omp_get_max_threads());
    cerr << "Render begins, using " << parallelS.size() << " threads..." << std::endl;
#pragma omp parallel for
    // i is for horizontal, j is for vertical
    for (int j = imageHeight - 1; j >= 0; --j) {
        int threadId = j / ((imageHeight) / omp_get_max_threads());
        int sum = std::accumulate(progress.begin(), progress.end(), 0);
        cerr << std::setprecision(3) << "\33[2K\r" << ((double)sum / (double)(imageHeight - 1)) * 100 << ' ' << '%' << "done";

        progress[threadId]++;
        for (int i = 0; i < imageWidth; ++i) {
            color pixelColor(0, 0, 0);
            for (int c = 0; c < antiAliasingConf; c++) {
                double horizontalStep = (double)(i + random_double()) / (imageWidth - 1);
                double verticalStep = (double)(j + random_double()) / (imageHeight - 1);
                auto r = cam.getRay(horizontalStep, verticalStep);

                pixelColor += rayColor(r, world);
            }
            write_color(parallelS[threadId], pixelColor, antiAliasingConf);
        }
    }

    cerr << "\nRender finished, writing image..." << std::endl;

    // write to image
    for (auto it = parallelS.rbegin(); it != parallelS.rend(); it++) {
        outImage << *it;
    }

    // close file
    outImage.close();

    auto end = std::chrono::high_resolution_clock::now();
    auto wall = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    cerr << "Program Finished. Run time: " << wall.count() << "\n";
}