#include <windows.h>
#include <stdio.h>

int main() {
    HKEY hKeySoftware;
    LONG lResult;
    DWORD dwIndex = 0;
    char szSubkeyName[256];
    DWORD cchNameSize;

    lResult = RegOpenKeyExA(HKEY_CURRENT_USER, "Software", 0, KEY_READ, &hKeySoftware);

    if (lResult != ERROR_SUCCESS) {
        fprintf(stderr, "Error: could not open key. Code: %ld\n", lResult);
        return 1;
    }

    while (1) {
        cchNameSize = sizeof(szSubkeyName);
        lResult = RegEnumKeyExA(hKeySoftware, dwIndex, szSubkeyName, &cchNameSize, NULL, NULL, NULL, NULL);

        if (lResult == ERROR_NO_MORE_ITEMS) {
            break;
        }
        else if (lResult == ERROR_SUCCESS) {
            printf("%s\n", szSubkeyName);
            dwIndex++;
        }
        else {
            fprintf(stderr, "Error: at index %lu\n", dwIndex);
            break;
        }
    }

    RegCloseKey(hKeySoftware);
    return 0;
}