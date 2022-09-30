#include "../inc/timer.h"

void start(t_time **time) {

    (* time)->Started = true;
    (* time)->Paused = false;

    (* time)->StartTicks = SDL_GetTicks();
    (* time)->PausedTicks = 0;

}

void stop(t_time **time) {

    (* time)->Started = false;
    (* time)->Paused = false;

    (* time)->StartTicks = 0;
    (* time)->PausedTicks = 0;

}

void pause(t_time **time) {
    if((* time)->Started && !(* time)->Paused) {

        (* time)->Paused = true;
        (* time)->PausedTicks = SDL_GetTicks() - (* time)->StartTicks;
        (* time)->StartTicks = 0;

    }
}

void unpause(t_time **time) {
    if ((* time)->Started && (* time)->Paused) {

        (* time)->Paused = false;
        (* time)->StartTicks = SDL_GetTicks() - (* time)->PausedTicks;
        (* time)->PausedTicks = 0;

    }
}

uint32_t getTicks(t_time *time) {
    if(time->Started) {
        if(time->Paused)
            return time->PausedTicks;
        else
            return SDL_GetTicks() - time->StartTicks;
    }
    return 0;
}
