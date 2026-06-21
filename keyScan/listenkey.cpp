#include <iostream>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <chrono>
#include <windows.h>

int main() {

    std::vector <uint8_t> valuesHexBuffer;
    bool listen = true;
    const int timeMax = 5;
    auto lastActivity = std::chrono::steady_clock::now();
    while (listen)
    {
        bool keyPress = false;
        for(char key = 'A'; key <= 'Z'; key++){
            if (GetAsyncKeyState(key))
                {
                     valuesHexBuffer.push_back(static_cast<uint8_t>(key));
                     keyPress = true;
                     while (GetAsyncKeyState(key)) { 
                    Sleep(10);
                }
            } 
        }
        
        if (keyPress) {
            lastActivity = std::chrono::steady_clock::now();
        } 
        else {
            auto timeCurrent = std::chrono::steady_clock::now();
            auto secondsElapsed = std::chrono::duration_cast<std::chrono::seconds>(timeCurrent - lastActivity).count();

            if (secondsElapsed >= timeMax) {
                listen = false;
            }
        }
        
        Sleep(10);
    }

    for (uint8_t byte : valuesHexBuffer) {
        std::cout << "0x" << std::hex << std::uppercase << (int)byte << " ";
    }

    return 0;
    
}