#include <windows.h>
#include <winsvc.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    SC_HANDLE hSCManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
    if (!hSCManager) return 1;

    DWORD dwBytesNeeded = 0;
    DWORD dwServicesReturned = 0;
    DWORD dwResumeHandle = 0;

    EnumServicesStatusExA(
        hSCManager, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_ACTIVE,
        NULL, 0, &dwBytesNeeded, &dwServicesReturned, &dwResumeHandle, NULL);

    LPENUM_SERVICE_STATUS_PROCESSA pServices = (LPENUM_SERVICE_STATUS_PROCESSA)malloc(dwBytesNeeded);

    if (EnumServicesStatusExA(
        hSCManager, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_ACTIVE,
        (LPBYTE)pServices, dwBytesNeeded, &dwBytesNeeded, &dwServicesReturned, &dwResumeHandle, NULL)) {

        for (DWORD i = 0; i < dwServicesReturned; i++) {
            if (pServices[i].ServiceStatusProcess.dwCurrentState == SERVICE_RUNNING) {
                printf("[PID: %lu] %s (%s)\n",
                    pServices[i].ServiceStatusProcess.dwProcessId,
                    pServices[i].lpServiceName,
                    pServices[i].lpDisplayName);
            }
        }
    }

    free(pServices);
    CloseServiceHandle(hSCManager);
    return 0;
}