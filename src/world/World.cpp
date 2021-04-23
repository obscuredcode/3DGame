//
// Created by mac on 5/2/20.
//

#include <world/World.h>
#include <client/Game.h>

void World::Create() {
    //OBB staticOBB;
    t.solid = true;
    t.Create(0,-10,0,-5,90,0,5,3,0.2);
    t.SetColor(0.5f,0.0f,0.0f,0.5f);
    t.BuildOBB();
    Tiles.push_back(t);

    t.Create(0,0,0,-5,90,0,5,3,0.2);
    t.SetColor(0.0f,0.5f,0.0f,0.5f);
    t.BuildOBB();
    Tiles.push_back(t);

    t.Create(0,-5,0,0,0,0,5,3,0.2);
    t.SetColor(0.0f,0.0f,0.5f,0.5f);
    t.BuildOBB();
    Tiles.push_back(t);

    teapot.solid = false;
    teapot.Create(1,-15,-2,-5,0,0,1.0f,1.0f,1.0f);
    teapot.SetColor(1,1,1,1);
    Tiles.push_back(teapot);

    //t.Create(0,-5,-3,3,0,0,1000,0.1,1000);
    //t.SetColor(0.75f,0.75f,0.75f,1.0f);
    //Tiles.push_back(t);
}
void World::Update(float delta) {
    player.Update(delta);
}
void World::PlaySound(Sound sound) {
    Game::GetInstance()->audioManager.PlaySound(sound);
}