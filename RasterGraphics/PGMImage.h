#pragma once
#include "Vector.hpp"
#include "Image.h"
#include <vector>

class PGMImage : public Image {
private:
	int maxValue = 15;
	Vector<Vector<int>> pixels;

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

