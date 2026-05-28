#include "PPMImage.h"
#include <iostream>
#include <fstream>
#include <vector>

bool PPMImage::isGrayscale() const {
	for (const Vector<RGB>& row : pixels) {
		for (const RGB& p : row) {
			if (p.r != p.g || p.g != p.b) {
				return false;
			}
		}
	}

	return true;
}

void PPMImage::load(std::istream& in) {
	std::string magic;
	in >> magic;

	in >> width >> height;
	in >> maxValue;

	pixels = Vector<Vector<RGB>>();
	pixels.clear();
	pixels.resize(height, Vector<RGB>(width, RGB()));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
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

	for (const Vector<RGB>& row : pixels) {
		for (const RGB& p : row) {
			out << p.r << " " << p.g << " " << p.b << " ";
		}
	}
	out << "\n";
}

void PPMImage::grayscale() {
	if (isGrayscale()) {
		return;
	}

	for (Vector<RGB>& row : pixels) {
		for (RGB& p : row)
		{
			int gray = static_cast<int>(0.299 * p.r + 0.587 * p.g + 0.114 * p.b);
			
			p.r = p.g = p.b = gray;
		}
	}
}

void PPMImage::monochrome() {
	for (Vector<RGB>& row : pixels) {
		for (RGB& p : row) {
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
	for (Vector<RGB>& row : pixels) {
		for (RGB& p : row)
		{
			p.r = maxValue - p.r;
			p.g = maxValue - p.g;
			p.b = maxValue - p.b;
		}
	}
}

void PPMImage::rotateLeft() {
	Vector<Vector<RGB>> result;
	result.resize(width, Vector<RGB>(height, RGB()));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			result[width - j - 1][i] = pixels[i][j];
		}
	}
		
	pixels = result;
	std::swap(width, height);
}

void PPMImage::rotateRight() {
	Vector<Vector<RGB>> result;
	result.resize(width, Vector<RGB>(height, RGB()));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			result[j][height - i - 1] = pixels[i][j];
		}
	}

	pixels = result;
	std::swap(width, height);
}

Image* PPMImage::collageHorizontal(const Image* other) const {
	const PPMImage* rhs = dynamic_cast<const PPMImage*>(other);

	if (!rhs) {
		return nullptr;
	}

	if (height != rhs->height) {
		return nullptr;
	}

	PPMImage* result = new PPMImage;

	result->width = width + rhs->width;
	result->height = height;

	result->pixels.resize(result->height, Vector<RGB>(result->width, RGB()));

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

Image* PPMImage::collageVertical(const Image* other) const {
	const PPMImage* rhs = dynamic_cast<const PPMImage*>(other);

	if (!rhs) {
		return nullptr;
	}

	if (width != rhs->width) {
		return nullptr;
	}

	PPMImage* result = new PPMImage;

	result->width = width;
	result->height = height + rhs->height;

	result->pixels.resize(result->height, Vector<RGB>(result->width, RGB()));

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

Image* PPMImage::clone() const {
	return new PPMImage(*this);
}