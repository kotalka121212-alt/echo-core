#pragma once
#include <raylib.h>
#include <raymath.h>



    class FlyCamera {
    public:
        FlyCamera(Vector3 startPos = { 0.0f, 2.0f, 5.0f });

        void update(float deltaTime);
        Camera3D get() const;

        Vector3 getPosition() const;
        void setPosition(Vector3 pos);

    private:
        Camera3D camera;
        float yaw;
        float pitch;
        float moveSpeed;
        float mouseSensitivity;
    };

