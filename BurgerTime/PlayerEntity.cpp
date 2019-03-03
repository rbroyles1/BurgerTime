#include "PlayerEntity.h"
#include "PlayerRenderComponent.h"
#include "PlayerRigidBodyComponent.h"

PlayerEntity::PlayerEntity(Engine * engine, Coordinate position) : Entity(engine, position) {
	PlayerRigidBodyComponent* rigidBodyComponent = new PlayerRigidBodyComponent(this->engine, this);
	PlayerRenderComponent* renderComponent = new PlayerRenderComponent(this->engine, this);
	
	this->addComponent(rigidBodyComponent);
	this->addComponent(renderComponent);

	this->addReceiver(rigidBodyComponent);
	this->addReceiver(renderComponent);
}

void PlayerEntity::receive(Message message) {
	this->send(message);

	if (message == FLOOR_BOUND_COLLISION) {
		SDL_Log("Collision!");
	}
}

PlayerEntity::~PlayerEntity() {

}
