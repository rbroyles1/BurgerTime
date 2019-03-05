#pragma once
#include <vector>
#include "Receiver.h"

class Receiver;
enum Message { NULL_MESSAGE, EXIT, MOVE_LEFT, MOVE_RIGHT, FLOOR_BOUND_COLLISION, COUNT };

class MessageDispatcher {
	std::vector<Receiver*>* receivers;

public:
	MessageDispatcher();
	
	void subscribe(Message message, Receiver* receiver);
	void send(Message message);

	~MessageDispatcher();
};

