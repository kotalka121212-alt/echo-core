#include "model.h"
#include <iostream>

ModelManager::~ModelManager() {
    clear(); // Гарантированная выгрузка при выходе из игры
}

bool ModelManager::load(const std::string& name, const std::string& path) {
    // Если уже загружено — пропускаем
    if (models.find(name) != models.end()) {
        return true;
    }

    Model newModel = LoadModel(path.c_str());
    
    // Проверяем на битый файл или отсутствие мешей
    if (newModel.meshCount == 0) {
        std::cerr << "[ModelManager] Не удалось загрузить модель: " << path << std::endl;
        return false;
    }

    models[name] = newModel;
    return true;
}

Model& ModelManager::get(const std::string& name) {
    auto it = models.find(name);
    if (it != models.end()) {
        return it->second;
    }
    
    // Возвращаем пустую заглушку во избежание краша
    static Model emptyModel = { 0 };
    return emptyModel;
}

bool ModelManager::has(const std::string& name) const {
    return models.find(name) != models.end();
}

void ModelManager::draw(const std::string& name, Vector3 position, float scale, Color tint) const {
    auto it = models.find(name);
    if (it != models.end()) {
        DrawModel(it->second, position, scale, tint);
    } else {
        // Если модели нет в менеджере — рисуем розовый куб ошибки
        DrawCube(position, 1.0f, 1.0f, 1.0f, MAGENTA);
        DrawCubeWires(position, 1.0f, 1.0f, 1.0f, BLACK);
    }
}

void ModelManager::unload(const std::string& name) {
    auto it = models.find(name);
    if (it != models.end()) {
        UnloadModel(it->second); // Выгружаем из ОЗУ/ВРЕМЕННОЙ памяти видеокарты
        models.erase(it);
    }
}

void ModelManager::clear() {
    for (auto& pair : models) {
        UnloadModel(pair.second);
    }
    models.clear();
}


