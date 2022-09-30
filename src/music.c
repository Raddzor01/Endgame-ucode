#include "../inc/music.h"

Mix_Music **soundboard;

void play_music() {
  soundboard = init_soundboard();
  srand(time(NULL));
  Mix_PlayMusic(soundboard[rand() % 3 + 1], 1);
}

Mix_Music **init_soundboard() {
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  soundboard = (Mix_Music **)malloc(sizeof(Mix_Music *) * 4);
  soundboard[0] = Mix_LoadMUS("./resource/music/menu_mus.mp3");
  soundboard[1] = Mix_LoadMUS("./resource/music/game_mus1.mp3");
  soundboard[2] = Mix_LoadMUS("./resource/music/game_mus2.mp3");
  soundboard[3] = Mix_LoadMUS("./resource/music/game_mus3.mp3");
  return soundboard;
}

void free_soundboard(Mix_Music ***soundboard) {
  for (int i = 0; i < 4; i++) {
    Mix_FreeMusic((* soundboard)[i]);
    (* soundboard)[i] = NULL;
  }
  free((* soundboard));
  (* soundboard) = NULL;
}
