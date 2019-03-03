#pragma once

enum Message { NULL_MESSAGE, EXIT, MOVE_LEFT, MOVE_RIGHT, FLOOR_BOUND_COLLISION };

class Receiver {
public:
	virtual void receive(Message message) = 0;
};