#include "PBMImage.hpp"
#include <fstream>
#include <vector>
#include <iostream>

void PBMImage::load(std::istream& in) {
	std::string magic;
	in >> magic;

	in >> width >> height;

	pixels.resize(height, std::vector<int>(width));

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			in >> pixels[i][j];
		}
	}
}

void PBMImage::save(std::ostream& out) const {
	out << "P2\n";
	out << width << " " << height << "\n";

	for (const auto& row : pixels) {
		for (const auto& p : row) {
			out << p << " ";
		}

		out << '\n';
	}
}

void PBMImage::grayscale() {
	return;
}

void PBMImage::monochrome() {
	return;
}

void PBMImage::negative() {
	for (auto& row : pixels) {
		for (auto& p : row) {
			p = 1 - p;
		}
	}
}

void PBMImage::rotateLeft() {
	std::vector<std::vector<int>> result(width, std::vector<int>(height));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			result[width - j - 1][i] = pixels[i][j];
		}
	}

	pixels = result;
	std::swap(width, height);
}

void PBMImage::rotateRight() {
	std::vector<std::vector<int>> result(width, std::vector<int>(height));

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

Image* PBMImage::clone() const {
	return new PBMImage(*this);
}