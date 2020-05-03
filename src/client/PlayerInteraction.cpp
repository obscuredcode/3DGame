//
// Created by najimac on 4/24/20.
//

#include "client/Game.h"
#include "PlayerInteraction.h"
#include <thread>
#include <math.h>
typedef glm::vec3 vec3 ;

float MAX_ROT_X = 360;
float MAX_HEAD_PITCH = 90;
int Center_mx;
int Center_my;

void PlayerInteraction::MouseUpdate() {
    int mx,my;
    SDL_GetMouseState(&mx,&my);
    float dphi = (mx-lastMouseX ) * 0.4f;
    float dtheta = -(my-lastMouseY) * 0.4f;
    float rotationY = player->GetRotationVec3().y;
    float headPitch = player->GetHeadPitch();
    rotationY += dphi;
    headPitch += dtheta;
    Center_mx = Game::GetInstance()->displayManager.GetWidth()/2;
    Center_my = Game::GetInstance()->displayManager.GetHeight()/2;
    //if(rotationY > MAX_ROT_X) {SDL_WarpMouseInWindow(Game::GetInstance()->displayManager.GetMainWindow(),Center_mx,Center_my);}
    //if(rotationY < 0) {rotationY += 360; SDL_WarpMouseInWindow(Game::GetInstance()->displayManager.GetMainWindow(),Center_mx,Center_my);}
    //if(mx < 0 || my < 0) SDL_WarpMouseInWindow(Game::GetInstance()->displayManager.GetMainWindow(),Center_mx,Center_my);
    if(headPitch > MAX_HEAD_PITCH) {
        headPitch = 90;
        rotationY = 270;
    }
    if(headPitch < -MAX_HEAD_PITCH) headPitch = 0;
    player->SetRotation(std::fmod(rotationY+360,360));
    player->SetHeadPitch(headPitch);

    SDL_GetMouseState(&lastMouseX,&lastMouseY);
    //lastMouseX = mx;
    //lastMouseY = my;
}

void PlayerInteraction::CheckKeys() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]) {
        player->SetSpeed(player->maxSpeed);
    } else if(state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]) {
        player->SetSpeed(-player->maxSpeed);
    } else  if(state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) {
        player->SetSpeedStrafe(player->maxSpeedStrafe);
    } else if(state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) {
        player->SetSpeedStrafe(-player->maxSpeedStrafe);
    } else if(state[SDL_SCANCODE_P]) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    } else {
        player->SetSpeed(0);
        player->SetSpeedStrafe(0);
    }
}
void PlayerInteraction::KeyDown(SDL_KeyboardEvent keyEvent) {
    switch(keyEvent.keysym.sym) {
/*        case SDLK_w:
            player->SetSpeed(player->maxSpeed);
            break;
        case SDLK_s:
            player->SetSpeed(-player->maxSpeed);
            break;
        case SDLK_UP:
            player->SetSpeed(player->maxSpeed);
            break;
        case SDLK_DOWN:
            player->SetSpeed(-player->maxSpeed);
            break;
        case SDLK_d:
            player->SetSpeedStrafe(player->maxSpeedStrafe);
            break;
        case SDLK_a:
            player->SetSpeedStrafe(-player->maxSpeedStrafe);
            break;
        case SDLK_RIGHT:
            player->SetSpeedStrafe(player->maxSpeedStrafe);
            break;
        case SDLK_LEFT:
            player->SetSpeedStrafe(-player->maxSpeedStrafe);
            break;*/
    }
}

void PlayerInteraction::KeyUp(SDL_KeyboardEvent keyEvent) {
    switch(keyEvent.keysym.sym) {
/*        case SDLK_w:
            player->SetSpeed(0);
            break;
        case SDLK_s:
            player->SetSpeed(0);
            break;
        case SDLK_UP:
            player->SetSpeed(0);
            break;
        case SDLK_DOWN:
            player->SetSpeed(0);
        case SDLK_d:
            player->SetSpeedStrafe(0);
            break;
        case SDLK_a:
            player->SetSpeedStrafe(0);
            break;
        case SDLK_RIGHT:
            player->SetSpeedStrafe(0);
            break;
        case SDLK_LEFT:
            player->SetSpeedStrafe(0);
            break;*/
        case SDLK_MINUS:
            player->FoV -= 2.0f; break;
        case SDLK_EQUALS:
            player->FoV += 2.0f; break;
        case SDLK_c:
            thirdPersonView = not thirdPersonView; break;
        case SDLK_q:
            Game::GetInstance()->Kill();
    }
}
