#include <iostream>
#include <fstream>
#include "PPMImage.hpp"
#include "PGMImage.hpp"
#include "PBMImage.hpp"

int main() {

    std::ifstream input("image.pbm");

    if (!input.is_open()) {
        std::cout << "Cannot open file!\n";
        return 1;
    }

    PBMImage img;


    img.load(input);

    input.close();

    // реярнбе

    //img.grayscale();

    // img.monochrome();

    img.negative();

    img.rotateLeft();

    // img.rotateRight();

    std::ofstream output("result.pbm");

    if (!output.is_open()) {
        std::cout << "Cannot create output file!\n";
        return 1;
    }

    img.save(output);

    output.close();

    std::cout << "Done!\n";

    return 0;
}