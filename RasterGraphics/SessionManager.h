#pragma once
#include "Session.h"
#include <vector>

class SessionManager {
private:
	Vector<Session*> sessions;
	Session* currentSession = nullptr;
	int nextID = 1;

public:
	SessionManager() = default;
	SessionManager(const SessionManager&) = delete;
	SessionManager& operator=(const SessionManager&) = delete;
	~SessionManager();

	void addSession(Session* session);
	Session* getCurrentSession() const;
	void switchSession(int id);
	int generateID();
};

