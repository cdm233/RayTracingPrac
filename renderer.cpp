#include "renderer.h"

extern camera *cam;
extern hittableList world;

renderer::renderer(int width, int height, int anti) {
    imageWidth = width;
    imageHeight = height;
    antiAliasingConf = anti;
    threadCount = omp_get_max_threads();
    progress = vector<int>(threadCount, 0);
    totalProgress = 0;
    imageBuffer.resize(threadCount);
};

void renderer::render() {
// i is for horizontal, j is for vertical
#pragma omp parallel for
    for (int j = imageHeight - 1; j >= 0; --j) {
        int threadId = j / ((imageHeight) / threadCount);
        if (progress[threadId] == ((imageHeight) / threadCount) - 1) {
#pragma omp critical
            {
                totalProgress++;
                cerr << "Batch " << threadId << " done! " << threadCount - totalProgress << " batches left..." << endl;
            }
        }
        // int sum = std::accumulate(progress.begin(), progress.end(), 0);
        // double ratio = ((double)sum / (double)(imageHeight - 1)) * 100;
        // cerr << std::setprecision(3) << "\33[2K\r" << ratio << '%' << " done";

        progress[threadId]++;
        for (int i = 0; i < imageWidth; ++i) {
            color pixelColor(0, 0, 0);
            for (int c = 0; c < antiAliasingConf; c++) {
                double horizontalStep = (double)(i + random_double()) / (imageWidth - 1);
                double verticalStep = (double)(j + random_double()) / (imageHeight - 1);
                auto r = cam->getRay(horizontalStep, verticalStep);

                auto temp = rayColor(r, world);
                // cout << r.direction  << endl;
                pixelColor += temp;
            }
            write_color(imageBuffer[threadId], pixelColor, antiAliasingConf);
        }
    }
}

color renderer::rayColor(ray r, hittableList &world) {
    hitRecord temp;
    if (world.hit(r, 0, infinity, temp)) {
        return 0.5 * color(temp.normal.x() + 1, temp.normal.y() + 1, temp.normal.z() + 1);
    }
    // cout << "not hit" << endl;

    auto unitDir = unit_vector(r.direction);

    // the more tiled up, the more blue it gets
    // y ranges from -1 to 1, thus we offset it by 1.0 and normalize it back by 0.5
    auto modifier = (unitDir.y() + 1.0) * 0.5;

    // linear blend between white and blue
    return (1.0 - modifier) * color(1.0, 1.0, 1.0) + color(0.5, 0.7, 1.0) * modifier;
}

bool renderer::exportImage(int type, string name) {
    string fileName = name + ".ppm";
    // Open image file
    std::ofstream outImage;
    outImage.open(fileName);

    outImage << "P3\n"
             << imageWidth << ' ' << imageHeight << "\n255\n";

    // write to image
    for (auto it = imageBuffer.rbegin(); it != imageBuffer.rend(); it++) {
        outImage << *it;
    }

    // close file
    outImage.close();

    return true;
}

void renderer::write_color(std::string &s, color pixel_color, int sampleNum) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    r /= sampleNum;
    g /= sampleNum;
    b /= sampleNum;

    // cout << sampleNum << " ";

    s += std::to_string(static_cast<int>(255.999 * limit(r, 0.0, 0.999999))) + " " +
         std::to_string(static_cast<int>(255.999 * limit(g, 0.0, 0.999999))) + " " +
         std::to_string(static_cast<int>(255.999 * limit(b, 0.0, 0.999999)));
    s += "\n";
}
