//
// Created by najimac on 4/20/20.
//

#include "client/Game.h"
#include <iostream>
#include <SDL_events.h>
#include "client/render/DisplayManager.h"
#include "client/render/RenderGame.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <PlayerInteraction.h>
#include <glm/gtx/projection.hpp>

using ms = std::chrono::milliseconds;
using hclock = std::chrono::high_resolution_clock;


RenderGame renderGame;


void Game::ProfileStart(std::string Name) {
    timeprofiles.insert(std::pair<std::string,hclock::time_point>(Name,hclock ::now()));
}
void Game::ProfileEnd(std::string Name) {
    hclock::time_point time = timeprofiles.find(Name)->second;
    hclock::duration dur = hclock::now() - timeprofiles[Name];
    if(std::chrono::duration_cast<ms>(dur).count() < 10) {
        printf("%s done in %li micros.\n", Name.c_str(),
               std::chrono::duration_cast<std::chrono::microseconds>(dur).count());
    } else {
        printf("%s done in %li ms.\n", Name.c_str(),
                std::chrono::duration_cast<ms>(dur).count());
    }
}
bool shouldClose = false;
void Game::Kill() {
    shouldClose = true;
}
static int WindowEvent(void* data, SDL_Event* event) {
    return ((DisplayManager*) data)->WindowEventHandler(event);
}
static Game* game = 0;
Game* Game::GetInstance() {
    if(game == 0) {
        game = new Game();
    }
    return game;
}



int Game::Init(std::filesystem::path wd) {
    timeprofiles.begin();
    WorkingDirectory = wd;
    ProfileStart("Initialization");
    ProfileStart("Setting Up Display");
    displayManager = DisplayManager();
    displayManager.Init();
    if(!displayManager.CreateMainWindow(800,600,"Game")) {
        printf("Failed to create window");
        return EXIT_FAILURE;
    }
    SDL_AddEventWatch(WindowEvent,&displayManager);
    //printf("Directory: %s\n",WorkingDirectory.c_str());
    ProfileEnd("Setting Up Display");
    ProfileStart("Initializing Physics");
    world.player = Player(&world,-5,0,-10);
    playerInteraction = PlayerInteraction(&world.player);
    ProfileEnd("Initializing Physics");
    ProfileStart("Building World");
    world.Create();
    ProfileEnd("Building World");
    ProfileStart("Initializing Renderer");
    renderGame = RenderGame(WorkingDirectory,&displayManager);
    renderGame.Init(&world);
    renderGame.view.viewerEntity = &world.player;
    ProfileEnd("Initializing Renderer");
    ProfileStart("Initializing Audio");
    audioManager.Init();
    ProfileEnd("Initializing Audio");
    ProfileEnd("Initialization");
    int frameCount = 0;
    int time = 0;
    int fps = 60;
    using clock = std::chrono::steady_clock;
    auto nextFrame = clock::now();
    std::chrono::duration<float> delta = ms(16);
    while(!shouldClose) {
        auto start = clock::now();
        nextFrame += ms(1000/fps);
        Update(fps,delta.count());
        std::this_thread::sleep_until(nextFrame);
        delta = std::chrono::duration_cast<ms>(clock::now()-start);
    }
    printf("Quitting.");
    renderGame.Destroy();
    audioManager.Destroy();
    displayManager.DestroyMainWindow();
    return EXIT_SUCCESS;
};
int i = 0;
void Game::Update(int fps, float delta) {
    SDL_Event event;
    if(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT: Kill(); break;
            case SDL_KEYDOWN:
                playerInteraction.KeyDown(event.key);
                renderGame.KeyDown(event.key); break;
            case SDL_KEYUP:
                playerInteraction.KeyUp(event.key); break;
        }
    }
    //SDL_PumpEvents();
    playerInteraction.CheckKeys();
    playerInteraction.MouseUpdate();
/*    world.playerAABB.Build(&world.player);
    if(world.playerAABB.IsIntersecting(&world.block3)) {
        glm::vec3 normal = glm::vec3(0,0,1);
        glm::vec3 speed = glm::vec3 (world.player.GetSpeedStrafe(),0,world.player.GetSpeed());
        glm::mat4 r =glm::rotate(glm::identity<glm::mat4>(),world.player.GetRotationVec3().y,glm::vec3(0,1,1));
        speed = glm::vec3(r*glm::vec4(speed,0));
        PrintVec3("Speed",speed);
        speed = speed - (normal * glm::dot(speed,normal));
        world.player.SetSpeed(-speed.z);
        world.player.SetSpeedStrafe(-speed.x);
        //world.player.SetSpeedStrafe(world.player.GetSpeed());
        //world.player.SetSpeed(0);
    }
    if(world.playerAABB.IsIntersecting(&world.block1)) {
        glm::vec3 normal = glm::vec3(1,0,0);
        glm::vec3 speed = glm::vec3 (world.player.GetSpeedStrafe(),0,world.player.GetSpeed());
        glm::mat4 r =glm::rotate(glm::identity<glm::mat4>(),world.player.GetRotationVec3().y,glm::vec3(0,1,1));
        speed = glm::vec3(r*glm::vec4(speed,0));
        PrintVec3("Speed",speed);
        speed = speed - (normal * glm::dot(speed,normal));
        world.player.SetSpeed(-speed.z);
        world.player.SetSpeedStrafe(-speed.x);
        //world.player.SetSpeedStrafe(world.player.GetSpeed());
       // world.player.SetSpeed(0);
    }*/
    world.Update(delta);
    renderGame.Render(fps,delta,&world);
}