#include "Entity.h"
#include "model/model.h" // Подключаем менеджер, чтобы вызывать его методы

Entity::Entity(Vector3 startPos)
    : position(startPos), alive(true), modelName(""), camera(nullptr) {}

void Entity::render(const ModelManager& modelMgr) const {
    // Если имя модели задано и она есть в кэше менеджера — рисуем её
    if (!modelName.empty() && modelMgr.has(modelName)) {
        modelMgr.draw(modelName, position); 
    } else {
        // Красивая дефолтная заглушка (серый куб), если модель ещё не назначена
        DrawCube(position, 1.0f, 1.0f, 1.0f, GRAY);
        DrawCubeWires(position, 1.0f, 1.0f, 1.0f, DARKGRAY);
    }
}







