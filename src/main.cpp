#include <SDL3/SDL.h>

#include "game.h"

#ifdef _WIN32
int WinMain(int argc, const char* argv[]){
#else
int main(int argc, const char* argv[]){
#endif
    Game game;
    return 0;
}