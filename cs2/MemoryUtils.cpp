#include "MemoryUtils.h"

DWORD MemoryUtils::getLocalPlayer() {
    return readMemory<DWORD>(clientBaseAddr_ + engine2_dll::dwNetworkGameClient_getLocalPlayer);
}

DWORD MemoryUtils::getEntityList() {
	return readMemory<DWORD>(clientBaseAddr_ + client_dll::dwEntityList);
}

/*boolean MemoryUtils::isOnGround() {
	return readMemory<bool>(getLocalPlayer() + client_dll::flag) & (1 << 0);
}*/

// ... Implement other methods similarly
