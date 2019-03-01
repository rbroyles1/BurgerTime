#pragma once

enum Message { EXIT, MOVE_LEFT, MOVE_RIGHT };

class Receiver {
public:
	virtual void receive(Message message) = 0;
};