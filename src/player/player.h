#pragma once
#include <raylib.h>
#include <raymath.h>

namespace Engine {

    class Player {
    public:
        Player(Vector3 startPos = { 0, 0.5f, 0 });
        void update(float deltaTime);
        void render() const;

        Vector3 getPosition() const;
        void setPosition(Vector3 pos);

        void setSpeed(float s);
        float getSpeed() const;

    private:
        Vector3 position;
        float speed;
        float size;
    };

}