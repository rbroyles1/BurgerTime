#include "MessageDispatcher.h"

MessageDispatcher::MessageDispatcher() {
	this->receivers = new std::vector<Receiver*>[Message::COUNT]();
}

void MessageDispatcher::subscribe(Message message, Receiver * receiver) {
	this->receivers[message].push_back(receiver);
}

void MessageDispatcher::send(Message message) {
	for (Receiver* receiver : this->receivers[message]) {
		receiver->receive(message);
	}
}

MessageDispatcher::~MessageDispatcher() {
	delete[] this->receivers;
}