//
// Created by najimac on 4/26/20.
//

#include "client/audio/AudioManager.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <cstdio>
#include <cstring>
#include <string>

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

bool AudioManager::CheckErrors() {
    error = alGetError();
    if (error != AL_NO_ERROR) {
        printf("OpenAL error %s!\n", openAlErrorToString(error).c_str());
        return true;
    }
    return false;
}
void AudioManager::Init() {
    printf("Opening audio device.\n");
    device = alcOpenDevice(NULL);
    if (!device) {
        printf("Failed to initialize audio devices.\n");
    }
    CheckErrors();
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
    CheckErrors();
}
void AudioManager::Destroy() {
    // delete sources and buffers
    device = alcGetContextsDevice(audioContext);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(audioContext);
    alcCloseDevice(device);
}