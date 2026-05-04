#pragma once
#include "Image.hpp"
#include <iostream>
#include <fstream>
#include <vector>

struct RGB {
	int r = 0;
	int g = 0;
	int b = 0;
};

class PPMImage : public Image {
private:
	int maxValue = 255;
	std::vector<std::vector<RGB>> pixels;

public:
	void load(std::istream& in) override;
	void save(std::ostream& out) const override;

	void grayscale() override;
	void monochrome() override;
	void negative() override;
	void rotateLeft() override;
	void rotateRight() override;

	Image* clone() const override;
};

