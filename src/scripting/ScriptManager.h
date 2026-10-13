#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#pragma once

// Внутри твоей библиотеки движка
#include <lua.hpp>
#include <string>

class ScriptManager {
private:
    lua_State* L;

public:
    ScriptManager() {
        L = luaL_newstate();
        luaL_openlibs(L); // Загружаем базовые библиотеки Lua
    }

    ~ScriptManager() {
        if (L) lua_close(L);
    }

    // Возвращаем указатель, чтобы код игры мог регистрировать свои функции
    lua_State* GetState() { return L; }

    // Запуск файла со скриптом
    bool RunFile(const std::string& path) {
        if (luaL_dofile(L, path.c_str()) != LUA_OK) {
            // Тут твоя система логов движка выводит ошибку
            std::string error = lua_tostring(L, -1);
            return false;
        }
        return true;
    }
};


#endif