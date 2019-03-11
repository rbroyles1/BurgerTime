#pragma once
#include <vector>
#include "Receiver.h"

class Receiver;
enum Message { NULL_MESSAGE, EXIT, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN,
	ON_FLOOR, ON_INGREDIENT_1, ON_INGREDIENT_2, ON_INGREDIENT_3, ON_INGREDIENT_4, INGREDIENT_ON_FLOOR, INGREDIENT_INGREDIENT_HIT,
	INTERSECT_LIMIT_LEFT, INTERSECT_LIMIT_RIGHT, INTERSECT_STAIRS, INTERSECT_UP_STAIRS, INTERSECT_DOWN_STAIRS,
	ENEMY_ATTACK,
	INGREDIENT_FLOOR_HIT, INGREDIENT_FINISHED, PLAYER_DIED, GAME_VICTORY,
	COUNT };

class MessageDispatcher {
	std::vector<Receiver*>* receivers;

public:
	MessageDispatcher();
	
	void subscribe(Message message, Receiver* receiver);
	void send(Message message);

	~MessageDispatcher();
};

