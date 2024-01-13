#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include <Windows.h>
#include <string>
#include <stdexcept>
#include "offsets.hpp"  // Assuming this file contains necessary offsets

class MemoryUtils {
public:
    MemoryUtils(HANDLE hProcess, DWORD clientBaseAddr)
        : hProcess_(hProcess), clientBaseAddr_(clientBaseAddr) {
        validateProcessHandle();
    }

    DWORD getLocalPlayer();
    DWORD getEntityList();
    boolean isOnGround();

    // ... other methods for eyepos, location, ammo, jump state, etc.

    template <typename T>
    void writeMemory(DWORD address, const T& value) {
        if (!writeProcessMemory(address, &value, sizeof(T))) {
            throw std::runtime_error("Failed to write memory at address " + std::to_string(address));
        }
    }

private:
    HANDLE hProcess_;
    DWORD clientBaseAddr_;

    void validateProcessHandle() {
        if (hProcess_ == NULL || hProcess_ == INVALID_HANDLE_VALUE) {
            throw std::runtime_error("Invalid process handle.");
        }
    }

    template <typename T>
    T readMemory(DWORD address) {
        T buffer{};
        if (!readProcessMemory(address, &buffer, sizeof(T))) {
            throw std::runtime_error("Failed to read memory at address " + std::to_string(address));
        }
        return buffer;
    }

    bool readProcessMemory(DWORD address, LPVOID buffer, SIZE_T size) {
        SIZE_T bytesRead;
        BOOL result = ReadProcessMemory(hProcess_, reinterpret_cast<LPCVOID>(address), buffer, size, &bytesRead);
        return result && (bytesRead == size);
    }

    bool writeProcessMemory(DWORD address, LPCVOID buffer, SIZE_T size) {
        SIZE_T bytesWritten;
        BOOL result = WriteProcessMemory(hProcess_, reinterpret_cast<LPVOID>(address), buffer, size, &bytesWritten);
        return result && (bytesWritten == size);
    }
};

#endif // MEMORY_UTILS_H
