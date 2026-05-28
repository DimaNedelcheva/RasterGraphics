#include "CommandHandler.h"
#include "ImageCreator.h"
#include "Image.h"
#include <iostream>
#include <fstream>

void CommandHandler::run() {
	std::string command;

	while (true) {
		std::cout << "> ";

		std::cin >> command;

		if (command == "exit") {
			break;
		}

		else if (command == "load") {

			std::string fileName;

			Session* session = nullptr;
			bool hasImages = false;

			while (std::cin >> fileName) {

				if (fileName == "done") {
					break;
				}

				Image* image = ImageCreator::createImage(fileName);

				if (!image) {
					std::cout << "Cannot open file!" << std::endl;
					continue;
				}

				std::ifstream in(fileName);

				image->load(in);

				if (!session) {
					session = new Session(manager.generateID());
				}

				session->addImage(image, fileName);

				hasImages = true;

				std::cout << "Image \"" << fileName << "\" added" << std::endl;
			}

			if (!hasImages) {
				std::cout << "No images loaded!" << std::endl;
				delete session;
				continue;
			}

			manager.addSession(session);

			std::cout << "Session with ID: "
				<< session->getId()
				<< " started!"
				<< std::endl;
		}

		else if (command == "add") {
			std::string fileName;
			std::cin >> fileName;

			Session* current = manager.getCurrentSession();

			if (!current) {
				std::cout << "No active session!" << std::endl;
				continue;
			}

			Image* image = ImageCreator::createImage(fileName);

			if (!image) {
				std::cout << "Cannot open file!" << std::endl;
				continue;
			}

			std::ifstream in(fileName);

			image->load(in);

			current->addImage(image, fileName);

			std::cout << "Image \"" << fileName << "\" added" << std::endl;
		}

		else if (command == "grayscale") {
			Session* current = manager.getCurrentSession();

			if (current) {
				current->addTransform("grayscale");
				std::cout << "Transformation added" << std::endl;
			}
		}

		else if (command == "monochrome") {
			Session* current = manager.getCurrentSession();

			if (current) {
				current->addTransform("monochrome");
				std::cout << "Transformation added" << std::endl;
			}
		}

		else if (command == "negative") {
			Session* current = manager.getCurrentSession();

			if (current) {
				current->addTransform("negative");
				std::cout << "Transformation added" << std::endl;
			}
		}

		else if (command == "rotate") {
			std::string direction;
			std::cin >> direction;

			Session* current = manager.getCurrentSession();

			if (!current) {
				continue;
			}

			if (direction == "left") {
				current->addTransform("rotate left");
			}

			else if (direction == "right") {
				current->addTransform("rotate right");
			}

			std::cout << "Transformation added" << std::endl;
		}

		else if (command == "undo") {
			Session* current = manager.getCurrentSession();

			if (current) {
				current->undo();
			}
		}

		else if (command == "save") {
			Session* current = manager.getCurrentSession();

			if (current) {
				current->save();
			}
		}

		else if (command == "saveas") {
			std::string newName;

			std::cin >> newName;

			Session* current = manager.getCurrentSession();


			if (current) {
				current->saveAs(newName);
			}
		}

		else if (command == "session") {
			std::string second;

			std::cin >> second;

			if (second == "info") {
				Session* current = manager.getCurrentSession();

				if (current) {
					current->info();
				}
			}
		}

		else if (command == "switch") {
			int id;

			std::cin >> id;

			manager.switchSession(id);
		}

		else if (command == "collage") {
			std::string direction;
			std::string img1;
			std::string img2;
			std::string outName;

			std::cin >> direction >> img1 >> img2 >> outName;

			Session* current = manager.getCurrentSession();

			if (!current) {
				std::cout << "No active session!" << std::endl;
				continue;
			}

			Image* first = current->getImageByName(img1);
			Image* second = current->getImageByName(img2);

			if (!first || !second) {
				std::cout << "Images not found!" << std::endl;
				continue;
			}

			Image* result = nullptr;

			if (direction == "horizontal") {
				result = first->collageHorizontal(second);
			}

			else if (direction == "vertical") {
				result = first->collageVertical(second);
			}

			if (!result) {
				std::cout << "Cannot create collage!" << std::endl;
				continue;
			}

			current->addImage(result, outName);

			std::cout << "New collage \"" << outName << "\" created" << std::endl;
		}

		else if (command == "help") {
			std::cout << "Commands:\n";

			std::cout << "load\n";
			std::cout << "add\n";
			std::cout << "grayscale\n";
			std::cout << "monochrome\n";
			std::cout << "negative\n";
			std::cout << "rotate left/right\n";
			std::cout << "undo\n";
			std::cout << "save\n";
			std::cout << "saveas\n";
			std::cout << "switch\n";
			std::cout << "session info\n";
			std::cout << "collage\n";
			std::cout << "exit\n";
		}

		else {
			std::cout << "Unknown command" << std::endl;
		}
	}

}