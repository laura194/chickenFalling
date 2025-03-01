#include "Game.h"

// Initialize game variables and default values
void Game::initVariables() {
    this->window = nullptr;
    this->endGame = false;
    this->score = 0;
    this->hearts = 3;
    this->heartsDisplay.resize(this->hearts); // Prepare hearts display
    this->highscore = 0;
    this->maxChickens = 20;
    this->chickenSpawnTimer = 0.f;
    this->chickenSpawnTimerMax = 35.f;

}

// Set up the game window (size, title, icon, framerate limit)
void Game::initWindow() {
    this->videoMode.width = 800;
    this->videoMode.height = 600;
    this->window = new RenderWindow(this->videoMode, "Chicken Falling", Style::Titlebar | Style::Close);
    this->window->setFramerateLimit(60);

    Image icon;
    if (icon.loadFromFile("Textures/icon.png")) {
        this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    else {
        cout << "ERROR::GAME::INITWINDOW::Failed to load window icon" << endl;
    }
}

// Load fonts for text rendering
void Game::initFonts() {
    if (!this->font.loadFromFile("Fonts/pixel.ttf")) {
        cout << "ERROR::GAME::INITFONTS::Failed to load font" << endl;
    }
}


// Load all textures (background, score board, hearts)
void Game::initTextures() {
    //Background texture start screen
    if (!this->backgroundTextureStartScreen.loadFromFile("Textures/startscreen_background.png")) {
        cout << "ERROR::GAME::INITTEXTURES::Failed to load background texture (start screen)" << endl;
    }
    //Background texture main game
    if (!this->backgroundTexture.loadFromFile("Textures/background.png")) {
        cout << "ERROR::GAME::INITTEXTURES::Failed to load background texture (main game)" << endl;
    }
    //Score board
    if (!this->scoreBoardTexture.loadFromFile("Textures/score_board.png")) {
        cout << "ERROR::GAME::INITTEXTURES::Failed to load score board texture" << endl;
    }
    //Hearts
    if (!this->heartTexture.loadFromFile("Textures/heart.png")) {
        cout << "ERROR::GAME::INITTEXTURES::Failed to load heart texture" << endl;
    }

}

// Setup background sprite to fit window size
void Game::initBackground() {

    this->background.setTexture(this->backgroundTexture);
    this->background.setScale(
        static_cast<float>(this->window->getSize().x) / this->background.getLocalBounds().width,
        static_cast<float>(this->window->getSize().y) / this->background.getLocalBounds().height
    );
}

// Initialize the scoreboard text and graphic
void Game::initScoreBoard() {
    this->scoreText.setFont(this->font);
    this->scoreText.setCharacterSize(30);
    this->scoreText.setPosition(10.f, 20.f);

    this->scoreText.setFillColor(Color::White);
    this->scoreText.setString("N/A");

    this->highscoreText.setFont(this->font);
    this->highscoreText.setCharacterSize(30);
    this->highscoreText.setPosition(10.f, 50.f);

    this->highscoreText.setFillColor(Color::White);
    this->highscoreText.setString("N/A");

    this->scoreBoard.setTexture(this->scoreBoardTexture);
    this->scoreBoard.setPosition(2.f, 0.f);
    this->scoreBoard.setScale(1.5f, 1.5f);
}

// Initialize hearts display
void Game::initHearts() {
    for (int i = 0; i < this->heartsDisplay.size(); i++) {
        this->heartsDisplay[i].setTexture(this->heartTexture);
        this->heartsDisplay[i].setScale(2.5f, 2.5f);
        this->heartsDisplay[i].setPosition(15.f + i * 44.f, 90.f);
    }
}

// Setup the initial start screen (background and start button)
void Game::initStartScreen() {
    
    this->backgroundStartScreen.setTexture(this->backgroundTextureStartScreen);
    this->backgroundStartScreen.setScale(
        static_cast<float>(this->window->getSize().x) / this->backgroundStartScreen.getLocalBounds().width,
        static_cast<float>(this->window->getSize().y) / this->backgroundStartScreen.getLocalBounds().height
    );
    this->showStartScreen = true;

    // Invisible clickable button for starting the game
    this->startButton.setSize(Vector2f(220.f, 60.f));
    this->startButton.setFillColor(Color(0, 0, 0, 0)); 
    this->startButton.setPosition(290.f, 410.f);
}


// Constructor
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initTextures();
    this->initBackground();
    this->initScoreBoard();
    this->initFonts();
    this->initHearts();
    this->loadHighScore();
    this->initStartScreen();
}

// Destructor
Game::~Game() {
    delete this->window;
}

// Check if window is still open
bool Game::running() const {
    return this->window->isOpen();

}

// Check if game has ended
bool Game::getEndGame() const {
    return this->endGame;
}

// Handle input events (window close, escape key, mouse click)
void Game::pollEvents() {
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
        case Event::Closed:
            this->window->close();
            break;

        case Event::KeyPressed:
            if (ev.key.code == Keyboard::Escape) this->window->close();
            break;

        case Event::MouseButtonPressed:
            if (this->showStartScreen && ev.mouseButton.button == Mouse::Left) {
                Vector2f mousePos = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));

                if (this->startButton.getGlobalBounds().contains(mousePos)) {
                    this->showStartScreen = false; 
                }
            }
            break;

        default:
            break;
        }
    }
}

// Spawn new chickens at random positions and types
void Game::spawnChickens() {
    const float windowWidth = static_cast<float>(this->window->getSize().x);
    constexpr float size = 4.f;
    constexpr float chickenWidth = 16 * size;
    float speed = 2.f;
    ChickenType type;
    int points = 1;

    // Randomize chicken type
    if (const int randomType = rand() % 1000; randomType == 0) {
        type = ChickenType::DUCK;
        speed = 4.f;
        points = 100;
    }
    else if (randomType < 20) {
        type = ChickenType::RAINBOW;
        speed = 3.f;
        points = 10;
    }
    else if (randomType < 340) {
        type = ChickenType::WHITE;
    }
    else if (randomType < 670) {
        type = ChickenType::BROWN;
    }
    else {
        type = ChickenType::GRAY;
    }

    // Randomly spawn from left or right
    bool isFacingLeft = rand() % 2 == 0;

    float x;
    if (isFacingLeft) {
        x = static_cast<float>(rand() % static_cast<int>(windowWidth - chickenWidth)) + chickenWidth;
    }
    else {
        x = static_cast<float>(rand() % static_cast<int>(windowWidth - chickenWidth));
    }

    float y = 0.f;
    this->chickens.emplace_back(x, y, speed, type, isFacingLeft, size, points);

}

// Update all game logic
void Game::update() {
    this->pollEvents();

    if (this->showStartScreen) {
        return; 
    }

    if (!this->endGame) {
        this->updateMousePositions();
        this->updateText();
        this->updateHearts();
        this->updateChickens();
    }

    if (this->hearts <= 0) {
        this->endGame = true;
        this->saveHighScore();
    }
}

// Update mouse position relative to window
void Game::updateMousePositions() {
    this->mousePosWindow = Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

}

// Update chicken movement and check for collisions
void Game::updateChickens() {
    // Spawn new chicken if timer reaches max and not exceeding max chickens
    if (this->chickens.size() < this->maxChickens) {
        if (this->chickenSpawnTimer >= this->chickenSpawnTimerMax) {
            this->spawnChickens();
            this->chickenSpawnTimer = 0.f;
        }
        else {
            this->chickenSpawnTimer += 1.f;
        }
    }

    // Update all existing chickens (movement, check if missed)
    for (int i = 0; i < this->chickens.size(); i++) {
        this->chickens[i].move();

        // Chicken falls off screen — player loses heart
        if (this->chickens[i].getY() > static_cast<float>(this->window->getSize().y)) {
            this->chickens.erase(this->chickens.begin() + i);
            this->hearts -= 1;
        }
    }

    // Check for mouse clicks on chickens (removing them and increasing score)
    if (Mouse::isButtonPressed(Mouse::Left)) {
        if (!this->mouseHeld) {
            this->mouseHeld = true;
            for (int i = 0; i < this->chickens.size(); ++i) {
                if (FloatRect chickenBounds = this->chickens[i].getGlobalBounds(); chickenBounds.contains(this->mousePosView)) {
                    this->score += chickens[i].getPoints();
                    this->chickens.erase(this->chickens.begin() + i);
                    break; // Only allow one chicken per click
                }
                
            }
        }
    }
    else {
        this->mouseHeld = false;
    }
}

// Update score and highscore text strings
void Game::updateText() {
    stringstream scoreStream;
    scoreStream << this->score;
    this->scoreText.setString(scoreStream.str());
    stringstream highscoreStream;
    highscoreStream << "HS: " << this->highscore;
    this->highscoreText.setString(highscoreStream.str());
}

// Update the heart display to match current heart count
void Game::updateHearts() {
    for (size_t i = 0; i < this->heartsDisplay.size(); i++) {
        if (i < this->hearts) {
            this->heartsDisplay[i].setColor(Color::White);
        }
        else {
            this->heartsDisplay[i].setColor(Color(100, 100, 100)); 
        }
    }
}

// Render all graphics for the game
void Game::render() {
    this->window->clear();
    if (this->showStartScreen) {
        this->renderStartScreen(*this->window);
    }
    else {
        
		this->renderMainBackground(*this->window);
        this->renderText(*this->window);
        this->renderHearts(*this->window);
        this->renderChickens(*this->window);
    }
    this->window->display();

}

// Draw the start screen with background and invisible start button
void Game::renderStartScreen(RenderTarget& target) {
    target.draw(this->backgroundStartScreen);
}

// Draw the main game background and the scoreboard
void Game::renderMainBackground(RenderTarget& target) {
    target.draw(this->background);
    target.draw(this->scoreBoard);
}


// Draw all the chickens
void Game::renderChickens(RenderTarget& target) {
    for (auto& chicken : this->chickens) {
        target.draw(chicken);
    }
}

// Draw all text (score and highscore)
void Game::renderText(RenderTarget& target) const {
    target.draw(this->scoreText);
    target.draw(this->highscoreText);
}

// Draw the player's remaining hearts
void Game::renderHearts(RenderTarget& target) {
    for (auto& heart : this->heartsDisplay) {
        target.draw(heart);
    }
}

// Save highscore to file if the current score is higher
void Game::saveHighScore() {
    if (this->score > this->highscore) {
        this->highscore = this->score;
        std::ofstream file("highscore.txt");
        if (file.is_open()) {
            file << this->highscore;
        }
        file.close();
    }

}
// Load highscore from file
void Game::loadHighScore() {
    ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> this->highscore;
    }
    else {
        this->highscore = 0; // No highscore file found — default to zero
    }
    file.close();
}
