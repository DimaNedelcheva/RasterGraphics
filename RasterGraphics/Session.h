#pragma once
#include "Vector.hpp"
#include "Image.h"

class Session {
private:
	int id;
	Vector<Image*> images;
	Vector<std::string> pendingTransforms;
	Vector<std::string> fileNames;

	void applyTransforms(Image* image);

public:
	Session(int id);
	Session(const Session& other) = delete;
	Session& operator=(const Session& other) = delete;
	~Session();
	int getId() const; 

	Image* getImageByName(const std::string& name) const;
	void addImage(Image*, const std::string& fileName);
	void addTransform(const std::string& transform);
	void undo();
	void save();
	void saveAs(const std::string& newFileName);
	void info() const;
};