#pragma once
#include <raylib.h>
#include <memory>

namespace Engine {

    class ModelComponent;   // ← forward declaration, этого достаточно для shared_ptr

    class Entity {
    public:
        Entity(Vector3 startPos = { 0.0f, 0.0f, 0.0f });
        virtual ~Entity() = default;

        virtual void update(float deltaTime) {}
        virtual void render() const;

        void setModel(std::shared_ptr<ModelComponent> m) { model = m; }
        bool hasModel() const { return model != nullptr; }

    protected:
        Vector3 position;
        std::shared_ptr<ModelComponent> model;
    };

}


