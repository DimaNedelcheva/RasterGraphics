#include "PGMImage.hpp"
#include <fstream>
#include <vector>
#include <iostream>

void PGMImage::load(std::istream& in) {
	std::string magic;
	in >> magic;

	in >> width >> height;
	in >> maxValue;

	pixels.resize(height, std::vector<int>(width));

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			in >> pixels[i][j];
		}
	}
}

void PGMImage::save(std::ostream& out) const {
	out << "P2\n";
	out << width << " " << height << "\n";
	out << maxValue << "\n";

	for (const auto& row : pixels)
	{
		for (const auto& p : row)
		{
			out << p << " ";
		}

		out << '\n';
	}
}