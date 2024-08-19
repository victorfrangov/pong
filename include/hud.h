#ifndef HUD
#define HUD

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
// #include <string>

#include "globals.h"
#include "player.h"

class Graphics;
class Singleplayer;

enum Dash{
    DASH,
    NODASH,
};

struct HudItem {
    std::string text;
    Vector2f pos;
    Dash dash;
    float sizeScale = 1;
};

class Hud{
public:    
    Hud(Graphics &p_graphics);
    ~Hud();

    void draw(Menu p_menu, float p_fps, int p_elapsedTime);

    // void update();

    void renderText(const std::string& p_text, float p_x, float p_y, float p_texW, float p_texH);

    void renderMenu();

    void renderOptions();

    void renderFrameInfo(float p_fps, int p_elapsedTime);

    // void toggleFps();

    void renderPoints(Player* p_player);

    void renderLose();

    void renderSPOptions();

    void renderMPOptions();

    void handleKeyInput(SDL_Scancode p_key, Menu* p_menu = nullptr);

    void handleSelect(Menu* p_menu);

    void renderHudItems();

    // inline bool getRunning() const { return this->_isRunning; }

    // inline void setRunning(bool isRunning) { this->_isRunning = isRunning; }

    inline unsigned int getOptionIndex() { return this->_selectedOptionIndex; }

    inline void setOptionIndex(int p_optionIndex) { this->_selectedOptionIndex = p_optionIndex; }
private:
    Graphics& _graphics;
    TTF_Font* _font;
    SDL_Color _color;
    std::vector<HudItem> _hudItem;    

    bool _showFPS = false;
    unsigned int _selectedOptionIndex = 1;
    
    int _firstVectorIndex = 0;
    int _secondVectorIndex = 0;
    int _thirdVectorIndex = 0;

    // bool _isRunning;
};

#endif /* HUD */