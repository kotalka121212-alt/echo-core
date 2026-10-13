#pragma once
#include <raylib.h>
#include <string>

class FlyCamera;    // Вперед-объявление камеры
class ModelManager; // Вперед-объявление менеджера моделей

class Entity {
public:
    Entity(Vector3 startPos = { 0.0f, 0.0f, 0.0f });
    virtual ~Entity() = default;

    virtual void update(float deltaTime) {}
    
    // Метод отрисовки теперь принимает ссылку на менеджер моделей
    virtual void render(const ModelManager& modelMgr) const; 

    Vector3 getPosition() const { return position; }
    void setPosition(Vector3 pos) { position = pos; }

    // Установка текстового имени модели (например, "hero" или "goblin")
    void setModelName(const std::string& name) { modelName = name; }
    std::string getModelName() const { return modelName; }
    bool hasModel() const { return !modelName.empty(); }

    // Привязка камеры
    void attachCamera(FlyCamera* cam) { camera = cam; }
    bool hasCamera() const { return camera != nullptr; }
    FlyCamera* getCamera() const { return camera; }

    bool isAlive() const { return alive; }
    void kill() { alive = false; }

protected:
    Vector3 position;
    bool alive;
    std::string modelName;     // Имя модели, зарегистрированное в ModelManager
    FlyCamera* camera;         // Камера, привязанная к этой сущности
};


