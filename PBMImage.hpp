#pragma once
#include "Image.hpp"
#include <fstream>
#include <vector>

class PBMImage : public Image {
private:
	std::vector<std::vector<int>> pixels;

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