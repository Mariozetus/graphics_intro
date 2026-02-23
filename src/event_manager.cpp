#include "event_manager.h"

void EventManager::initEventManager(GLFWwindow* window)
{
    glfwSetKeyCallback(window, keyboardManager);
    EventManager::window = window;
}

void EventManager::keyboardManager(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    switch (action) {
        case GLFW_PRESS:{
            EventManager::keymap[key] = true;
        } break;
        case GLFW_RELEASE:{
            EventManager::keymap[key] = false;
        }break;
    }
}

void EventManager::updateEvents()
{
    glfwPollEvents(); // Update del resto de eventos de ventana
}
