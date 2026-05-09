#include "Session.hpp"
#include <fstream>
#include <iostream>

Session::Session(int id) : id(id) {}

Session::~Session() {
	for (Image* img : images) {
		delete[] img;
	}
}

int Session::getId() const {
	return id;
}

void Session::addImage(Image* image, const std::string& filename) {
	images.push_back(image);
	fileNames.push_back(filename);
}

void Session::addTransform(const std::string& transform) {
	pendingTransforms.push_back(transform);
}

void Session::undo() {
	if (!pendingTransforms.empty()) {
		pendingTransforms.pop_back();
	}
}

void Session::applyTransforms(Image* image) {
	for (const std::string& t : pendingTransforms)
	{
		if (t == "grayscale") {
			image->grayscale();
		}

		else if (t == "monochrome") {
			image->monochrome();
		}

		else if (t == "negative") {
			image->negative();
		}

		else if (t == "rotate left") {
			image->rotateLeft();
		}

		else if (t == "rotate right") {
			image->rotateRight();
		}
	}
}

void Session::save() {
	for (size_t i = 0; i < images.size(); i++)
	{
		Image* copy = images[i]->clone();

		applyTransforms(copy);

		std::ofstream out(fileNames[i]);

		if (!out.is_open()) {
			std::cout << "Cannot save file!\n";
			delete copy;
			continue;
		}

		copy->save(out);

		delete copy;
	}
}

void Session::saveAs(const std::string& newFileName) {
	if (images.empty()) return;

	Image* copy = images[0]->clone();

	applyTransforms(copy);

	std::ofstream out(newFileName);

	if (!out.is_open()) {
		std::cout << "Cannot save file!\n";
		delete copy;
		return;
	}

	copy->save(out);

	delete copy;
}

void Session::info() const {
	std::cout << "Session ID: " << id << std::endl;
	std::cout << "Images: " << std::endl;

	for (const auto& name : fileNames) {
		std::cout << name << std::endl;
	}

	std::cout << "Pending transformations:\n";

	for (const auto& t : pendingTransforms) {
		std::cout << t << std::endl;
	}
}