#pragma once
#include <raylib.h>
#include <string>
#include <unordered_map>

class ModelManager {
public:
    ModelManager() = default;
    ~ModelManager(); // Очистит память видеокарты при уничтожении

    // Загрузить 3D-модель под уникальным текстовым именем
    bool load(const std::string& name, const std::string& path);

    // Получить ссылку на саму структуру Model из Raylib (например, для шейдеров)
    Model& get(const std::string& name);

    // Проверить, загружена ли модель с таким именем
    bool has(const std::string& name) const;

    // Отрисовать модель по имени
    void draw(const std::string& name, Vector3 position, float scale = 1.0f, Color tint = WHITE) const;

    // Выгрузить конкретную модель из видеопамяти
    void unload(const std::string& name);

    // Полностью очистить кэш (выгрузить все модели)
    void clear();

private:
    std::unordered_map<std::string, Model> models;
};



