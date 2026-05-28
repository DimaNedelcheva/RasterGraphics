#pragma once
#include "Image.h"
#include "Vector.hpp"
#include <fstream>
#include <vector>


class PBMImage : public Image {
private:
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