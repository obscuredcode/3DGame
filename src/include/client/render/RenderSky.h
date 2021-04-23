//
// Created by mac on 4/29/20.
//

#ifndef GAME_RENDERSKY_H
#define GAME_RENDERSKY_H


#include <client/View.h>

class RenderSky {
    std::filesystem::path res;
public:
    View* view;

    void Init();

    void Destroy();

    void Render(int fps,float delta);

    RenderSky(std::filesystem::path res,View* view) {
        this->res = res;
        this->view = view;
    };
    RenderSky() {};
};


#endif //GAME_RENDERSKY_H
