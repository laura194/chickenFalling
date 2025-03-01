
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Chicken.h"

using namespace sf;
using namespace std;


/**
 * @class Game
 * @brief Main class for the Chicken Falling game.
 *
 * Handles the game window, game logic, rendering, and player interaction.
 */
class Game {

public:

    /**
     * @brief Constructor for the Game class.
     */
    Game();

	/**
	 * @brief Destructor for the Game class.
	 */
    ~Game();

    /**
    * @brief Checks if the game window is open.
    * @return True if the window is open, otherwise false.
    */
    bool running() const;

    /**
    * @brief Checks if the game has ended.
    * @return True if the game has ended, otherwise false.
    */
    bool getEndGame() const;

    /**
     * @brief Polls and processes window events.
     */
    void pollEvents();

    /**
     * @brief Spawns a new chicken.
     */
    void spawnChickens();

    /**
     * @brief Updates the game logic (chickens, score, hearts, etc.).
     */
    void update();

    /**
     * @brief Renders the entire game frame.
     */
    void render();

private:

    //Window
    RenderWindow* window{};      ///< Pointer to the game window.
    Event ev;                    ///< SFML event for handling input.
    VideoMode videoMode;         ///< Video mode for the game window.

    //StartScreen
    bool showStartScreen;        ///< Flag indicating whether the start screen is displayed.
    RectangleShape startButton;  ///< Invisible clickable area for the start button.

    //Fonts
    Font font;                   ///< Main font for UI elements.

    //Mouse positions
    Vector2i mousePosWindow;     ///< Mouse position in window coordinates.
    Vector2f mousePosView;       ///< Mouse position in world coordinates.


    //Game logic
    bool endGame;                ///< Flag indicating whether the game has ended.
    int score;                   ///< Current player score.
    int highscore;               ///< Highest recorded score.
    int hearts;                  ///< Number of remaining hearts (lives).
    bool mouseHeld;              ///< Flag to prevent holding the mouse button from counting as multiple clicks.

    //Background
    Texture backgroundTextureStartScreen; ///< Texture for the start screen background.
    Sprite backgroundStartScreen;         ///< Sprite for the start screen background.
    Texture backgroundTexture;            ///< Texture for the main game background.
    Sprite background;                    ///< Sprite for the main game background.

    //Score board
    Texture scoreBoardTexture;            ///< Texture for the score board.
    Sprite scoreBoard;                    ///< Sprite for the score board.
    Text scoreText;                       ///< Text showing the current score.
    Text highscoreText;                   ///< Text showing the highscore.
    Texture heartTexture;                 ///< Texture for the heart icons.
    vector<Sprite> heartsDisplay;         ///< Vector of heart sprites to display remaining lives.

    //Chickens
    vector<Chicken> chickens;            ///< Vector storing all active chickens.
    int maxChickens;                     ///< Maximum number of chickens allowed on screen.
    float chickenSpawnTimer;             ///< Timer to control chicken spawning.
    float chickenSpawnTimerMax;          ///< Maximum time before a new chicken spawns.


    /**
     * @brief Initializes the game window.
     */
    void initWindow();

    /**
     * @brief Initializes all member variables.
     */
    void initVariables();

    /**
     * @brief Initializes the game fonts.
     */
    void initFonts();

    /**
     * @brief Loads textures required by the game.
     */
    void initTextures();

    /**
     * @brief Sets up the background sprite.
     */
    void initBackground();

    /**
     * @brief Sets up the score board display.
     */
    void initScoreBoard();

    /**
     * @brief Initializes heart display for lives.
     */
    void initHearts();

    /**
     * @brief Initializes the start screen.
     */
    void initStartScreen();

    /**
     * @brief Updates the current mouse positions.
     */
    void updateMousePositions();

    /**
     * @brief Updates chicken movement and checks for collisions.
     */
    void updateChickens();

    /**
     * @brief Updates the score and highscore display.
     */
    void updateText();

    /**
     * @brief Updates the heart display based on remaining lives.
     */
    void updateHearts();

	/**
	 * @brief Renders the start screen.
	 * @param target Render target to draw the start screen on.
	 */
	void renderStartScreen(RenderTarget& target);

	/**
	 * @brief Renders the main game background.
	 * @param target Render target to draw the background on.
	 */
	void renderMainBackground(RenderTarget& target);

    /**
     * @brief Renders all chickens.
     * @param target Render target to draw the chickens on.
     */
    void renderChickens(RenderTarget& target);

    /**
     * @brief Renders the score and highscore text.
     * @param target Render target to draw the text on.
     */
    void renderText(RenderTarget& target) const;

    /**
     * @brief Renders the heart icons.
     * @param target Render target to draw the hearts on.
     */
    void renderHearts(RenderTarget& target);

    /**
     * @brief Saves the current highscore to a file.
     */
    void saveHighScore();

    /**
     * @brief Loads the highscore from a file.
     */
    void loadHighScore();


    
};



#endif //GAME_H

