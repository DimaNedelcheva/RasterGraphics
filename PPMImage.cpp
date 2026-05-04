#include "PPMImage.hpp"
#include <iostream>
#include <fstream>
#include <vector>

void PPMImage::load(std::istream& in) {
	std::string magic;
	in >> magic;

	in >> width >> height;

	pixels.resize(height, std::vector<RGB>(width));

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			in >> pixels[i][j].r
				>> pixels[i][j].g
				>> pixels[i][j].b;
		}
	}
}

void PPMImage::save(std::ostream& out) const {
	out << "P3\n";
	out << width << " " << height << "\n";
	out << maxValue << "\n";

	for (const auto& row : pixels) {
		for (const auto& p : row) {
			out << p.r << " " << p.g << " " << p.b << " ";
		}
	}
	out << "\n";
}

void PPMImage::grayscale() {
	for (auto& row : pixels) {
		for (auto& p : row)
		{
			int gray = static_cast<int>(0.299 * p.r + 0.587 * p.g + 0.114 * p.b);
			
			p.r = p.g = p.b = gray;
		}
	}
}