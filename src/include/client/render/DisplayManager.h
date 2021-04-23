//
// Created by mac on 4/20/20.
//

#ifndef GAME_DISPLAYMANAGER_H
#define GAME_DISPLAYMANAGER_H

#include <SDL_events.h>

class DisplayManager {
    int width, height;
    SDL_Window* mainWindow;
public:
    void Init();
    bool CreateMainWindow(int width, int height,const char* name);
    void SetMainWindowFullScreen(bool fullscreen);
    void DestroyMainWindow();
    SDL_Window* GetMainWindow() {return mainWindow;}
    bool Update();
    void GrabMouse();
    void ReleaseMouse();
    void HideCursor();
    void ShowCursor();
    int WindowEventHandler(SDL_Event *event);
    int GetWidth();
    int GetHeight();
    void SetTitle(char* text);
};


#endif //GAME_DISPLAYMANAGER_H
