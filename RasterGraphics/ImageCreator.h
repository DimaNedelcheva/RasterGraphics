#pragma once

#include <string>
#include "Image.h"

class ImageCreator {
public:
	static Image* createImage(const std::string& fileName);
};