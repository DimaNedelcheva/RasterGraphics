#include "ImageCreator.h"
#include "PPMImage.h"
#include "PGMImage.h"
#include "PBMImage.h"

#include <fstream>

Image* ImageCreator::createImage(const std::string& fileName) {
	std::ifstream in(fileName);

	if (!in.is_open()) {
		return nullptr;
	}

	std::string magic;

	in >> magic;

	if (magic == "P3") {
		return new PPMImage();
	}

	else if (magic == "P2") {
		return new PGMImage();
	}

	else if (magic == "P1") {
		return new PBMImage();
	}

	return nullptr;
}
