#include <SDL3/SDL.h>
#include <ctime>

#include "game.h"

#ifdef _WIN32
int WinMain(int argc, const char* argv[]){
#else
int main(int argc, const char* argv[]){
#endif
    srand(static_cast<unsigned int>(time(NULL)));
    Game game;
    return 0;
}