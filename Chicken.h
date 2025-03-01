#pragma once

#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

/**
 * @enum ChickenType
 * @brief Enum representing different types of chickens in the game.
 */
enum class ChickenType {
    WHITE,      ///< Standard white chicken.
    BROWN,      ///< Brown chicken with slightly different appearance.
    GRAY,       ///< Gray chicken.
    RAINBOW,    ///< Special rainbow chicken.
    DUCK        ///< Duck (bonus or rare type).
};

/**
 * @class Chicken
 * @brief Class representing a single chicken in the game.
 *
 * Each chicken has a position, speed, type, size, and point value.
 * Chickens move across the screen and animate.
 */
class Chicken : public Drawable {
public:
    /**
     * @brief Constructor for the Chicken class.
     * @param x Initial x-coordinate.
     * @param y Initial y-coordinate.
     * @param speed Movement speed of the chicken.
     * @param type Type of chicken.
     * @param isFacingLeft Whether the chicken is facing left.
     * @param size Scale factor for the chicken sprite.
     * @param points Point value when the chicken is collected.
     */
    Chicken(float x, float y, float speed, ChickenType type, bool isFacingLeft, float size, int points);

    /**
     * @brief Destructor for the Chicken class.
     */
    ~Chicken();

    /**
     * @brief Moves the chicken according to its speed and direction.
     */
    void move();

    /**
     * @brief Draw function override to render the chicken.
     * @param target Render target.
     * @param states Render states.
     */
    void draw(RenderTarget& target, RenderStates states) const override;

    /**
     * @brief Gets the current x-coordinate of the chicken.
     * @return The x-coordinate.
     */
    float getX() const;

    /**
     * @brief Gets the current y-coordinate of the chicken.
     * @return The y-coordinate.
     */
    float getY() const;

    /**
     * @brief Gets the global bounding box of the chicken sprite.
     * @return FloatRect representing the chicken's bounds.
     */
    FloatRect getGlobalBounds() const;

    /**
     * @brief Gets the type of the chicken.
     * @return The chicken type.
     */
    ChickenType getType() const;

    /**
     * @brief Gets the point value of the chicken.
     * @return The point value.
     */
    int getPoints() const;
    

private:
    // Position and movement
    float x;                 ///< X-coordinate of the chicken.
    float y;                 ///< Y-coordinate of the chicken.
    float speed;             ///< Movement speed.

    // Chicken properties
    ChickenType type;        ///< Type of the chicken.
    int points;              ///< Point value for collecting this chicken.

    // Graphics
    Sprite sprite;           ///< Sprite for the chicken.
    Texture texture;         ///< Texture for the chicken.
    inline static map<ChickenType, Texture> textureMap; ///< Static map to hold textures for different chicken types.

    // Animation
    int currentFrame;        ///< Current animation frame.
    Clock animationClock;    ///< Clock to control frame timing.
    static constexpr int FRAME_COUNT = 8;       ///< Total number of animation frames.
    static constexpr int FRAME_WIDTH = 16;      ///< Width of each frame in the sprite sheet.
    static constexpr int FRAME_HEIGHT = 16;     ///< Height of each frame in the sprite sheet.
    static constexpr float FRAME_TIME = 0.1f;   ///< Time per animation frame.

    /**
     * @brief Loads textures for all chicken types.
     */
    void initTextures();

    /**
     * @brief Updates the chicken animation (frame switching).
     */
    void updateAnimation();

    /**
     * @brief Initializes the sprite for the chicken.
     * @param isFacingLeft Whether the chicken is facing left.
     * @param size Scale factor for the sprite.
     */
    void initSprite(bool isFacingLeft, float size);
};

