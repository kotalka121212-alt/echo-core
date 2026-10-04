#pragma once
#include <raylib.h>
#include <raymath.h>



    class Player {
    public:
        Player(Vector3 startPos = { 0.0f, 0.5f, 0.0f });

        void update(float deltaTime);   // двигает игрока
        void render() const;            // рисует куб

        Vector3 getPosition() const;
        void setPosition(Vector3 pos);

    private:
        Vector3 position;   // где игрок
        float speed;        // как быстро двигается
        float size;         // размер куба
    };

