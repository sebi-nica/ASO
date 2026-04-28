#include <windows.h>
#include <winsvc.h>
#include <stdio.h>

int main() {
    SC_HANDLE hSCManager;
    DWORD dwBytesNeeded = 0;
    DWORD dwServicesReturned = 0;
    DWORD dwResumeHandle = 0;

    hSCManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
    if (!hSCManager) {
        fprintf(stderr, "Error: Couldn't open SCManager. Code: %lu\n", GetLastError());
        return 1;
    }

    EnumServicesStatusExA(
        hSCManager, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_ACTIVE,
        NULL, 0, &dwBytesNeeded, &dwServicesReturned, &dwResumeHandle, NULL);

    LPENUM_SERVICE_STATUS_PROCESSA pServices = (LPENUM_SERVICE_STATUS_PROCESSA)malloc(dwBytesNeeded);

    if (EnumServicesStatusExA(
        hSCManager, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_ACTIVE,
        (LPBYTE)pServices, dwBytesNeeded, &dwBytesNeeded, &dwServicesReturned, &dwResumeHandle, NULL)) {

        for (DWORD i = 0; i < dwServicesReturned; i++) {
            DWORD dwPid = pServices[i].ServiceStatusProcess.dwProcessId;
            printf("[PID: %lu] %s (%s)\n", dwPid, pServices[i].lpServiceName, pServices[i].lpDisplayName);
        }
    }

    free(pServices);
    CloseServiceHandle(hSCManager);
    return 0;
}