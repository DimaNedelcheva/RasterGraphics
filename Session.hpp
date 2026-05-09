#pragma once
#include <vector>
#include "Image.hpp"

class Session {
private:
	int id;
	std::vector<Image*> images;
	std::vector<std::string> pendingTransforms;
	std::vector<std::string> fileNames;

	void applyTransforms(Image* image);

public:
	Session(int id);
	~Session();
	int getId() const; 

	void addImage(Image*, const std::string& fileName);
	void addTransform(const std::string& transform);
	void undo();
	void save();
	void saveAs(const std::string& newFileName);
	void info() const;
};