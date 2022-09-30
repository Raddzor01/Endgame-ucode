#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

typedef struct s_time {
    uint32_t StartTicks;
	uint32_t PausedTicks;
	bool Paused;
	bool Started;
} t_time;

void start(t_time **time);
void stop(t_time **time);
void pause(t_time **time);
void unpause(t_time **time);
uint32_t getTicks(t_time *time);
