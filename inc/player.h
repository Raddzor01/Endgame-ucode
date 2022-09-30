#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../inc/texture_object.h"

typedef enum ACTION {
    IDLE,
    MOVING_LEFT,
    MOVING_RIGHT
} t_action;



typedef struct s_player {
    SDL_Rect player_pos;
    bool can_jump;
    SDL_Texture *player_texture;
    int velocityX, velocityY;
    t_action sprite;
    int death_count;
} t_player;

#define GRAVITY 1   // Zero in space, small value on Moon, big value on Jupiter
#define PLAYER_SPEED 10
#define PLAYER__JUMP_HIGH -20

void handleEvent(SDL_Event event, t_player **players);

void init_player(t_player **player, SDL_Renderer *renderer);

bool move(t_player **player, t_render_object **objects, int size, Mix_Chunk *died, Mix_Chunk *tuturu);

bool checkCollision(SDL_Rect a, SDL_Rect b);

void render_player(t_player *player, SDL_Renderer *renderer, int x, int y, SDL_Rect clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

bool check_collisions_spike(SDL_Rect a, t_render_object **objects, int size);
