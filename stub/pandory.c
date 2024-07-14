#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <unistd.h>

#ifdef __MINGW32__
#include <windows.h>
#define realpath(N,R) _fullpath((R),(N),_MAX_PATH)
char* fmt = "%s/bin/pandorytool.exe";
#else
#include <limits.h>
char* fmt = "%s/bin/pandorytool";
#endif

int main (int argc, char *argv[])
{
    char path[PATH_MAX];
    if (realpath(argv[0], path) != NULL) {
        char * folder = dirname(path);
        char binaryPath[PATH_MAX];
        snprintf(binaryPath, sizeof(binaryPath), fmt, folder);

#ifdef __MINGW32__
        if (access(binaryPath, F_OK) != -1) {
            // Prepare the command line arguments
            char commandLine[PATH_MAX * 2] = {0};
            snprintf(commandLine, sizeof(commandLine), "\"%s\"", binaryPath);
            for (int i = 1; i < argc; ++i) {
                strcat(commandLine, " ");
                strcat(commandLine, argv[i]);
            }

            // Initialize the STARTUPINFO structure
            STARTUPINFO si;
            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);

            // Initialize the PROCESS_INFORMATION structure
            PROCESS_INFORMATION pi;
            ZeroMemory(&pi, sizeof(pi));

            // Create the new process
            if (CreateProcess(NULL, commandLine, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
                // Wait for the process to complete
                WaitForSingleObject(pi.hProcess, INFINITE);

                // Close process and thread handles
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
                return 0;
            }
        }
#else
        if (access(binaryPath, F_OK) != -1) {
            execvp(binaryPath, argv);
            return 0;
        }
#endif
    } 
    printf("Pandory cannot find all required files. Please reinstall.\n");
    return 0;
}