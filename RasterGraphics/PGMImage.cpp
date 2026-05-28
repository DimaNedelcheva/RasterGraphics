#include "PGMImage.h"
#include <fstream>
#include <iostream>

void PGMImage::load(std::istream& in) {
	std::string magic;
	in >> magic;

	in >> width >> height;
	in >> maxValue;

	pixels = Vector<Vector<int>>();
	pixels.clear();
	pixels.resize(height, Vector<int>(width, 0));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			in >> pixels[i][j];
		}
	}
}

void PGMImage::save(std::ostream& out) const {
	out << "P2\n";
	out << width << " " << height << "\n";
	out << maxValue << "\n";

	for (const Vector<int>& row : pixels) {
		for (const int& p : row) {
			out << p << " ";
		}

		out << '\n';
	}
}

void PGMImage::grayscale() {
	return;
}

void PGMImage::monochrome() {
	for (Vector<int>& row : pixels) {
		for (int& p : row) {
			if (p > 7)
			{
				p = 15;
			}

			else
			{
				p = 0;
			}
		}
	}
}

void PGMImage::negative() {
	for (Vector<int>& row : pixels) {
		for (int& p : row) {
			p = maxValue - p;
		}
	}
}

void PGMImage::rotateLeft() {
	Vector<Vector<int>> result;

	result.resize(width, Vector<int>(height, 0));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			result[width - j - 1][i] = pixels[i][j];
		}
	}

	pixels = result;
	std::swap(width, height);
}

void PGMImage::rotateRight() {
	Vector<Vector<int>> result;

	result.resize(width, Vector<int>(height, 0));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			result[j][height - i - 1] = pixels[i][j];
		}
	}

	pixels = result;
	std::swap(width, height);
}

Image* PGMImage::collageHorizontal(const Image* other) const {
	const PGMImage* rhs = dynamic_cast<const PGMImage*>(other);

	if (!rhs) {
		return nullptr;
	}

	if (height != rhs->height) {
		return nullptr;
	}

	PGMImage* result = new PGMImage;

	result->width = width + rhs->width;
	result->height = height;
	result->maxValue = maxValue;

	result->pixels.resize(result->height, Vector<int>(result->width, 0));

	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {
			result->pixels[i][j] = pixels[i][j];
		}

		for (int j = 0; j < rhs->width; j++) {
			result->pixels[i][j + width] = rhs->pixels[i][j];
		}
	}

	return result;
}

Image* PGMImage::collageVertical(const Image* other) const {
	const PGMImage* rhs = dynamic_cast<const PGMImage*>(other);

	if (!rhs) {
		return nullptr;
	}

	if (width != rhs->width) {
		return nullptr;
	}

	PGMImage* result = new PGMImage;

	result->width = width;
	result->height = height + rhs->height;
	result->maxValue = maxValue;

	result->pixels.resize(result->height, Vector<int>(width, 0));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			result->pixels[i][j] = pixels[i][j];
		}
	}

	for (int i = 0; i < rhs->height; i++) {
		for (int j = 0; j < width; j++) {
			result->pixels[i + height][j] = rhs->pixels[i][j];
		}
	}

	return result;
}

Image* PGMImage::clone() const {
	return new PGMImage(*this);
}