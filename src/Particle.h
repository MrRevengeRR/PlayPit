#include "raylib.h"
#include <math.h>

class Particle {
    private:
        Vector2 position;
        Vector2 velocity;
        Color color;

        float getDistance(Vector2 otherpositionition);
        Vector2 getNormal(Vector2 otherpositionition);

    public:
        Particle(int screenWidth, int screenHeight);
        Particle(Vector2 position, Vector2 velocity, Color color);

        void attract(Vector2 positionToAttract, float multiplier);
        void doFriction(float amount);
        void move(int screenWidth, int screenHeight);
        void drawPixel();
        void reset();
};

Particle::Particle(int screenWidth, int screenHeight) {
    position.x = GetRandomValue(0, screenWidth-1);
    position.y = GetRandomValue(0, screenHeight-1);
    velocity.x = GetRandomValue(-100, 100) / 100.f;
    velocity.y = GetRandomValue(-100, 100) / 100.f;
    //color = {GetRandomValue(0,255),GetRandomValue(0,255),GetRandomValue(0,255),255};
    color = {0,0,0,100};
}

Particle::Particle(Vector2 _pos, Vector2 _vel, Color _color) {
    position = _pos;
    velocity = _vel;
    color = _color;
}

float Particle::getDistance(Vector2 otherPos) {
    const float dx = position.x - otherPos.x;
    const float dy = position.y - otherPos.y;
    return sqrt((dx*dx) + (dy*dy));
}

Vector2 Particle::getNormal(Vector2 otherPos) {
    float dist = getDistance(otherPos);
    if (dist == 0.0f) dist = 1;
    const float dx = position.x - otherPos.x;
    const float dy = position.y - otherPos.y;
    Vector2 normal = {dx*(1/dist), dy*(1/dist)};
    return normal;
}

void Particle::attract(Vector2 posToAttract, float multiplier) {
    float dist = fmax(getDistance(posToAttract),0.5);
    Vector2 normal = getNormal(posToAttract);

    velocity.x -= normal.x/dist;
    velocity.y -= normal.y/dist;
}

void Particle::doFriction(float amount) {
    velocity.x *= amount;
    velocity.y *= amount;
}

void Particle::move(int screenWidth, int screenHeight) {
    position.x += velocity.x;
    position.y += velocity.y;
    if (position.x < 0)
        position.x += screenWidth;
    if (position.x >= screenWidth)
        position.x -= screenWidth;
    if (position.y < 0)
        position.y += screenHeight;
    if (position.y >= screenHeight)
        position.y -= screenHeight;
}

void Particle::drawPixel() {
    DrawPixelV(position, color);
}

void Particle::reset() {
    position.x = -10;
    position.y = -10;
    drawPixel();
}