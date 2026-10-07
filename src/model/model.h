#pragma once
#include <raylib.h>
#include <string>



    class ModelComponent {
    public:
        ModelComponent() = default;
        ModelComponent(const std::string& path);

        ~ModelComponent();

        bool load(const std::string& path);
        void unload();

        void render(Vector3 position, float scale = 1.0f, Color tint = WHITE) const;

        bool isLoaded() const { return loaded; }
        Model getModel() const { return model; }

    private:
        Model model = { 0 };
        bool loaded = false;
    };

