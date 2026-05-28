#include "SessionManager.h"
#include <iostream>

SessionManager::~SessionManager() {
	for (Session* s : sessions) {
		delete s;
	}
}

int SessionManager::generateID() {
	return nextID++;
}

void SessionManager::addSession(Session* session) {
	sessions.push_back(session);
	currentSession = session;
}

Session* SessionManager::getCurrentSession() const {
	return currentSession;
}

void SessionManager::switchSession(int id) {
	for (Session* s : sessions) {
		if (s->getId() == id)
		{
			currentSession = s;

			std::cout << "You switched to session with ID: " << id << std::endl;

			return;
		}
	}

	std::cout << "No such session!\n";
}