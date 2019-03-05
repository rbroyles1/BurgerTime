#pragma once
#include "MessageDispatcher.h"

enum Message;

class Receiver {
public:
	virtual void receive(Message message) = 0;
};