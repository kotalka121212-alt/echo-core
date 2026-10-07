#include "model.h"
#include <iostream>



    ModelComponent::ModelComponent(const std::string& path) {
        load(path);
    }

    ModelComponent::~ModelComponent() {
        unload();
    }

    bool ModelComponent::load(const std::string& path) {
        if (loaded) unload();

        model = LoadModel(path.c_str());
        if (model.meshCount == 0) {
            std::cerr << "[Model] Failed to load: " << path << std::endl;
            loaded = false;
            return false;
        }

        loaded = true;
        return true;
    }

    void ModelComponent::unload() {
        if (loaded) {
            UnloadModel(model);
            loaded = false;
        }
    }

    void ModelComponent::render(Vector3 position, float scale, Color tint) const {
        if (!loaded) return;

        DrawModel(model, position, scale, tint);
    }

