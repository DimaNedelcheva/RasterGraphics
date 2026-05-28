#include "PBMImage.h"
#include <fstream>
#include <vector>
#include <iostream>

void PBMImage::load(std::istream& in) {
	std::string magic;
	in >> magic;

	in >> width >> height;

	pixels = Vector<Vector<int>>();
	pixels.resize(height, Vector<int>(width, 0));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			in >> pixels[i][j];
		}
	}
}

void PBMImage::save(std::ostream& out) const {
	out << "P1\n";
	out << width << " " << height << "\n";

	for (const Vector<int>& row : pixels) {
		for (const int& p : row) {
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
	for (Vector<int>& row : pixels) {
		for (int& p : row) {
			p = 1 - p;
		}
	}
}

void PBMImage::rotateLeft() {
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

void PBMImage::rotateRight() {
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

Image* PBMImage::collageHorizontal(const Image* other) const {
	const PBMImage* rhs = dynamic_cast<const PBMImage*>(other);

	if (!rhs) {
		return nullptr;
	}

	if (height != rhs->height) {
		return nullptr;
	}

	PBMImage* result = new PBMImage;

	result->width = width + rhs->width;
	result->height = height;

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


Image* PBMImage::collageVertical(const Image* other) const {
	const PBMImage* rhs = dynamic_cast<const PBMImage*>(other);

	if (!rhs) {
		return nullptr;
	}

	if (width != rhs->width) {
		return nullptr;
	}

	PBMImage* result = new PBMImage;

	result->width = width;
	result->height = height + rhs->height;

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

Image* PBMImage::clone() const {
	return new PBMImage(*this);
}