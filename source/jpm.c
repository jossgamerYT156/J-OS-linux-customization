#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // Check if any arguments were provided
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <apt_command> [args...]\n", argv[0]);
        return 1;
    }

    // Check if the command is for version or help
    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        printf("jpm V-0.0.10\n");
        printf("The J-Custom package manager\n");
        return 0;
    } else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printf("Usage: jpm <command> [args...]\n");
        printf("\n");
        printf("Commands:\n");
        printf("  update            Update package lists\n");
        printf("  upgrade           Upgrade packages\n");
        printf("  install <pkg>     Install package\n");
        printf("  remove <pkg>      Remove package\n");
        printf("  ...               Add more commands as needed\n");
        return 0;
    }

    // Concatenate "apt" with the command name
    char command[1024];
    snprintf(command, sizeof(command), "apt %s", argv[1]);

    // Execute the apt command with provided arguments
    int pid = fork();
    if (pid == 0) {
        // Child process
        execl("/bin/bash", "bash", "-c", command, NULL);
        // If execl fails, print error and exit
        perror("Error executing command");
        exit(1);
    } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        // Check if child process exited normally
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            fprintf(stderr, "Child process terminated abnormally\n");
            return 1;
        }
    } else {
        // Fork failed
        perror("Fork failed");
        return 1;
    }
}
