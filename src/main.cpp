#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "voxel/voxel.h"
#include "player/player.h"
#include "camera/camera.h"
#include "model/model.h" // Убедись, что заголовок называется ModelManager.h

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;
    
    InitWindow(screenWidth, screenHeight, "Echo Engine — Lighting Setup");
    SetTargetFPS(144);

    // 1. Инициализируем Игрока и Камеру
    Player player({ 0.0f, 0.5f, 0.0f });
    FlyCamera cam({ 0.0f, 5.0f, 10.0f });

    // Устанавливаем чувствительность мыши
    cam.setMouseSensitivity(10.0f);

    // 2. Архитектурная связка: привязываем их друг к другу
    player.attachCamera(&cam);
    cam.setTargetEntity(&player);
    cam.setMode(CustomCameraMode::FOLLOW); // Включаем режим от 3-го лица

    // 3. Инициализируем менеджер моделей
    ModelManager modelMgr;
    
    // ВАЖНО: Добавили расширение .glb (или укажи .obj, если это обжект)
    // Загружаем модель под именем "character" прямо в игрока!
    if (modelMgr.load("character", "../Untitled.glb")) {
        player.setModelName("character"); // Теперь игрок знает, что он должен рисовать эту модель!
    } else {
        std::cout << "[ERROR] Не удалось загрузить модель игрока! Бегаем кубиком." << std::endl;
    }

    // 4. ЗАГРУЗКА ШЕЙДЕРА ОСВЕЩЕНИЯ ДЛЯ МИРА
    Shader shader = LoadShader("../assets/shaders/lighting.vs", "../assets/shaders/lighting.fs");
    int lightPosLoc    = GetShaderLocation(shader, "lightPos");
    int viewPosLoc     = GetShaderLocation(shader, "viewPos");
    int lightColorLoc  = GetShaderLocation(shader, "lightColor");
    int objectColorLoc = GetShaderLocation(shader, "objectColor");

    // Навешиваем шейдер освещения на материалы нашей модельки персонажа в менеджере
    if (modelMgr.has("character")) {
        Model& modelData = modelMgr.get("character");
        for (int i = 0; i < modelData.materialCount; i++) {
            modelData.materials[i].shader = shader;
        }
    }

    // Параметры освещения
    Vector3 lightPos = { 5.0f, 10.0f, 5.0f };
    Vector3 lightColor = { 1.0f, 1.0f, 1.0f };
    Vector3 objectColor = { 0.8f, 0.6f, 0.4f };

    DisableCursor();
    // Убираем жесткий DisableCursor, так как наша камера сама им рулит при зажатии ПКМ
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // ОБНОВЛЕНИЕ: Игрок двигается и сам внутри обновляет камеру
        player.update(deltaTime); 

        // Передаем позицию камеры в шейдер для расчета бликов (Specular)
        Vector3 viewPos = cam.getPosition();

        // Обновляем юниформы шейдера освещения перед отрисовкой
        SetShaderValue(shader, lightPosLoc,    &lightPos,    SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, viewPosLoc,     &viewPos,     SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, lightColorLoc,  &lightColor,  SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, objectColorLoc, &objectColor, SHADER_UNIFORM_VEC3);

        // --- ОТРИСОВКА НА ЭКРАН ---
        BeginDrawing();
            ClearBackground(DARKBLUE); // Красивый фон неба по умолчанию

            // Включаем 3D-режим нашей RPG камеры
            BeginMode3D(player.getCamera()->get()); 

                DrawGrid(50, 1.0f); // Сетка под ногами
                
                // РИСУЕМ ИГРОКА: Теперь он сам пойдет в modelMgr, найдет там модель 
                // "character" (твою Untitled) и нарисует её прямо на своей текущей позиции!
                player.render(modelMgr); 

            EndMode3D(); // Закрываем 3D режим

            // Рисуем обычный 2D интерфейс и счетчик кадров поверх сцены
            DrawFPS(10, 10);

        EndDrawing();
    }

    // ВЫГРУЗКА РЕСУРСОВ ИЗ ПАМЯТИ
    UnloadShader(shader);
    modelMgr.clear(); // Менеджер сам честно очистит всю видеопамять от загруженных моделей

    ShowCursor(); // Возвращаем курсор системе перед выходом
    CloseWindow();
    return 0;
}






