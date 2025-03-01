#ifndef CHICKEN_H
#define CHICKEN_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>


using namespace sf;
using namespace std;


enum class ChickenType {
    WHITE,
    BROWN,
    GRAY,
    RAINBOW,
    DUCK
};

class Chicken : public Drawable {
private:
    //Variables
    float x;
    float y;
    float speed;
    ChickenType type;
    int points;
    Sprite sprite;
    Texture texture;
    inline static map<ChickenType, Texture> textureMap;
    int currentFrame;               // Der aktuelle Animationsframe
    Clock animationClock;           // Timer für die Animation
    static constexpr int FRAME_COUNT = 8; // Anzahl der Frames
    static constexpr int FRAME_WIDTH = 16; // Breite eines Frames
    static constexpr int FRAME_HEIGHT = 16; // Höhe eines Frames
    static constexpr float FRAME_TIME = 0.1f; // Dauer pro Frame (in Sekunden)

    //Private functions
    void initTextures();
    void updateAnimation();


public:
    //Constructor / Destructors
    Chicken(float x, float y, float speed, ChickenType type, bool isFacingLeft, float size, int points);
    ~Chicken();

    void move();
    float getX() const;
    float getY() const;

    FloatRect getGlobalBounds() const {
        return sprite.getGlobalBounds();
    }
    ChickenType getType() const {
        return type;
    }
    int getPoints() const {
        return this->points;
    }
protected:
    void draw(RenderTarget& target, RenderStates states) const override;

};



#endif //CHICKEN_H
