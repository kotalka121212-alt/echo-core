#include "player.h"
#include "voxel/voxel.h"
#include "camera/camera.h"
#include <raymath.h>

Player::Player(Vector3 startPos)
    : Entity(startPos), speed(5.0f), size(1.0f) {}

void Player::update(float deltaTime) {
    Vector3 moveDirection = { 0.0f, 0.0f, 0.0f };

    // Считываем горизонтальные нажатия (WASD)
    speed = 5.0f;
    
    if (IsKeyDown(KEY_LEFT_CONTROL)) speed = 10.0f; 



    if (IsKeyDown(KEY_W)) moveDirection.z += 1.0f;
    if (IsKeyDown(KEY_S)) moveDirection.z -= 1.0f;
    if (IsKeyDown(KEY_A)) moveDirection.x += 1.0f;
    if (IsKeyDown(KEY_D)) moveDirection.x -= 1.0f;

    // ВСТРАИВАЕМ ПОЛЕТ ВВЕРХ И ВНИЗ НАПРЯМУЮ В ИГРОКА
    // Движение по оси Y идет строго вертикально, независимо от камеры
    if (IsKeyDown(KEY_SPACE))      position.y += speed * deltaTime * 0.5; // Вверх
    if (IsKeyDown(KEY_LEFT_SHIFT)) position.y -= speed * deltaTime * 0.5; // Вниз

    // Обрабатываем горизонтальное перемещение относительно взгляда камеры
    if ((moveDirection.x != 0.0f || moveDirection.z != 0.0f) && hasCamera()) {
        Vector3 camPos = camera->getPosition();
        Vector3 targetPos = position; 
        
        // Вектор "вперед" по взгляду камеры (прижатый к земле)
        Vector3 forward = Vector3Subtract(targetPos, camPos);
        forward.y = 0.0f; 
        forward = Vector3Normalize(forward);

        // Вектор "вправо" относительно камеры
        Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, Vector3{ 0.0f, 1.0f, 0.0f }));

        // Собираем итоговый вектор горизонтального движения
        Vector3 finalDirection = { 0.0f, 0.0f, 0.0f };
        
        if (IsKeyDown(KEY_W)) finalDirection = Vector3Add(finalDirection, forward);
        if (IsKeyDown(KEY_S)) finalDirection = Vector3Subtract(finalDirection, forward);
        if (IsKeyDown(KEY_A)) finalDirection = Vector3Subtract(finalDirection, right);
        if (IsKeyDown(KEY_D)) finalDirection = Vector3Add(finalDirection, right);

        // Применяем горизонтальное смещение к позиции игрока
        if (Vector3Length(finalDirection) > 0.0f) {
            finalDirection = Vector3Normalize(finalDirection);
            finalDirection = Vector3Scale(finalDirection, speed * deltaTime);
            position = Vector3Add(position, finalDirection);
        }
    }

    // После того как подвигали игрока (включая его высоту Y), 
    // привязанная камера автоматически обновляет свою позицию за ним
    if (hasCamera()) {
        camera->update(deltaTime); 
    }
}


void Player::render(const ModelManager& modelMgr) const {
    if (hasModel()) {
        Entity::render(modelMgr); // Рисуем low-poly модель из менеджера
    } else {
        voxel::draw_cube(position, size, BLUE, DARKBLUE); // Наш воксельный куб
    }
}



