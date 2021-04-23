//
// Created by mac on 4/20/20.
//

#include "client/render/DisplayManager.h"
#include <iostream>
#define GL_GLEXT_PROTOTYPES

#include <SDL.h>
#include <SDL_opengl.h>

#include <stdio.h>
#include <client/Game.h>

SDL_Window* mainWindow;
SDL_GLContext context;
SDL_Surface* mainSurface;

void DisplayManager::Init() {
    Game::GetInstance()->ProfileStart("Setting Up SDL");
    /* First, initialize SDL's video subsystem. */
    if(GL_VERSION_3_2) printf("OPENGL 3.2\n");
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        /* Failed, exit. */
        fprintf( stderr, "Video initialization failed: %s\n",
                 SDL_GetError( ) );
    }
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 0 );
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,8);
    SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
    Game::GetInstance()->ProfileEnd("Setting Up SDL");

}
bool DisplayManager::CreateMainWindow(int width, int height,const char* name) { // return Frame?
    this->width = width;
    this->height = height;
    //Create window
    Game::GetInstance()->ProfileStart("Creating Window");
    mainWindow = SDL_CreateWindow( name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_OPENGL|SDL_WINDOW_ALWAYS_ON_TOP );
    if( mainWindow == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    SDL_SetWindowInputFocus(mainWindow);
    SDL_SetWindowResizable(mainWindow, SDL_TRUE );
    context = SDL_GL_CreateContext(mainWindow);
    Game::GetInstance()->ProfileEnd("Creating Window");
    //SDL_GL_MakeCurrent(mainWindow,context);
    //if( glewInit() != GLEW_OK ) printf("GLEW failed to initialize.\n");
    //if(GLEW_VERSION_3_2) printf("GLEW 3.2\n");
    mainSurface = SDL_GetWindowSurface(mainWindow);
    return true;
}
void DisplayManager::SetMainWindowFullScreen(bool fullscreen) {
    if(fullscreen) {
       // glfwSetWindowMonitor(mainWindow, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
}
void DisplayManager::DestroyMainWindow() {
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
}
int DisplayManager::WindowEventHandler(SDL_Event *event) {
    switch (event->window.event) {
        case SDL_WINDOWEVENT_RESIZED:
            SDL_GetWindowSize(SDL_GetWindowFromID(event->window.windowID),&this->width,&this->height); break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            GrabMouse();
            HideCursor(); break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            ReleaseMouse();
            ShowCursor(); break;
    }
}
void DisplayManager::HideCursor() {

    SDL_ShowCursor(SDL_FALSE);
}
void DisplayManager::ShowCursor() {
    SDL_ShowCursor(SDL_TRUE);
}
void DisplayManager::GrabMouse() {
    //SDL_CaptureMouse(SDL_TRUE);
}
void DisplayManager::ReleaseMouse() {
    SDL_CaptureMouse(SDL_FALSE);
}
bool DisplayManager::Update() {
    //glViewport(0,0,width,height);  // move to frame buffer
    SDL_GL_SwapWindow(mainWindow);
    //SDL_UpdateWindowSurface(mainWindow);

    return false;
}
int DisplayManager::GetWidth() {
    return this->width;
}
int DisplayManager::GetHeight() {
    return this->height;
}
void DisplayManager::SetTitle(char* text) {
    SDL_SetWindowTitle(mainWindow,text);
}