//
// Created by mac on 4/24/20.
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

// http://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-a-physics-library/
void ScreenPosToWorldRay(
        int mouseX, int mouseY,             // Mouse position, in pixels, from bottom-left corner of the window
        int screenWidth, int screenHeight,  // Window size, in pixels
        glm::mat4 ViewMatrix,               // Camera position and orientation
        glm::mat4 ProjectionMatrix,         // Camera parameters (ratio, field of view, near and far planes)
        glm::vec3& out_origin,              // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
        glm::vec3& out_direction            // Ouput : Direction, in world space, of the ray that goes "through" the mouse.
){

    // The ray Start and End positions, in Normalized Device Coordinates (Have you read Tutorial 4 ?)
    glm::vec4 lRayStart_NDC(
            ((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
            ((float)mouseY/(float)screenHeight - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
            -1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
            1.0f
    );
    glm::vec4 lRayEnd_NDC(
            ((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f,
            ((float)mouseY/(float)screenHeight - 0.5f) * 2.0f,
            0.0,
            1.0f
    );


    // The Projection matrix goes from Camera Space to NDC.
    // So inverse(ProjectionMatrix) goes from NDC to Camera Space.
    glm::mat4 InverseProjectionMatrix = glm::inverse(ProjectionMatrix);

    // The View Matrix goes from World Space to Camera Space.
    // So inverse(ViewMatrix) goes from Camera Space to World Space.
    glm::mat4 InverseViewMatrix = glm::inverse(ViewMatrix);

    glm::vec4 lRayStart_camera = InverseProjectionMatrix * lRayStart_NDC;    lRayStart_camera/=lRayStart_camera.w;
    glm::vec4 lRayStart_world  = InverseViewMatrix       * lRayStart_camera; lRayStart_world /=lRayStart_world .w;
    glm::vec4 lRayEnd_camera   = InverseProjectionMatrix * lRayEnd_NDC;      lRayEnd_camera  /=lRayEnd_camera  .w;
    glm::vec4 lRayEnd_world    = InverseViewMatrix       * lRayEnd_camera;   lRayEnd_world   /=lRayEnd_world   .w;


    // Faster way (just one inverse)
    //glm::mat4 M = glm::inverse(ProjectionMatrix * ViewMatrix);
    //glm::vec4 lRayStart_world = M * lRayStart_NDC; lRayStart_world/=lRayStart_world.w;
    //glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ; lRayEnd_world  /=lRayEnd_world.w;


    glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
    lRayDir_world = glm::normalize(lRayDir_world);


    out_origin = glm::vec3(lRayStart_world);
    out_direction = glm::normalize(lRayDir_world);
}

bool ascending(const std::tuple<float,Tile*>& a,const std::tuple<float,Tile*>& b) {
    return std::get<0>(a) < std::get<0>(b);
}
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

    SDL_GetMouseState(&mx,&my);
    View* view = &Game::GetInstance()->renderGame.view;
    glm::vec3 out_origin;
    glm::vec3 out_direction;
    ScreenPosToWorldRay(mx,my, Center_mx * 2, Center_my * 2,
                        view->GetView(),view->GetProjection(),
                        out_origin,out_direction
    );
    for(int i = 0; i < player->world->Tiles.size(); i++) {
        float dis;
        if(player->world->Tiles[i].bb.TestRayOBBIntersection(out_origin,out_direction,dis)) {
            if(dis < 10.0f && dis != 0.000000) {
                player->world->SetColor(i,1);
                //player->SelectedTiles.push_back(std::make_tuple(dis,&player->world->Tiles[i]));
            }
        } else {
            player->world->SetColor(i,0.5);
        }
    }
   // player->SelectedTiles.clear();

   // std::sort(player->SelectedTiles.front(),player->SelectedTiles.back(),ascending);
    //std::get<1>(player->SelectedTiles.back())->SetColor(1,0,0,1);
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
    }
}

void PlayerInteraction::KeyUp(SDL_KeyboardEvent keyEvent) {
    switch(keyEvent.keysym.sym) {
        case SDLK_MINUS:
            player->FoV -= 2.0f; break;
        case SDLK_EQUALS:
            player->FoV += 2.0f; break;
        case SDLK_c:
            thirdPersonView = not thirdPersonView; break;
        case SDLK_z:
            player->world->PlaySound(Sound(glm::vec3(0,0,0),glm::vec3(0,0,0))); break;
        case SDLK_m:
            int mx,my; SDL_GetMouseState(&mx,&my);
            SDL_SetWindowPosition(Game::GetInstance()->displayManager.GetMainWindow(),mx,my); break;
        case SDLK_q:
            Game::GetInstance()->Kill();
    }
}

void PlayerInteraction::MouseDown(SDL_MouseButtonEvent event) {
}
