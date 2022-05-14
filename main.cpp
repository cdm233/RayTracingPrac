#include <iostream>

#include "camera.h"
#include "color.h"
#include "hittableList.h"
#include "sphere.h"
#include "utilities.h"

#define ANTIALIASINGCONFIG 10

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
    // Image
    const double aspectRatio = 9.0 / 16.0;
    const int imageWidth = 1920;
    const int imageHeight = imageWidth * aspectRatio;

    // Camera
    camera cam;

    // world
    hittableList world;
    world.add(make_shared<sphere>(point3d(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3d(0, -100.5, -1), 100));

    // Render
    std::cout << "P3\n"
              << imageWidth << ' ' << imageHeight << "\n255\n";

    // i is for horizontal, j is for vertical
    for (int j = imageHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            color pixelColor(0, 0, 0);
            for (int c = 0; c < ANTIALIASINGCONFIG; c++) {
                double horizontalStep = (double)(i + random_double()) / (imageWidth - 1);
                double verticalStep = (double)(j + random_double()) / (imageHeight - 1);
                auto r = cam.getRay(horizontalStep, verticalStep);

                pixelColor += rayColor(r, world);
            }
            write_color(std::cout, pixelColor, ANTIALIASINGCONFIG);
        }
    }

    std::cerr << "\nDone.\n";
}