//
// Created by mac on 4/26/20.
//

#include "client/audio/AudioManager.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

// credit: https://stackoverflow.com/users/28411/rjfalconer
std::string openAlErrorToString(int err) {
    switch (err) {
        case AL_NO_ERROR:
            return "AL_NO_ERROR";
            //    case AL_INVALID_DEVICE: return "AL_INVALID_DEVICE";
            //    case AL_INVALID_CONTEXT: return "AL_INVALID_CONTEXT";
        case AL_INVALID_ENUM:
            return "AL_INVALID_ENUM";
        case AL_INVALID_OPERATION:
            return "AL_INVALID_OPERATION";
        case AL_INVALID_VALUE:
            return "AL_INVALID_VALUE";
        case AL_OUT_OF_MEMORY:
            return "AL_OUT_OF_MEMORY";
            /* ... */
        default:
            char s[32];
            sprintf(s, "Unknown error code %d", err);
            return s;
    }
}
// https://ffainelli.github.io/openal-example/
static void list_audio_devices(const ALCchar *devices)
{
    const ALCchar *device = devices, *next = devices + 1;
    size_t len = 0;
    fprintf(stdout, "Devices list:\n");
    fprintf(stdout, "----------\n");
    while (device && *device != '\0' && next && *next != '\0') {
        fprintf(stdout, "%s\n", device);
        len = strlen(device);
        device += (len + 1);
        next += (len + 2);
    }
    fprintf(stdout, "----------\n");
}

ALCenum error;
ALCdevice  *device;
ALCcontext  *audioContext;

bool AudioManager::CheckErrors(const char* source) {
    error = alGetError();
    if (error != AL_NO_ERROR) {
        printf("OpenAL error %s from %s!\n", openAlErrorToString(error).c_str(),source);
        return true;
    }
    return false;
}


ALuint buffer;

void AudioManager::Init() {
    printf("Opening audio device.\n");
    device = alcOpenDevice(NULL);
    if (!device) {
        printf("Failed to initialize audio devices.\n");
    }
    CheckErrors("initialization");

    ALboolean enumeration;
    enumeration = alcIsExtensionPresent(NULL,"ALC_ENUMERATION_EXT");
    if(enumeration == AL_FALSE) {
        printf("Enumeration of audio devices is not supported!\n");
    } else {
        printf("Enumerating audio devices.\n");
        list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
    }

    printf("Creating audio context.\n");
    audioContext = alcCreateContext(device,NULL);
    if(!alcMakeContextCurrent(audioContext))
        printf("Failed to make audio context current!\n");
    CheckErrors("audio context");

    //alGenBuffers(1,&buffer);
    buffer = alutCreateBufferHelloWorld();
    CheckErrors("audio buffer");

}
void AudioManager::LoadWav(std::string name) {
    std::filesystem::path v = res;
    char s[256];
    sprintf(s,"/res/sound/%s.wav",name.c_str());
    std::filesystem::path path = v.concat(s);
    printf("loaded %s.\n",path.c_str());
    buffer = alutCreateBufferFromFile(path.c_str());
    char c[128];
    sprintf(c,"loading wav %s",name.c_str());
    CheckErrors(c);
    printf("alut %s.\n",alutGetErrorString(alutGetError()));
}
void AudioManager::Listen(glm::vec3 position, glm::vec3 velocity, glm::vec3 up, glm::vec3 direction) {
    alListener3f(AL_POSITION,position.x,position.y,position.z);
    CheckErrors("listener position");
    alListener3f(AL_VELOCITY,velocity.x,velocity.y,velocity.z);
    CheckErrors("listener velocity");
    ALfloat orientation[] = {
            direction.x,direction.y,direction.z,
            up.x,up.y,up.z
    };
    alListenerfv(AL_ORIENTATION,orientation);
    CheckErrors("listener orientation");
    ALsizei size, freq;
    ALenum format;
    ALvoid *data;
    ALboolean loop = AL_FALSE;

}
//std::vector<ALuint> sources;
ALuint source;
void AudioManager::PlaySound(Sound sound) {

    alGenSources((ALuint)1, &source);
    CheckErrors("generating source");
    alSourcef(source, AL_PITCH, 1);
    CheckErrors("source pitch");
    alSourcef(source, AL_GAIN, 10);
    CheckErrors("source gain");
    alSource3f(source, AL_POSITION, sound.position.x, sound.position.y, sound.position.z);
    CheckErrors("source position");
    alSource3f(source, AL_VELOCITY, sound.velocity.x, sound.velocity.y, sound.velocity.z);
    CheckErrors("source velocity");
    alSourcei(source, AL_LOOPING, AL_FALSE);
    CheckErrors("source looping");
    alSourcei(source,AL_BUFFER,buffer);
    CheckErrors("binding source to buffer");
    alSourcePlay(source);
}
void AudioManager::Destroy() {
    // delete sources and buffers
    alDeleteSources(1,&source);
    alDeleteBuffers(1,&buffer);
    device = alcGetContextsDevice(audioContext);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(audioContext);
    alcCloseDevice(device);
    alutExit();
}