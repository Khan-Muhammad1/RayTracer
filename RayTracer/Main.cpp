#include <iostream>
#include "Parser.h"
#include "RayTracer.h"
#include "ppm.h"
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: raytracer.exe <input_file>" << std::endl;
        return 1;
    }

    // parse input file
    Scene scene = parseInputFile(argv[1]);

    // image buffer
    std::vector<std::vector<Color>> image(scene.resY, std::vector<Color>(scene.resX));

    // precompute camera parameters
    float pixelWidth = (scene.right - scene.left) / scene.resX;
    float pixelHeight = (scene.top - scene.bottom) / scene.resY;
    Vector3 cameraPos(0, 0, 0);

    // ray tracing loop
    for (int y = 0; y < scene.resY; ++y) {
        float py = scene.top - pixelHeight * (y + 0.5f);
        for (int x = 0; x < scene.resX; ++x) {
            float px = scene.left + pixelWidth * (x + 0.5f);

            Vector3 pixelPos(px, py, -scene.nearPlane);
            Vector3 rayDir = pixelPos - cameraPos;
            rayDir.normalize();
            Ray ray(cameraPos, rayDir);

            Color color = traceRay(ray, scene, 0);
            image[y][x] = color;
        }
        
    }

    // prepare pixel data
    unsigned char* pixels = new unsigned char[3 * scene.resX * scene.resY];
    for (int y = 0; y < scene.resY; ++y) {
        for (int x = 0; x < scene.resX; ++x) {
            int index = ((scene.resY - y - 1) * scene.resX + x) * 3; // Flip vertically
            Color& color = image[y][x];
            pixels[index] = static_cast<unsigned char>(color.r * 255);
            pixels[index + 1] = static_cast<unsigned char>(color.g * 255);
            pixels[index + 2] = static_cast<unsigned char>(color.b * 255);
        }
    }

    // P6 for binary output
    save_imageP6(scene.resX, scene.resY, scene.outputFileName.c_str(), pixels);

    // clean up
    delete[] pixels;

    std::cout << "Rendering complete. Image saved to " << scene.outputFileName << std::endl;

    return 0;
}
