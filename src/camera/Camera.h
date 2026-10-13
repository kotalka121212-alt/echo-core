#pragma once
#include <raylib.h>
#include <raymath.h>

class Entity; // Вперед-объявление

// Избегаем конфликта с внутренним CameraMode из raylib.h
enum class CustomCameraMode {
    FLY,    // Свободный полет (WASD + мышь)
    FOLLOW  // Слежение от 3-го лица за игроком
};

class FlyCamera {
public:
    FlyCamera(Vector3 startPos = { 0.0f, 2.0f, 5.0f });

    void update(float deltaTime);                        
    void setTargetEntity(const Entity* entity);         
    void setMode(CustomCameraMode newMode);                  

    Camera3D get() const;
    Vector3 getPosition() const;
    void setPosition(Vector3 pos);

    void setMouseSensitivity(float a) { mouseSensitivity = a; }

private:
    void updateFlyMode(float deltaTime);                 
    void updateFollowMode(float deltaTime);              

    Camera3D camera;
    CustomCameraMode mode;
    const Entity* targetEntity;

    float yaw;
    float pitch;
    float moveSpeed;
    float mouseSensitivity;

    // Параметры RPG слежения
    float followDistance;
    float followHeight;
    float smoothness; 
};

