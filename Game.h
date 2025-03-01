
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Chicken.h"

using namespace sf;
using namespace std;

class Game {
private:

    //Variables

    //Window
    RenderWindow* window{};
    Event ev;
    VideoMode videoMode;

    //StartScreen
    bool showStartScreen;
    RectangleShape startButton;
    Text startButtonText;

    //Fonts
    Font font;

    //Mouse positions
    Vector2i mousePosWindow;
    Vector2f mousePosView;

    //Game logic
    bool endGame;
    int score;
    int highscore;
    int hearts;
    bool mouseHeld;

    //Game objects

    //Background
    Texture backgroundTextureStartScreen;
    Sprite backgroundStartScreen;
    Texture backgroundTexture;
    Sprite background;

    //Score board
    Texture scoreBoardTexture;
    Sprite scoreBoard;
    Text scoreText;
    Text highscoreText;
    Texture heartTexture;
    vector<Sprite> heartsDisplay;

    //Chickens
    vector<Chicken> chickens;
    int maxChickens;
    float chickenSpawnTimer;
    float chickenSpawnTimerMax;



    //Private functions
    void initWindow();
    void initVariables();
    void initFonts();
    void initTextures();
    void initBackground();
    void initScoreBoard();
    void initHearts();
    void initStartScreen();




public:
    //Constructors / Destructors
    Game();
    ~Game();

    //Accessors
    bool running() const;
    bool getEndGame() const;



    //Public functions
    void pollEvents();
    void spawnChickens();
    void update();
    void updateMousePositions();
    void updateChickens();
    void updateText();
    void updateHearts();
    void render();
    void renderChickens(RenderTarget& target);
    void renderText(RenderTarget& target) const;
    void renderHearts(RenderTarget& target);
    void saveHighScore();
    void loadHighScore();

};



#endif //GAME_H

