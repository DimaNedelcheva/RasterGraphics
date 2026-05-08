#pragma once
#include "Image.hpp"
#include <vector>

class PGMImage : public Image {
private:
	int maxValue = 15;
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

