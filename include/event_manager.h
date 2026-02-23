#pragma once
#include "common.h"

class EventManager{

public:
    static inline map<int, bool> keymap; // Keyboard state
    static inline GLFWwindow* window = nullptr;
    
    /*
    Inicia el EventManager
    Parametros:
        window: ventana en la que iniciar el eventManager
    */
    
    static void initEventManager(GLFWwindow* window);
    static void keyboardManager(GLFWwindow *window, int key, int scancode, int action, int mods); // keyboard events
    static void mouseMovementManager(); // mouse movement events
    static void updateEvents();

};