#include "PPMImage.hpp"
#include <iostream>
#include <fstream>
#include <vector>

void PPMImage::load(std::istream& in) {
	std::string magic;
	in >> magic;

	in >> width >> height;
	in >> maxValue;

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

void PPMImage::monochrome() {
	for (auto& row : pixels) {
		for (auto& p : row) {
			int gray = static_cast<int>(0.299 * p.r + 0.587 * p.g + 0.114 * p.b);

			if (gray > 127)
			{
				p.r = p.g = p.b = 255;
			}

			else
			{
				p.r = p.g = p.b = 0;
			}
		}
	}
}

void PPMImage::negative() {
	for (auto& row : pixels) {
		for (auto& p : row)
		{
			p.r = maxValue - p.r;
			p.g = maxValue - p.g;
			p.b = maxValue - p.b;
		}
	}
}

void PPMImage::rotateLeft() {
	std::vector<std::vector<RGB>> result(width, std::vector<RGB>(height));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			result[width - j - 1][i] = pixels[i][j];
		}
	}
		
	pixels = result;
	std::swap(width, height);
}

void PPMImage::rotateRight() {
	std::vector<std::vector<RGB>> result(width, std::vector<RGB>(height));

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			result[j][height - i - 1] = pixels[i][j];
		}
	}

	pixels = result;
	std::swap(width, height);
}

Image* PPMImage::clone() const {
	return new PPMImage(*this);
}