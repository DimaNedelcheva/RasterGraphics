#pragma once
#include "SessionManager.h"

class CommandHandler {
private:
	SessionManager manager;

public:
	void run();
};