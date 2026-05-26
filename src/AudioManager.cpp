#include "AudioManager.h"

AudioManager::AudioManager() {
}

AudioManager::~AudioManager() {
    for (auto& pair : sounds) {
        if (pair.second) {
            Mix_FreeChunk(pair.second);
        }
    }
    
    for (auto& pair : music) {
        if (pair.second) {
            Mix_FreeMusic(pair.second);
        }
    }
    
    Mix_CloseAudio();
}

bool AudioManager::initialize() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        return false;
    }
    
    // Load sound effects and music here
    // loadSound("drop", "assets/sounds/drop.wav");
    // loadSound("lineClear", "assets/sounds/lineclear.wav");
    // loadMusic("bgm", "assets/sounds/bgm.ogg");
    
    return true;
}

void AudioManager::playSound(const std::string& soundName) {
    if (sounds.find(soundName) != sounds.end()) {
        Mix_PlayChannel(-1, sounds[soundName], 0);
    }
}

void AudioManager::playMusic(const std::string& musicName) {
    if (music.find(musicName) != music.end()) {
        Mix_PlayMusic(music[musicName], -1);
    }
}

void AudioManager::stopMusic() {
    Mix_HaltMusic();
}

void AudioManager::setVolume(int volume) {
    Mix_Volume(-1, volume);
}

bool AudioManager::loadSound(const std::string& name, const std::string& path) {
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if (chunk) {
        sounds[name] = chunk;
        return true;
    }
    return false;
}

bool AudioManager::loadMusic(const std::string& name, const std::string& path) {
    Mix_Music* mus = Mix_LoadMUS(path.c_str());
    if (mus) {
        music[name] = mus;
        return true;
    }
    return false;
}
