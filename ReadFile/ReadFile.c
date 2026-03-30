#include <stdio.h>
#include <string.h>

#define MAX_PATH 260

int main() {
    char szFilePath[MAX_PATH];
    FILE* pFile = NULL;

    if (fgets(szFilePath, sizeof(szFilePath), stdin) != NULL) {
        szFilePath[strcspn(szFilePath, "\r\n")] = 0;
    }

    if (fopen_s(&pFile, szFilePath, "rb") != 0 || pFile == NULL) {
        fprintf(stderr, "Error: file doesnt exist or cant be opened.\n");
        return 1;
    }

    char arrchBuffer[4096];
    size_t stBytesRead;

    while ((stBytesRead = fread(arrchBuffer, 1, sizeof(arrchBuffer), pFile)) > 0) {
        fwrite(arrchBuffer, 1, stBytesRead, stdout);
    }

    fclose(pFile);
    return 0;
}