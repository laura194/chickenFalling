#include "Chicken.h"

Chicken::Chicken(float x, float y, float speed, ChickenType type, bool isFacingLeft, float size, int points)
    : x(x), y(y), speed(speed), type(type), points(points), currentFrame(0) {
    initTextures();
    sprite.setTextureRect(IntRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT));

    float scaleX = isFacingLeft ? (size * (-1)) : size;
    sprite.setScale(scaleX, size);
}



Chicken::~Chicken() {

}

void Chicken::initTextures() {

    if (textureMap.empty()) {
        map<ChickenType, string> texturePaths = {
            {ChickenType::WHITE, "Textures/Chicken_Textures/chicken_white.png"},
            {ChickenType::BROWN, "Textures/Chicken_Textures/chicken_brown.png"},
            {ChickenType::GRAY, "Textures/Chicken_Textures/chicken_gray.png"},
            {ChickenType::RAINBOW, "Textures/Chicken_Textures/chicken_rainbow.png"},
            {ChickenType::DUCK, "Textures/Chicken_Textures/chicken_duck.png"}
        };

        for (const auto& [type, path] : texturePaths) {
            if (!textureMap[type].loadFromFile(path)) {
                cout << "ERROR::CHICKEN::INITTEXTURES::Failed to load " << path << endl;
            }
        }
    }

    if (textureMap.find(type) != textureMap.end()) {
        sprite.setTexture(textureMap[type]);
    }
}

void Chicken::move() {
    y += speed;  
    sprite.setPosition(x, y);
    updateAnimation(); 
}

void Chicken::draw(RenderTarget& target, const RenderStates states) const {
    target.draw(sprite, states);
}

float Chicken::getX() const { return x; }
float Chicken::getY() const { return y; }

void Chicken::updateAnimation() {
    if (animationClock.getElapsedTime().asSeconds() > FRAME_TIME) {
        currentFrame = (currentFrame + 1) % FRAME_COUNT; 
        sprite.setTextureRect(IntRect(currentFrame * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT));
        animationClock.restart();
    }
}


