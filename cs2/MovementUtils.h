#ifndef MOVEMENT_UTILS_H
#define MOVEMENT_UTILS_H

#include <Windows.h>
#include "offsets.hpp"  // Assuming this file contains necessary offsets

class MovementUtils {
public:
    MovementUtils(HANDLE hProcess, DWORD clientBaseAddr)
        : hProcess_(hProcess), clientBaseAddr_(clientBaseAddr) {}

    void performBhop(DWORD localPlayerAddr);

private:
    HANDLE hProcess_;
    DWORD clientBaseAddr_;

    void writeMemory(DWORD address, const void* value, SIZE_T size) {
        WriteProcessMemory(hProcess_, reinterpret_cast<LPVOID>(address), value, size, nullptr);
    }
};

#endif // MOVEMENT_UTILS_H
