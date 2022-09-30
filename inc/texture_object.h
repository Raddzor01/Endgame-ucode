#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

typedef enum TYPE_OBJECT {
    PLATFORM,
    DOOR,
    SPIKE
} e_type_object;

typedef struct s_render_object {
    SDL_Rect ObjectHitbox;
    SDL_Texture *ObjectTexture;
    e_type_object type_object;
} t_render_object;

void init_render_objects(t_render_object ***objects, SDL_Renderer *renderer, int key);

void init_render_object(t_render_object **map_object, SDL_Renderer *renderer, char *reference, int x, int y, int height, int weigth);

t_render_object **init_struct_render_objects (int size);

void free_render_object (t_render_object **texture_object);

void render_texture(t_render_object *object, SDL_Renderer *renderer, int x, int y, SDL_Rect clip, double angle, SDL_Point* center, SDL_RendererFlip flip );
