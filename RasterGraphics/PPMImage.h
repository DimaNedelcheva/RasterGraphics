#pragma once
#include "Image.h"
#include "Vector.hpp"
#include <iostream>
#include <fstream>

struct RGB {
	int r = 0;
	int g = 0;
	int b = 0;
};

class PPMImage : public Image {
private:
	int maxValue = 255;
	Vector<Vector<RGB>> pixels;

	bool isGrayscale() const;
public:
	void load(std::istream& in) override;
	void save(std::ostream& out) const override;

	void grayscale() override;
	void monochrome() override;
	void negative() override;
	void rotateLeft() override;
	void rotateRight() override;
	Image* collageHorizontal(const Image* other) const override;
	Image* collageVertical(const Image* other) const override;

	Image* clone() const override;
};

