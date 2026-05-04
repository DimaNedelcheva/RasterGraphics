#pragma once
#include <iostream>
#include <fstream>

class Image {
protected:
	int width;
	int height;

public:
	virtual ~Image() = default;

	virtual void load(std::istream&) = 0;
	virtual void save(std::ostream&) const = 0;

	virtual void grayscale() = 0;
	virtual void monochrome() = 0;
	virtual void negative() = 0;
	virtual void rotateLeft() = 0;
	virtual void rotateRight() = 0;

	virtual Image* clone() const = 0;

	int getWidth() const {
		return width;
	}

	int getHeigth() const {
		return height;
	}
};