#include <iostream>
#include <Windows.h>

int main() {

    POINT cursorPoint;

    std::cout << "Starting mouse tracker. Press Ctrl+C in this window to stop." << std::endl;

    while (true) {
        if (GetCursorPos(&cursorPoint)) {
            std::cout << "\rMouse Coordinates -> X: " << cursorPoint.x << ", Y: " << cursorPoint.y << "   ";
        }

        Sleep(100);
    }

    return 0;  
}