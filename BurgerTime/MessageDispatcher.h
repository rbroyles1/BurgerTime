#pragma once
#include <vector>
#include "Receiver.h"

class Receiver;
enum Message { NULL_MESSAGE, EXIT, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN,
	INTERSECT_FLOOR, INTERSECT_LIMIT_LEFT, INTERSECT_LIMIT_RIGHT, INTERSECT_STAIRS, INTERSECT_UP_STAIRS, INTERSECT_DOWN_STAIRS,
	COUNT };

class MessageDispatcher {
	std::vector<Receiver*>* receivers;

public:
	MessageDispatcher();
	
	void subscribe(Message message, Receiver* receiver);
	void send(Message message);

	~MessageDispatcher();
};

