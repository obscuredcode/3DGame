//
// Created by mac on 4/23/20.
//

#include <client/Game.h>
#include "entity/Player.h"

void Player::Update(float delta) {
    Entity::Update(delta);
    Game::GetInstance()->audioManager.Listen(position,GetVelocityVec3(),GetUpVec3(),GetDirectionVec3());
}
void Entity::Render(RenderCuboid* r) {
   // r->Render(position.x,position.y,position.z,0,0,0.5f,1,2,1,1,1,1);
}
