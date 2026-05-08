#include <iostream>
#include <fstream>
#include "PPMImage.hpp"

int main() {

    std::ifstream input("image.ppm");

    if (!input.is_open()) {
        std::cout << "Cannot open file!\n";
        return 1;
    }

    PPMImage img;

    img.load(input);

    input.close();

    // реярнбе

    //img.grayscale();

    // img.monochrome();

    img.negative();

    // img.rotateLeft();

    // img.rotateRight();

    std::ofstream output("result.ppm");

    if (!output.is_open()) {
        std::cout << "Cannot create output file!\n";
        return 1;
    }

    img.save(output);

    output.close();

    std::cout << "Done!\n";

    return 0;
}