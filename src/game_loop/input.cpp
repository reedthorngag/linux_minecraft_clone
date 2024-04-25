
#include "input.hpp"

void Input::press(unsigned int key) {
    keys[key] = true;
}

void Input::release(unsigned int key) {
    keys[key] = false;
}