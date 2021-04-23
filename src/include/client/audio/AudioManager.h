//
// Created by mac on 4/26/20.
//

#ifndef GAME_AUDIOMANAGER_H
#define GAME_AUDIOMANAGER_H



#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <filesystem>
#include "Sound.h"

class AudioManager {
bool CheckErrors(const char* source);
    std::filesystem::path res;
public:
    void Init();
    void Destroy();
    void LoadWav(std::string name);
    void Listen(glm::vec3 position, glm::vec3 velocity, glm::vec3 up, glm::vec3 direction);

    void PlaySound(Sound sound);
    AudioManager() {

    }
    AudioManager(std::filesystem::path res)
    {
        this->res = res;
    }
};


#endif //GAME_AUDIOMANAGER_H
