//
// Created by mac on 4/21/20.
//

#include <iostream>
#include "client/render/shader/StaticShader.h"
#include "client/render/RenderGame.h"
#include "client/render/model/CuboidModel.h"
#include "client/render/model/ObjModel.h"

#define GL_GLEXT_PROTOTYPES

#include <SDL.h>
#include <SDL_opengl.h>

#include <stdio.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <chrono>
#include <iomanip>
#include <math.h>
#include <client/render/tile/RenderCuboid.h>
#include <client/Game.h>
#include <unistd.h>
#include <client/View.h>
#include <client/render/RenderSky.h>
#include <physics/OBB.h>
#include <physics/AABB.h>
#include <client/render/RenderTerrain.h>

#define GL_GLEXT_PROTOTYPES

typedef float t_mat4x4[16];

static inline void mat4x4_ortho( t_mat4x4 out, float left, float right, float bottom, float top, float znear, float zfar )
{
#define T(a, b) (a * 4 + b)

    out[T(0,0)] = 2.0f / (right - left);
    out[T(0,1)] = 0.0f;
    out[T(0,2)] = 0.0f;
    out[T(0,3)] = 0.0f;

    out[T(1,1)] = 2.0f / (top - bottom);
    out[T(1,0)] = 0.0f;
    out[T(1,2)] = 0.0f;
    out[T(1,3)] = 0.0f;

    out[T(2,2)] = -2.0f / (zfar - znear);
    out[T(2,0)] = 0.0f;
    out[T(2,1)] = 0.0f;
    out[T(2,3)] = 0.0f;

    out[T(3,0)] = -(right + left) / (right - left);
    out[T(3,1)] = -(top + bottom) / (top - bottom);
    out[T(3,2)] = -(zfar + znear) / (zfar - znear);
    out[T(3,3)] = 1.0f;

#undef T
}

ObjModel* block;
ObjModel* tea;
TerrainMesh* terrainMesh;

RenderCuboid renderCuboid = RenderCuboid();
RenderCuboid renderTea = RenderCuboid();
RenderSky renderSky;
RenderTerrain renderTerrain;

StaticShader* terrainShader;
GLuint fbo;
GLuint rbo;

void RenderGame::Init(World* world) {
    Game::GetInstance()->ProfileStart("Shaders");
    shader = new StaticShader( res , "original","original");
    shader->Load();
    shader->Build(true);

    terrainShader = new StaticShader(res,"terrain","terrain");
    terrainShader->Load();
    terrainShader->Build(false);
    Game::GetInstance()->ProfileEnd("Shaders");
    glEnable(GL_CULL_FACE);
    //glEnable(GL_CLIP_PLANE0);
    //glEnable(GL_NORMALIZE);
   // glEnable(GL_DEPTH_CLAMP);

    glEnable( GL_DEPTH_TEST );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    Game::GetInstance()->ProfileStart("Loading Models");
    block = new ObjModel(res,"block");
    tea = new ObjModel(res,"teapot");
    renderCuboid = RenderCuboid(block);
    renderTea = RenderCuboid(tea);
    renderCuboid.Prepare();
    renderTea.Prepare();
    world->t = Tile(block);
    world->teapot = Tile(tea);
    terrainMesh = new TerrainMesh(res,"complex16");
    //terrainMesh->LoadModel();
    Game::GetInstance()->ProfileEnd("Loading Models");
    OBB obb = OBB();
    obb.Build(&world->t);
    Game::GetInstance()->ProfileStart("Loading Sky");
    renderSky = RenderSky(res,&view);
    renderSky.Init();
    Game::GetInstance()->ProfileEnd("Loading Sky");
    Game::GetInstance()->ProfileStart("Loading Terrain Renderer");
    renderTerrain = RenderTerrain(terrainMesh);
    renderTerrain.Prepare();
    Game::GetInstance()->ProfileEnd("Loading Terrain Renderer");
    //t_mat4x4 projection_matrix;
    //mat4x4_ortho( projection_matrix, (float)0, (float)600, (float)400, (float)0, 0.0f, 100.0f );
    //glUniformMatrix4fv( glGetUniformLocation(shader->GetShaderId(), "u_projection_matrix" ), 1, GL_FALSE, projection_matrix );
    //glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f),4.0f/3.0f,0.0f,100.0f);
    //glAttribute
    //glGenFramebuffers(1,&fbo);
    //glGenRenderbuffers(1,&rbo);
   // glBindFramebuffer(GL_FRAMEBUFFER,fbo);
   // if(glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    //    printf("Framebuffer not created!\n");
  //  glBindRenderbuffer(GL_RENDERBUFFER,rbo);
   // glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,displayManager->GetWidth(),displayManager->GetHeight());
  //  glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,rbo);
    // glBindBuffer(GL_ARRAY_BUFFER,0);
    // glBindVertexArray(0);

}

float amb = 0.4f;


int x = 0;
int y = 0;

void RenderGame::Render(int fps,float delta,World* world) {
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,displayManager->GetWidth(),displayManager->GetHeight());
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);  // move to frame buffer
    shader->Bind();
    glUniform1f(glGetUniformLocation(shader->GetShaderId(), "test" ),0);
    view.RenderCamera(displayManager,shader);
    renderCuboid.SetShader(shader);
    renderTea.SetShader(shader);
    glm::vec3 dir = glm::rotateY(view.viewerEntity->GetDirectionVec3(),glm::radians(view.viewerEntity->GetRotationVec3().y));
    glm::vec3 flash = view.viewerEntity->GetPositionVec3() + dir;
    shader->SetLight(flash.x,1,flash.z-5,amb,1,1,1);
    for(Tile tile : world->Tiles) {
        switch(tile.id) {
            case 0:
                renderCuboid.Render(tile, tile.color.x, tile.color.y, tile.color.z, tile.color.w); break;
            case 1:
                renderTea.Render(tile, tile.color.x, tile.color.y, tile.color.z, tile.color.w); break;
        }
    }

    shader->UnBind();
    renderSky.Render(fps,delta);
    terrainShader->Bind();
    renderTerrain.LoadShader(terrainShader);
    renderTerrain.Render(0,0,&view);
    terrainShader->UnBind();
    displayManager->Update();

    char s[256];
    sprintf(s,       "s per tick %.2f,fps %d,yaw %.2f,pitch %.2f,FoV %.2f, "
                     "x %.2f, z %.2f,width %d, height, %d, x %i, y %i\n"
            ,delta,fps,
            view.viewerEntity->GetRotationVec3().y,view.viewerEntity->GetHeadPitch(),view.viewerEntity->FoV,
            view.viewerEntity->GetPositionVec3().x,view.viewerEntity->GetPositionVec3().z,
            displayManager->GetWidth(),displayManager->GetHeight(),x, y);
    displayManager->SetTitle(s);
}

void RenderGame::KeyDown(SDL_KeyboardEvent e) {
    switch(e.keysym.sym) {
        case SDLK_RIGHTBRACKET:
            amb += 0.05;
            break;
        case SDLK_LEFTBRACKET:
            amb -= 0.05f;
            if (amb < 0) amb = 0.0f;
            break;
        case SDLK_y:
            terrainMesh->yv += 1; break;
        case SDLK_u:
            terrainMesh->yv -= 1; break;
        case SDLK_l:
            x += 1;
            terrainMesh->SetHeight(x,y,2); break;
        case SDLK_k:
            x -= 1;
            terrainMesh->SetHeight(x,y,2); break;
        case SDLK_PERIOD:
            y += 1;
            terrainMesh->SetHeight(x,y,2); break;
        case SDLK_COMMA:
            y -= 1;
            terrainMesh->SetHeight(x,y,2); break;
        case SDLK_ESCAPE:
            displayManager->ShowCursor();
            displayManager->ReleaseMouse();
            break;
    }
}
void RenderGame::Destroy() {
    shader->Destroy();
    renderSky.Destroy();
}