#pragma once

#include <SDL2/SDL_mixer.h>
#include <time.h>

void play_music();

Mix_Music **init_soundboard();

void free_soundboard(Mix_Music ***soundboard);
