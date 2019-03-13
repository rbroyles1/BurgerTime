#pragma once
#include "MessageDispatcher.h"
#include <unordered_set>

enum Message;

class Receiver {
	std::unordered_set<Message>* receivedMessages;

public:
	Receiver();

	virtual void receive(Message message);

	bool hasReceived(Message message);
	void clearMessages();

	~Receiver();
};