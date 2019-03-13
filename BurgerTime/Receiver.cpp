#include "Receiver.h"

Receiver::Receiver() {
	this->receivedMessages = new std::unordered_set<Message>();
}

void Receiver::receive(Message message) {
	this->receivedMessages->insert(message);
}

bool Receiver::hasReceived(Message message) {
	return this->receivedMessages->count(message) > 0;
}

void Receiver::clearMessages() {
	this->receivedMessages->clear();
}

Receiver::~Receiver() {
	delete this->receivedMessages;
}
